#include<reg52.h>

#define uint unsigned int
#define uchar unsigned char

uchar code duanma[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71,0x40};

uchar code weima[]={
0x7f,0xbf,0xdf,0xef,
0xf7,0xfb,0xfd,0xfe};

uint t;
uchar shi,fen,miao;
uchar a,b,c,d,e,f;

void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}

void display(a,b,c,d,e,f)
{
	P0=weima[0];
	P1=duanma[a];
	delay(1);
	P0=weima[1];
	P1=duanma[b];
	delay(1);
	P0=weima[2];
	P1=duanma[16];
	delay(1);
	P0=weima[3];
	P1=duanma[c];
	delay(1);
	P0=weima[4];
	P1=duanma[d];
	delay(1);
	P0=weima[5];
	P1=duanma[16];
	delay(1);
	P0=weima[6];
	P1=duanma[e];
	delay(1);
	P0=weima[7];
	P1=duanma[f];
	delay(1);
}

void init()
{
	shi=0;
	fen=0;
	miao=0;
	TMOD=0x01;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	EA=1;
	ET0=1;
	TR0=1;
}

void main()
{
	init();
	while(1)
	{
		display(a,b,c,d,e,f);
	}
}

void timer0() interrupt 1
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	t++;
	if(t==20)
	{
		t=0;
		miao++;
		if(miao==60)
			{
				miao=0;
				fen++;
				if(fen==60)
				{
					fen=0;
					shi++;
					if(shi==24)
						shi=0;
				}
			}
	}
	a=shi/10;
	b=shi%10;
	c=fen/10;
	d=fen%10;
	e=miao/10;
	f=miao%10;
}