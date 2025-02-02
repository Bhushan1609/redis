#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>

void error(const char *msg){
	perror(msg);
	exit(0);
}

int main(int argc, char *argv[]){

	if(argc < 3){
		fprintf(stderr, "usage %s hostname port\n", argv[0]);
		exit(0);
	}

	int sockfd, portno, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char buffer[255];

	portno = atoi(argv[2]);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if(sockfd < 0){
		error("Error Opening Socket");
	}

	server = gethostbyname(argv[1]);

	if(server == NULL){
		fprintf(stderr, "Error , no such host.\n");
	}

	bzero((char *)&serv_addr, sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	bcopy((char *) server -> h_addr, (char *)& serv_addr.sin_addr.s_addr, server -> h_length);
	serv_addr.sin_port = htons(portno);

	int rv = connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));

	if(rv < 0){
		error("Connection Failed!!");
	}
	
	int number1,number2,answer,choice;

START:

	bzero(buffer, 255);
	n = read(sockfd, buffer, 255);
	if(n < 0){
		error("Error Reading");
	}
	printf("Server - %s\n", buffer);
	scanf("%d", &choice);
	write(sockfd, &choice, sizeof(int));

	if(choice == 5){
		goto QUIT;
	}

	bzero(buffer, 255);
	n = read(sockfd, buffer, 255);
	if(n < 0){
		error("Error Reading");
	}
	printf("Server - %s\n", buffer);
	scanf("%d", &number1);
	write(sockfd, &number1, sizeof(int));

	bzero(buffer, 255);
	n = read(sockfd, buffer, 255);
	if(n < 0){
		error("Error Reading");
	}
	printf("Server - %s\n", buffer);
	scanf("%d", &number2);
	write(sockfd, &number2, sizeof(int));

	

	read(sockfd, &answer, sizeof(int));
	printf("Server - The Answer is %d\n\n", answer);

	if(choice != 5){
		goto START;
	}


QUIT:
	printf("Exited Succesfully!!");
	close(sockfd);
	return 0;
}
