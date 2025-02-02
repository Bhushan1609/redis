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

	int number1,number2,answer,choice;

START:
	n = write(newsockfd, "Enter your choice : \n1.Addition\n2.Subtraction\n3.Multiplication\n4.Division\n5.Exit\n",strlen("Enter your choice : \n1.Addition\n2.Subtraction\n3.Multiplication\n4.Division\n5.Exit\n"));
	if(n < 0){
		error("Error Writing!!");
	}

	read(newsockfd, &choice, sizeof(int));
	if(choice == 5){
		goto QUIT;
	}
	printf("Client - Choice is : %d\n", choice);

	

	n = write(newsockfd, "Enter Number1 : ", strlen("Enter Number1 : "));
	if(n < 0){
		error("Error Writing!!");
	}
	read(newsockfd, &number1, sizeof(int));
	printf("Client - Number 1 is : %d\n", number1);

	
	n = write(newsockfd, "Enter Number2 : ", strlen("Enter Number2 : "));
	if(n < 0){
		error("Error Writing!!");
	}
	read(newsockfd, &number2, sizeof(int));
	printf("Client - Number 2 is : %d\n", number2);

	

	switch(choice){
		case 1:
			answer = number1+number2;
			break;
		case 2:
			answer = number1-number2;
			break;
		case 3:
			answer = number1*number2;
			break;
		case 4:
			answer = number1/number2;
			break;
		case 5:
			goto QUIT;
			break;
	}

	write(newsockfd, &answer, sizeof(int));

	if(choice != 5){
		goto START;
	}

QUIT:
	close(newsockfd);
	close(sockfd);
	return 0;
}
