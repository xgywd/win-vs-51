#include <stdio.h>
void myprintf(int a);
int add(int a, int b);
int main ()
{
	scanf("%d", &a);       //注意参数","号后跟一空格
	
	myprintf(a);
    char m;
	//m=myprintf(a);
	printf ("%c", myprintf(add(a, 1)));   //其实是可以这样的,可以把每个有返回值的函数当成一个确切的值.而值是可以作为参数的.


}

int add(int a,int b)
{
	return a+b;          //会先计算a+b的值,然后值被返回.   
}

void myprintf (int a)
{
	//if (a*(-1)<0)         //这是什么鬼? if(a>0) 不就完了?下面那句判断也一样.
	if(a>0)
	{
		//return a>0;      //这又是什么鬼
		return 1; 
		
    }
	
	//if(a*(-1)>0)       //if (a<0)           //这里的缩进不对,同级代码要放在一列
	if (a<0)
	{  
		//return a<0;
		return -1;

	}
	
	else 
	{ 
		//return a=0;
		return 0;

	}

}
      