#ifndef SMS_1A99E4FF_2AF0_45b3_B39A_592D08C9B107
#define SMS_1A99E4FF_2AF0_45b3_B39A_592D08C9B107

#include "sms.h"

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

public:
	CSMSStorage(CSMSProtocol *pSMSPProtocol):m_pSMSPProtocol(pSMSPProtocol){
	}

	int init() {
				
	return	set_notifier();
	}
	virtual ~CSMSStorage() {};


	virtual int writeSMStoStorage(const char* sourceNo, const char* TargetNo, char* buf, unsigned int buf_size)=0;

	virtual int readGettedSMS(char* buf, unsigned int* buf_size) = 0;
	
	virtual int getNextSMSFromStorage()=0;

	virtual int getFirstSMSFromStorage()=0;

	virtual int clearStorage()=0;

	int OnNotify();

};


}
#endif

