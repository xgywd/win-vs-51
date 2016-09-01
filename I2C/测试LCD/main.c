#include <reg52.h>                //用于声明特殊功能寄存器的名称.
														//	如果没有这个头文件，特殊功能寄存器，只能用硬件的地址进行读写操作。
#include <intrins.h>							//空指令等操作	

#include "lcd.h"								//lcd1602驱动模块
#include "i2c.h"								//i2c 驱动模块
#include "ds1302.h"							//ds1302驱动模块

//代码部分
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
					
	lcdprintf(prin,2);		//年周月日时分秒

	
}