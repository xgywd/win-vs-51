include<reg52.h>
#include<intrins.h>
#define int unsigned int 
#define char unsigned char 
sbit ALE=P3^4;
sbit ADDA=P3^7;
sbit ADDB=P3^6;
sbit ADDC=P3^5;
sbit START=P1^7;
sbit EOC=P1^6;
sbit OE=P1^5;
sbit CLOCK=P1^4;
void daley (char n)
{
 char x,y;
 for(x=0;x<n;x++)
  for(y=100;y>0;y--);
}

void time_init()
{
TMOD=0x01;
TH0=0xff;
TL0=0x37;
TR0=1;
ET0=1;
EA=1;
}
void time()interrupt 1
{
CLOCK=~CLOCK;
TH0=0xff;
TL0=0x37;
TF0=0;
}
void main ()
{ char i;
  time_init(); 
  ALE=0;
  OE=0;
  ADDA=0;
  ADDB=0;
  ADDC=0;
  ALE=1;
  START=1;
  _nop_();
  START=0;
  _nop_();
  while(!EOC);
  OE=1;
  while(1);
  
}