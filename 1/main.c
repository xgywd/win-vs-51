#include <reg52.h>
#include <LCD.h>
#include <DS1302.h>


 code unsigned char write_rtc_address[7]={0x8c,0x8a,0x88,0x86,0x84,0x82,0x80};
 code unsigned char read_rtc_address[7]={0x8d,0x8b,0x89,0x87,0x85,0x83,0x81};
char time[7]={16,5,7,22,11,25,32};
void LCD_display();

void main()
{
	LCD_Init();
	RTC_Set();

	while(1)
	{
		Read_Time();
		LCD_display();
	}
}

void LCD_display()
{
	LCD_Write_Com(0x80+40);
	LCD_Write_Dat('0'+time[2]/16);	 	 
	LCD_Write_Dat('0'+time[2]%16);
	LCD_Write_Dat('-');
	LCD_Write_Dat('0'+time[1]/16);
	LCD_Write_Dat('0'+time[1]%16);
	LCD_Write_Dat('-');
	LCD_Write_Dat('0'+time[0]/16);
	LCD_Write_Dat('0'+time[0]%16);

	LCD_Write_Com(0x80);
    LCD_Write_Dat('2');
	LCD_Write_Dat('0');
	LCD_Write_Dat('0'+time[6]/16);
	LCD_Write_Dat('0'+time[6]%16);
	LCD_Write_Dat('-');
	LCD_Write_Dat('0'+time[4]/16);
	LCD_Write_Dat('0'+time[4]%16);
	
	LCD_Write_Com(0x8E);
	LCD_Write_Dat('0'+time[5]);//

}