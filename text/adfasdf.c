#include<reg52.h>
typedef unsigned int uint;
typedef unsigned char uchar;
sbit pwm=P0^3;//输出PWM信号
uchar count=0;
uint pwm_value=1500;//初值为1.5ms
uint value[]={1500,1000,1500,2000,1500};//
void delay_ms(uint x)
{uint i;
while(x--)
for(i=0;i<125;i++);}
void InitTimer(void)
{TMOD=0x11;//开定时器0,1
TH0=-20000/256;//定时20MS,20MS为一个周期
TL0=-20000%256;
TH1=-1500/256;//定时1.5MS,这时舵机处于0度
TL1=-1500%256;
EA=1;//开总断
TR0=1;//开定时器0
ET0=1;
TR1=1;//开定时器1
ET1=1;}
void timer0(void) interrupt 1//定时器0中断函数
{pwm=1;
TH0=-20000/256;
TL0=-20000%256;
TR1=1;
count++;}
void timer1(void) interrupt 3//定时器1中断函数
{pwm=0;
TH1=-pwm_value/256;
TL1=-pwm_value%256;
TR1=0;}
void main(void)//主函数
{uchar i;
InitTimer();
pwm_value=1500;
while(1)
{for(i=0;i<5;i++)
{pwm_value=value[i];//通过数组就可以改变舵机的转角度
delay_ms(1000);
}
}
}
