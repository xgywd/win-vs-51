#include <stdio.h>
typedef struct test
{
	int a;
	int b;
	int c;
	const char *str;
}test;                       //定义结构体test的名字为test . 这样就可以用test定义新结构体,省略了struct


typedef struct testclass
{
	test N;                  //如上所说
	const char *str;		
	struct testclass *next;	
}HWND;						//这两个结构体的定义,就是为了了解结构体的嵌套.而以下程序,会了解,数据在内存中的形态


int  main()
{
	HWND hwd;				//定义一个HWND结构体对象hwd.不要忘记结构体中还有另一个结构体test
	const char *p,**n;
	
	hwd.N.a=1;												
	hwd.N.b=2;
	hwd.N.c=3;				
	hwd.N.str="lakdjflkajsdflkjalsdkfj!\n";      //给hwd对象中的test对象中的元素赋值.
	hwd.next=&hwd;

	p=(char*)&hwd;								//,把hwd的首地址赋值给const char指针p.学习下类型的强制转换

	n=&hwd.N.str;								//请观察这个指针p.是怎么找到结构体中各元素位的.
												//hwd与N是怎么样存在的内存当中的.
	
	printf(",%d\n,%d\n,%d\n,%s\n",*p,*(p+4),*(p+8),*((char**)(p+12)));

	//试一下好玩的调用.
	hwd.next->N.a=1;
	return 0;
}