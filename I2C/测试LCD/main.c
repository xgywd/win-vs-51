#include <reg52.h>                //�����������⹦�ܼĴ���������.
														//	���û�����ͷ�ļ������⹦�ܼĴ�����ֻ����Ӳ���ĵ�ַ���ж�д������
#include <intrins.h>							//��ָ��Ȳ���	

#include "lcd.h"								//lcd1602����ģ��
#include "i2c.h"								//i2c ����ģ��
#include "ds1302.h"							//ds1302����ģ��

//���벿��
uchar prin[15]={0};
void time_show();
void main()
{		
	
		
   	init_lcd();
	
		init_i2c();
	
//		write_add(3,'a');
//		delay(1);
//		p[0]=read_add(3);
//		cls();
//		lcdprintf(p,1);
//		set_time();
		read_time(prin);
		time_show();
		while(1);
}

void time_show()
{
	cls();
					
	lcdprintf(prin,2);		//��������ʱ����

	
}