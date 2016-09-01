#include <reg52.h>
#include <intrins.h>
#define uint unsigned int 
#define uchar  unsigned char 

void delay(int i)
{
	uchar j;
	
	while(i--)
	{
				for(j=113;j>0;j--);
	}
	
}

void main()
{
	uint a=0xfe;
	P0=a;
	while (1)
	{
		
		P0=a;
		delay(500);
		a=_crol_(a,1);
		
	}
		
}