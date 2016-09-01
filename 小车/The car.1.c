#include<reg52.h>
#include<intrins.h>
#define	char  unsigned char 
#define int unsigned int 
sbit ENA=P1^2;//电机使能端 
sbit ENB=P1^3;//电机使能端
sbit IN1=P1^7;//前进 后退 电机
sbit IN2=P1^6;// 前进 后退 电机
sbit IN3=P1^5;//左转 右转 电机
sbit IN4=P1^4;//左转  右转 电机
sbit IN5=P1^0;//云台 左转 右转 电机
sbit IN6=P1^1;//云台左转 右转 电机
sbit trig=P2^0;//超声波模块启动端
sbit echo=P0^1;//超声波模块数据接收端
void L298_init();//驱动芯片初始化 
void motion_init();//运动初始化 
void forword();//前进函数 
void backoff();//后退函数 
void right();//右转函数 
void left();//左转函数 
void stop();//停止前进 后退  动作 
void direction_stop();//停止 左转 右转动作 
void ptz_left();//云台左转 
void ptz_right();//云台右转 
void ptz_judge();//云台转向判断 以及运动方式判断 
void trig_start();//超声波模块开始工作 信号 
void HC_SR04_init();//超声波模块初始化 
void ptz_init();//云台转向初始化 
void echo_handle();//超声波模块数据处理 

int n=0;//超声波模块数据储存变量 
//////////延时函数  单位 毫秒
void daley_ms(int i)         //延时函数  单位 毫秒
{
 char x,y;
 for(x=0;x<i;x++)
  for(y=1000;y>0;y--);
}
void daley_us(char i)         // 延时函数 单位 微秒
{  char x;
  for(x=0;x<=i;x++);
}
void L298_init()           // L298驱动芯片初始化函数 输出端使能 
{
	ENA=1;
	ENB=1;		
}
void motion_init()//小车前进后退初始化
{
IN1=1;
IN2=1;
} 
void forword()//小车前进函数
{
 IN1=0;
 IN2=1;
}
void backoff()//小车后退函数 
{
 IN1=1;
 IN2=0;
}
void right()//小车右转函数 
{
IN3=0; 
IN4=1;
}
void left()//小车左转函数
{
IN3=1; 
IN4=0;

} 
void stop()//小车停止前进  后退动作
{
 IN1=1;
 IN2=1;
}
void direction_stop()//小车转向动作停止 兼  转向动作初始化 
{
IN3=1; 
IN4=1;
}
void ptz_right()//云台右转函数
{
  IN5=0;
  IN6=1;
} 
void ptz_left()//云台左转函数
{
  IN5=1;
  IN6=0;
}
void ptz_init()
{
  IN5=1;
  IN6=1;
} 
void trig_start()//超声波模块开始工作 信号
{

	trig=1;
	daley_us(15);
	trig=0; 

}
void HC_SR04_init()//超声波模块初始化
{
  trig=0;
  echo=1;
}
void echo_handle()//超声波模块数据处理
{  
   while(!echo);
   while(echo)
   {
			n++;
   }
}
void  ptz_judge()//云台转向判断函数 以及转向 停止 
{ 
	while(echo);
  if(n<573)
  { 
		n=0;
   ptz_left();
   trig_start();
   echo_handle();
   while(echo);
   if(n<278)//左侧检测 有障碍物则 ： 
    {  n=0;
       ptz_right();
       trig_start();
       echo_handle();
	   while(echo);
       if(n<278)//检测右侧障碍物 ： 如有障碍物后退左转 延时1000ms 
       { 
       n=0;
       backoff();
       left(); 
       daley_ms(1000);
       forword();
       ptz_init();
       direction_stop();
       }
       else//右侧无障碍时 ：右转 前进 延时1000ms 
	   { n=0;
	   	forword();
	   	right();
	   	daley_ms(1000);
	   	ptz_init();
	   	direction_stop();
	   }
   	} 
	  else//左侧无障碍物 则： 
      { 
	  n=0;
	   forword();//	前进 
	   left();//左转 
	   daley_ms(1000);//延时 
	   ptz_init();//云台恢复到初始位置 
	   direction_stop();//转向停止    
	  } 	  	  
   }
   forword();
   direction_stop();
   ptz_init();

} 
void main()
{
 HC_SR04_init();//超声波模块初始化 
 L298_init();//驱动模块初始化 
 motion_init();//前进 后退  初始化
 direction_stop();//转向初始化 兼 转向初始化 
 ptz_init();//云台转向初始化
 while(1)
 {
 forword();//前进！！！！！
 trig_start();//开始测距
 echo_handle();//超声波数据处理 
 ptz_judge();//云台转向处理 以及  用运动方式处理 
 }  
}