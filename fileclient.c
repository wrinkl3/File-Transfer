/*
 * name: Alex Shatberashvili	
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <libgen.h> 
#include <unistd.h>

//fileclient ip_of_fileserver port_to_connect file_to_send
int main(int argc, char *argv[]){
	int sockfd, portnum, s, flen, size;
	char *server_ip, *file_addr, *filename;
	struct sockaddr_in serv_addr;
	FILE *fp;

	//checking the arg count
	if (argc < 4) {	
		fprintf(stderr,"insufficient arguments\n");
		exit(0);
	}
	//fetch the arguments
	server_ip = argv[1];
	file_addr = argv[3];
	filename = basename(file_addr);
	portnum = atoi(argv[2]);

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0){ 
        fprintf(stderr,"ERROR opening socket");
        exit(0);
    }
    printf("sending file %s to %s\n",file_addr,server_ip);
	//fill in the socket
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(portnum);
	s = inet_pton(AF_INET, server_ip, &(serv_addr.sin_addr));
  	if (s <= 0) {
        if (s == 0)
            fprintf(stderr, "Not in presentation format");
        else
            fprintf(stderr,"inet_pton");
        exit(EXIT_FAILURE);
    }
    //connect to the server
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){
        fprintf(stderr, "ERROR connecting");
        exit(0);
    }
    else{
    	printf("connected to %s on tcp %d\n", server_ip, portnum);
    }
    //open the file
    fp = fopen(file_addr, "rb");
    if(fp == NULL){
    	printf("can't open file %s\n", file_addr);
        exit(0);
    }
    else
    	printf("opened file %s\n", file_addr);
    //get file size
	fseek(fp, 0L, SEEK_END);
	size = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
    //count the name string length
    flen = strlen(filename);
    flen++; //account for the null terminator
    //send header info
    write(sockfd, &flen, sizeof(int));
    write(sockfd, filename, flen);
    //send the file
    printf("start sending file\n");
    int fd = fileno(fp);
    sendfile(sockfd, fd, NULL, size);
    printf("finish sending file\n");
    printf("closing file %s\n", file_addr);
    fclose(fp);
    printf("closing socket\n");
    close(sockfd);

    return 0;
}