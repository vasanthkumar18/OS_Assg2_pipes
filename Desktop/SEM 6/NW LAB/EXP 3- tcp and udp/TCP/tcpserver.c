#include <stdio.h> 
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#define MAX 80 
#define PORT 8080 
#define SA struct sockaddr 

// Function designed for chat between client and server. 
void func(int newsockfd) 
{ 
	char buff[MAX]; 
	int n; 
	// infinite loop for chat 
	for (;;) { 
		bzero(buff, MAX); 

		// read the message from client and copy it in buffer 
		read(newsockfd, buff, sizeof(buff)); 
		// print buffer which contains the client contents 
		printf("From CLIENT : %sTo CLIENT : ", buff); 
		bzero(buff, MAX); 
		n = 0; 
		// copy server message in the buffer 
		while ((buff[n++] = getchar()) != '\n') 
			; 

		// and send that buffer to client 
		write(newsockfd, buff, sizeof(buff)); 

		// if msg contains "Exit" then server exit and chat ended. 
		if (strncmp("end", buff, 3) == 0) { 
			printf("END OF SERVER \n"); 
			break; 
		} 
	} 
} 

// Driver function 
int main() 
{ 
	int sockfd, newsockfd, len; 
	struct sockaddr_in servaddr, cli; 

	// socket create and verification 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		printf("SOCKET CREATION FAILED \n"); 
		exit(0); 
	} 
	else
		printf("SOCKET IS CREATED\n"); 
	bzero(&servaddr, sizeof(servaddr)); 

	// assign IP, PORT 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_port = htons(PORT); 

	// Binding newly created socket to given IP and verification 
	if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
		printf("SOCKET BINDING IS FAILED\n"); 
		exit(0); 
	} 
	else
		printf("SOCKET IS BINDED \n"); 

	// Now server is ready to listen and verification 
	if ((listen(sockfd, 5)) != 0) { 
		printf("LISTENING IS FAILED\n"); 
		exit(0); 
	} 
	else
		printf("SERVER IS LISTENING\n"); 
	len = sizeof(cli); 

	// Accept the data packet from client and verification 
	newsockfd = accept(sockfd, (SA*)&cli, &len); 
	if (newsockfd < 0) { 
		printf("SERVER ACCEPTANCE IS  FAILED\n"); 
		exit(0); 
	} 
	else
		printf("SERVER ACCEPTED THE CLIENT\n"); 

	// Function for chatting between client and server 
	func(newsockfd); 

	// After chatting close the socket 
	close(sockfd); 
} 

