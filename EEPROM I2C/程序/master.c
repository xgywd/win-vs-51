#include<reg51.h>
#include<intrins.h>
#include<lcd1602.h>

sbit sda = P1^6;
sbit scl = P1^7;
sbit led = P1^0;

void start();
void stop();
void wbyte(unsigned char dat);
unsigned char rbyte();
void delay5us();
void ack();
void unanswer();

unsigned char kk='0';

void main()
{
  unsigned int i=0,j=0;
   
  init1602();
  led = 1;
  
  for(j=0; j<4;j++)
  {

	  start();		     //启动
	
	  wbyte(0xa0); 	     //控制字写
	  ack();		     //从机应答
	
	  wbyte(0);		     //写地址0
	  ack();		     //从机应答
	
	  
	  wbyte('a');	     //写入数据
	  ack();		     //从机应答
	  					 
	  stop();			 //停止信号
	
	  write_data(0x32);  //尝试向1602中写入‘1’
	
	
	  for(i=0; i<5000; i++);
	  i=0;				   //等待数据写入
	
	  start();			   //启动
	  wbyte(0xa0);		   ////控制字写
	  ack();			   //从机响应
	  wbyte(0);			   //写地址0
	  ack();			   //从机响应
	  start();			   //重新启动
	  wbyte(0xa1);		   //控制字读
	  ack();			   //从机响应
	  kk=rbyte();
	  unanswer();		   //主机不应答
	  stop();			   //停止
	  
	  write_data(kk);

	  for(i=0; i<5000; i++);
	  i=0;				   //等待数据写入
   }
  while(1);

}

void start()
{
  sda = 1;
  scl = 1;
  delay5us(); 
  sda = 0;
  delay5us();
  scl = 0; 
}

void stop()
{
  sda = 0;
  scl = 1;
  delay5us();
  sda = 1;
  delay5us();
  scl = 0;
}

void wbyte(unsigned char dat)
{
  unsigned char i = 0;
  for(i=0; i<8; i++)
  {
    dat = dat<<1;
	sda = CY;
	scl = 1;
	delay5us();
	scl = 0;
  }
}

unsigned char rbyte()
{
  unsigned char i,k=0;
  bit j;
  sda = 1;
  for(i=0;i<8;i++)
  {
    scl = 1;
	delay5us();
	j=sda;	  //sda是bit，所以上面j是bit
	k=(k<<1)|(unsigned char)j;
	scl = 0;
  }
  return k;
}

void delay5us()
{
  _nop_(); _nop_();
  _nop_(); _nop_();
  _nop_(); 
}

void ack()   //等待回应，若无回应则点亮LED
{
  sda = 1;		 
  led = 1;
  scl = 1;
  while(sda==1)led=0;
  led = 1;
  scl = 0;
}

void unanswer()
{
  sda = 1;
  scl = 1;
  delay5us();
  scl = 0;
}


