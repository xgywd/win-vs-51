#include	 <reg52.h>

#define uint unsigned int
sbit d0=0x81;
void main()

{
			uint a=5000;
			while(1)
			{
				P1=0xFE;
				while(a--);
				P1=0xFF;
																			//a=5000;
				while(a--);
			}
}