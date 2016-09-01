#include <LPC213X.H>
int main()

{
	PINSEL0=0X00000000;   //P0口配置为GPIO功能

	IODIR0=0XFFFFFFFF;    //P0口为输出状态
	IOSET0=0XFFFFFFFF; 	//P0口置高电平，所有LED关闭
	IOCLR0=0X00000002;  //P0.1置低电平，点亮第二个LED

	return 0;
}
