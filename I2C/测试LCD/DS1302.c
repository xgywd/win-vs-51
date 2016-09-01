#include <reg52.h>                //用于声明特殊功能寄存器的名称.
														//	如果没有这个头文件，特殊功能寄存器，只能用硬件的地址进行读写操作。
#include <intrins.h>							//空指令等操作	

#ifndef   XXXX_HHHH_II
#define   XXXX_HHHH_II
//代码部分
//typedef  unsigned int uint;
typedef  unsigned char uchar;

#endif
code unsigned char write_rtc_address[7]={0x8c,0x8a,0x88,0x86,0x84,0x82,0x80};
code unsigned char read_rtc_address[7]={0x8d,0x8b,0x89,0x87,0x85,0x83,0x81};
uchar time[7]={16,3,7,27,15,43,30};		//年周月日时分秒

sbit clk=P3^6;
sbit rst=P3^5;
sbit sda=P3^4;

void ds1302_wb(uchar dat)
{
	uchar i;
	for (i=0;i<8;i++)
	{
		clk=0;
		sda=dat&0x01;
		dat=dat>>1;
		clk=1;
	}
}
uchar ds1302_rb(uchar add)
{
	uchar i,dat;
	
	rst=0;
	_nop_();
	rst=1;
	_nop_();
	ds1302_wb(add);
	
	for (i=0;i<8;i++)
	{
		clk=0;
		dat=dat>>1;
		if(sda)
		{
			dat=dat|0x80;
		}
		clk=1;
	}
	rst=0;
	_nop_();
	sda=1;
	return dat;
}

void ds1302_write(uchar add,uchar dat)
{
	rst=0;
	_nop_();
	rst=1;
	_nop_();
	ds1302_wb(add);
	ds1302_wb(dat);
	rst=0;
	_nop_();
	sda=1;
}

void set_time()
{
	uchar i,j;
	
	for(i=0;i<7;i++)
	{
		j=time[i]/10;
		time[i]=time[i]%10;
		time[i]=time +j*16;
	}
	
	ds1302_write(0x8e,0x00);
	
	for(i=0;i<7;i++)
	{
		ds1302_write(write_rtc_address[i],time[i]);
	}
	
	ds1302_write(0x8e,0x80);
	
}
void read_time(uchar *p)
{
	uchar i;
	for(i=0;i<7;i++)
	{
		time[i]=ds1302_rb(read_rtc_address[i]);
		*p=time[i]/16+48;
		p++;
		*p=time[i]%16+48;
		p++;
	}
	
}





