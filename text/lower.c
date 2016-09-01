#include<reg52.h>
#define uint unsigned int
#define uchar unsigned char

uchar code duan[]={
0x3f,0x06,0x5b,0x4f,					 //用于共阴极数码管段码的数据表格
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71,0x00};

uchar num;

void comset()
{
	TMOD=0X20;//定时器1设置为工作方式2
	TH1=0Xfd;
	TL1=0xfd;//波特率为9600
	TR1=1;//启动定时器1
	REN=1;
	SM0=0;
	SM1=1;//串口通信设为工作方式1
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