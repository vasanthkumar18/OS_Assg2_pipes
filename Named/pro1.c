#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h> 
#include <time.h>
#include <errno.h>


int main(int argc, char *argv[])
{
	float arr[5];
	printf("PROCESS 1\n");
	printf("Input the temperatures of all 5 locations\n");
	int j=0;
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






	int fd=open("1to2",O_WRONLY);
	if(fd==-1)
	{
		printf("Unable to access the fifo\n");
		return 1;
	}
	
	int i=0;
	printf("WRITING TEMPERATURES TO 2nd PROCESS\n");
	while(i<5)
	{
		int p=write(fd,&arr[i],sizeof(float));
		if(p==-1)
		{
			printf("Unable to write to the fifo\n");
			return 2;
		}
		printf("Writing %f\n",arr[i]);
		i=i+1;
	}
	close(fd);
	printf("WRITING IS DONE\n\n");
	
	fd=open("3to1",O_RDONLY);
	if(fd==-1)
	{
		printf("unable to read categories from 3rd process\n");
		return 3;
	}
	int s[5];
	printf("READING CATEGORIES FROM 3rd PROCESS\n");
	
	for(i=0;i<5;i++)
	{
		read(fd,&s[i],sizeof(int));
	}
	close(fd);

	printf("\nTHE REVISED TEMPERATURES ARE:\n");
	for(i=0;i<5;i++)
	{
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

	






	






	
	return 0;
}
