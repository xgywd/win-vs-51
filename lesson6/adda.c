/******************************ͷ�ļ�������궨��**************************************************/
#include <reg52.h>                 
																		/*�����������⹦�ܼĴ���������.
																			���û�����ͷ�ļ������⹦�ܼĴ�����ֻ����Ӳ���ĵ�ַ���ж�д������*/

typedef  unsigned int uint;
typedef  unsigned char uchar;
/******************************����ȫ�ֺ����ͱ���*********************************************************/
/*�˴���������ȫ������*/
void delay(uint i);
sbit cs	=	P1^0;
sbit wr	=	P1^1;
sfr dat   = 0x80;
bit flag=0;

void main()
{
	uchar k=0,j=0;
	cs=0;
	wr=0;
	while(1)
	{
		dat=k;
		delay(100);
		if(255==k)
		{
			flag=1;
		}
		else if(0==k)
		{
			flag=0;
		}
		if(!flag)
		{
			k++;
		}
		else
		{
			k--;
		}
	}
}


void delay(uint i)
{
	uchar j;
	for(;i>0;i--)
		for(j=19;j>0;j--);
}