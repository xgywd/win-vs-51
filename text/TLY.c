#include <p18f2525.h>
#include <math.h>
#include <string.h> 
#define uchar unsigned char
#define uint unsigned int

//^^^^^^^^^^^^^^^^^^^^^����λ���������^^^^^^^^^^^^^^^^^^^^^^//
#pragma config WDT = OFF     //���Ź���ֹ
#pragma config OSC = HS      //����
#pragma config LVP = OFF     //�͵�ѹ��̽�ֹ


float Acc[3],Gyr[3],Mag[3],rpy[3];
float ROLL,PITCH,YAW;
unsigned char Re_buf[11];
unsigned char sign;
unsigned char counter=0;


//********���ں�������*******// 
void USART_Init(void);
void UartData(char dat);
void UartSend(uchar *ptr,unsigned char length);
void UartInit(void);
void UartReceive();

void delayms(unsigned char time)   //��ʱ����
{
	unsigned char i;
	unsigned char s;
	for(s=time;s<0;s--)
	for(i=192;i;i--);
}

//^^^^^^^^^^^^^^^^^^^^^��Ƭ�����ڳ�ʼ��^^^^^^^^^^^^^^^^^^^^^^//
void UartInit(void)		   
{
	TRISCbits.TRISC7=1;			//IO�����ʼ��RC7��RC6������Ϊ����
	TRISCbits.TRISC6=1;	
	PIE1bits.RCIE=0;		   //�رս���ʹ��RCIE
	RCSTA=0x00;				   //�رմ��ж˿�
	PIE1bits.RCIE=1;		   //���ڽ����ж�
	PIE1bits.TXIE=1;		   //���ڷ����ж�	
	RCSTA=0x90;				   //ʹ�ܴ��ж˿ڣ�ʹ����������
	TXSTA=0x24;				   //ʹ�ܷ��ͣ����ٲ�����	
	SPBRG=51;				   //���ò����ʼĴ���X=51��������Ϊ9600��������=Fosc/[16(X+1)]
	INTCON=0xC0;			   //ȫ���ж�GIE�򿪣�ʹ���ⲿ�ж�PEIE
}
//^^^^^^^^^^^�ֽڷ��ͺ���^^^^^^^^^^^^^^^^^^^//
void UartData(char dat)
{
	TXREG=dat;
	while(TXSTAbits.TRMT==0);
}
//^^^^^^^^^^^�ַ������ͺ���^^^^^^^^^^^^^^^^^^^//
void UartSend(unsigned char *ptr,unsigned char length)    //*s^^^^ptr
{
	int i=0;
	while(i<length)
	{
		UartData(*(ptr+i));
		i++;
	}
} 

//*******************�����ж�********************//
void UartReceive(void) 
{
	if(PIR1bits.RCIF&&PIE1bits.RCIE)

{
	PIR1bits.RCIF=0;
		 Re_buf[counter]=RCREG;
	    // if(counter==0&&Re_buf[0]!=0x5A&&counter==1&&Re_buf[1]!=0x5A) return;      //��0�ź�1�����ݲ���֡ͷ
	      
	      counter++;                                                                //�����֡ͷ��ʼ����
	      
	      if(counter==10)             //���յ�11������
	      {    
	         counter=0;               //���¸�ֵ��׼����һ֡���ݵĽ��� 
	         
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
         if(Re_buf[0]==0x5A&&Re_buf[1]==0x5A)      //���֡ͷ
      	{  
			switch(Re_buf[2])
			{
			case 0x15:          //������ٶ�
			{
			Acc[0]=((short)(Re_buf[4]<<8|Re_buf[5]))/16383.0;
		    Acc[1]=((short)(Re_buf[4]<<8|Re_buf[5]))/16383.0;
			Acc[2]=((short)(Re_buf[4]<<8|Re_buf[5]))/16383.0;
		
			}
			break; 

			case 0x25:         //����������
			{
			Gyr[0]=((short)(Re_buf[4]<<8|Re_buf[5]))/16383.0;
			Gyr[1]=((short)(Re_buf[6]<<8|Re_buf[7]))/16383.0;
			Gyr[2]=((short)(Re_buf[8]<<8|Re_buf[9]))/16383.0;
	
			}
			break;

		//	case 0x35:         //����������
			//{
		//	Mag[0]=((short)(Re_buf[4]<<8|Re_buf[5]))/16383.0;
		//	Mag[1]=((short)(Re_buf[6]<<8|Re_buf[7]))/16383.0;
		//	Mag[2]=((short)(Re_buf[8]<<8|Re_buf[9]))/16383.0;
	
		//	}
			break;
			
			case 0x45:          //ŷ��������
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
			
			case 0x65:            //��Ԫ������
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