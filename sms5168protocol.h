#ifndef SMS_51AD2DAD_B486_4391_A641_84C4719FF7DE
#define SMS_51AD2DAD_B486_4391_A641_84C4719FF7DE

#include <cc++/socket.h>
#include <sqlplus.hh>
#include <asm/errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <sstream>
#include "sms.h"
#include "smslogger.h"
#include "time.h"
#ifdef  CCXX_NAMESPACES
using namespace std;
using namespace ost;
#endif

#include "smstcpstream.h"

#define GWIP	"210.51.0.210"
#define GWPASSWORD	8001
#define GWUSER	""
#define GWPASSWD	""

#define WAITTIME	100000 //10��

namespace SMS {

#include "gw5168.h"


class CSMS5168Protocol: public CSMSProtocol{
	CSMSLogger* m_pSMSLogger;
	int m_connected;
	time_t m_lastrcvtime;
	time_t m_lastsendtime;
	unsigned long int m_serial;

unsigned long int getSerial(){ 
        return m_serial++;
}


int convertMsgFormat(struct CDeliver* pSMS,  SMSMessage** msg, unsigned int * msgLen){
	*msgLen=sizeof(SMSMessage)+strlen(pSMS->msg);
	*msg=(SMSMessage*) new char[*msgLen];

	memset(*msg,0,*msgLen);
	(*msg)->length=*msgLen;
	strncpy((*msg)->SenderNumber , pSMS->mobile , MOBILENUMBERLENGTH);
	(*msg)->SenderNumber[MOBILENUMBERLENGTH]=0;
	strncpy((*msg)->TargetNumber , pSMS->dst_num , MOBILENUMBERLENGTH);
	(*msg)->TargetNumber[MOBILENUMBERLENGTH];
	(*msg)->FeeTargetNumber[0]=0;
	(*msg)->SMSBodyLength=strlen(pSMS->msg);
	memcpy((*msg)->SMSBody, pSMS->msg, strlen(pSMS->msg));

	(*msg)->arriveTime=time(NULL);
	strncpy((*msg)->parentID,"5168",SMS_MAXCHILDCODE_LEN);
	(*msg)->parentID[SMS_PARENTID_LEN]=0;
	(*msg)->FeeType=0;

	return 0;
}



int process(struct CResp * pResp, CSMSStorage* pSMSStorage){
	syslog(LOG_ERR," recieve gw msg type: %d",pResp->head.dwCmdID);

	switch (pResp->head.dwCmdID)  {
	case SUBMITRESP:	//���Ͷ��ŵ����ػ�Ӧ
		if (pResp->sr.result==0) {
			syslog(LOG_ERR," msg %d ���ͳɹ���",pResp->sr.msg_id1);
		} else {
			syslog(LOG_ERR," msg %d ����ʧ��: 0x%u��",pResp->sr.msg_id1,pResp->sr.result);
		}
		break;
	case DELIVERY:		//�յ�����deliver����
		SMSMessage* formatedMsg;
		unsigned int msgLen;
		if (!convertMsgFormat(&(pResp->dl), &formatedMsg,&msgLen)){
			pSMSStorage->writeSMStoStorage(formatedMsg->SenderNumber,formatedMsg->TargetNumber,(char *)formatedMsg,msgLen);
			delete formatedMsg;
		} else {
			return -1;
		}
		break;
	case ALIVERESP: //keep alive
	default:
		break;
	}
	return 0;
}
public:
	CSMS5168Protocol() {
		m_pSMSLogger=NULL;
		m_connected=0;
		m_serial=0;
	}

