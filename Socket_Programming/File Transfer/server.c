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

	FILE *f;

	int ch = 0;
	f = fopen("newF.txt", "a");

	int words;

	read(newsockfd, &words, sizeof(int));

	while(ch != words){
		read(newsockfd, buffer, 255);
		fprintf(f, "%s ", buffer);
		ch++;
	}

	printf("File has been received successfully.  :))\n");


	close(newsockfd);
	close(sockfd);
	return 0;
}
