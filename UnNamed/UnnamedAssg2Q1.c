#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h> 
#include <time.h>
#include <errno.h>
#include <math.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	// fd[0] is read
	// fd[1] is write
	int fd0[2]; // main pipe
	int fd1[2]; // second pipe
	int fd2[2]; // third pipe

	if(pipe(fd0)==-1)
	{
		printf("Unable to read from pipe\n");
		return 1;
	}
	pipe(fd1);
	pipe(fd2);
	
	printf("1st PROCESS\n");
	printf("Input the temperatures of all 5 locations\n");
	int j=0;
	float arr[5];
	for(j=0;j<5;j++)
	{
		int d=1;
		while(d)
		{		
			scanf("%f",&arr[j]);
			if(arr[j]>=15 &&  arr[j]<=45)
			{
				d=0;
			}
			else 
			{
				printf("Please enter the value between 15 and 45\n");
			}
		}
		printf("Reading %f\n",arr[j]);
	}
			
	printf("READING IS DONE\n\n");
	
	write(fd0[1],arr,sizeof(float)*5);
	write(fd0[1],arr,sizeof(float)*5);
	close(fd0[1]);
	close(fd0[1]);
	
	int pid=fork();
	
	if(pid==0)
	{
		int pid1=fork();
		if(pid1==0)
		{
			printf("\n2nd PROCESS\n");
			float arr[5];
			read(fd0[0],arr,sizeof(float)*5);
			float avg=0.0;
			int i=0;
			for(i=0;i<5;i++)
			{
			avg+=arr[i];
			}
			avg=avg/(float)5;
			float SD = 0.0;
			for (i = 0; i <5; ++i)
        		SD += pow(arr[i] - avg, 2);
			SD=sqrt(SD/5);
			printf("The avg is %f and SD is %f\n\n",avg,SD);
			write(fd1[1],&avg,sizeof(float));
			write(fd1[1],&SD,sizeof(float));
			close(fd1[1]);
			
		}
		else
		{
			wait(NULL);
			printf("3rd PROCESS\n");
			float arr[5];
			int s[5];
			int i=0;
			read(fd0[0],arr,sizeof(float)*5);
			float avg,SD;
			read(fd1[0],&avg,sizeof(float));
			read(fd1[0],&SD,sizeof(float));
			
			for(i=0;i<5;i++)
			{
			
			if(arr[i]==avg)
				s[i]=0;
			else if(arr[i]>(avg+SD))
				s[i]=1;
			else if(arr[i]>avg && arr[i]<(avg+SD))
				s[i]=2;
			else if(arr[i]<avg && arr[i]>(avg-SD))
				s[i]=3;
			else if(arr[i]<(avg-SD))
				s[i]=4;
			printf("Category of temperature %d is %d\n",i+1,s[i]);
			
			}
			write(fd2[1],s,sizeof(int)*5);
			close(fd2[1]);
		}
	}
	else
	{
		wait(NULL);
		printf("\nBACK TO 1st PROCEESS from 3rd PROCESS\n");
		int s[5];
		int i=0;
		read(fd2[0],s,sizeof(int)*5);
		printf("\nTHE MODIFIED TEMPERATURES ARE:\n");
		for(i=0;i<5;i++)
		{
			printf("%d\n",s[i]);
			float h=arr[i];
			if(s[i]==0)
				printf("Temperature %d is %f\n",i+1,h);
			else if(s[i]==1)
				printf("Temperature %d is %f\n",i+1,h-3.0);
			else if(s[i]==2)
				printf("Temperature %d is %f\n",i+1,h-1.5);
			else if(s[i]==3)
				printf("Temperature %d is %f\n",i+1,h-2.0);
			else if(s[i]==4)
				printf("Temperature %d is %f\n",i+1,h-2.5);
		}

	
		printf("\n\nTEMPERATURE CONTROLLER TASK IS DONE\n");
		close(fd2[0]);
		close(fd1[0]);
		close(fd0[0]);
	}

return 0;
			
	
	
}