	/* {{{ Run(CSMSStorage* pSMSStorage) */
	int Run(CSMSStorage* pSMSStorage){
		int retCode;
		struct CResp msg;
		time_t now;
		m_pSMSLogger=new CSMSLogger;
		pSMSStorage->init();
		for(;;) {
			m_connected=0;
			for(;;) {
				if ((retCode=apiLogin(GWIP,GWPASSWORD,GWUSER,GWPASSWD))!=0) {
					syslog(LOG_ERR,"apiLogin error: %d",retCode);

				} else {
					retCode=apiRecv(&msg,WAITTIME);
					if (retCode==0) {
						int loginResult=(msg.lr.result & 0x1111);
						if (msg.lr.result==0) { //��¼�ɹ���
							m_connected=1;
							break;
						} else {
							if (msg.lr.result & 0x1) {
								syslog(LOG_ERR,"apiLogin failed: user/passwd error!");
							}
							if (msg.lr.result & 0x10) {
								syslog(LOG_ERR,"apiLogin failed: ip error!");
							}
							syslog(LOG_ERR,"apiLogin failed. result: 0x%u", msg.lr.result);
						}
					} else {
						syslog(LOG_ERR,"login -- apiRecv failed: %d", retCode);
					}
				}
				apiStop();
				sleep(10);
			}
			time(&m_lastrcvtime);
			time(&m_lastsendtime);
			pSMSStorage->OnNotify();
			while (retCode=apiRecv(&msg,WAITTIME)) {
				/* retcode:
				0�����ú����ɹ�
				1:  �������ݰ�ʧ��
				2:  ��ʱ
				3:  �Ⱥ����ݰ�ʧ��
				4:  ����Ͽ�
				*/
				if (retCode==0) {
					time(&m_lastrcvtime);
					process(&msg,pSMSStorage);
					continue;
				}
				switch(retCode) {
				case 1:
				case 4:
					m_connected=0;
					break;
				}
				time(&now);
				if (now-m_lastsendtime) {
					if (apiActive()!=0) {
						m_connected=0;
						break;
					}
				}
				time(&m_lastsendtime);
				if (now-m_lastrcvtime>3*WAITTIME) {
					m_connected=0;
					break;
				}
			}			

		}
		return 0;
	}
	/* }}} */

	
	/* {{{ Send(SMSMessage* msg) */
	int Send(SMSMessage* msg){
		if (m_connected==0) {
			return FAILED;
		}
		sigset_t sigmask, oldmask;

		sigemptyset(&sigmask);
		sigaddset(&sigmask,SIGUSR1);
		sigprocmask(SIG_BLOCK,&sigmask,&oldmask);

		int retCode;
		char buf[160];
		int len;
/*
apiSend(  DWORD msg_id1,DWORD	msg_id2,	char mobile[21],char 	service_id[10],char		 src_term[21],	char		 fee_term[21],	char msg[160],char 	udhi,BYTE 		pid,	BYTE	 isReply,	WORD 	msg_len,	BYTE msg_fmt);
  

  ����˵��:
msg_id1:   �û���Ϣid��
msg_id2:   ��������=0
mobile[21]:   ���պ���
           service_id:   �������. ����-lsxz
      	 src_term[21]:   ����Դ����(�ڽ����ֻ�����ʾ�ķ����ߺ���)���� '51687001' 
         fee_term[21]:   �ƷѺ���(Ϊ�ֻ�����,�����ĸ��ֻ����շ�)
           msg[160]:   ������Ϣ
udhi:   ͷ��ʾ(����Ϊ������ʱ���������壬�ı���Ϣ��0)
pid:    Э��ID(����Ϊ������ʱ���������壬�ı���Ϣ��0)
isReply:   �Ƿ���Ҫ״̬���棬ĿǰAPI����1��������Ҫ״̬���档
msg_len:  ������Ϣ����
msg_fmt:   ��Ϣ���� ��0��ASCII��  3������д������  4��������
 8��UCS2����15����GB���֣�
*/     
		len=msg->SMSBodyLength;
		if (len>159) 
			len=159;
		memcpy(buf,msg->SMSBody,len);
		buf[len]=0;
		retCode= apiSend(getSerial(),  0,msg->TargetNumber,msg->serviceCode,msg->SenderNumber,msg->FeeTargetNumber, buf,0,0,1,len,15);
		syslog(LOG_ERR,"send msg to 5618....");
				      
		if (retCode==0) {
			m_pSMSLogger->logIt(msg->SenderNumber, msg->TargetNumber,msg->FeeTargetNumber,msg->FeeType,msg->childCode,"58181888" ,msg->sendTime,time(NULL),msg->arriveTime,msg->SMSBody,msg->SMSBodyLength);
		} else {
			sigprocmask(SIG_SETMASK, &oldmask, NULL);
			return FAILED;
		}
		sigprocmask(SIG_SETMASK, &oldmask, NULL);
		return SUCCESS;

	}
	/* }}} */

	~CSMS5168Protocol() {
		delete m_pSMSLogger;
	}
};

}

#endif
