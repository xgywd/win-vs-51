#include<reg52.h>
#define uint unsigned int
#define uchar unsigned char
uchar num;
void comset()
{
	TMOD=0X20;//��ʱ��1����Ϊ������ʽ2
	TH1=0Xfd;
	TL1=0xfd;//������Ϊ9600
	TR1=1;//������ʱ��1
	
	SM0=0;
	SM1=1;//����ͨ����Ϊ������ʽ1
	//PCON=0x00;
	
	ES=1;
	REN=1;
	EA=1;
	
}

void main()
{
	 comset();
	 num=0;
	 while(1)
	 	{
			P0=num;
			
		}
}

void ser() interrupt 4
{
	num=SBUF;
	
	RI=0;
}