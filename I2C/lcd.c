/******************************头文件加载与宏定义**************************************************/
#include <reg52.h>                 
																		/*用于声明特殊功能寄存器的名称.
																		如果没有这个头文件，特殊功能寄存器，只能用硬件的地址进行读写操作。*/
																		
#include <intrins.h>							//空指令等操作	

#ifndef   XXXX_HHHH_II
#define   XXXX_HHHH_II
//代码部分
typedef  unsigned int uint;
typedef  unsigned char uchar;

#endif
uchar sh=0;
sbit rs=P2^6;
sbit rw=P2^5;
sbit e=P2^7;

uchar table1[32]={0};	//缓冲 LCD
/******************************声明全局函数和变量*********************************************************/
/*此处增加其它全局声明*/

void delay(uint i)
{
	int k,j;
	
	for(k=0;k<i;k++)
		for (j=55;j>0;j--)
		{
			_nop_();
			_nop_();
		}
}

void wcom(uchar com)
{
	rs=0;
	rw=0;
	P0=com;
	delay(2);
	e=1;
	e=0;
}
void wdat(uchar dat)
{
	rs=1;
	rw=0;
	P0=dat;
	delay(2);
	e=1;
	e=0;	
}

void init ()
{
	
	delay(30);
	wcom(0x38);
	delay(10);
	wcom(0x38);
	delay(10);
	wcom(0x38);
	wcom(0x38);
	wcom(0x08);
	wcom(0x01);
	wcom(0x06);
	wcom(0x0c);
	TMOD=0x01;
	TH0=(65536-1000)/256;	/*定时器0是由两个8位寄存器TH0与TL0组成,
														定时器初值计算方法为65536减去定时间隔除以256放入高8位,*/
	TL0=(65536-1000)%256;	/*再用65536减去定时间隔取余256放入低8位*/
	ET0=1; //开定时器0中断
	TR0=1;	//启动定时器0 
	EA=1;	//开总中断 	
	
	
}
void show()
{
		
		if(16==sh)	//如果显示达到16个字符.换行
		{
				wcom(0x80+0x40);	//换行语句
			
		}
		if(32==sh)
		{
			sh=0;
		}
			
		wdat(table1[sh]);	//显示当前字符
		sh++;
}

void lcdprintf(const char *p)
{
	uchar i;
	while(*p)
	{
		table1[i]=*p;
		p++;
		i++;
		if(32==i)
		{
			return;
		}
	}
	
}

void lcdshow() interrupt 1
{
	TH0=(65536-1000)/256;
	
	TL0=(65536-1000)%256;
	
	show();
}

