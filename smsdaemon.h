#ifndef SMS_H_APP_4C9557A02420417f850745DF202C81A5
#define SMS_H_APP_4C9557A02420417f850745DF202C81A5

#include "app.h"

namespace SMS{

class CSMSDaemon: public RCL::CApplication{
/*
 * 1�����캯������ CSMSPProtocol������
 * 2������ʱ���� CSMSStorage ������
 * 3������ʱ���� CSMSPrivilige ������
 * 4������ Daemon ��ʼ��
 * 5��ʹ�� CSMSPProtocol ���� Listen
 * 6��accept ��ʹ�� CSMSPrivilige ������֤
 * 7�� fork �ӽ��̣����������ͨ����֤�����ӣ���ɱ���ӽ���
 * 8��ʹ�� CStorage ���� dnotify incoming Ŀ¼
 * 9�������� read socket ��
 * 10������� incoming �ļ������ CSMSStorage ���� CSMSDaemon �ķ��ͺ���
 */
 
protected:
	CSMSProtocol	*m_pSMSProtocol;
	CSMSStorage *m_pSMSStorage;

	
public:
	CSMSDaemon(char* applicationName,int logFacility)
	{
		openlog(applicationName,LOG_PID,logFacility);		
	}

	int IsDaemon() {
		return 1;
	}

/*
	int ProcessChild(){

		m_pSMSStorage->Init(this); //��ʼ���������жϴ�����

		SMSMessage* pSMS;

		while (m_SMSPProtocol->Receive(pSMS))
		{
			try{
			// to do: �ж���ϢȨ�� 
			m_pSMSStorage->writeSMStoStorage(pSMS->SenderNumber,pSMS->TargetNumber,reinterrupt_cast<char*>(pSMS),pSMS->length); /// ������Ϣ���洢�����ӿ���ϸ��
			} catch ( exception e){
				syslog(LOG_ERR,"storage error: " , e.what());
			}
			delete pSMS;
		}
		return 0;
	}
*/
	int Run();

	int OnSignalChild();

	int OnSignalTerm();

	virtual ~CSMSDaemon();
	
};



}

#endif
