#ifndef AKA_SMS_6D37B40E_AE4A_47B2_8757_91FF70855638
#define AKA_SMS_6D37B40E_AE4A_47B2_8757_91FF70855638

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef uint32_t UINT32;
typedef uint64_t UINT64;
typedef	uint8_t	 UINT8;
typedef char	OCTETSTRING;

//COMMAND_ID����
#define CMPP_CMD_CONNECT			0x00000001	//��������
#define CMPP_CMD_CONNECT_RESP		0x80000001	//��������Ӧ��
#define CMPP_CMD_TERMINATE			0x00000002	//��ֹ����
#define CMPP_CMD_TERMINATE_RESP		0x80000002	//��ֹ����Ӧ��
#define CMPP_CMD_SUBMIT				0x00000004	//�ύ����
#define CMPP_CMD_SUBMIT_RESP		0x80000004	//�ύ����Ӧ��
#define CMPP_CMD_DELIVER			0x00000005	//�����·�
#define CMPP_CMD_DELIVER_RESP		0x80000005	//�·�����Ӧ��
#define CMPP_CMD_QUERY				0x00000006	//���Ͷ���״̬��ѯ
#define CMPP_CMD_QUERY_RESP			0x80000006	//���Ͷ���״̬��ѯӦ��
#define CMPP_CMD_CANCEL				0x00000007	//ɾ������
#define CMPP_CMD_CANCEL_RESP		0x80000007	//ɾ������Ӧ��
#define CMPP_CMD_ACTIVE_TEST		0x00000008	//�������
#define CMPP_CMD_ACTIVE_TEST_RESP	0x80000008	//�������Ӧ��

//�˿ں�
#define CMPP_LONGCONNECTION_PORT	7890	//�����ӣ�SP�����ؼ䣩
#define CMPP_SHORTCONNECTION_PORT	7900	//�����ӣ�SP�����ؼ������֮�䣩

// ��Ϣͷ(������Ϣ������ͷ)
typedef struct _CMPP_HEADER{
	UINT32 Total_Length;	//��Ϣ�ܳ���(����Ϣͷ����Ϣ��)
	UINT32 Command_Id;	//�������Ӧ����
	UINT32 Sequence_Id;	//��Ϣ��ˮ��,˳���ۼ�,����Ϊ1,ѭ��ʹ�ã�һ�������Ӧ����Ϣ����ˮ�ű�����ͬ��
}CMPP_HEADER, *PCMPP_HEADER;

//SP�������ӵ�ISMG��CMPP_CONNECT������ (SP-> ISMG)
typedef struct _CMPP_CONNECT{
	OCTETSTRING Source_Addr[6]; //Դ��ַ���˴�ΪSP_Id����SP����ҵ����
	OCTETSTRING AuthenticatorSource[16]; /*	Octet String	���ڼ���Դ��ַ����ֵͨ������MD5 hash����ó�����ʾ���£�
		AuthenticatorSource =
		MD5��Source_Addr+9 �ֽڵ�0 +shared secret+timestamp��
		Shared secret ���й��ƶ���Դ��ַʵ�������̶���timestamp��ʽΪ��MMDDHHMMSS��������ʱ���룬10λ��
		*/
	UINT8 Version;	//1	Unsigned Integer	˫��Э�̵İ汾��(��λ4bit��ʾ���汾��,��λ4bit��ʾ�ΰ汾��)
	UINT32  Timestamp;	//4	Unsigned Integer	ʱ���������,�ɿͻ��˲���,��ʽΪMMDDHHMMSS��������ʱ���룬10λ(ʮ���ƣ����ֵ����ͣ��Ҷ��� ��

}CMPP_CONNECT, *PCMPP_CONNECT;


