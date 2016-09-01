#include <reg51.h>
#include <intrins.h>
#define LCD_GPIO P0
sbit DSIO=P3^4;
sbit RST=P3^5;
sbit SCLK=P3^6;

sbit E=P2^7;
sbit RW=P2^5;
sbit RS=P2^6;


code unsigned char write_rtc_address[7]={0x80,0x82,0x84,0x86,0x88,0x8a,0x8c};
code unsigned char read_rtc_address[7]={0x81,0x83,0x85,0x87,0x89,0x8b,0x8d};

unsigned char tmp_date[]={0,8,23,20,7,3,16};

void Write_DS1302(unsigned char address,unsigned char dat);

unsigned char Read_DS1302(unsigned char address);

void LcdDisplay();

void Set_RTC();

void Delay1ms(unsigned int c)
{
	unsigned char a,b;
	for(;c>0;c--)
	{
		for(b=199;b>0;b--)
		{
			for(a=1;a>0;a--)
			;
		}
	}
}

void LCDWrite_com(unsigned char com)
{	
	E=0;
	RS=0;
	RW=0;

	LCD_GPIO=com;
	Delay1ms(1);
	E=1;
	Delay1ms(5);
	E=0;

}
 
void LCD_Init()
{
	LCDWrite_com(0x38);
	LCDWrite_com(0x0c);
	LCDWrite_com(0x06);	
	LCDWrite_com(0x01);
	LCDWrite_com(0x80);
}

void LCDWrite_Data(unsigned char dat)
{
	E=0;
	RS=1;
	RW=0;
	LCD_GPIO=dat;
	Delay1ms(1);
	E=1;
	Delay1ms(5);
	E=0;
}

void Write_DS1302(unsigned char addr,unsigned char dat)
{
	unsigned char n;
	RST=0;
	_nop_();

	SCLK=0;
	_nop_();
	RST=1;
	_nop_();

	for(n=0;n<8;n++)
	{
		DSIO=addr&0x01;
		addr>>=1;
		SCLK=1;
		_nop_();
		SCLK=0;
		_nop_();
	}
	for(n=0;n<8;n++)
	{
		DSIO=dat&0x01;
		dat>>=1;
		SCLK=1;
		_nop_();
		SCLK=0;
		_nop_();
	}

	RST=0;
	_nop_();

}

unsigned char Read_DS1302(unsigned char addr)
{
	unsigned char n,dat;
	RST=0;
	_nop_();
	
	SCLK=0;
	_nop_();
	RST=1;
	_nop_();

	for(n=0;n<8;n++)
	{
		DSIO=addr&0x01;
		addr>>=1;
		SCLK=1;
		_nop_();
		SCLK=0;
		_nop_();
	}
	_nop_();

	for(n=0;n<8;n++)
	{	 
	
		if(DSIO)
		{	
	
			dat|=0x80;
			SCLK=0;
			dat>>=1;

			_nop_();  			

			SCLK=1;	
			_nop_();
		}
	
		else
		{
			dat>>=1;

			SCLK=0;
			_nop_();  			

			SCLK=1;	
			_nop_();
		}

	}

	RST=0;
	_nop_();

	SCLK=1;
	_nop_();

	DSIO=0;
	_nop_();

	DSIO=1;
	_nop_();

	return dat;
			
}

void Set_RTC(void)
{
	unsigned char i,*p,tmp;
	for(i=1;i<7;i++)
	{
		tmp=tmp_date[i]/10;
		tmp_date[i]=tmp_date[i]%10;
		tmp_date[i]+=tmp*16;
	}

	Write_DS1302(0x8E,0x00);

	p=write_rtc_address;
	for(i=0;i<7;i++)
	{
		Write_DS1302(*p,tmp_date[i]);
		p++;
	}

	Write_DS1302(0x8E,0x80);


}



void Ds1302Init()
{

	Write_DS1302(0x8E,0x00);	  //禁止写保护，就是关闭写保护功能


	Set_RTC();		 



}

void Ds1302ReadTime()
{
	unsigned char n;
	for (n=0; n<7; n++)//读取7个字节的时钟信号：分秒时日月周年
	{
		tmp_date[n] = Read_DS1302(read_rtc_address[n]);
	}		
}


void main()
{
	LCD_Init();
	Ds1302Init();
	while(1)
	{
   	    Ds1302ReadTime();
		LcdDisplay();

	}
	
}
/*******************************************************************************
* 函数名         : LcdDisplay()
* 函数功能		   : 显示函数
* 输入           : 无
* 输出         	 : 无
*******************************************************************************/

void LcdDisplay()
{
	LCDWrite_com(0x80+0x40);
	LCDWrite_Data('0'+tmp_date[2]/16);				//时
	LCDWrite_Data('0'+(tmp_date[2]&0x0f));				 
	LCDWrite_Data('-');
	LCDWrite_Data('0'+tmp_date[1]/16);				//分
	LCDWrite_Data('0'+(tmp_date[1]&0x0f));	
	LCDWrite_Data('-');
	LCDWrite_Data('0'+tmp_date[0]/16);				//秒
	LCDWrite_Data('0'+(tmp_date[0]%16));//&0x0f);

	LCDWrite_com(0x80);
	LCDWrite_Data('2');
	LCDWrite_Data('0');
	LCDWrite_Data('0'+tmp_date[6]/16);			//年
	LCDWrite_Data('0'+(tmp_date[6]&0x0f));
	LCDWrite_Data('-');
	LCDWrite_Data('0'+tmp_date[4]/16);			//月
	LCDWrite_Data('0'+(tmp_date[4]&0x0f));
	LCDWrite_Data('-');
	LCDWrite_Data('0'+tmp_date[3]/16);			//日
	LCDWrite_Data('0'+(tmp_date[3]&0x0f));
	LCDWrite_com(0x8D);
	LCDWrite_Data('0'+(tmp_date[5]&0x07));	//星期			 
}

