#include<reg51.h>
#define uint unsigned int
#define uchar unsigned char
sbit key1=P2^0;
uint t1;
uchar bai,shi,ge;
uchar code duanma[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71,
0x76,0x79,0x38,0};
uchar code weima[]={
0x7f,0xbf,0xdf,0xef,
0xf7,0xfb,0xfd,0xfe};
void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}
void init()
{
	t1=0;
	key1=1;
	TMOD=0x10;
	TH1=(65536-10000)/256;
	TL1=(65536-10000)%256;
	EA=1;
	ET1=1;
	TR1=1;
}
void display(bai,shi,ge);
void main()
{
	init();
	while(1)
	{
		 if(key1==0)
		 {
		 	delay(10);
			if(key1==0)
			{
				TR1=0;
			}
/*			while(!key1);
			delay(10);			
			while(!key1); */  //À… ÷ºÏ≤‚  
		 } 
		 else
		 	TR1=1;
		display(bai,shi,ge);
	}
}
void display(bai,shi,ge)
{
	 P0=weima[0];
	 P1=duanma[bai];
	 delay(1);
	 P0=weima[1];
	 P1=duanma[shi];
	 delay(1);
	 P0=weima[2];
	 P1=duanma[ge];
	 delay(1);
}
void timer1() interrupt 3
{
	TH1=(65536-10000)/256;
	TL1=(65536-10000)%256;
	t1++;
	if(t1==1000)
		t1=0;
		bai=t1/100;
		shi=t1%100/10;
		ge=t1%10;	

}