//CMPP_CONNECT_RESP��Ϣ���壨ISMG -> SP��
typedef struct _CMPP_CONNECT_RESP{
	UINT8 Status; //	״̬
/*
0����ȷ
1����Ϣ�ṹ��
 2���Ƿ�Դ��ַ
 3����֤��
 4���汾̫��
  5~ ����������
*/
	OCTETSTRING AuthenticatorISMG[16]; //	Octet String	ISMG��֤�룬���ڼ���ISMG��
/*
��ֵͨ������MD5 hash����ó�����ʾ���£�
AuthenticatorISMG =MD5��Status+AuthenticatorSource+shared secret����Shared secret ���й��ƶ���Դ��ַʵ�������̶���AuthenticatorSourceΪԴ��ַʵ�巢�͸�ISMG�Ķ�Ӧ��ϢCMPP_Connect�е�ֵ��
 ��֤����ʱ������Ϊ�ա�
*/
	UINT8 Version; //	1	Unsigned Integer	������֧�ֵ���߰汾��

}CMPP_CONNECT_RESP, *PCMPP_CONNECT_RESP;

/*
CMPP_TERMINATE��Ϣ���壨SP -> ISMG��ISMG -> SP��
����Ϣ�塣
CMPP_TERMINATE_RESP��Ϣ���壨SP -> ISMG��ISMG -> SP��
����Ϣ�塣
*/

//SP��ISMG�ύ���ţ�CMPP_SUBMIT������ (SP->ISMG)
typedef struct _CMPP_SUBMIT_PART1 {
	UINT64 Msg_Id;		//	8	Unsigned Integer	��Ϣ��ʶ����SP��������ر��������������ա�
	UINT8 Pk_total;	//1	Unsigned Integer	��ͬMsg_Id����Ϣ����������1��ʼ
	UINT8 Pk_number;	//1	Unsigned Integer	��ͬMsg_Id����Ϣ��ţ���1��ʼ
	UINT8 Registered_Delivery;	//1	Unsigned Integer	�Ƿ�Ҫ�󷵻�״̬ȷ�ϱ��棺
/*
0������Ҫ
1����Ҫ
2������SMC����
 �������Ͷ��Ž������ؼƷ�ʹ�ã������͸�Ŀ���ն�)
*/
	UINT8 Msg_level;	//1	Unsigned Integer	��Ϣ����
	OCTETSTRING Service_Id[10]; //	Octet String	ҵ�����ͣ������֡���ĸ�ͷ��ŵ���ϡ�
	UINT8 Fee_UserType; //	1	Unsigned Integer	�Ʒ��û������ֶ�
/*
0����Ŀ���ն�MSISDN�Ʒѣ�
1����Դ�ն�MSISDN�Ʒѣ�
2����SP�Ʒ�;
3����ʾ���ֶ���Ч����˭�ƷѲμ�Fee_terminal_Id�ֶΡ�
*/
	OCTETSTRING Fee_terminal_Id[21];	//Unsigned Integer	���Ʒ��û��ĺ��루�籾�ֽ���գ����ʾ���ֶ���Ч����˭�ƷѲμ�Fee_UserType�ֶΣ����ֶ���Fee_UserType�ֶλ��⣩
	UINT8 TP_pId; //	1	Unsigned Integer	GSMЭ�����͡���ϸ�ǽ�����ο�GSM03.40�е�9.2.3.9
	UINT8 TP_udhi; //	1	Unsigned Integer	GSMЭ�����͡���ϸ�ǽ�����ο�GSM03.40�е�9.2.3.23,��ʹ��1λ���Ҷ���
	UINT8 Msg_Fmt; //	1	Unsigned Integer	��Ϣ��ʽ
/*
  0��ASCII��
  3������д������
  4����������Ϣ
  8��UCS2����
15����GB����  ������������ 
*/
	OCTETSTRING Msg_src[6];	//	Octet String	��Ϣ������Դ(SP_Id)
	OCTETSTRING FeeType[2];	//Octet String	�ʷ����
/*
01����"�Ʒ��û�����"���
02����"�Ʒ��û�����"��������Ϣ��
03����"�Ʒ��û�����"��������ȡ��Ϣ��
04����"�Ʒ��û�����"����Ϣ�ѷⶥ
05����"�Ʒ��û�����"���շ�����SPʵ��
*/
	OCTETSTRING FeeCode[6]; //	Octet String	�ʷѴ��루�Է�Ϊ��λ��
	OCTETSTRING ValId_Time[17]; //	Octet String	�����Ч�ڣ���ʽ��ѭSMPP3.3Э��
	OCTETSTRING At_Time[17]; //	Octet String	��ʱ����ʱ�䣬��ʽ��ѭSMPP3.3Э��
	OCTETSTRING Src_Id[21]; 	//Octet String	Դ����
/*
SP�ķ�������ǰ׺Ϊ�������ĳ�����, ���ؽ��ú����������SMPPЭ��Submit_SM��Ϣ��Ӧ��source_addr�ֶΣ��ú����������û��ֻ�����ʾΪ����Ϣ�����к���
*/
}CMPP_SUBMIT_PART1, *PCMPP_SUBMIT_PART1;

