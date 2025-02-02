/*
	filename server_ipaddress portno
	
	argv[0] = filename
	argv[1] = server_ipaddress
	argv[2] = portno
*/
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
	
	while(1){
		bzero(buffer, 255);
		fgets(buffer, 255, stdin);
		n = write(sockfd, buffer, strlen(buffer));
		if(n < 0){
			error("Error on Writing");
		}
		bzero(buffer, 255);
		n = read(sockfd, buffer , 255);
		if(n < 0){
			error("Error on Reading");
		}
		printf("Server :%s", buffer);

		if(strncmp("Bye", buffer, 3)==0){
			break;
		}
	}
	close(sockfd);
	return 0;
}

/*
	#include<netdb.h> ==> for struct hostent *server; {store the info of given host such as internet protcol,etc}
	gethostbyname(argv[1]); in built function for the checking ip address for server
*/