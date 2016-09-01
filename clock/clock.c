/*本程序做为单片机时钟的控制程序.*/


/******************************头文件加载与宏定义**************************************************/
#include <reg52.h>                 
																		/*用于声明特殊功能寄存器的名称.
																			如果没有这个头文件，特殊功能寄存器，只能用硬件的地址进行读写操作。*/

typedef  unsigned int uint;
typedef  unsigned char uchar;
/******************************声明全局函数和变量*********************************************************/
/*此处增加其它全局声明*/
char shi=0;
char fen=0;
char miao=0;
char flag=0;

uchar pulse_num=0;	/*时间脉冲50毫秒一次*/
uchar pulse_dly=0;

void delay(uint i);  /*延时函数*/
void gettime();		/*获取时间函数*/

void seting();    //设置按钮反应函数
void show();			//显示函数

void key();				//检测按键1与2的函数


sbit save=P1^3;     //573与138的锁存开关 
sbit key1=P3^0;
sbit key2=P3^1;


uchar code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};/* 共阴数码管显示段编码0-f*/
uchar table1[]={0x00,0x00,0x40,0x00,0x00,0x40,0x00,0x00};										/*显示缓存*/
//uchar code table2[]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07};										/*8位一体数码管 位选编码*/

/**************************************主函数*************************************************/
void main()
{
	/*C51所有变量声明必须在代码段前*/
	
	
	/*此处增加其它局部声明*/
	
/************************************定时器初始化***************************************************/
	
	TMOD=0x11;		/*0000 0001   TMOD 是计时器工作方式寄存器,有8位
	
									高四位设置定时器1.低四位定时器0. 两者设置相同.
									
									低四位0001 
									低两位01 代表方式1:16位寄存器
									{00	代表方式0:13位寄存器(高8,低5).
									10	代表方式3:8位自动重装定时:高8位溢出后,	
									低8位数值自动装入高8位做为初值.
									11	代表方式4:分为两个单独的8位定时/计数器}. 
									最高位0代表:GATE位(0不受中断控制,1受中断控制),
									第二位代表:CT位(选择0为定时器,选择1为计数器)*/
	/*********************************定时器加载初值******************************************************/
	
	TH0=(65536-50000)/256;	/*定时器0是由两个8位寄存器TH0与TL0组成,
							  定时器初值计算方法为65536减去定时间隔除以256放入高8位,*/
	TL0=(65536-50000)%256;	/*再用65536减去定时间隔取余256放入低8位*/
	
	TH1=(65536-1000)/256;
	
	TL1=(65536-1000)%256;
	/**********************************开中断*****************************************************/
	
	EA=1;	//开总中断
	ET0=1; //开定时器0中断
	TR0=1;	//启动定时器0
	ET1=1;	//开定时器1中断
	TR1=1;	//启动定时器1
	
	EX0=1;   //开外部中断0
	IT0=1;	//设置中断方式为下降沿.
	
	/***************************************************************************************/
		P1=0;
		P2=0;
	while(1)
	{
		if(flag)
		{
			seting();
		}
		
		gettime();
		
		show();
	}
}




void time() interrupt 1
{
	TH0=(65536-50000)/256;	/*因为计时器溢出,数据清零,所以要恢复计时器初值*/
	TL0=(65536-50000)%256;	
	pulse_num++;

}


void delaytime() interrupt 3
{
	TH1=(65536-1000)/256;
	
	TL1=(65536-1000)%256;
	
	pulse_dly++;
}


void init0() interrupt 0
{
	flag++;
	if(4==flag)
	{
		flag=0;
	}
}


void delay(uint i)
{
	pulse_dly=0;
	while(i!=pulse_dly);
}


void gettime()
{
	
	if(20==pulse_num)
	{
		miao++;
		if(60==miao)
		{
			miao=0;
			fen++;
			if(60==fen)
			{
				fen=0;
				shi++;
				if(24==shi)
				{
					shi=0;
				}
			}
		}
		pulse_num=0;
	}
}

void seting()
{
	uint k=0;
	uchar i,j,h;
			
	while(1)
	{
		k++;
		key();
		if (!flag)
		{
			pulse_num=0;
			return;
			
		}
		
			
		if(40==k)
		{
			switch (flag)
			{
				case 1:
						j=table1[7];
						h=table1[6];
						table1[7]=0x00;
						table1[6]=0x00;
						break;
				case 2:	
						j=table1[4];
						h=table1[3];
						table1[4]=0x00;
						table1[3]=0x00;
						break;
				case 3:
						j=table1[1];
						h=table1[0];
						table1[1]=0x00;
						table1[0]=0x00;
						break;
				
			}
		
			
		}
		if (80==k)
		{
			
			switch (flag)
			{
				case 1:
						table1[7]=j;
						table1[6]=h;
						k=0;
						break;
				case 2:	
						table1[4]=j;
						table1[3]=h;
						k=0;
						break;
				case 3:
						table1[1]=j;
						table1[0]=h;
						k=0;
			}			break;
		}
		
		for(i=0;i<8;i++)
		{
			P1=i;				//位选   573关闭 138关闭
			
			P2=table1[i];				//段选	设置显示的数字
			save=1;							//573LE 138 打开
			delay(1);
		}
	}		
		
}

void key()
{
	
	P3=0xff;
	
	
	if (!key1)
	{
		delay(5);
		if (!key1)
		{
			switch (flag)
			{
				case 1:
					shi++;
					if(shi>23)
					{
						shi=0;
					}
					break;
				case 2:
					fen++;
					if(fen>59)
					{
						fen=0;
					}
					break;
				case 3:
					miao++;
					if(miao>59)
					{
						miao=0;
					}
					break;
			}
		}
		
		while(!key1)
		{
			show();
		}
		delay(5);
		while (!key1)
		{
			show();
		}
	}
	
	P3=0xff;
	
	if (!key2)
	{
		delay(5);
		if (!key2)
		{
			switch (flag)
			{
				case 1:
					shi--;
					if(shi<0)
					{
						shi=23;
					}
					break;
				case 2:
					fen--;
					if(fen<0)
					{
						fen=59;
					}
					break;
				case 3:
					miao--;
					if(miao<0)
					{
						miao=59;
					}
					break;
			}
		}
		
		while(!key2)
		{
			show();
		}
		delay(5);
		while (!key2)
		{
			show();
		}
	}
	
}


void show()
{
	uchar i;
	
	table1[7]=table[shi/10];
	table1[6]=table[shi%10];
	table1[4]=table[fen/10];
	table1[3]=table[fen%10];
	table1[1]=table[miao/10];
	table1[0]=table[miao%10];
	
	for(i=0;i<8;i++)
	{
		P1=i;				//位选   573关闭 138关闭
		
		P2=table1[i];				//段选	设置显示的数字
		save=1;							//573LE 138 打开
		delay(1);
	}
}






