#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
//bit write=0;
sbit sda=P2^0;
sbit scl=P2^1;
sbit LSA=P2^2;/*3-8������*/
sbit LSB=P2^3;
sbit LSC=P2^4;
uchar t1,sec;
void delay()
{ ;; }
void delay1(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);	
}
uchar code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71};
void duanxuan( uint i)
{
		switch(i)	 //λѡ��ѡ�����������ܣ�
		{
			case(0):
				LSA=0;LSB=0;LSC=0; break;//��ʾ��0λ
			case(1):
				LSA=1;LSB=0;LSC=0; break;//��ʾ��1λ
			case(2):
				LSA=0;LSB=1;LSC=0; break;//��ʾ��2λ
			case(3):
				LSA=1;LSB=1;LSC=0; break;//��ʾ��3λ
			case(4):
				LSA=0;LSB=0;LSC=1; break;//��ʾ��4λ
			case(5):
				LSA=1;LSB=0;LSC=1; break;//��ʾ��5λ
			case(6):
				LSA=0;LSB=1;LSC=1; break;//��ʾ��6λ
			case(7):
				LSA=1;LSB=1;LSC=1; break;//��ʾ��7λ	
		}
 }
void display(uchar shi,uchar ge)
{
  duanxuan(1);
  P0=table[ge];
  delay1(5);
  P0=0x00;
   duanxuan(3);
  P0=table[shi];
  delay1(5); 
  P0=0x00; 
} 
void start()  //��ʼ�ź�
{	
	sda=1;
	delay();
	scl=1;
	delay();
	sda=0;
	delay();
}

void stop()   //ֹͣ
{
	sda=0;
	delay();
	scl=1;
	delay();
	sda=1;
	delay();
}

void respons()  //Ӧ��
{
	uchar i;
	scl=1;
	delay();
	while((sda==1)&&(i<250))i++;
	scl=0;
	delay();
}

void init()
{
	sda=1;
	delay();
	scl=1;
	delay();
}

void write_byte(uchar date)
{
	uchar i,temp;
	temp=date;


	for(i=0;i<8;i++)
	{
		temp=temp<<1;
		scl=0;
	    delay();
		sda=CY;
		delay();
		scl=1;
		delay();
	//	scl=0;
     //   delay();
	}
	scl=0;
	delay();
	sda=1;
	delay();
}

uchar read_byte()
{
	uchar i,k;
	scl=0;
	delay();
	sda=1;
	delay();
	for(i=0;i<8;i++)
	{
		scl=1;
		delay();	
		k=(k<<1)|sda;
		scl=0;
		delay();	
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
	stop();
	return date;
}
void main()
{
init();
sec=read_add(2);
if(sec>100)
TMOD=0x01;
TH0=(65536-50000)/256;
TL0=(65536-50000)%256;
EA=1;
ET0=1;
TR0=1;
while(1)
	{
		  display(sec/10,sec%10);
		 write_add(2,sec);
		}
		}
void timer0() interrupt 1
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	t1++;
	if(t1==20)
		{
		t1=0;
			sec++;
			if(sec==100)
			sec=0;		
		 }
}