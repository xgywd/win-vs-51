#include <reg52.h>                 
																/*�����������⹦�ܼĴ���������.
																	���û�����ͷ�ļ������⹦�ܼĴ�����ֻ����Ӳ���ĵ�ַ���ж�д������*/
																	
#include <intrins.h>							//��ָ��Ȳ���	

#ifndef   XXXX_HHHH_II
#define   XXXX_HHHH_II
//���벿��
typedef  unsigned int uint;
typedef  unsigned char uchar;

#endif


sbit sda=P2^1;
sbit scl=P2^0;


/******************************����ȫ�ֺ����ͱ���*********************************************************/

void delay1()
{ ;; }
void start()  //��ʼ�ź�
{	
	sda=1;
	scl=1;
	delay1();
	sda=0;
	delay1();
}

void stop()   //ֹͣ
{
	sda=0;
	scl=1;
	delay1();
	sda=1;
	delay1();
}

void respons()  //Ӧ��
{
	uchar i;
	scl=1;
	delay1();
	while((sda==1)&&(i<250))i++;
	scl=0;
	delay1();
}
void norespons() //��Ӧ��
{
	scl=1;
	sda=1;
	delay1();
	scl=0;
	delay1();
}

void init_i2c() //��ʼ��
{
	sda=1;
	delay1();
	scl=1;
	delay1();
}

void write_byte(uchar date)          //д�뵥�ֽ�
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

uchar read_byte()              //�������ֽ�
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

