#include<reg52.h>
#define uint unsigned int
#define uchar unsigned char
uchar num;
void comset()
{
	TMOD=0X20;//定时器1设置为工作方式2
	TH1=0Xfd;
	TL1=0xfd;//波特率为9600
	TR1=1;//启动定时器1
	
	SM0=0;
	SM1=1;//串口通信设为工作方式1
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