#include <LPC213X.H>
int main()

{
	PINSEL0=0X00000000;   //P0������ΪGPIO����

	IODIR0=0XFFFFFFFF;    //P0��Ϊ���״̬
	IOSET0=0XFFFFFFFF; 	//P0���øߵ�ƽ������LED�ر�
	IOCLR0=0X00000002;  //P0.1�õ͵�ƽ�������ڶ���LED

	return 0;
}
