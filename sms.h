#ifndef FDA51240_4423_4793_BF0A_29227CA73204
#define FDA51240_4423_4793_BF0A_29227CA73204

#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <syslog.h>
#include <signal.h>
#include <cassert>
#include <string>
#include <exception>
#include <stdexcept>



namespace SMS{

#define MOBILENUMBERLENGTH 16  //���볤��
#define FEETYPE_DEFAULT 1;
#define SMSTYPE_TEXT	1;


class CSMSProtocol;
class CSMSStorage;
class CSMSDaemon;

struct SMSMessage{
	unsigned int length;
	char SenderNumber[MOBILENUMBERLENGTH];
	char TargetNumber[MOBILENUMBERLENGTH];
	int FeeType;
	char FeeTargetNumber[MOBILENUMBERLENGTH];
	int SMSType;
	unsigned int SMSBodyLength;
	char SMSBody[0];
};



}


#include "smsdaemon.h"
#include "smsstorage.h"
#include "smsprotocol.h"

#endif
