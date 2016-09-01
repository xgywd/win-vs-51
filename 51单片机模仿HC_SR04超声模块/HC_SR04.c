/*
软件模拟HC_SRO4超声模块

作者:五号智能

需求:需要主控制单片机启动的第一时间进行初始化,初始化代码

 trig=0; 
 echo=1;
 
使用方法:你只需要提供一个10uS以上脉冲触发信号。
此程序便按arr数组里标的时间,让echo引脚发出不同时长的高电平.来模拟HC_SR04

功能:被触发后,模拟超声模块输出.输出5次,每次间隔5秒,

距离从长到短,使用着可以自行设置数组arr来模拟


HC_SR04说明书:

基本工作原理：
(1)采用IO口TRIG触发测距，给最少10us的高电平信号。
(2)模块自动发送8个40khz的方波，自动检测是否有信号返回；
(3)有信号返回，通过IO口ECHO输出一个高电平，
	高电平持续的时间就是超声波从发射到返回的时间。
	测试距离=(高电平时间*声速(340M/S))/2;
	每次触发高电平必须15us以上

*/



#include<reg52.h>
#include <intrins.h>

sbit trig=P3^2;          //模拟HC_SR04的两个引脚定义,可自行更改
sbit echo=P2^1;
unsigned int conter=0;
unsigned int ec=0;
unsigned int arr[]={588,400,350,200,50,1};   //此处为模拟发出的超声时长.可自行设置
unsigned int timer=0;
unsigned int flag=0;
void daley_10us(unsigned int n)//12M
{
	_nop_();
	_nop_();
	while(n--);
}

void main ()
{	
	unsigned int a=0;
	
	TMOD=0x01;
	TH0=(65536-50000)/256;	
							 
	TL0=(65536-50000)%256;	
	
	ET0=1;
	EA=1;
	echo=0;				//初始化echo电平为低

	while(trig);      //等待初始化指令
	
	echo=0;
	TR0=1;	//启动定时器0 
	
	while(1)
	{
		if(flag)
		{
			a=arr[ec];
			flag=0;
		}			
		
		if(conter>1)			//如果高电平时间超过2次计时自增,大约10us 
		{
			echo=1;			//拉高echo电平
			if(ec<6)		//判断数组下标是否溢出
			{
				daley_10us(a);	//循环设置拉高电平的时间
			}
			else
			{
				ec=0;					//数组溢出电标归0
				daley_10us(a);	//拉高电平的延时.
			}
			
			echo=0;				//延时结束时,拉低电平
			daley_10us(1);	//拉高电平的延时.
			conter=0;				//触发信号标志归0
			
		}
		if(trig)         //检测高电平触发信号
		{
			conter++;		//对高电平时间进行计时
		}
				
	}	
	
	

}
void delaytime() interrupt 1
{
	TH0=(65536-50000)/256;
	
	TL0=(65536-50000)%256;
	if(100==timer)
	{
		timer=0;
		ec++;				//数组下标自增
		flag=1;
	}
	timer++;
	

}



		
	
	   
	   
	   