typedef struct _CMPP_SUBMIT_PART2 {
	UINT8 DestUsr_tl;//	1	Unsigned Integer	������Ϣ���û�����(С��100���û�)
}CMPP_SUBMIT_PART2, *PCMPP_SUBMIT_PART2;

typedef struct _CMPP_SUBMIT_PART3 {
	OCTETSTRING Dest_terminal_Id[0][21]; //	21*DestUsr_tl	Octet String	���ն��ŵ�MSISDN����
}CMPP_SUBMIT_PART3, *PCMPP_SUBMIT_PART3;

typedef struct _CMPP_SUBMIT_PART4 {
	UINT8 Msg_Length;	//1	Unsigned Integer	��Ϣ����(Msg_FmtֵΪ0ʱ��<160���ֽڣ�����<=140���ֽ�)
}CMPP_SUBMIT_PART4, *PCMPP_SUBMIT_PART4;

typedef struct _CMPP_SUBMIT_PART5 {
	OCTETSTRING Msg_Content[0];//	Msg_length	Octet String	��Ϣ����
}CMPP_SUBMIT_PART5, *PCMPP_SUBMIT_PART5;

typedef struct _CMPP_SUBMIT_PART6 {
	OCTETSTRING Reserve[8]; //	8	Octet String	����
}CMPP_SUBMIT_PART6, *PCMPP_SUBMIT_PART6;

//CMPP_SUBMIT_RESP��Ϣ���壨ISMG -> SP��
typedef struct _CMPP_SUBMIT_RESP {
	UINT64 Msg_Id;//	8	Unsigned Integer	��Ϣ��ʶ�������㷨���£�
/*
����64λ��8�ֽڣ���������
��1��	ʱ�䣨��ʽΪMMDDHHMMSS��������ʱ���룩��bit64~bit39������
bit64~bit61���·ݵĶ����Ʊ�ʾ��
bit60~bit56���յĶ����Ʊ�ʾ��
bit55~bit51��Сʱ�Ķ����Ʊ�ʾ��
bit50~bit45���ֵĶ����Ʊ�ʾ��
bit44~bit39����Ķ����Ʊ�ʾ��
��2��	�������ش��룺bit38~bit17���Ѷ������صĴ���ת��Ϊ������д�����ֶ��С�
��3��	���кţ�bit16~bit1��˳�����ӣ�����Ϊ1��ѭ��ʹ�á�
�������粻�����������㣬�Ҷ��롣
��SP���������Ӧ����Ϣ��Sequence_Idһ���ԾͿɵõ�CMPP_Submit��Ϣ��Msg_Id��
*/
	UINT8 Result;  //	1	Unsigned Integer	���
/*
0����ȷ
1����Ϣ�ṹ��
 2�������ִ�
 3����Ϣ����ظ�
4����Ϣ���ȴ�
5���ʷѴ����
6�����������Ϣ��
7��ҵ������
8���������ƴ�
9~ ����������
*/
}CMPP_SUBMIT_RESP , *PCMPP_SUBMIT_RESP;

