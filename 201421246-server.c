#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCK_PATH "cal_socket"

typedef struct massage
{	
	int type;
	int operator;
	double value[2];
}massage;

int main (void)
{
	int s, c, len;
	unsigned t;
	struct sockaddr_un local,remote;
	char str[100];
	struct massage msg;

	pid_t pid;

	if ((s=socket(AF_UNIX, SOCK_STREAM, 0)) == -1)
	{
		perror("socket");
		exit(1);
	}

	local.sun_family=AF_UNIX;
	strcpy(local.sun_path,SOCK_PATH);
	unlink(local.sun_path);
	len=strlen(local.sun_path)+sizeof(local.sun_family);

	if(bind(s, (struct sockaddr *)&local,len) == -1)
	{
		perror("bind");
		exit(1);
	}

	if(listen(s,5)== -1)
	{
		perror("listen");
		exit(1);
	}

	for(;;)
	{
		int done, n;
		printf("연결을 기다리는 중 입니다...\n");
		t=sizeof(remote);

		if((c=accept(s,(struct sockaddr *)&remote,&t)) ==-1)
		{
			perror("accept");
			exit(1);
		}

		printf("연결 성공.\n");

		done =0;

		pid=fork();
		

		if(pid==0)
		{

			do
			{
				n=recv(c,&msg,100,0);
				if (n<=0)
				{
					if (n<0)
						perror("recv");
					done=1;
				}
			
				msg.type=2;
				if(msg.operator==1)
				{
					msg.value[0]=msg.value[0]+msg.value[1];
				}else
			
				if(msg.operator==2)
			
				{
					msg.value[0]=msg.value[0]-msg.value[1];
				}else
			
				if(msg.operator==3)
				{
					msg.value[0]=msg.value[0]*msg.value[1];
				}else

				if(msg.operator==4)
				{
					msg.value[0]=msg.value[0]/msg.value[1];
				}else
					msg.value[0]=0;

				if (!done)
					if(send(c,&msg,n,0)<0)
					{
						perror("send");
						done=1;
					}
			}
			while(!done);
			exit(0);
		}

		close(c);
	}
	

return 0;
}
