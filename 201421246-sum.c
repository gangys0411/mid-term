#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int start=1;
	int resert=0;
	int num=10;
	pid_t pid;	

	pid=vfork();

	for(int i=0; i<num; i++)
	{
		if(pid==0)
		{
			for(int j=0; j<100;j++)
			{
				resert=resert+start;
				start++;
			}
			exit(0);
		}

		else if(pid>0)
		{
			pid=vfork();
		}
	}
	printf("%d\n", resert);
	return 0;
}
