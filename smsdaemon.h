#ifndef SMS_H_APP_4C9557A02420417f850745DF202C81A5
#define SMS_H_APP_4C9557A02420417f850745DF202C81A5

#include "app.h"
#include <setjmp.h>

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
	jmp_buf m_jmpBuf;

	
public:
	CSMSDaemon(char* applicationName,int logFacility)
	{
		openlog(applicationName,LOG_PID,logFacility);		
	}

	int IsDaemon() {
		return 1;
	}

	int Run();

	int OnSignalChild();

	int OnSignalTerm();

	virtual ~CSMSDaemon();
	
};



}

#endif
