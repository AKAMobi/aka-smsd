#include "sms.h"
#include "smsdaemon.h"
#include <sys/types.h>
#include <sys/wait.h>

using namespace SMS;

int CSMSDaemon::Run(){

		//��ֹ����δ��ȷ��ʼ��
		assert(m_pSMSProtocol);

		m_pSMSProtocol->Run(m_pSMSStorage);

		return 1;
}


int CSMSDaemon::OnSignalChild(){
	int statloc;
	return wait(&statloc);
}

int CSMSDaemon::OnSignalTerm(){
	syslog(LOG_ERR,"Terminated by SIGTERM(kill)");
	exit(0);
	return 0;
}

CSMSDaemon::~CSMSDaemon(){
		delete m_pSMSProtocol;
		delete m_pSMSStorage;
}
