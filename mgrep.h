#ifndef MGREP_6BA4F54F_8745_43C9_8EE1_BC83A35F4ED0
#define MGREP_6BA4F54F_8745_43C9_8EE1_BC83A35F4ED0

#define MAXPAT  256
#define MAXLINE 1024
#define MAXSYM  256
#define MAXMEMBER1 4096
#define MAXPATFILE 2600 /*pattern�ļ�����󳤶�*/
#define BLOCKSIZE  8192  /*����Ԥ�������ݴ�С*/
#define MAXHASH    512  /*patternʹ�õ�hash���С*/
#define mm 	   511  /*����hashֵ��ȡģ����*/
#define max_num    200 /*����pattern����*/
#define W_DELIM	   128
#define L_DELIM    10

extern int ONLYCOUNT, FNAME, SILENT, FILENAMEONLY, num_of_matched;
extern int INVERSE;
extern int WORDBOUND, WHOLELINE, NOUPPER;
extern unsigned char *CurrentFileName;
extern int total_line;

void default_setting();
int prepf(int fp,void** patternbuf,size_t* patt_image_len);
int mgrep(int fp,void* patternbuf);
int mgrep_str(char* data,int len,void* patternbuf);
void releasepf(void* patternbuf);

#endif