//SP��ISMG��ѯ���Ͷ���״̬��CMPP_QUERY������
typedef struct _CMPP_QUERY{
	OCTETSTRING Time[8];//	8	Octet String	ʱ��YYYYMMDD(��ȷ����)
	UINT8 Query_Type;//	1	Unsigned Integer	��ѯ���
/*
0��������ѯ
1����ҵ�����Ͳ�ѯ 
*/
	OCTETSTRING Query_Code[10]; //	10	Octet String	��ѯ��
/*
��Query_TypeΪ0ʱ��������Ч����Query_TypeΪ1ʱ��������дҵ������Service_Id. 
*/
	OCTETSTRING Reserve[8]; //	8	Octet String	����
}CMPP_QUERY, *PCMPP_QUERY;

//CMPP_QUERY_RESP��Ϣ�Ķ��壨ISMG -> SP��
typedef struct _CMPP_QUERY_RESP{
	UINT8 Query_Type; //	1	Unsigned Integer	��ѯ���
/*
0��������ѯ
1����ҵ�����Ͳ�ѯ 
*/
	OCTETSTRING Query_Code[10]; //	10	Octet String	��ѯ��
	UINT32 MT_TLMsg; //	4	Unsigned Integer	��SP������Ϣ����
	UINT32 MT_Tlusr; //	4	Unsigned Integer	��SP�����û�����
	UINT32 MT_Scs; //	4	Unsigned Integer	�ɹ�ת������
	UINT32 MT_WT; //	4	Unsigned Integer	��ת������
	UINT32 MT_FL; //	4	Unsigned Integer	ת��ʧ������
	UINT32 MO_Scs; //	4	Unsigned Integer	��SP�ɹ��ʹ�����
	UINT32 MO_WT; //	4	Unsigned Integer	��SP���ʹ�����
	UINT32 MO_FL; //	4	Unsigned Integer	��SP�ʹ�ʧ������
}CMPP_QUERY_RESP, *PCMPP_QUERY_RESP;

//ISMG��SP�ͽ����ţ�CMPP_DELIVER������
typedef struct _CMPP_DELIVER_PART1{
	UINT64 Msg_Id; //	8	Unsigned Integer	��Ϣ��ʶ
/*
�����㷨���£�
����64λ��8�ֽڣ���������
��1��	ʱ�䣨��ʽΪMMDDHHMMSS��������ʱ���룩��bit64~bit39������
bit64~bit61���·ݵĶ����Ʊ�ʾ��
bit60~bit56���յĶ����Ʊ�ʾ��
bit55~bit51��Сʱ�Ķ����Ʊ�ʾ��
bit50~bit45���ֵĶ����Ʊ�ʾ��
bit44~bit39����Ķ����Ʊ�ʾ��
��2��	�������ش��룺bit38~bit17���Ѷ������صĴ���ת��Ϊ������д�����ֶ��С�
��3��	���кţ�bit16~bit1��˳�����ӣ�����Ϊ1��ѭ��ʹ�á�
�������粻�����������㣬�Ҷ��롣
*/
	OCTETSTRING Dest_Id[21]; //	21	Octet String	Ŀ�ĺ��� 

/*
SP�ķ�����룬һ��4--6λ��������ǰ׺Ϊ�������ĳ����룻�ú������ֻ��û�����Ϣ�ı��к��롣
*/
	OCTETSTRING Service_Id[10]; //	10	Octet String	ҵ�����ͣ������֡���ĸ�ͷ��ŵ���ϡ�
	UINT8 TP_pid; //	1	Unsigned Integer	GSMЭ�����͡���ϸ������ο�GSM03.40�е�9.2.3.9
	UINT8 TP_udhi; //	1	Unsigned Integer	GSMЭ�����͡���ϸ������ο�GSM03.40�е�9.2.3.23����ʹ��1λ���Ҷ���
	UINT8 Msg_Fmt; //	1	Unsigned Integer	��Ϣ��ʽ
/*
  0��ASCII��
  3������д������
  4����������Ϣ
  8��UCS2����
15����GB����   
*/
	OCTETSTRING Src_terminal_Id[21]; //	21	Octet String	Դ�ն�MSISDN���루״̬����ʱ��ΪCMPP_SUBMIT��Ϣ��Ŀ���ն˺��룩
	UINT8 Registered_Delivery; //	1	Unsigned Integer	�Ƿ�Ϊ״̬����
/*
0����״̬����
1��״̬����
*/
	UINT8 Msg_Length; //	1	Unsigned Integer	��Ϣ����
	OCTETSTRING Msg_Content[0]; //	Msg_length	Octet String	��Ϣ����
}CMPP_DELIVER_PART1, *PCMPP_DELIVER_PART1;

