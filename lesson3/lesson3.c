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
uchar setp_table[]={0x89,0x90,0xa1,0xc0};
void main()
{
	uint a=0xfe;
	uchar i;
	P0=a;

	while (1)
		{
			for(i=0;i<4;i++)
				{
					delay(500);
					P0=a;
					a=_crol_(a,1);
					P1=setp_table[i];
				}
		}
}