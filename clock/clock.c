/*��������Ϊ��Ƭ��ʱ�ӵĿ��Ƴ���.*/


/******************************ͷ�ļ�������궨��**************************************************/
#include <reg52.h>                 
																		/*�����������⹦�ܼĴ���������.
																			���û�����ͷ�ļ������⹦�ܼĴ�����ֻ����Ӳ���ĵ�ַ���ж�д������*/

typedef  unsigned int uint;
typedef  unsigned char uchar;
/******************************����ȫ�ֺ����ͱ���*********************************************************/
/*�˴���������ȫ������*/
char shi=0;
char fen=0;
char miao=0;
char flag=0;

uchar pulse_num=0;	/*ʱ������50����һ��*/
uchar pulse_dly=0;

void delay(uint i);  /*��ʱ����*/
void gettime();		/*��ȡʱ�亯��*/

void seting();    //���ð�ť��Ӧ����
void show();			//��ʾ����

void key();				//��ⰴ��1��2�ĺ���


sbit save=P1^3;     //573��138�����濪�� 
sbit key1=P3^0;
sbit key2=P3^1;


uchar code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};/* �����������ʾ�α���0-f*/
uchar table1[]={0x00,0x00,0x40,0x00,0x00,0x40,0x00,0x00};										/*��ʾ����*/
//uchar code table2[]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07};										/*8λһ������� λѡ����*/

/**************************************������*************************************************/
void main()
{
	/*C51���б������������ڴ����ǰ*/
	
	
	/*�˴����������ֲ�����*/
	
/************************************��ʱ����ʼ��***************************************************/
	
	TMOD=0x11;		/*0000 0001   TMOD �Ǽ�ʱ��������ʽ�Ĵ���,��8λ
	
									����λ���ö�ʱ��1.����λ��ʱ��0. ����������ͬ.
									
									����λ0001 
									����λ01 ����ʽ1:16λ�Ĵ���
									{00	����ʽ0:13λ�Ĵ���(��8,��5).
									10	����ʽ3:8λ�Զ���װ��ʱ:��8λ�����,	
									��8λ��ֵ�Զ�װ���8λ��Ϊ��ֵ.
									11	����ʽ4:��Ϊ����������8λ��ʱ/������}. 
									���λ0����:GATEλ(0�����жϿ���,1���жϿ���),
									�ڶ�λ����:CTλ(ѡ��0Ϊ��ʱ��,ѡ��1Ϊ������)*/
	/*********************************��ʱ�����س�ֵ******************************************************/
	
	TH0=(65536-50000)/256;	/*��ʱ��0��������8λ�Ĵ���TH0��TL0���,
							  ��ʱ����ֵ���㷽��Ϊ65536��ȥ��ʱ�������256�����8λ,*/
	TL0=(65536-50000)%256;	/*����65536��ȥ��ʱ���ȡ��256�����8λ*/
	
	TH1=(65536-1000)/256;
	
	TL1=(65536-1000)%256;
	/**********************************���ж�*****************************************************/
	
	EA=1;	//�����ж�
	ET0=1; //����ʱ��0�ж�
	TR0=1;	//������ʱ��0
	ET1=1;	//����ʱ��1�ж�
	TR1=1;	//������ʱ��1
	
	EX0=1;   //���ⲿ�ж�0
	IT0=1;	//�����жϷ�ʽΪ�½���.
	
	/***************************************************************************************/
		P1=0;
		P2=0;
	while(1)
	{
		if(flag)
		{
			seting();
		}
		
		gettime();
		
		show();
	}
}




void time() interrupt 1
{
	TH0=(65536-50000)/256;	/*��Ϊ��ʱ�����,��������,����Ҫ�ָ���ʱ����ֵ*/
	TL0=(65536-50000)%256;	
	pulse_num++;

}


void delaytime() interrupt 3
{
	TH1=(65536-1000)/256;
	
	TL1=(65536-1000)%256;
	
	pulse_dly++;
}


void init0() interrupt 0
{
	flag++;
	if(4==flag)
	{
		flag=0;
	}
}


void delay(uint i)
{
	pulse_dly=0;
	while(i!=pulse_dly);
}


void gettime()
{
	
	if(20==pulse_num)
	{
		miao++;
		if(60==miao)
		{
			miao=0;
			fen++;
			if(60==fen)
			{
				fen=0;
				shi++;
				if(24==shi)
				{
					shi=0;
				}
			}
		}
		pulse_num=0;
	}
}

void seting()
{
	uint k=0;
	uchar i,j,h;
			
	while(1)
	{
		k++;
		key();
		if (!flag)
		{
			pulse_num=0;
			return;
			
		}
		
			
		if(40==k)
		{
			switch (flag)
			{
				case 1:
						j=table1[7];
						h=table1[6];
						table1[7]=0x00;
						table1[6]=0x00;
						break;
				case 2:	
						j=table1[4];
						h=table1[3];
						table1[4]=0x00;
						table1[3]=0x00;
						break;
				case 3:
						j=table1[1];
						h=table1[0];
						table1[1]=0x00;
						table1[0]=0x00;
						break;
				
			}
		
			
		}
		if (80==k)
		{
			
			switch (flag)
			{
				case 1:
						table1[7]=j;
						table1[6]=h;
						k=0;
						break;
				case 2:	
						table1[4]=j;
						table1[3]=h;
						k=0;
						break;
				case 3:
						table1[1]=j;
						table1[0]=h;
						k=0;
			}			break;
		}
		
		for(i=0;i<8;i++)
		{
			P1=i;				//λѡ   573�ر� 138�ر�
			
			P2=table1[i];				//��ѡ	������ʾ������
			save=1;							//573LE 138 ��
			delay(1);
		}
	}		
		
}

void key()
{
	
	P3=0xff;
	
	
	if (!key1)
	{
		delay(5);
		if (!key1)
		{
			switch (flag)
			{
				case 1:
					shi++;
					if(shi>23)
					{
						shi=0;
					}
					break;
				case 2:
					fen++;
					if(fen>59)
					{
						fen=0;
					}
					break;
				case 3:
					miao++;
					if(miao>59)
					{
						miao=0;
					}
					break;
			}
		}
		
		while(!key1)
		{
			show();
		}
		delay(5);
		while (!key1)
		{
			show();
		}
	}
	
	P3=0xff;
	
	if (!key2)
	{
		delay(5);
		if (!key2)
		{
			switch (flag)
			{
				case 1:
					shi--;
					if(shi<0)
					{
						shi=23;
					}
					break;
				case 2:
					fen--;
					if(fen<0)
					{
						fen=59;
					}
					break;
				case 3:
					miao--;
					if(miao<0)
					{
						miao=59;
					}
					break;
			}
		}
		
		while(!key2)
		{
			show();
		}
		delay(5);
		while (!key2)
		{
			show();
		}
	}
	
}


void show()
{
	uchar i;
	
	table1[7]=table[shi/10];
	table1[6]=table[shi%10];
	table1[4]=table[fen/10];
	table1[3]=table[fen%10];
	table1[1]=table[miao/10];
	table1[0]=table[miao%10];
	
	for(i=0;i<8;i++)
	{
		P1=i;				//λѡ   573�ر� 138�ر�
		
		P2=table1[i];				//��ѡ	������ʾ������
		save=1;							//573LE 138 ��
		delay(1);
	}
}






