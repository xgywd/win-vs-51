/**************************************头文件**********************************************/

#include<reg52.h>						//包含文件REG52.H,将此文件作为头文件放入该程序

/**************************************宏定义**********************************************/

#define uint unsigned int				//由预处理器做替代，把程序中所有的词替代
#define uchar unsigned char				//替换完毕再编译

/**************************************位定义**********************************************/

sbit wr=P3^6;							//定义特殊功能寄存器P3.6位变量为wr
sbit rd=P3^7;							//定义特殊功能寄存器P3.7位变量为rd
sbit dula=P3^4;							//定义位变量dula，段码锁存控制
sbit wela=P3^5;							//定义位变量wela，位码锁存控制

/************************************字符定义**********************************************/

uchar code duanma[]={					 //定义一个无符号字符串duanma[]存入ROM
0x3f,0x06,0x5b,0x4f,					 //用于共阴极数码管段码的数据表格
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71};

uchar code weima[]={					//定义一个无符号字符串weima[]存入ROM
0xfe,0xfd,0xfb,0xf7,					//用于共阴极数码管位码的数据表格
0xef,0xdf,0xbf,0x7f};					//按照数码管的排列编码，发光取低电平，熄灭取高电平

uint temp;								 //定义无符号整型变量temp，用于采集数字信号数据

/************************************字符定义**********************************************/

void delay(uint z)						//延时函数，无符号整型，形参，局部变量
{										
	uint x,y;							//无符号整型，实参，局部变量
	for(x=z;x>0;x--)					//for循环   for（表达式1；表达式2；表达式3）{语句}
		for(y=248;y>0;y--);				//for循环嵌套函数，计算次数x乘以y，达到延时目的
		//执行过程；1.求解表达式1
		//2.求解表达式2，若其值为真（非0即为真），
		//则执行for语句，然后执行第三步，否则结束for语句，直接跳出，不再执行第三步。
		//3.求解表达式3	          4.跳到第二步重复执行
}

/************************************显示函数**********************************************/

void display(uint num)	               //无返回值，无符号整型，形参，局部变量
{
		uchar ge,_ge,_shi;			   //定义局部变量，形参，用于分解
		float num1;					   //定义无符号整型，用于数据计算
		num1=(num*19.61f)/10;					   //按比例求值
		ge=(int)num1/100;				  //num1分解出百位作为个位 
		_ge=(int)num1%100/10;			  //分解出十位作为小数点后一位
		_shi=(int)num1%10;				  //分解出个位作为小数点后第二位

		P1=duanma[ge]+0x80;			  //输出个位，后加小数点
        dula=1;						  //打开段码锁存，proteus仿真要先赋值，再打开锁存
		dula=0;						  //关闭段码锁存
		P1=weima[5];				  //输出位码
		wela=1;					  	//打开位码锁存
		wela=0;						  //关闭位码锁存
		delay(1);					  //延时，给出显示时间
		P1=0xff;					  //消隐，作为位码
		wela=1;						  //打开位码锁存
		wela=0;						  //关闭位码锁存

		P1=duanma[_ge];				  //微观上讲，是一个接着一个亮一段时间然后熄灭
        dula=1;						  //通过快速依次地扫描超过肉眼分辨速度
		dula=0;						  //让人认为是同时显示
		P1=weima[6];
		wela=1;
		wela=0;
		delay(1);
		P1=0xff;
		wela=1;
		wela=0;


		P1=duanma[_shi];
        dula=1;
		dula=0;
		P1=weima[7];
		wela=1;
		wela=0;
		delay(1);
		P1=0xff;
		wela=1;
		wela=0;

}

/************************************启动函数**********************************************/

void start()						//启动ADC0804的A/D转换，为外部写数据控制信号
{
	wr=1;							//先给高电平，再低电平，再高电平
	wr=0;							//此信号的上升沿可以启动
	wr=1;
}

/************************************主函数**********************************************/

void main()						 //主函数无返回值
{	
	P0=0xff;			//根据寄存器口两线相接，“与”的特性，P0口都置1，准备接收数据
	while(1)
	{		start();			 //启动A/D转换
			delay(1);			 //等待转换结束，转换时间大约100us
			rd=0;				 //给ADC0804的RD脚低电平，使其转换完成的数据加载到DB口
			delay(1);			 //等待数据加载到DB口，连接在P0口
			temp=P0;			 //将P0数据赋给temp
			rd=1;				 //关闭加载	
			display(temp);		  //将计算的结果显示出来
	 }
}