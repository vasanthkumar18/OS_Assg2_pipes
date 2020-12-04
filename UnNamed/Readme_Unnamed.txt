========================================UN-NAMED PIPELINES====================================

Here, we call 2 fork() functions. 
The main program is process 1 and the first fork is Process 3 and the third fork is Process 2

STEP 1: Create the UnnamedAssg2Q1.c
	The main program it reads the 5 temperatures in an array and sends the data to Process 2 via fork() call.
	The process 2 calculates average and standard deviation and sends them to Process 3 via another fork() call.
	The process 3 calculates categories of each temperature accoring to question and sends the data to Process 1
	And inturn, main program odifies the temperature according to question and displays it.
STEP 2: Compile and run the program using:
	command: gcc UnnamedAssg2Q1.c -lm
		 ./a.out 

Both pipelines (unnamed and named) uses the same kind of logic and algorithm. The only difference being is that waiting was done in unnamed pipelines, while the pipe simply waits to be opened for reading and writing in the named implementation.
		
	

	
