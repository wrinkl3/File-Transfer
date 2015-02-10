#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

//fileclient ip_of_fileserver port_to_connect file_to_send
int main(int argc, char *argv[]){
	int sockfd, portnum, n;
    struct sockaddr_in serv_addr;
    char buffer[256];

    if (argc < 4) {
       printf("insufficient ammount of arguments\n");
       exit(0);
    }
    portnum = atoi(argv[2]);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
}