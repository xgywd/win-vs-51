#include <reg51.h>
#define	uchar unsigned char
#define uint unsigned int 
sbit lcden=P2^7;
sbit lcdrw=P2^5;
sbit lcdrs=P2^6;
uchar code table[]="I like mcu !";
uchar mumb;
void delay (uint z)
{		 			   
	  uint x	, y	;
	  for(x=z;x>0;x--)
	  for(y=100;y>0;y--);
}
void Write_com(uchar com)
{
	lcdrs=0;
	lcdrw=0;
	P0=com;
	delay(5);
	lcden=1;
	delay(5);
	lcden=0;
}
void Write_data(uchar date)
{
	lcdrs=1;
	lcdrw=0;
	P0=date;
	delay(5);
	lcden=1;
	delay(5);
	lcden=0;
}

void Init()	
{
	lcden=0; 
	Write_com(0x38);
	Write_com(0x0e);
	Write_com(0x06);
	Write_com(0x80+0x10);
}
void main()
{
 Init()	;

 while(1)
{ 
	for(mumb=0; mumb<12; mumb++)
	{
		Write_data(table[mumb]) ;
		delay(500);
		Write_com(0x18)	;
		delay(500);
	 }
	}
}

