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

	  start();		     //����
	
	  wbyte(0xa0); 	     //������д
	  ack();		     //�ӻ�Ӧ��
	
	  wbyte(0);		     //д��ַ0
	  ack();		     //�ӻ�Ӧ��
	
	  
	  wbyte('a');	     //д������
	  ack();		     //�ӻ�Ӧ��
	  					 
	  stop();			 //ֹͣ�ź�
	
	  write_data(0x32);  //������1602��д�롮1��
	
	
	  for(i=0; i<5000; i++);
	  i=0;				   //�ȴ�����д��
	
	  start();			   //����
	  wbyte(0xa0);		   ////������д
	  ack();			   //�ӻ���Ӧ
	  wbyte(0);			   //д��ַ0
	  ack();			   //�ӻ���Ӧ
	  start();			   //��������
	  wbyte(0xa1);		   //�����ֶ�
	  ack();			   //�ӻ���Ӧ
	  kk=rbyte();
	  unanswer();		   //������Ӧ��
	  stop();			   //ֹͣ
	  
	  write_data(kk);

	  for(i=0; i<5000; i++);
	  i=0;				   //�ȴ�����д��
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
	j=sda;	  //sda��bit����������j��bit
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

void ack()   //�ȴ���Ӧ�����޻�Ӧ�����LED
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


