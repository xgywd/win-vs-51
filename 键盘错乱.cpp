#include<stdio.h>
#include<string.h>
int	main()
{
	int n,i,j,k,length;
	char str[100];
	char a[27]="qwertyuiopasdfghjklzxcvbnm";
	char hastab[124];
	for (i=0;i<27;i++)			//这个循环是亮点
	{
		hastab[(int)a[i]]=a[i-1];
	}
	while(scanf("%d",&n)!=EOF)
	{
		for(i=0;i<n;i++)
		{
			scanf("%s",str);
			length=strlen(str);
			for(j=0;j<length;j++)
			{
				if(str[j]=='q') 
				{
					printf("p");
				}
				else if(str[j]=='a')
				{
					printf("l");
				}
				else if(str[j]=='z') 
				{
					printf("m");
				}
				else
				{
					printf("%c",hastab[(int)str[j]]);
				}
			}
			printf("\n");
		}
	}
	system("pause");
	return 0;
}
