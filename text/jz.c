#include<reg52.h>
#include<intrins.h>
#define unchar unsigned char
#define unint unsigned int 
unchar temp,bai,shi,ge;
unint num;
sbit wela=P2^7;
sbit dula=P2^6;
unchar code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71,
0x76,0x79,0x38,0x3f,0};
void delay(unint x)
{
	unchar j;
	for(x;x>0;x--)
		for(j=110;j>0;j--);
}
void display(unint nums)
{
	bai=nums/100;
	shi=nums%100/10;
	ge=nums%10;
	
	wela=1;
	P0=0xfe;
	wela=0;
	dula=1;
	P0=table[bai];
	dula=0;
	P0=0xff;
	delay(5);

	wela=1;
	P0=0xfd;
	wela=0;
	dula=1;
	P0=table[shi];
	dula=0;
	P0=0xff;
	delay(5);

	wela=1;
	P0=0xfb;
	wela=0;
	dula=1;
	P0=table[ge];
	dula=0;
	P0=0xff;
	delay(5);
}
void keyscan()
{
	P3=0xfe;
	temp=P3;
	temp=temp&0xf0;
	while(temp!=0xf0)
	{
		delay(10);//抖动检测
		temp=P3;
		temp=temp&0xf0;
		while(temp!=0xf0)
		{
			temp=P3;
			switch(temp)
			{
				case 0xee:num=1;break;
				case 0xde:num=4;break;
				case 0xbe:num=9;break;
				case 0x7e:num=16;break;
			}
			while(temp!=0xf0)//松手检测
			{
				temp=P3;
				temp=temp&0xf0;
			}

		  display(num);	//这是一个显示函数
		}
			
	}
	P3=0xfd;
	temp=P3;
	temp=temp&0xf0;
	while(temp!=0xf0)
	{
		delay(10);//抖动检测
		temp=P3;
		temp=temp&0xf0;
		while(temp!=0xf0)
		{
			temp=P3;
			switch(temp)
			{
				case 0xed:num=25;break;
				case 0xdd:num=36;break;
				case 0xbd:num=49;break;
				case 0x7d:num=64;break;
			}
			while(temp!=0xf0)
			{
				temp=P3;
				temp=temp&0xf0;
			}

		  display(num);
		}
		
	}		
	P3=0xfb;
	temp=P3;
	temp=temp&0xf0;
	while(temp!=0xf0)
	{
		delay(10);//抖动检测
		temp=P3;
		temp=temp&0xf0;
		while(temp!=0xf0)
		{
			temp=P3;
			switch(temp)
			{
				case 0xeb:num=81;break;
				case 0xdb:num=100;break;
				case 0xbb:num=121;break;
				case 0x7b:num=144;break;
			}
			while(temp!=0xf0)
			{
				temp=P3;
				temp=temp&0xf0;
			}

		 display(num);
		}
			
	}
		
	P3=0xf7;
	temp=P3;
	temp=temp&0xf0;
	while(temp!=0xf0)
	{
		delay(10);//抖动检测
		temp=P3;
		temp=temp&0xf0;
		while(temp!=0xf0)
		{
			temp=P3;
			switch(temp)
			{
				case 0xe7:num=169;break;
				case 0xd7:num=196;break;
				case 0xb7:num=225;break;
				case 0x77:num=256;break;
			}
			while(temp!=0xf0)
			{
				temp=P3;
				temp=temp&0xf0;
			}
		 display(num);

		}
			
	}		

}
void main()
{
	wela=1;
	P0=0xf8;
	wela=0;
	P0=0xff;
	dula=1;
	P0=0x3f;
	dula=0;
	while(1)
	{
    	keyscan();

	}

}

