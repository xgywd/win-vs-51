/*此驱动占用了定时器0,如果不需要请自行更改*/

#ifndef   XXXX_HHHH_II
#define   XXXX_HHHH_II
//代码部分
typedef  unsigned int uint;
typedef  unsigned char uchar;

#endif

#ifndef   HEAD_LABEL_III
#define   HEAD_LABEL_III
//代码部分
void init();	//1602初始化函数
//void delay( uchar i);   //延时函数
void lcdprintf(const char *p);    //在屏幕打印字符,字符缓冲32字节,超出会截断
#endif