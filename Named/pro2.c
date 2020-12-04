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

float standarddeviation(float arr[], float avg)
{
	float SD = 0.0;
	int i=0;
	for (i = 0; i <5; ++i)
        SD += pow(arr[i] - avg, 2);

	return sqrt(SD /5);
}

int main(int argc, char *argv)
{	
	printf("PROCESS 2\n");

	
	float arr[5];
	int fd=open("1to2",O_RDONLY);	
	if(fd==-1)
	{
		printf("Unable to access the fifo to read temperaturess\n");
		return 1;
	}
	int i=0;
	printf("READING TEMPERATURES FROM 1st PROCESS\n");
	for(i=0;i<5;i++)
	{
		if(read(fd,&arr[i],sizeof(float))==-1)
		{
			printf("Unable to read temperatures from fifo\n");
			return 2;
		}
		printf("Reading %f\n",arr[i]);
	}
	close(fd);




	float avg=0.0;
	for(i=0;i<5;i++)
	{
		avg+=arr[i];
	}
	avg=avg/(float)5;
	float SD=0.0;
	SD=standarddeviation(arr,avg);

	printf("\nWRITING AVERAGE, SD TO 3rd PROCESS \n");
	fd=open("2to3",O_WRONLY);
	if(fd==-1)
	{
		printf("Unable to access the fifo to give Average and SD\n");
		return 1;
	}
	if(write(fd,&avg,sizeof(float))==-1)
	{
		printf("Unable to write average to fifo\n");
		return 3;
	}
	printf("Writing avg=%f\n",avg);
	if(write(fd,&SD,sizeof(float))==-1)
	{
		printf("Unable to write SD to fifo\n");
		return 4;
	}
	printf("Writing SD=%f\n",SD);
	i=0;
	while(i<5)
	{
		write(fd,&arr[i],sizeof(float));
		i=i+1;
	}
	close(fd);
	
	
	
	

}
