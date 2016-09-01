#include <stdio.h>
float aver (float *p2 );
int main ()                                                                                                                               

{
	float av[5],a,*p1;
	int i;
	   
	    for(i=0;i<5;i++)
		{
			scanf ("%f",&av[i]);

		}
		    p1=av;    

		    a=aver (p1);
		
		  
		    printf("%f\n",a);

}

float aver (float *p2)
{
	     
	     int j;
		 float sum=0;
		 float b;
		 for (j=0;j<5;j++);
		 
		 {	 
			 sum=sum+*p2++;

		 }
		 
		 
            b=sum/5;
         
            return b;
}
