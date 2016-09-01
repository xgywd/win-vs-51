#include <reg52.h>
#define GPIO P0

sbit E=P2^7;
sbit RW=P2^5;
sbit RS=P2^6;
void Delay1ms(int a)
{
	int b,c;
	for(;a>0;a--)
		for(b=199;b>0;b--);
}


void LCD_Write_Com(char com)
{
	E=0;
	RW=0;
	RS=0;
	GPIO=com;
	Delay1ms(1);
	E=1;
	Delay1ms(1); 
	E=0;	
}

void LCD_Write_Dat(char dat)
{
	E=0;
	RW=0;
	RS=1;
	GPIO=dat;
	Delay1ms(1);
	E=1;
	Delay1ms(1);
	E=0;	
}

void LCD_Init()
{
	LCD_Write_Com(0x38);
	LCD_Write_Com(0x0c);
	LCD_Write_Com(0x06);	
	LCD_Write_Com(0x01);
	LCD_Write_Com(0x80);
}