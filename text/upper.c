#include<reg52.h>//定义头文件，直接调用文件命令
#define uint unsigned int
#define uchar unsigned char

uchar code duan[]={
0x3f,0x06,0x5b,0x4f,					 //用于共阴极数码管段码的数据表格
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71,0x00};

uchar temp,num,signal,flag;

uchar keyscan(); //按键扫描

void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}

void comset()
{
	TMOD=0X20;//定时器1设置为工作方式2
	TH1=0Xfd;
	TL1=0xfd;//波特率为9600
	TR1=1;//启动定时器1
	SM0=0;
	SM1=1;//串口通信设为工作方式1
}

void main()
{
	comset();
	num=16;
	while(1)
		{
			signal=duan[keyscan()];
			P1=signal;
			if(flag==1)
				{
				SBUF=signal;
				while(!TI);
				TI=0;
				flag=0;
				}
		}
}

uchar keyscan()
{
	P0=0xfe;
	temp=P0;
	temp=temp&0xf0;
	while(temp!=0xf0)
		{
			delay(5);
			temp=P0;
			temp=temp&0xf0;
			while(temp!=0xf0)
				{
					temp=P0;
					switch(temp)
						{
							case 0xee:num=0;
								break;
							case 0xde:num=1;
								break;
							case 0xbe:num=2;
								break;
							case 0x7e:num=3;
								break;
						}
					while(temp!=0xf0)
						{
							temp=P0;
							temp=temp&0xf0;
							flag=1;			
						}
				}
		}
	P0=0xfd;
	temp=P0;
	temp=temp&0xf0;
	while(temp!=0xf0)
		{
			delay(5);
			temp=P0;
			temp=temp&0xf0;
			while(temp!=0xf0)
				{
					temp=P0;
					switch(temp)
						{
							case 0xed:num=4;
								break;
							case 0xdd:num=5;
								break;
							case 0xbd:num=6;
								break;
							case 0x7d:num=7;
								break;
						}
					while(temp!=0xf0)
						{
							temp=P0;
							temp=temp&0xf0;
							flag=1;
						}
				}
		}
	P0=0xfb;
	temp=P0;
	temp=temp&0xf0;
	while(temp!=0xf0)
		{
			delay(5);
			temp=P0;
			temp=temp&0xf0;
			while(temp!=0xf0)
				{
					temp=P0;
					switch(temp)
						{
							case 0xeb:num=8;
								break;
							case 0xdb:num=9;
								break;
							case 0xbb:num=10;
								break;
							case 0x7b:num=11;
								break;
						}
					while(temp!=0xf0)
						{
							temp=P0;
							temp=temp&0xf0;
							flag=1;
						}
				}
		}
	P0=0xf7;
	temp=P0;
	temp=temp&0xf0;
	while(temp!=0xf0)
		{
			delay(5);
			temp=P0;
			temp=temp&0xf0;
			while(temp!=0xf0)
				{
					temp=P0;
					switch(temp)
						{
							case 0xe7:num=12;
								break;
							case 0xd7:num=13;
								break;
							case 0xb7:num=14;
								break;
							case 0x77:num=15;
								break;
						}
					while(temp!=0xf0)
						{
							temp=P0;
							temp=temp&0xf0;
							flag=1;
						}
				}
		}
	return num;
}