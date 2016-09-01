#include<reg52.h>
#include <intrins.h>
#define uchar unsigned char
#define uint  unsigned int
#define Delay4us(){_nop_();_nop_();_nop_();_nop_();}
sbit SCL=P2^6;
sbit SDA=P2^7;
sbit LC=P2^0;

uchar Recv_Buffer;
uchar code table[]={0xc0,0xf9,0xa4,0xb0, 0x99,0x92,0x82,0xf8, 0x80,0x90,0x8c,0xff} ;  //不加点
uchar code table1[]={0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10,0x0c,0xff};   //加点
uint Voltage[]={'0','0','0','0'}; 
bit bdata IIC_ERROR;
uchar num[4];
void delay(uint ms)
{
uchar i;
while(ms--)
for(i=0;i<120;i++);
}

void Display_Result() //不带点
{
P3=0xef;//千位
P0=table[num[3]];
delay(5);
P3=0xdf;//百位
P0=table1[num[2]];
delay(5);
P3=0x7f;//十位
P0=table[num[1]];
delay(5);
P3=0xbf;//个位
P0=table[num[0]];
delay(5);
}
void Display_Result1() //带点
{
P3=0xef;//千位
P0=table[num[3]];
delay(5);
P3=0xdf;//百位
P0=table[num[2]];
delay(5);
P3=0x7f;//十位
P0=table[num[1]];
delay(5);
P3=0xbf;//个位
P0=table[num[0]];
delay(5);
}
void init()
{
EA=1;
TMOD=0x01;
TH0=(65536-150)/256;
TL0=(65536-150)%256;
ET0=1;
TR0=1;
}
void Convert_To_Voltage(uchar val)
{        
        uchar Tmp,Tmp1; 
        val=val*1.28;                 
        Voltage[2]=val/100;           //整数部分
        Tmp=val%100;                  // 第一位小数
        Voltage[1]=Tmp*10/100;
    Tmp1=(Tmp*10)%100;
        Voltage[0]=Tmp1*10/100;
}        
void Convert_To_Voltage1(uchar val)
{        
        uchar Tmp,Tmp1; 
        val=val*1.28;                 
        Voltage[2]=val/100;           //整数部分
        Tmp=val%100;                  // 第一位小数
        Voltage[1]=Tmp*10/100;
    Tmp1=(Tmp*10)%100;
        Voltage[0]=Tmp1*10/100;
}
//启动I2C总线
void IIC_Start()
{
     SDA=1;SCL=1;Delay4us();SDA=0;Delay4us();SCL=0;
}
//停止I2C总线
void IIC_Stop()
{
     SDA=0;SCL=1;Delay4us();SDA=1; Delay4us();SCL=0;
}
// 从机发送应答位
void Slave_ACK()
{
     SDA=0;SCL=1;Delay4us();SCL=0;SDA=1;
}
// 从机发送非应答位
void Slave_NOACK()
{
     SDA=1;SCL=1;Delay4us();SCL=0;SDA=0;
}
//发送一字节
void IIC_SendByte(uchar wd)
{
        uchar i;
        for(i=0;i<8;i++) //循环移入8位
        {
                SDA=(bit)(wd&0x80);_nop_();_nop_();
                SCL=1;Delay4us();SCL=0;wd<<=1;
        }
                Delay4us();
                SDA=1;                                 //释放总线并准备读取应答
                SCL=1;
                Delay4us();
                IIC_ERROR=SDA;                        //IIC_ERROR=1表示无应答
                SCL=0;
                Delay4us();
}
//接收一字节
uchar IIC_ReceiveByte()
{
        uchar i,rd=0x00;
        for(i=0;i<8;i++)
        {
            SCL=1;rd<<=1;rd|=SDA;Delay4us();SCL=0;Delay4us();
        }
        SCL=0;Delay4us();
        return rd;
}
//连续读入4路通道的A/D转换结果并保存到Recv_Buffer
void ADC_PCF8591(uchar CtrlByte)
{
        uchar i=0;
        IIC_Start();
        IIC_SendByte(0x90);                         // 发送写地址
        if(IIC_ERROR==1)return;
        IIC_SendByte(CtrlByte);                  //发送控制字节
        if(IIC_ERROR==1)return;
        IIC_Start();                            //重新发送开始命令
        IIC_SendByte(0x91);                        // 发送读地址
        if(IIC_ERROR==1)return;
        IIC_ReceiveByte();                        //空读一次,调整读顺序
        Slave_ACK();                            //收到一字节后发送一个应答位
        Recv_Buffer=IIC_ReceiveByte();
        Slave_ACK();                         //收到一个字节后发送一个应答位
        Slave_NOACK();
        IIC_Stop();                          //收到一个字节后发送一个非应答位
}
// 向 PCF8591发送1字节进行AD转换
void main()
{
LC=0;
while(P1==0xff)
{
num[0]=10;
num[1]=10;
num[2]=10;
num[3]=10;
Display_Result();
}

while(1)
        {         
        uchar i;
             
                 if(LC==0){ADC_PCF8591(0x00); Convert_To_Voltage(Recv_Buffer);}
                 else     {ADC_PCF8591(0x01); Convert_To_Voltage1(Recv_Buffer);}
                 num[0]=Voltage[0];
                 num[1]=Voltage[1];
                 num[2]=Voltage[2];
                 num[3]=0;
                 if((num[0]>=0)&&(num[1]>=0)&&(num[2]>=2)) //大于0.2v
                 {
                    if(LC==0)   //超量程
                     {num[3]=1 ;
                      num[2]=11;
                       num[1]=11;
                       num[0]=11;
                           }
                    else {LC=0; Convert_To_Voltage(Recv_Buffer);}
                 }                 
                 if((num[2]==0)&&(num[1]<2)) //小于2v
                 {LC=1; Convert_To_Voltage1(Recv_Buffer);
                 } 
                 if        (LC==1) {for(i=1;i<50;i++) Display_Result1();}  //量程0.2v~2v
                 else { for(i=1;i<50;i++) Display_Result();}  //显示A/D转换结果,量程0~0.2v

        }
}
