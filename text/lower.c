#include<reg52.h>
#define uint unsigned int
#define uchar unsigned char

uchar code duan[]={
0x3f,0x06,0x5b,0x4f,					 //���ڹ���������ܶ�������ݱ��
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71,0x00};

uchar num;

void comset()
{
	TMOD=0X20;//��ʱ��1����Ϊ������ʽ2
	TH1=0Xfd;
	TL1=0xfd;//������Ϊ9600
	TR1=1;//������ʱ��1
	REN=1;
	SM0=0;
	SM1=1;//����ͨ����Ϊ������ʽ1
	EA=1;
	ES=1;
}

void main()
{
	 comset();
	 num=0;
	 while(1)
	 	{
		}
}

void ser() interrupt 4
{
	num=SBUF;
	P0=SBUF;
	RI=0;
}