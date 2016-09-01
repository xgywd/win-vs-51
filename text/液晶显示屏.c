#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
uchar code table[]="I LIKE LIU!";
uchar code table1[]="1996.10.26";
sbit lcden=P2^7;
sbit lcdrs=P2^6;
sbit lcdrw=P2^5;
uchar num;


void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}
void write_com(uchar com)
{
	lcdrs=0;
	lcdrw=0;
	P3=com;
	delay(5);
	lcden=1;
	delay(5);
	lcden=0;
}
void wcom(uchar com)
{
	rs=0;
	rw=0;
	P0=com;
	delay(2);
	e=1;
	e=0;
}


void write_data(uchar date)
{
	lcdrs=1;
	lcdrw=0;
	P3=date;
	delay(5);
	lcden=1;
	delay(5);
	lcden=0;
}
void init()
{
	lcden=0;
	lcdrw=0;
	lcdrw=0;
	write_com(0x38);
	write_com(0x0e);
	write_com(0x06);
	write_com(0x01);
}
void main()
{
	init();
	write_com(0x80+10);
	for(num=0;num<11;num++)
	{
		write_data(table[num]);
		delay(20);
	}
	write_com(0x80+0x40+10);
	for(num=0;num<10;num++)
	{
		write_data(table1[num]);
		delay(20);
	}
	for(num=0;num<16;num++)
	{
	write_com(0x18);
	delay(200);
	}
	while(1);
}