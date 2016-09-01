#include<reg52.h>
#define uint unsigned int
#define uchar unsigned char
sbit csda=P3^2;
sbit wr=P3^6;
uint x;
uchar flag;

void main()
{
	csda=0;
	wr=0;
	x=0;
	flag=1;
	while(1)
	{
		P0=x;
		if(x==0)
			flag=1;
			
		if(x==0xff)
			flag=0;
			
		if(flag==1)
			x++;
		if(flag==0)
			x--; 

	}
}