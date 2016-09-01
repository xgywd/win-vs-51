/******************************头文件加载与宏定义**************************************************/
#include <reg52.h>                 
																		/*用于声明特殊功能寄存器的名称.
																			如果没有这个头文件，特殊功能寄存器，只能用硬件的地址进行读写操作。*/

typedef  unsigned int uint;
typedef  unsigned char uchar;
/******************************声明全局函数和变量*********************************************************/
/*此处增加其它全局声明*/
void delay(uint i);
sbit cs	=	P1^0;
sbit wr	=	P1^1;
sfr dat   = 0x80;
bit flag=0;

void main()
{
	uchar k=0,j=0;
	cs=0;
	wr=0;
	while(1)
	{
		dat=k;
		delay(100);
		if(255==k)
		{
			flag=1;
		}
		else if(0==k)
		{
			flag=0;
		}
		if(!flag)
		{
			k++;
		}
		else
		{
			k--;
		}
	}
}


void delay(uint i)
{
	uchar j;
	for(;i>0;i--)
		for(j=19;j>0;j--);
}