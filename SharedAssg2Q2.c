#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h> 
#include <time.h>
#include <errno.h>
#include <math.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <pthread.h>

#define MAX_LEN 10
#define FILENAME "password"


#define P1 "p1_semaphore"
#define P2 "p2_semaphore"
#define P3 "p3_semaphore"

typedef struct os
{
	char password[MAX_LEN];
	int a;	// to calculate alphanumerical characters
	int s;  // to calculate special characters
	int strength; // to decide the strenth;
} assign;

int main(void)
{
	// making the shared memory with a given size,key and id
	key_t key=ftok(FILENAME,0);
	int shmid=shmget(key,sizeof(assign),0666 | IPC_CREAT);
	assign *input=(assign *)shmat(shmid,(void *)0,0);

	// unlinking the semaphores to make sure it is unlinked before execution
	sem_unlink(P1);
	sem_unlink(P2);
	sem_unlink(P3);
	
	// creating semaphores for the 3 processes
	sem_t *p1s=sem_open(P1,O_CREAT,0660,0);
	sem_t *p2s=sem_open(P2,O_CREAT,0660,0);
	sem_t *p3s=sem_open(P3,O_CREAT,0660,0);

	if(p1s==SEM_FAILED)
	{
	printf("Unable to open the P1 semaphore\n");
	}
	if(p2s==SEM_FAILED)
	{
	printf("Unable to open the P2 semaphore\n");
	}
	if(p3s==SEM_FAILED)
	{
	printf("Unable to open the P3 semaphore\n");
	}

	int pid=fork();
	if(pid==0)
	{
		int pid1=fork();
		if(pid1==0)
		{
			//printf("\nPROCESS 2\n");
			sem_wait(p2s);
			int i=0,l=0;
			for(i=0;i<strlen(input->password);i++)
			{
			if (('A' <= input->password[i] && input->password[i] <= 'Z')||('a' <= input->password[i] && input->password[i] <= 'z') ||('0' <= input->password[i] && input->password[i]<= '9'))
                		{
                    			l++; // incrementing alphanumerical chars
               			}
			}
			input->a=l;
			input->s=i-l; // since remaining all are special chars.
			printf("\nThe number of alphanumeric chars are %d and special chars are %d\n",input->a,input->s);
			sem_post(p3s);
			sem_close(p2s);
		}
		else
		{
			//printf("\nPROCESS 3\n");
			sem_wait(p3s);
			if(input->a>=input->s)
				input->strength=0; // weak
			else
				input->strength=1;// strong
			sem_post(p1s);
			sem_close(p3s);
		}
	}
	else
	{
		//printf("PROCESS 1\n");
		printf("Enter the Password\n");
		scanf("%s",input->password);
		input->password[10]='\0';
		printf("The input password is taken as %s\n",input->password);
		sem_post(p2s); // going to process 2
		sem_wait(p1s);
		//printf("BACK TO PROCESS 1 FROM PROCESS 3\n");
		if(input->strength==1)
			printf("The password is STRONG\n");
		else if(input->strength==0)
			printf("The password is WEAK\n");
		
		sem_close(p1s);
	
		// unlinking the semaphores 
		sem_unlink(P1);
		sem_unlink(P2);
		sem_unlink(P3);
	}

return 0;
			
		
		
		
}
