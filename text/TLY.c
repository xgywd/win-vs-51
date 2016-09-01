#include <p18f2525.h>
#include <math.h>
#include <string.h> 
#define uchar unsigned char
#define uint unsigned int

//^^^^^^^^^^^^^^^^^^^^^配置位的软件设置^^^^^^^^^^^^^^^^^^^^^^//
#pragma config WDT = OFF     //看门狗禁止
#pragma config OSC = HS      //晶振
#pragma config LVP = OFF     //低电压编程禁止


float Acc[3],Gyr[3],Mag[3],rpy[3];
float ROLL,PITCH,YAW;
unsigned char Re_buf[11];
unsigned char sign;
unsigned char counter=0;


//********串口函数声明*******// 
void USART_Init(void);
void UartData(char dat);
void UartSend(uchar *ptr,unsigned char length);
void UartInit(void);
void UartReceive();

void delayms(unsigned char time)   //延时函数
{
	unsigned char i;
	unsigned char s;
	for(s=time;s<0;s--)
	for(i=192;i;i--);
}

//^^^^^^^^^^^^^^^^^^^^^单片机串口初始化^^^^^^^^^^^^^^^^^^^^^^//
void UartInit(void)		   
{
	TRISCbits.TRISC7=1;			//IO方向初始化RC7、RC6口设置为输入
	TRISCbits.TRISC6=1;	
	PIE1bits.RCIE=0;		   //关闭接收使能RCIE
	RCSTA=0x00;				   //关闭串行端口
	PIE1bits.RCIE=1;		   //串口接收中断
	PIE1bits.TXIE=1;		   //串口发送中断	
	RCSTA=0x90;				   //使能串行端口，使能连续接收
	TXSTA=0x24;				   //使能发送，高速波特率	
	SPBRG=51;				   //设置波特率寄存器X=51，波特率为9600；波特率=Fosc/[16(X+1)]
	INTCON=0xC0;			   //全局中断GIE打开；使能外部中断PEIE
}
//^^^^^^^^^^^字节发送函数^^^^^^^^^^^^^^^^^^^//
void UartData(char dat)
{
	TXREG=dat;
	while(TXSTAbits.TRMT==0);
}
//^^^^^^^^^^^字符串发送函数^^^^^^^^^^^^^^^^^^^//
void UartSend(unsigned char *ptr,unsigned char length)    //*s^^^^ptr
{
	int i=0;
	while(i<length)
	{
		UartData(*(ptr+i));
		i++;
	}
} 

//*******************串口中断********************//
void UartReceive(void) 
{
	if(PIR1bits.RCIF&&PIE1bits.RCIE)

{
	PIR1bits.RCIF=0;
		 Re_buf[counter]=RCREG;
	    // if(counter==0&&Re_buf[0]!=0x5A&&counter==1&&Re_buf[1]!=0x5A) return;      //第0号和1号数据不是帧头
	      
	      counter++;                                                                //如果是帧头则开始计数
	      
	      if(counter==10)             //接收到11个数据
	      {    
	         counter=0;               //重新赋值，准备下一帧数据的接收 
	         
	         sign=1;
	   
	      }
	     
	  }
	  
}	  

void main(void)
{
 
   	    TRISBbits.TRISB3=0;
		PORTBbits.RB3=1;
		TRISBbits.TRISB4=0;
		PORTBbits.RB4=1;
		//delayms(50);
        UartInit(); 
   while(1)
   {     
      if(sign)
	   {
		sign=0;
         if(Re_buf[0]==0x5A&&Re_buf[1]==0x5A)      //检查帧头
      	{  
			switch(Re_buf[2])
			{
			case 0x15:          //三轴加速度
			{
			Acc[0]=((short)(Re_buf[4]<<8|Re_buf[5]))/16383.0;
		    Acc[1]=((short)(Re_buf[4]<<8|Re_buf[5]))/16383.0;
			Acc[2]=((short)(Re_buf[4]<<8|Re_buf[5]))/16383.0;
		
			}
			break; 

			case 0x25:         //陀螺仪数据
			{
			Gyr[0]=((short)(Re_buf[4]<<8|Re_buf[5]))/16383.0;
			Gyr[1]=((short)(Re_buf[6]<<8|Re_buf[7]))/16383.0;
			Gyr[2]=((short)(Re_buf[8]<<8|Re_buf[9]))/16383.0;
	
			}
			break;

		//	case 0x35:         //磁力计数据
			//{
		//	Mag[0]=((short)(Re_buf[4]<<8|Re_buf[5]))/16383.0;
		//	Mag[1]=((short)(Re_buf[6]<<8|Re_buf[7]))/16383.0;
		//	Mag[2]=((short)(Re_buf[8]<<8|Re_buf[9]))/16383.0;
	
		//	}
			break;
			
			case 0x45:          //欧拉角数据
			{
			ROLL=((short)(Re_buf[4]<<8|Re_buf[5]))/16383.0*100;
			PITCH=((short)(Re_buf[6]<<8|Re_buf[7]))/16383.0*100;
			YAW=((short)(Re_buf[8]<<8|Re_buf[9]))/16383.0*100;
			rpy[0]=ROLL;
			rpy[1]=PITCH;
			rpy[2]=YAW;
	
			}
			break;
			
			
			
			
		
			/*
			
			case 0x65:            //四元数数据
			{
			Q[0]=((short)(Re_buf[0]<<8|Re_buf[1]))/16383.0*10000;
			Q[1]=((short)(Re_buf[2]<<8|Re_buf[3]))/16383.0*10000;
			Q[2]=((short)(Re_buf[4]<<8|Re_buf[5]))/16383.0*10000;
			Q[3]=((short)(Re_buf[6]<<8|Re_buf[7]))/16383.0*10000;
			}
			break;	
			
			*/	
	          }		
     	  }
      }
   }
}