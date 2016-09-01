/********************************ͷ�ļ�����**********************************************/

#include<reg52.h>						//��reg52.h�ļ���Ϊͷ�ļ��������

/********************************�궨��**********************************************/

#define uint unsigned int				//���޷������ͺ궨��Ϊuint
#define uchar unsigned char				//���޷����ַ��ͺ궨��Ϊuchar

/************************************λ����**********************************************/

sbit duan=P2^6;							//����P2.6�˿�Ϊ����duan,���ƶ����������������
sbit wei=P2^7;							//����P2.7�˿�Ϊ����wei������λ���������������

/********************************�ַ�����**********************************************/

uchar code duanma[]={					//����һ���޷����ַ���duanma[]����ROM
0x3f,0x06,0x5b,0x4f,					//���ڹ���������ܶ�������ݱ���
0x66,0x6d,0x7d,0x07,					//����LED��������ܵ����к���Ҫ���ֵ����б���
0x7f,0x6f,0x77,0x7c,					//����ȡ�ߵ�ƽ��Ϩ��ȡ�͵�ƽ
0x39,0x5e,0x79,0x71};					// ����duanma[0]�͵���0x3f

uchar code weima[]={					//����һ���޷����ַ���weima[]����ROM
0xfe,0xfd,0xfb,0xf7,					//���ڹ����������λ������ݱ���
0xef,0xdf,0xbf,0x7f};					//��������ܵ����б��룬����ȡ�͵�ƽ��Ϩ��ȡ�ߵ�ƽ

uchar a,b,c;						//�����޷����ַ�������ʵ�ʲ���a,b,c
uint num;							//�޷������ͱ�����ʵ�ʲ���num

/********************************�Ӻ�������**********************************************/

void delay(uint z);					  	//��ʱ��������
void display(uchar bai,uchar shi,uchar ge);//������ʾ��������

/********************************������**************************************************/

void main()								//�޷���ֵ������������ֻ��һ��
{
	num=520;							//num��ֵ520
	while(1)							//while��1��ѭ���������ڷ�0��Ϊ�棨��������ȥ��
	{									//��ִ��{}�����
										//ֻ��������Ϊ0��0��Ϊ�٣��������Ҳ���ִ��{���}
		  display(a,b,c);				//��ʾ��������ʵ�ʲ���a,b,c������ʽ����bai,shi,ge
	}									//������Ҫ�ô�ѭ����ѭ��ɨ������ܣ�ʵʱ��ʾnum
}

/********************************��ʱ����***********************************************/

void delay(uint z) //�����޷���ֵ����delay()�������޷������ͱ���z��Ϊ�ֲ���������ʽ����
{
	uint x,y;							 //�����޷������ͱ���x,y���ñ���Ϊ�ֲ��������β�
	for(x=z;x>0;x--)					 //forѭ��   for������ʽ1������ʽ2������ʽ3��
		for(y=110;y>0;y--);				 //			{��䣨�ڲ���Ϊ�գ�}
}	//����forѭ��Ƕ�׺�����
	//��y����0��ִ��һ��x--����x��һ�ٸ���x�������ռ������Ϊx����y���ﵽ��ʱĿ��
	//ִ�й��̣�1.������ʽ1
	//			2.������ʽ2������ֵΪ�棨��0��Ϊ�棩��
	//��ִ��for��䣬Ȼ��ִ�е��������������for��䣬ֱ������������ִ�е�������
	//			3.������ʽ3	4.�����ڶ����ظ�ִ��

/********************************��ʾ����**********************************************/

void display(uchar bai,uchar shi,uchar ge)//�����޷���ֵ���ֲ���������ʽ����bai,shi,ge
{

	a=num/100;							 //num����100���̣����ֽ��num�İ�λ������a
	b=num%100/10;						 //num����100���������ٳ���10���̣��ֽ�ʮλ����b
	c=num%10;							 //num����10�����������ֽ����λ����c

	P1=duanma[bai];						 //����P1�����duanma[]��bai+1λ��������Ϊ����
	duan=1;								 //�򿪶��������
	duan=0;								 //�رն��������
	P1=weima[5];						 //P1���weima[]��6λ������Ϊλ�룬ѡ��6�������
	wei=1;								 //��λ�������
	wei=0;								 //�ر�λ�������
	delay(1);							 //����z=1����������ʱ����Ϊ��ʱ
	P1=0xff;							 //P1ȫ������ߵ�ƽ����λ������򿪣��ﵽ����Ŀ��
	wei=1;								 //��λ�������
	wei=0;								 //�ر�λ�������

	P1=duanma[shi];						 //P1�����duanma[]��shi+1λ������Ϊ����
	duan=1;								 //�򿪶��������
	duan=0;								 //�رն��������
	P1=weima[6];						  //����weima[]��7λ������Ϊ���룬ѡ��7�������
	wei=1;								 //λ�������
	wei=0;								  //�ر�λ������
	delay(1);							  //��ʱ
	P1=0xff;							 //P1ȫ���ߵ�ƽ���ȴ�λ������򿪣�ʵ������
	wei=1;								 //λ�������
	wei=0;								  //�ر�λ������

	P1=duanma[ge];						   //��������ͬ�ϣ��������������ѭ��ɨ�衣
	duan=1;								  //ʵ����ͬһʱ��ֻ����ʾһ�������
	duan=0;								  //΢���Ͻ�����һ������һ����һ��ʱ��Ȼ��Ϩ��
	P1=weima[7];						  //���������ܶ�̬ɨ��
	wei=1;								  //�Ӷ�ʵ�����˿͹�����Ϊ��ͬʱ��ʾ
	wei=0;
	delay(1);
	P1=0xff;
	wei=1;
	wei=0;								   //ע�Ⱑ�������������ֽӷ�Ҫ�ȸ�ֵ�ٿ�����

}