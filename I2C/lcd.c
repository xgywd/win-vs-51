/******************************ͷ�ļ�������궨��**************************************************/
#include <reg52.h>                 
																		/*�����������⹦�ܼĴ���������.
																		���û�����ͷ�ļ������⹦�ܼĴ�����ֻ����Ӳ���ĵ�ַ���ж�д������*/
																		
#include <intrins.h>							//��ָ��Ȳ���	

#ifndef   XXXX_HHHH_II
#define   XXXX_HHHH_II
//���벿��
typedef  unsigned int uint;
typedef  unsigned char uchar;

#endif
uchar sh=0;
sbit rs=P2^6;
sbit rw=P2^5;
sbit e=P2^7;

uchar table1[32]={0};	//���� LCD
/******************************����ȫ�ֺ����ͱ���*********************************************************/
/*�˴���������ȫ������*/

void delay(uint i)
{
	int k,j;
	
	for(k=0;k<i;k++)
		for (j=55;j>0;j--)
		{
			_nop_();
			_nop_();
		}
}

void wcom(uchar com)
{
	rs=0;
	rw=0;
	P0=com;
	delay(2);
	e=1;
	e=0;
}
void wdat(uchar dat)
{
	rs=1;
	rw=0;
	P0=dat;
	delay(2);
	e=1;
	e=0;	
}

void init ()
{
	
	delay(30);
	wcom(0x38);
	delay(10);
	wcom(0x38);
	delay(10);
	wcom(0x38);
	wcom(0x38);
	wcom(0x08);
	wcom(0x01);
	wcom(0x06);
	wcom(0x0c);
	TMOD=0x01;
	TH0=(65536-1000)/256;	/*��ʱ��0��������8λ�Ĵ���TH0��TL0���,
														��ʱ����ֵ���㷽��Ϊ65536��ȥ��ʱ�������256�����8λ,*/
	TL0=(65536-1000)%256;	/*����65536��ȥ��ʱ���ȡ��256�����8λ*/
	ET0=1; //����ʱ��0�ж�
	TR0=1;	//������ʱ��0 
	EA=1;	//�����ж� 	
	
	
}
void show()
{
		
		if(16==sh)	//�����ʾ�ﵽ16���ַ�.����
		{
				wcom(0x80+0x40);	//�������
			
		}
		if(32==sh)
		{
			sh=0;
		}
			
		wdat(table1[sh]);	//��ʾ��ǰ�ַ�
		sh++;
}

void lcdprintf(const char *p)
{
	uchar i;
	while(*p)
	{
		table1[i]=*p;
		p++;
		i++;
		if(32==i)
		{
			return;
		}
	}
	
}

void lcdshow() interrupt 1
{
	TH0=(65536-1000)/256;
	
	TL0=(65536-1000)%256;
	
	show();
}
