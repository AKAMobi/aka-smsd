#ifndef SMS_A6CC8CFE_F731_4b1d_9373_9F0A880D48B2
#define SMS_A6CC8CFE_F731_4b1d_9373_9F0A880D48B2
/*   ������ͨѶЭ�鶨�� */

namespace SMS {

#define FEETYPE_1 1

//�������ͳ�������

#define testport "4000"

//��Ϣ���ͳ�������
#define MSGTYPE_SM		0
#define MSGTYPE_SMR		1
#define MSGTYPE_SMS		2
#define MSGTYPE_RM		3
#define MSGTYPE_CD		4
#define MSGTYPE_CDR		5
#define MSGTYPE_PWD		10    //��֤��������

#define CONNECTION_USER_LEN		20
#define CONNECTION_PASSWORD_LEN 50



typedef struct _SMSChildProtocolHead{
	byte msgTypeID;	//��Ϣ����
	byte SMSSerialNo[4];		//����Ϣ�������������ɵ���Ϣ���кţ���λ��ǰ
	byte msgLength[4]; //������ͷ��Ϣ����Ϣ�峤�ȣ��ֽ�������λ��ǰ����λ�ں�
	byte unused[4];	//������������checksum
} SMSChildProtocolHead, *PSMSChildProtocolHead;

typedef struct _SMSChildProtocolCommon { //���ڴ�����Ϣͷ�Ľṹ
	SMSChildProtocolHead head;		//ͷ��Ϣ	
} SMSChildProtocolCommon, *PSMSChildProtocolCommon;


typedef struct _SMSChildProtocolSendMessage { //�������صķ��Ͷ�����Ϣ
	SMSChildProtocolHead head;		//ͷ��Ϣ
	char senderNo[MOBILENUMBERLENGTH+1];  //���ŵķ��ͷ�����
	char targetNo[MOBILENUMBERLENGTH+1];	//���ŵĽ��շ�����
	char feeTargetNo[MOBILENUMBERLENGTH+1];		//���ζ��żƷѵĶ������
	byte feeTypeID;				//		�շ����ʹ���
	byte smsTypeID;				//		��������
	byte smsBodyLength[4];		//�������ݳ��ȣ��ֽڣ� ��λ��ǰ����λ�ں�
	char smsBody[0];		//��������
}SMSChildProtocolSendMessage, *PSMSChildProtocolSendMessage; 

#define MSG_OK					0
#define MSGERR_SENDERNO			11
#define MSGERR_TARGETNO			12
#define MSGERR_FEETARGETNO		21
#define MSGERR_FEETYPE			22
#define MSGERR_SMSTYPE			31
#define MSGERR_SMSLEN			41
#define MSGERR_MSGTYPE			51

typedef struct _SMSChildProtocolSendMessgeReceived{ //�������ؽ��ܵ����Ͷ�����Ϣ֮��ķ���
	SMSChildProtocolHead head;		//ͷ��Ϣ
	byte SerialNo[4];			//�ɱ����������ɵ���Ϣ���кţ���λ��ǰ
	byte ErrorNo;			 //�Է��Ͷ�����Ϣ����validate֮��Ľ��
} SMSChildProtocolSendMessgeReceived, *PSMSChildProtocolSendMessgeReceived;

#define SEND_OK					0

typedef struct _SMSChildProtocolSendMessageSended{ //�������سɹ����Ͷ�����Ϣ֮��ķ���
	SMSChildProtocolHead head;		//ͷ��Ϣ
	byte SerialNo[4];			//�ɱ����������ɵ���Ϣ���кţ���λ��ǰ
	byte ErrorNo;			 //���ͽ��
}SMSChildProtocolSendMessageSended, *PSMSChildProtocolSendMessageSended;

typedef struct _SMSChildProtocolReceivedMessage{ //��������ת�������εĶ���
	SMSChildProtocolHead head;		//ͷ��Ϣ
	char senderNo[MOBILENUMBERLENGTH+1];  //���ŵķ��ͷ�����
	char targetNo[MOBILENUMBERLENGTH+1];	//���ŵĽ��շ�����
	byte smsTypeID;				//		��������
	byte smsLength[4];		//�������ݳ��ȣ��ֽڣ� ��λ��ǰ����λ�ں�
	char smsBody[0];		//��������
}SMSChildProtocolReceivedMessage, *PSMSChildProtocolReceivedMessage;

typedef struct _SMSChildProtocolConnectionDetect{ //�������ض����ν���״̬���
	SMSChildProtocolHead head;		//ͷ��Ϣ
	byte SerialNo[4];			//�ɱ����������ɵ���Ϣ���кţ���λ��ǰ
}	SMSChildProtocolConnectionDetect, *PSMSChildProtocolConnectionDetect;

typedef struct _SMSChildProtocolReply{ //���ζԱ�������״̬���Ļظ�
	SMSChildProtocolHead head;		//ͷ��Ϣ
	byte SerialNo[4];			//�ɱ����������ɵ���Ϣ���кţ���λ��ǰ
}	SMSChildProtocolReply, *PSMSChildProtocolReply;

typedef struct _SMSChildProtocolPassword{ //��֤�����û���������
	SMSChildProtocolHead head;		//ͷ��Ϣ
	char user[CONNECTION_USER_LEN];			
	char password[CONNECTION_PASSWORD_LEN];
}	SMSChildProtocolPassword, *PSMSChildProtocolPassword;

inline unsigned long int sms_byteToLong(byte arg[4]) {
	long tmp;
	tmp=(arg[0]<<24)+(arg[1]<<16)+(arg[2]<<8)+arg[3];
	return tmp;
}

inline void sms_longToByte(byte* arg, unsigned long int num) {
	(arg)[0]=num>>24;
	(arg)[1]=(num<<8)>>24;
	(arg)[2]=(num<<16)>>24;
	(arg)[3]=(num<<24)>>24;
}

}

#endif
