/*本程序做为单片机时钟的控制程序.*/


/******************************头文件加载与宏定义**************************************************/
#include <reg52.h>                 
																		/*用于声明特殊功能寄存器的名称.
																			如果没有这个头文件，特殊功能寄存器，只能用硬件的地址进行读写操作。*/

typedef  unsigned int uint;
typedef  unsigned char uchar;
/******************************声明全局函数和变量*********************************************************/
/*此处增加其它全局声明*/
uchar code table[]={0x3f,0x06,0x5b,0x4f,
										0x66,0x6d,0x7d,0x07,
										0x7f,0x6f,0x77,0x7c,
										0x39,0x5e,0x79,0x71};/* 共阴数码管显示段编码0-f*/
sbit weila=P2^7;
sbit dula=P2^6;

void delay(uint a)
{
	uint b;
	for(;a>0;a--)
		for(b=110;b>0;b--);
	
}

void main()
{
	uint num;
	weila=1;
	P0=0xf0;
	weila=0;
	while(1)
	{
		for (num=0;num<16;num++)
		{
			dula=1;
			P0=table[num];
			dula=0;
			delay(500);
			
		}
	}
}