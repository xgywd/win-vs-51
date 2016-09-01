
#ifndef   XXXX_HHHH_II
#define   XXXX_HHHH_II
//代码部分
typedef  unsigned int uint;
typedef  unsigned char uchar;

#endif


#ifndef   HEAD_LABEL_IV
#define   HEAD_LABEL_IV
//代码部分
void init(); //初始化


void start(); //开始信号
void stop();   //停止
void respons();  //应答

void write_byte(uchar);        //写字节

uchar read_byte();            //读字节


void write_add( uchar address, uchar date); //指定地址写数据
uchar read_add( uchar address);                //指定地址读数据

#endif
