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


sbit sda=P2^1;
sbit scl=P2^0;


/******************************声明全局函数和变量*********************************************************/

void delay1()
{ ;; }
void start()  //开始信号
{	
	sda=1;
	scl=1;
	delay1();
	sda=0;
	delay1();
}

void stop()   //停止
{
	sda=0;
	scl=1;
	delay1();
	sda=1;
	delay1();
}

void respons()  //应答
{
	uchar i;
	scl=1;
	delay1();
	while((sda==1)&&(i<250))i++;
	scl=0;
	delay1();
}
void norespons() //不应答
{
	scl=1;
	sda=1;
	delay1();
	scl=0;
	delay1();
}

void init_i2c() //初始化
{
	sda=1;
	delay1();
	scl=1;
	delay1();
}

void write_byte(uchar date)          //写入单字节
{
	uchar i,temp;
	temp=date;

	
	for(i=0;i<8;i++)
	{
		scl=0;
		temp=temp<<1;
		sda=CY;
		
		delay1();
		scl=1;
		delay1();
	}
	scl=0;
	delay1();
	sda=1;
	delay1();
}

uchar read_byte()              //读出单字节
{
	uchar i,k;
	scl=0;
	delay1();
	sda=1;
	delay1();
	for(i=0;i<8;i++)
	{
		scl=1;
		delay1();	
		k=(k<<1)|sda;
		scl=0;
		delay1();	
	}
	return k;
}
void write_add(uchar address,uchar date)
{
	start();
	write_byte(0xa0);
	respons();
	write_byte(address);
	respons();
	write_byte(date);
	respons();
	stop();
}

uchar read_add(uchar address)
{
	uchar date;
	start();
	write_byte(0xa0);
	respons();
	write_byte(address);
	respons();
	start();
	write_byte(0xa1);
	respons();
	date=read_byte();
	norespons(); 
	stop();
	return date;
}

