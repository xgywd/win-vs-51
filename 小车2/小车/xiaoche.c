/* 买了个四驱车的底盘，双直流电机，一只驱动左边两轮，一只驱动		   
右边两轮。驱动电压为4.5-9V，配两个红外对管，打算一直装在小车前方		  
，一只装在小车底盘，分别检测前方障碍和台阶，小车碰到前方障碍后		    
左边两轮停止，右轮驱动，实现转弯。碰到台阶后小车先后退，然后左轮		   
停止，右轮驱动实现转弯，转弯结束后小车继续前进，如此循环*/           

#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
uchar cs1,cs2,num1,num2;
uchar code table[]={0,1};	  //占空比50% 
sbit qdg=P3^4;				  //前红外对管，检测小车前方障碍 
sbit xdg=P3^5;				  //下红外对管，检测小车是否碰到台阶 
sbit in1=P1^0;				  //L298输入 
sbit in2=P1^1;				  //L298输入 
sbit in3=P1^2;				  //L298输入 
sbit in4=P1^3;			      //L298输入 
sbit ena=P1^4;			      //L298输入使能A   
sbit enb=P1^5;			      //L298输入使能B 

void delay(int z)			  //延时函数 
{
	uint x,y;
	for(x=z;x>0;x--)
	   for(y=110;y>0;y--);
	
}

void init()					//初始化函数 
{
	TMOD=0x11;
	TH0=(65536-500)/256;
	TL0=(65536-500)%256;
	ET0=1;
	TR0=1;
	EA=1;
}

void main()
{
  init();
  while(1)
   {
	  if(qdg==1)		  //如果前方没有检测到障碍，对管输出高电平		 
		{
		   ena=1;		  //L298使能端A为高 
		   enb=1;		  //L298使能端B为高 
		   in2=0;		  //L298IN2为低，小车左轮前进	  
		   in4=0;		  //L298IN4为低，小车右轮前进	  
		}
	  else
		{
		   ena=0;		  //如果前方检测到障碍，L298使能端为低 ，左轮停止（小车转弯）		   
		   delay(1000);
		   ena=1;		  //一秒后转弯结束，继续两轮驱动前进 
		}
	  if(xdg==0)		  //如果小车下方未检测到障碍（碰到台阶）	   
	    {
		   in2=1;		  //L298IN2为高，小车左轮后退 
		   in4=1;		  //L298IN4为高，小车右轮后退 
		   delay(1000);
		   ena=0;		  //后退一秒后，左轮停止（转弯）  
		   delay(1000);	  //一秒后转弯结束，小车继续前进 
			
		}
	}
}

void timer0() interrupt 1
{
    TH0=(65536-500)/256;
    TL0=(65536-500)%256;
    cs1++;
    if (cs1==10)   
	  {
		cs1=0;   
    	num1++;
		if(num1==3)
		num1=0;
		in1=table[num1];

		num2++;
		if(num2==3)
		num2=0;
		in3=table[num2];
	  }
}