typedef struct CMPP_DELIVER_PART2 {
	OCTETSTRING Reserved[8]; //	8	Octet String	������
}CMPP_DELIVER_PART2, *PCMPP_DELIVER_PART2;

//״̬�������ݶ��壺
typedef struct _CMPP_STATSREPORT{
	UINT64 Msg_Id; //	8	Unsigned Integer	��Ϣ��ʶ
/*
	SP�ύ���ţ�CMPP_SUBMIT������ʱ����SP������ISMG������Msg_Id��
*/
	OCTETSTRING Stat[7]; //	7	Octet String	���Ͷ��ŵ�Ӧ������������SMPPЭ��Ҫ����stat�ֶζ�����ͬ�������һ��SP���ݸ��ֶ�ȷ��CMPP_SUBMIT��Ϣ�Ĵ���״̬��
	OCTETSTRING Submit_time[10]; //	10	Octet String	YYMMDDHHMM��YYΪ��ĺ���λ00-99��MM��01-12��DD��01-31��HH��00-23��MM��00-59��
	OCTETSTRING Done_time[10]; //	10	Octet String	YYMMDDHHMM
	OCTETSTRING Dest_terminal_Id[21]; //	21	Octet String	Ŀ���ն�MSISDN����(SP����CMPP_SUBMIT��Ϣ��Ŀ���ն�)
	UINT32 SMSC_sequence;//	4	Unsigned Integer	ȡ��SMSC����״̬�������Ϣ���е���Ϣ��ʶ��
}CMPP_STATSREPORT, *PCMPP_STATSREPORT;

//CMPP_DELIVER_RESP��Ϣ���壨SP -> ISMG��
typedef struct _CMPP_DELIVER_RESP {
	UINT64 Msg_Id; //	8	Unsigned Integer	��Ϣ��ʶ
/*
��CMPP_DELIVER�е�Msg_Id�ֶΣ�
*/
	UINT8 Result; //	1	Unsigned Integer	���
/*
0����ȷ
1����Ϣ�ṹ��
 2�������ִ�
 3����Ϣ����ظ�
4����Ϣ���ȴ�
5���ʷѴ����
6�����������Ϣ��
7��ҵ������
8: �������ƴ�
9~ ����������
*/
} CMPP_DELIVER_RESP, *PCMPP_DELIVER_RESP;

//SP��ISMG����ɾ�����ţ�CMPP_CANCEL������
typedef struct _CMPP_CANCEL {
	UINT64 Msg_Id; //	8	Unsigned Integer	��Ϣ��ʶ��SP��Ҫɾ������Ϣ��ʶ��
}CMPP_CANCEL , *PCMPP_CANCEL;

//CMPP_CANCEL_RESP��Ϣ���壨ISMG ' SP��
typedef struct _CMPP_CANCEL_RESP{
	UINT8 Success_Id; //	1	Unsigned Integer	�ɹ���ʶ
/*
0���ɹ�
1��ʧ��
*/
}CMPP_CANCEL_RESP, *PCMPP_CANCEL_RESP;

// CMPP_ACTIVE_TEST_RESP���壨SP -> ISMG��ISMG -> SP��
typedef struct _CMPP_ACTIVE_TEST_RESP{
	UINT8 Reserved;
}CMPP_ACTIVE_TEST_RESP, *PCMPP_ACTIVE_TEST_RESP;

#ifdef __cplusplus
}
#endif
#endif
