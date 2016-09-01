/*************************************头文件*********************************************/

#include<reg51.h>

/*************************************宏定义*********************************************/

#define uint unsigned int
#define uchar unsigned char

/*************************************位定义*********************************************/

sbit duan=P0^6;
sbit wei=P0^7;
sbit key1=P0^0;
sbit key2=P0^1;
sbit key3=P0^2;
sbit key4=P0^3;


/***********************************字符定义*********************************************/

uchar code duanma[]={					 //定义一个无符号字符串duanma[]存入ROM
0x3f,0x06,0x5b,0x4f,					 //用于共阴极数码管段码的数据表格
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71,0x40};

uchar xiancun[]={						 //定义无符号字符串存入RAM，用作显存
0,0,0,0,0,0,0,0};

uchar code weima[]={					//定义一个无符号字符串weima[]存入ROM
0xfe,0xfd,0xfb,0xf7,					//用于共阴极数码管位码的数据表格
0xef,0xdf,0xbf,0x7f};					//按照数码管的排列编码，发光取低电平，熄灭取高

char shi,fen,miao;
uchar flag_set,flag_zt;
uint tt;

/***********************************函数申明*********************************************/

void init();
void delay();
void display();
void keynum();
void seting();

/*************************************主函数*********************************************/

void main()
{
	init();
	while(1)
	{
		display();
		keynum();
		while(flag_set)
		{
			  set();
		}
	}	
}

/***********************************初始函数*********************************************/

void init()
{
	flag_set=0;
	flag_zt=0;
	P0=0x0f;
	shi=0;
	fen=0;
	miao=0;
	
	TMOD=0X01;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	EA=1;
	ET0=1;
	TR0=1;
}

/***********************************延时函数*********************************************/

void delay(uint y)
{
	while(y--);
}

/***********************************显示函数*********************************************/

void display()
{
	uchar i;
	xiancun[0]=duanma[shi/10];
	xiancun[1]=duanma[shi%10];
	xiancun[2]=duanma[16];
	xiancun[3]=duanma[fen/10];
	xiancun[4]=duanma[fen%10];
	xiancun[5]=duanma[16];
	xiancun[6]=duanma[miao/10];
	xiancun[7]=duanma[miao%10];

	for(i=0;i<8;i++)
	{
		P1=xiancun[i];
		duan=1;
		duan=0;
		P1=weima[i];
		wei=1;
		wei=0;
		delay(1);
		P1=0xff;
		wei=1;
		wei=0;
	}

}

/*******************************按键控制函数*********************************************/

void keynum()
{
if(!key1)
{
	delay(5);
	if(!key1)
		{
			if(flag_set==0)
				{
				flag_set=1;
				flag_zt=1;
				}
			else
				{
				flag_set=0;
				flag_zt=0;
				}
		}
		
	while(!key1)
		{
			delay(5);
			while(!key1)
			display();
		}
}
if(!key2)
{
	delay(5);
	if(!key2)
		{
			if(flag_set==1)
				{
					flag_zt++;
					if(flag_zt==3)
						flag_zt=1;
				}
					
		}
	while(!key2)
		{
			delay(5);
			while(!key2)
			display();
		}
}
if(!key3)
{
	delay(5);
	if(!key3)
		{
			if(flag_set==1)
				{
					switch(flag_zt)
					{
						case 1:
								miao++;
								if(miao==60)
									miao=0;
								break;

						case 2:
								fen++;
								if(fen==60)
									fen=0;
								 break;
						case 3:
								shi++;
								if(shi==24)
									shi=0;
								 break;	
					}
				}
		}
	while(!key3)
		{
			delay(5);
			while(!key3)
			display();
		}
}
if(!key4)
{
	delay(5);
	if(!key4)
		{
			if(flag_set==1)
				{
					switch(flag_zt)
					{	case 1:
								miao--;
								if(miao<0)
									miao=59;
								break;

						case 2:
								fen--;
								if(fen<0)
									fen=59;
								 break;
						case 3:
								shi--;
								if(shi<0)
									miao=23;
								 break;
					 }
				}
		}

	while(!key4)
		{
			delay(5);
			while(!key4)
			display();
		}
}
}

/***********************************控显函数*********************************************/

void seting()
{
	uint k=0;
	uchar i,j,h;
	keynum();			
	while(flag_zt)
	{
		uint k;
		uchar m,n;
		k++;
		key();

		if(40==k)
		{
			switch (flag_zt)
			{
				case 0:
						m=xiancun[6];
						n=xiancun[7];
						xiancun[6]=0x00;
						xiancun[7]=0x00;
						break;
				case 1:	
						m=xiancun[3];
						n=xiancun[4];
						xiancun[3]=0x00;
						xiancun[4]=0x00;
						break;
				case 2:
						m=xiancun[0];
						n=xiancun[1];
						xiancun[0]=0x00;
						xiancun[1]=0x00;
						break;
				
			}
		}
		if (80==k)
		{
			
			switch (flag_zt)
			{
				case 0:
						xiancun[6]=m;
						xiancun[7]=n;
						k=0;
						break;
				case 1:	
						xiancun[3]=m;
						xiancun[4]=n;
						k=0;
						break;
				case 2:
						xiancun[0]=m;
						xiancun[1]=n;
						k=0;
			}			break;
		}
		
	display();
	}		
		
}

/***********************************中断函数*********************************************/

void timer0() interrupt 1
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	tt++;
	if(tt==20)
	{
		tt=0;
		miao++;
		if(miao==60)
			{
				miao=0;
				fen++;
				if(fen==60)
					{
						fen=0;
						shi++;
						if(shi==24)
							shi=0;
					}
			}
	}
}