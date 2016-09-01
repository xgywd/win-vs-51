#include <stdio.h>
int myprintf(int a);
int main ()
{   
	int a,m;
	scanf("%d",&a);
	myprintf(a);
	m=myprintf(a);
switch (m);
	{
	 case -1:
		 printf("a是正数");
		 break;
	 case 1:
		 printf("a是负数");
		 break;
	 case 0:
		 printf("a是零");
		 
         break;
	}

	
}

int myprintf (int a)
{
	if (a*(-1)<0)
	{
		return -1;
    }
	  if(a*(-1)>0)
	  {  
		  return 1;

	  }
	     else 
		 { 
			 return 0;

		 }

}
      