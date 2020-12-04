==========================SHARED MEMORY=============================


STEP 1: Create SharedAssg2Q2.c
	Here, we define we the keysize, keyid of the shared memory using ftok,shmat,shmget
	We make a structure to define the password which has it's strength,password, count of alphanumeric characters and count of special characters.
	
	The semamphores are unlinked and new semaphores are created for each process. 
	Two forks are called for the two process except for the main process.
	The main program is process 1 and the first fork is Process 3 and the third fork is Process 2

	In main, program reads the string by taking ONLY 10 characters( since the size of password is limited to 10 as per the question).
		 sem_post call is done for P2, i.e process 2 semograph to start it 
		 sem_wait call is done for P1, so that it waits until it is called again to resume

	In P2, sem_wait makes sures P2 starts only after sem_post is called.
	       It calculates the count of alphanumeric characters and special characters (total characters-alphanumeric = special characters).
	       It will then call sem_post for P3, to start and will close P2 using sem_close
			
	In P3, sem_wait ensures P3 starts only after sem_post is called. 
	       It calculates if given password is STRONG or WEAK (BY intialising STRENGTH to 1 or 0) based on the count of alphanumeric charactres and special characters and stores it in strenth.
	       It will then call sem_post for P1, to start and will close P3 using sem_close
	In P1, It checks if strength is 1 or 0 and prints results accordingly i.e. if 1 then STRONG else WEAK.
	       It will close P1 by sem_close

STEP 2: Compile and run SharedAssg2Q2.c using:
	command: gcc SharedAssg2Q2.c -Wall -pedantic -std=c99 -D_XOPEN_SOURCE=700 -pthread
		./a.out


