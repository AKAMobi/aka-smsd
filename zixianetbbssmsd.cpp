#include "smsbbschildprotocol.h"
#include "smsdiskstorage.h"

using namespace SMS;
using namespace std;

class CMyDaemon: public CSMSDaemon{
public:
	

	CMyDaemon(char* applicationName,int logFacility): CSMSDaemon(applicationName,logFacility){
		m_pSMSProtocol=new CSMSBBSChildProtocol("13","zixiabbs","202.205.10.10",4003);
		m_pSMSStorage = new CSMSDiskStorage(m_pSMSProtocol,"/home/roy/gateway/in","/home/roy/gateway/zixiabbsgo");
	}
};

CMyDaemon myDaemon("zixia.net.bbschild",LOG_LOCAL0);
