#ifndef SMS_1A99E4FF_2AF0_45b3_B39A_592D08C9B107
#define SMS_1A99E4FF_2AF0_45b3_B39A_592D08C9B107

#include "sms.h"
#include "mgrep.h"
#include "sys/file.h"

namespace SMS{

class SMS_Storage_error : public std::runtime_error{
public:
	 SMS_Storage_error(const std::string& whatString): std::runtime_error(whatString) {};

};

class CSMSStorage{

	//general class
/*
 * 1������ incoming Ŀ¼�� dnotify
 * 2����� incoming Ŀ¼�������ļ�����ȫ������ CSMSStorage ���ڴ����
 * 3���ṩ�ӿڽ��ڴ�����е� SMS ���ݸ� CSMSDaemon
 * 4����� CSMSDaemon ������ϣ����� CSMSDaemon ���� CSMSStorage ��ɾ���ӿڣ�
 *	ɾ�� queue Ŀ¼�з�����ϵ� SMS �ļ�
 * 5���ṩ�ӿڣ���Ҫ���͵� SMS д�� Storage �� outgoing Ŀ¼
 */
 protected:
	CSMSProtocol	*m_pSMSPProtocol;
	virtual int set_notifier()=0;
	char* m_buffer;
	void* m_filterBuf;

public:
	CSMSStorage(CSMSProtocol *pSMSPProtocol):m_pSMSPProtocol(pSMSPProtocol){
	}

	int init() {
	    int fp;
	    size_t pattern_imagesize;
	    default_setting();
	    fp = open(SMSHOME "etc/badword", O_RDONLY);
	    if (fp==-1) {
			syslog(LOG_ERR,"can't open badword file!");
			return -1;
		}
		flock(fp,LOCK_EX);
		prepf(fp,&m_filterBuf,&pattern_imagesize);

		flock(fp,LOCK_UN);
		close(fp);
		return	set_notifier();
	}
	virtual ~CSMSStorage() {};


	virtual int writeSMStoStorage(const char* sourceNo, const char* TargetNo, char* buf, unsigned int buf_size);

	virtual int readGettedSMS(char* buf, unsigned int* buf_size) = 0;
	
	virtual int getNextSMSFromStorage()=0;

	virtual int getFirstSMSFromStorage()=0;

	virtual int clearStorage()=0;

	virtual int recordSended()=0;

	virtual int backupError()=0;

	int OnNotify();

};


}
#endif

