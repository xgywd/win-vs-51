/*������ռ���˶�ʱ��0,�������Ҫ�����и���*/

#ifndef   XXXX_HHHH_II
#define   XXXX_HHHH_II
//���벿��
typedef  unsigned int uint;
typedef  unsigned char uchar;
#endif

#ifndef   HEAD_LABEL_III
#define   HEAD_LABEL_III
//���벿��
void init_lcd();	//1602��ʼ������
void cls();				//��������
void delay(uint i);    //��ʱ����
void lcdprintf(const char *p,uchar j);    //����Ļ��ӡ�ַ�,�ַ�����32�ֽ�,������ض�

#endif