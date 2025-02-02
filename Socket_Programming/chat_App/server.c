#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

void error(const char *msg){
	perror(msg);
	exit(1);
}


int main(int argc,char *argv[]){ 

	if(argc < 2){
		fprintf(stderr,"Port Number not provided, Program terminated!!\n");
		exit(1); 
	}

	int sockfd, newsockfd, portno, n;
	char buffer[255];
	struct sockaddr_in serv_addr, cli_addr;
	socklen_t clilen;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if(sockfd < 0){
		error("Error Opening Scoket!!");
	}

	bzero((char *) &serv_addr, sizeof(serv_addr));

	portno = atoi(argv[1]);

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);

	int rv = bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

	if(rv < 0){
		error("Binding Failed");
	}

	listen(sockfd, 5);
	clilen = sizeof(cli_addr);

	newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &clilen);

	if(newsockfd < 0){
		error("Error on Accept");
	}

	while(1){
		bzero(buffer, 255);
		n = read(newsockfd, buffer, 255);
		if(n < 0){
			error("Error on Reading");
		}
		printf("Client : %s\n", buffer);
		bzero(buffer, 255);
		fgets(buffer, 255, stdin);

		n = write(newsockfd, buffer, strlen(buffer));
		if(n < 0){
			error("Error on Writing");
		}

		if(strncmp("Bye", buffer, 3)==0){
			break;
		}
	}
	close(newsockfd);
	close(sockfd);
	return 0;
}

/*
	perror() is a standard C library function that prints a descriptive error message

	argc: The number of arguments passed to the program.
	argv[]: The arguments themselves, with argv[0] being the name of the program (the path used to invoke it).

	argc is 2 one {for the file name} and 1 for the {port_number}.

	stderr: This is the standard error stream, used for printing error messages and warnings.
	printf(), but instead of sending the output to the standard output (i.e., the console),
	fprintf() sends the output to a file or any other output stream.

	socklen_t clilen;{32 bit datatype}

	sockaddr_in {gives internet address which provide by file netinet/in.h}

	bzero();clear a data, a text , or anything it is referncing to.

	htons stands for Host to Network Short.
	htons() function is used to convert a 16-bit short integer (or "short") from host byte order to network byte order.

	The fgets() function in C is used to read a line of text from a stream (usually standard input, stdin) into a character array (buffer). 
*/