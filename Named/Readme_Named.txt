====================================NAMED PIPELINES======================================

The processes Pro1,pro2,pro3 are made and the 3 pipes 1to2, 2to3, 3to1 are created to share the data between processes.

Pipes were basically meant for communincation related processes. Here we use 3 pipes for bi-directional communication. Pipe is also called as FIFO(First in First out).

STEP 1: Create 3 pipes 1to2,2to3,3to1 using
	command: mkfifo 1to2
		 mkfifo 2to3 
		 mkfifo 3to1
STEP 2: Create 3 Processes codes which are proc1.c, proc2.c and proc3.c 
	PROC 1:
	In Process 1, it reads the 5 temperatures in an array and sends the data to Process 2 via 1to2 pipe
	PROC 2:
	In Process 2, it reads the data given by Process 1 via 1to2 pipe and calculates average and standard deviation and sends them to Process 3 along with the 5 tempertaures via 2to3 pipe
	PROC 3:
	In Process 3, it reads the data given by Process 2 via 2to3 pipe and calculates categories of each temperature accoring to question and sends the data to Process 1 via 3to1 pipe
	PROC 1:
	Again in Process 1, it reads the categories given by Process 3 via 3to1 pipe and modifies the temperature according and displays it. 

STEP 3: Compile and run all 3 Programs using:
	command: gcc pro1.c -lm
		 ./a.out 
		gcc pro2.c -lm
		./a.out
		gcc pro3.c -lm
		./a.out

		
	

	
