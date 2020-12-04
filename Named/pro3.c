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

int main(int argc, char *argv)
{
	printf("PROCESS 3\n");



	float arr[5];
	int i=0;
	printf("READING AVERAGE, SD FROM 2nd PROCESS\n");
	int fd=open("2to3",O_RDONLY);
	if(fd==-1)
	{
		printf("Unable to access the fifo to read average and SD\n");
		return 1;
	}
	float avg=0.0;
	float SD=0.0;
	if(read(fd,&avg,sizeof(float))==-1)
	{
		printf("Unable to read average from fifo\n");
		return 3;
	}
	printf("Reading avg=%f\n",avg);
	if(read(fd,&SD,sizeof(float))==-1)
	{
		printf("Unable to read SD from fifo\n");
		return 4;
	}
	printf("Reading SD=%f\n",SD);
	
	for(i=0;i<5;i++)
	{
		read(fd,&arr[i],sizeof(float));
	}
	close(fd);

	
	fd=open("3to1",O_WRONLY);
	if(fd==-1)
	{
		printf("unable to open process 1 to send categories\n");
		return 5;
	}
	printf("\nWRITING CATEGORIES TO 1st PROCESS\n");
	int s[5];
	
	
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
		write(fd,&s[i],sizeof(int));
		printf("Writing category of temperature %d as %d\n",i+1,s[i]);
	}
	close(fd);



	
		
		
	
}
