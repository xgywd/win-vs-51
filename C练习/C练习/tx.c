#include <stdio.h>
typedef struct test
{
	int a;
	int b;
	int c;
	const char *str;
}test;                       //����ṹ��test������Ϊtest . �����Ϳ�����test�����½ṹ��,ʡ����struct


typedef struct testclass
{
	test N;                  //������˵
	const char *str;		
	struct testclass *next;	
}HWND;						//�������ṹ��Ķ���,����Ϊ���˽�ṹ���Ƕ��.�����³���,���˽�,�������ڴ��е���̬


int  main()
{
	HWND hwd;				//����һ��HWND�ṹ�����hwd.��Ҫ���ǽṹ���л�����һ���ṹ��test
	const char *p,**n;
	
	hwd.N.a=1;												
	hwd.N.b=2;
	hwd.N.c=3;				
	hwd.N.str="lakdjflkajsdflkjalsdkfj!\n";      //��hwd�����е�test�����е�Ԫ�ظ�ֵ.
	hwd.next=&hwd;

	p=(char*)&hwd;								//,��hwd���׵�ַ��ֵ��const charָ��p.ѧϰ�����͵�ǿ��ת��

	n=&hwd.N.str;								//��۲����ָ��p.����ô�ҵ��ṹ���и�Ԫ��λ��.
												//hwd��N����ô�����ڵ��ڴ浱�е�.
	
	printf(",%d\n,%d\n,%d\n,%s\n",*p,*(p+4),*(p+8),*((char**)(p+12)));

	//��һ�º���ĵ���.
	hwd.next->N.a=1;
	return 0;
}