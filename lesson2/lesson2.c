#include <reg52.h>
#define uint unsigned int 
#define uchar  unsigned char 
sbit led1=P1^0;
void delay();

void main()
{
	
while(1)
	{	
		led1=0;
		delay();
		delay();
		led1=1;
		delay();
		delay();
	}
	
}
void delay(void)
{
	uchar i,j;
	
	for(i=200;i>0;i--)
				for(j=200;j>0;j--);
	
}