
	typedef unsigned long int DWORD ;

	#define OAKSID_REQ                                                   0x00000000     // ������Ϣ���ͱ�־
	#define OAKSID_ACK                                                   0x80000000     // Ӧ����Ϣ���ͱ�־
	#define BUFLEN_MOBILENO                                               (15+1)       //�ֻ����볤�� 

	//����,
	//���Ͱ�ͷ����Ϊ
	typedef  struct _tagOAKSREQHeader{
		 DWORD   dwType;                     //��Ϣ����
		 DWORD   dwLength;                   //��Ϣ�峤��(������ͷ��Ϣ)
		 DWORD   dwCheckSum;                 //Ŀǰʼ����0����
	}OAKSREQHEADER,*POAKSREQHEADER; 
	//�շѴ���(FeeID)����Ϊ
	//1                           ���(sp�е�ͨ����)
	//2                           0.20Ԫ
	//4                           1.00Ԫ
	//25                          2.00Ԫ
	//0.5Ԫ�Ĵ������ڴ���

	//���Ͱ��ṹ����
	#define OAKSID_SM_ZIXIASENDTEXT                                      0x00000200     
	typedef struct{
		 OAKSREQHEADER header;                      
		 int  nSerialID;                                  //���к�id,ֱ���ڻظ���ʱ��д��.
		 char szSrcMobileNo[BUFLEN_MOBILENO];             //���ͷ��ֻ�����
		 char szDstMobileNo[BUFLEN_MOBILENO];             //���շ��ֻ�����
		 int  nFeeID;                                     //�շ�id, ���������
		 int  nSendDate;                                  //�������ڣ�=0��ʾ���Ϸ��ͣ��������ڷ��ͣ���ʽYYMMDDHHMI(����YY��MM��DD����Ϊ0��Ϊ0ʱ��ʾÿ�ꡢ�¡���)
		 int  lenText;                                    //��Ϣ���ݳ��ȣ���������Ϣ�����
	}OAKSREQSMZIXIASENDTEXT,*POAKSREQSMZIXIASENDTEXT; 


	//���հ�ͷ����Ϊ
	typedef  struct _tagOAKSHeader{
		 DWORD   dwType;                     //��Ϣ����
		 DWORD   dwLength;                   //��Ϣ�峤��(������ͷ��Ϣ)
		 DWORD   dwResult;                   //�������
	}OAKSACKHEADER,*POAKSACKHEADER; 

	//�ظ����ṹ����
	typedef struct{
		 OAKSACKHEADER header;
		 int  nSerialID;                                //���к�id, �ظ���ʱ����д.
	}OAKSACKSMZIXIASENDTEXT,*POAKSACKSMZIXIASENDTEXT;



	//����ֵ����header�е�dwResult �� ����Ϊ��
	#define		OAKSBIT_SUCCESS								1				//���ͳɹ�
	
	#define     OAKSERR_SM_SOCKET                           410            //������Socket����
	#define     OAKSERR_SM_INVALIDID                        411            //�û��ֻ�������Ч
	#define     OAKSERR_SM_INVALIDSENDNO                    412            //���ͷ��ֻ�������Ч
	#define     OAKSERR_SM_INVALIDRECVNO                    413            //���շ��ֻ�������Ч
	#define     OAKSERR_SM_MSGTOOLENGTH                     417             //������Ϣ������Ϊ�գ���Ч��
	#define     OAKSERR_SM_MOBILESVRERR                     420             //���й��ƶ�����ͨѶʧ��
	#define     OAKSERR_SM_BUSY                             503            //������æ
	#define     OAKSERR_SM_INVALIDMOBILENO                  508            //�ֻ��������
	#define     OAKSERR_SM_PASTDATE                         510            //���ڷ���ʱ���Ѿ�����
	#define     OAKSERR_SM_INVALIDSEND                      525            //�ƶ�����ͨ���ֻ����벻�ܻ��෢��
	#define     OAKSERR_SM_INVALIDMSGID                     526            //����������
	#define     OAKSERR_SM_DISABLEMSGID                     532            //���������ͣ
	 
const char host_18dx[]="61.48.28.121";
const char port_18dx[]="6002";

