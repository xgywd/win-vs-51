
#include <reg52.h>
#include <intrins.h>

sbit SDA=P3^4;
sbit RST=P3^5;
sbit SCLK=P3^6;

extern  char time[7];
extern  code unsigned char write_rtc_address[7];
extern  code unsigned char read_rtc_address[7];

void DS1302_Write_Byte(char dat)
{
	char n;
	
	for(n=0;n<8;n++)
	{
		SCLK=0;
		SDA=dat&0x01;  //1010 0010  & 0000 0001
		dat>>=1;
		SCLK=1;
	}
	SDA=1;
}

void DS1302_Write(char addr,char dat)
{
	RST=0;
	_nop_();
	_nop_();
	RST=1;
	_nop_();
	_nop_();
	DS1302_Write_Byte(addr);
	DS1302_Write_Byte(dat);
	RST=0;
	_nop_();
	_nop_();
}

char DS1302_Read(char addr)
{
	  char n=0;
	  char dat=0;
	 	RST=0;
		_nop_();
		_nop_();
		RST=1;
		_nop_();
		_nop_();
		DS1302_Write_Byte(addr);
	
	  for(n=0;n<8;n++)
	  {	 
	    dat>>=1;
			SCLK=0;	
			if(SDA)
				{
					dat|=0x80;       //0000 0000  | 1000 0000
				}
				 SCLK=1;
				_nop_();
			}		 

	  RST=0;
	  _nop_();
			_nop_();
	  SCLK=0;
	  _nop_();
			_nop_();
		SCLK=1;
	  SDA=1;
	  return dat;

}

void RTC_Set() //初始，把time数组元素变成BCD码,并读给DS1302
{
	unsigned char i,tmp;
	
	for(i=0;i<7;i++)
	{
		tmp=time[i]/10;
		time[i]=time[i]%10;
		time[i]=tmp*16+time[i];
	}
	DS1302_Write(0x8E,0x00);
	
	
	for(i=0;i<7;i++)
	{
		DS1302_Write(write_rtc_address[i],time[i]);
	}	
	
	DS1302_Write(0x8e,0x80);
}

void Read_Time()	   //从DS1302读出当前时间的BCD码
{
	int i;
	
	for(i=0;i<7;i++)
	{
	  	time[i]=DS1302_Read(read_rtc_address[i]);
	}
}

