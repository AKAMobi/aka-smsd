#ifndef MOBILENUMBERLENGTH
#define MOBILENUMBERLENGTH 16  //���볤��
#endif
#define OAKSID_SM_SVRMOINFO             (0x100 + 88)

typedef struct{
        OAKSREQHEADER h;
        int  nReserve;                                          //������
        char szMobileNo[BUFLEN_MOBILENO];  //�ֻ�����
        char szSPCode[20];                                 //spcode 5818��������� �� 1801
        int  nLenMsg;                                      //���ݳ���
}*POAKSREQTRANSFERMOINFO,OAKSREQTRANSFERMOINFO;            //��������������

const char* testport="5818";
