
#ifndef   XXXX_HHHH_II
#define   XXXX_HHHH_II
//���벿��
typedef  unsigned int uint;
typedef  unsigned char uchar;

#endif


#ifndef   HEAD_LABEL_IV
#define   HEAD_LABEL_IV
//���벿��
void init(); //��ʼ��


void start(); //��ʼ�ź�
void stop();   //ֹͣ
void respons();  //Ӧ��

void write_byte(uchar);        //д�ֽ�

uchar read_byte();            //���ֽ�


void write_add( uchar address, uchar date); //ָ����ַд����
uchar read_add( uchar address);                //ָ����ַ������

#endif
