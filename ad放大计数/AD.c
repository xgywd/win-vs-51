#include <reg52.h> 
#define Segment P0
#define sl P2 
sbit clear=P1^3;
sbit fp2=P1^2;    //定义数据端口地址，0时分频处理，1时不分频
unsigned char count;      //定时 1s 计数 
unsigned char d[4];       //对应数码管的各位 
unsigned char dangwei;    //档位 
unsigned int timeN;       //不同档位计时值 
unsigned int fCount;      //脉冲下降沿次数 
unsigned int regCount;    //脉冲次数暂存 
unsigned int pCount;      //频率显示 

unsigned char Num[10]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90}; //七段数码管代码	共阳极
void Delay(unsigned int DelayTime) 
{
   while(DelayTime--);
}
  
void dispbuf() 
{ 
 { 
  if(dangwei==0)     //档位
    { 
     d[3]=0; 
     d[2]=pCount/100; 
     d[1]=(pCount%100)/10; 
     d[0]=pCount%10; 
     
     sl=0x01;Delay(1);Segment=Num[d[3]];Delay(200);   
     sl=0x02;Delay(1);Segment=Num[d[2]];Delay(200);
     sl=0x04;Delay(1);Segment=Num[d[1]];Delay(200);
     sl=0x08;Delay(1);Segment=Num[d[0]];Delay(200); 
    }
   else if(dangwei==1) 
    { 
       d[3]=pCount/1000;
       d[2]=(pCount%1000)/100; 
       d[1]=(pCount%100)/10; 
       d[0]=pCount%10; 

       sl=0x01;Delay(1);Segment=Num[d[3]];Delay(200);       
       sl=0x02;Delay(1);Segment=Num[d[2]];Delay(200);  
       sl=0x04;Delay(1);Segment=Num[d[1]]&0x7f;Delay(200); //带小数点 
       sl=0x08;Delay(1);Segment=Num[d[0]];Delay(200); 
    }  
else 
  { 
    d[3]=0;
    d[2]=0; 
    d[1]=0; 
    d[0]=0; 
  }
 } 
}



void intial()
  {
   clear=1;           //分频器初始化
   fp2=1;
   timeN=20;          //档位初始化为 Hz 档
   dangwei=0; 
   TMOD=0x51;       //定时器0，工作方式1，计数器1，工作方式1
   TH0= (65536-50000)/256; 
   TL0= (65536-50000)%256; 
						
						//计数器1计数初值
   TH1=0xff;         // 256-1;       
   TH1=0xff;         // 256-1;
   TR0=1;           //开定时器0中断 
   ET0=1;           //定时器0允许 
   TR1=1;           //开计数器1中断 
   ET1=1;           //允许计数器1中断
   EA=1;            //总中断允许
  } 
  
  
  
void main() 
  { 
	intial(); 
    while(1) 
       { 
	  dispbuf();
       } 
  }
 void timer0() interrupt 1
 {
  {
   count++; 
   if(count==timeN) 
    {
     ET1=0;      //计时1s，暂停外部计数1
     TR1=0;
     count=0;
    regCount=fCount;        //更新显示
     fCount=0;               //频率计数清零
     clear=0;                //硬件分频器清零
     clear=1; 
    }  
  if(dangwei==0)          //档位切换
  { 
    pCount=regCount;
    if(regCount>999) 
    {
      pCount=0;              //显示清零
      dangwei=1;
      timeN=1;               //定时 50ms
      fp2=0;                 //硬件分频处理
      TH1=0xfb;              //50分频 256-5 
      TL1=0xfb;              //256-5
      pCount=regCount*10;    //换算成相应的显示：f=regCount*100
    } 
  }
  else if(dangwei==1) 
   {
    if(regCount<1) 
     { 
      dangwei=0; 
      timeN=20;             //定时 1s 
      fp2=1;                //不分频 
      TH1=0xff;             //256-1 
      TL1=0xff;             //256-1
     } 
    else if(regCount<1000)       //KHz 档 
     {
      dangwei=1;
      timeN=1;               //定时 50ms
      fp2=0;                 //硬件分频处理
      TH1=0xfb;              //50分频 256-5 
      TL1=0xfb;              //256-5
      pCount=regCount*10;    //换算成相应的显示：f=regCount*100
     } 
    else 
{   
 dangwei=3;        //超出范围
     }
  }
  ET1=1;               //恢复外部计数 1 
  TR1=1; 
 } 
   TH0=(65536-50000)/256; 
   TL0=(65536-50000)%256; 
 }
 
 
 
void enterFre() interrupt 3       //外部频率输入 
{ 
   TH1=0xff;         // 256-1;       
   TH1=0xff;         // 256-1;
	fCount++;
}