/*
 * name: Alex Shatberashvili	
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

 static int BUFFER_SIZE = 256;
 static int DEFAULT_CHUNCK_SIZE = 64;

//fileserver ip_to_bind port_to_listen
int main(int argc, char *argv[]){
	int sockfd, newsockfd, portnum, s, clilen, flen, data_recieved;
	char *ip_addr, *filename;
	struct sockaddr_in serv_addr, cli_addr;
	char buffer[BUFFER_SIZE];
	FILE *fp;
	//check the arg count
	if (argc < 2) {
		fprintf(stderr, "insufficient ammount of arguments\n");
		exit(0);
	}
	//fetch the arguments
	portnum = atoi(argv[2]);
	ip_addr = argv[1];
	//create the socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0){ 
        fprintf(stderr,"ERROR opening socket");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(portnum);
    s = inet_pton(AF_INET, ip_addr, &(serv_addr.sin_addr));
  	if (s <= 0) {
        if (s == 0)
            fprintf(stderr, "Not in presentation format");
        else
            fprintf(stderr,"inet_pton");
        exit(EXIT_FAILURE);
    }
	if(bind(sockfd, (struct sockaddr *) &serv_addr, 
		sizeof(serv_addr)) < 0){ 
		fprintf(stderr, "ERROR on binding");
			exit(0);
    	}
    printf("Listening for connection")
    listen(sockfd,5);
    clilen = sizeof(cli_addr);
	newsockfd = accept(sockfd, 
	(struct sockaddr *) &cli_addr, &clilen);
	if(newsockfd<=0){
		fprintf(stderr, "Not in presentation format");
		exit(0);
	} 
	else{
		printf("Accepted Connection");
	}
	//get the filename length
	read(newsockfd, &flen, sizeof(int));
	//get the filename
	char filename[flen];
	read(newsockfd, filename, flen);
	//create the new file to be copied into
	fp = fopen(filename, "wb");
	if(fp == NULL){
		fprintf(stderr, "Can't create the file");
		exit(0);
	}
	while((data_received = read(newsockfd, buffer, BUFFER_SIZE)) >0){
		fwrite(buffer, 1, data_received, fp);
	}


	fclose(fp);
	close(newsockfd);
	close(sockfd);
	exit(0);
}