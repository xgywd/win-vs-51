#ifndef LCD_CHAR_1602_2005_4_9
#define LCD_CHAR_1602_2005_4_9
#define uchar unsigned char
#define uint unsigned int

sbit lcdrs = P2^0;   
sbit lcdrw = P2^1;
sbit lcden = P2^2;

void delay(uint z)		  //延时函数，此处使用晶振为11.0592MHz
{
    uint x,y;

    for(x=z;x>0;x--)
	{
        for(y=110;y>0;y--)
		{
		  ;
		}
    }
}

void write_com(uchar com)   //写入指令数据到 lcd
{ 
    lcdrw=0;
    lcdrs=0;
    P3=com;
    delay(5);
    lcden=1;
    delay(5);
    lcden=0;
}

void write_data(uchar date) 	//写入字符显示数据到 lcd
{	
    lcdrw=0;
    lcdrs=1;
    P3=date;
    delay(5);
    lcden=1;
    delay(5);
    lcden=0;
}

void init1602()		//1602液晶初始化设定
{
    lcdrw=0;
    lcden=0;
    write_com(0x3C);
    write_com(0x0c);
    write_com(0x06);
    write_com(0x01);
    write_com(0x80);
}

#endif