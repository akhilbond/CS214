#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include "libnetfiles.h"

static int socketfd;

int netserverinit(const char * hostname){
	
	
	int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
    portno = 12345;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
    	return -1;
    server = gethostbyname(hostname);
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        return -1;
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
    	return -1;
    socketfd = sockfd;
    return 0;
    
}

void netserverdestroy() {
	close(socketfd);
}

void empty(char* str, int len) {
	int i;
	for (i = 0; i < len; i++) {
		str[i] = '\0';
	}
}

int netopen(const char *pathname, int flags){ 

	if(flags == O_RDONLY){
		status = O_RDONLY;
	}else if(flags == O_WRONLY){
		status = O_WRONLY;
	}else if(flags == O_RDWR){
		status = O_RDWR;
	}
	
	char message[255];
	
	
	sprintf(message, "%d", OPEN_CODE); 
	ssize_t sendCode = write(socketfd, message, strlen(message)); //send code for open to server
	
	if(sendCode != strlen(message)){ //checks for error for the code sent
		fprintf(stderr, "Cannot not send code to server: %s", strerror(errno));
		return -1;
	}
	
	
	
	
	
	
	sprintf(message, "%s", pathname);
	ssize_t sendPathname = write(socketfd, message, strlen(message)); //sends the pathname(or filename) to server
	
	if(sendPathname != strlen(message)) {
		fprintf(stderr, "Cannot not send pathname to server: %s", strerror(errno));
		return -1;
	}
	
	sprintf(message, "%d", flags);
	ssize_t sent = write(socketfd, message, strlen(message)); //sends the flag to server
	
	if (sent != strlen(message)) {
		fprintf(stderr, "Cannot send flags to server: %s", strerror(errno));
		return -1;
	}
	
	
	
	
	empty(message,255);
	
	int readCode = read(socketfd, message, 1); //reads a flag from server saying if open was successful or not
	int i = atoi(message);
	if(!i){
		fprintf(stderr, "Cannot open file: %s", strerror(errno));
		return -1;
	}
	
	empty(message,255);
	
	int readFileDescriptor = read(socketfd, message, 255); //reads the file discriptor from server
	int fd;
	sscanf(message," %d",&fd);
	
	return fd;
	
}






ssize_t netread(int filedes, void* buff, size_t nbyte){

	if(status == O_WRONLY){
		fprintf(stderr, "Request does not match: %s", strerror(errno));
		return -1;
	}
	
	
	char message[255];
	
	sprintf(message, "%d", READ_CODE); 
	ssize_t sendCode = write(socketfd, message, strlen(message)); //send code for read to server
	
	if(sendCode != strlen(message)){
		fprintf(stderr, "Cannot not send code to server: %s", strerror(errno));
		return -1;
	}
	
	
	
	
	sprintf(message, "%d", filedes);
	ssize_t sendFiledes = write(socketfd, message, strlen(message)); //sends the file discriptor to server
	
	if(sendFiledes != strlen(message)) {
		fprintf(stderr, "Cannot not send file descriptor to server: %s", strerror(errno));
		return -1;
	}
	empty(message, 255);
	
	
	
	
	
	
	sprintf(message, "%zu", nbyte);
	ssize_t sent = write(socketfd, message, strlen(message)); //sends number of bytes to server
	if (sent != strlen(message)) {
		fprintf(stderr, "Cannot send flags to server: %s", strerror(errno));
		return -1;
	}
	empty(message, 255);
	
	
	
	
	
	
	
	
	
	int readCode = read(socketfd, message, 1); //reads a flag from server saying if read was successful or not
	int i = atoi(message);
	if(!i){
		fprintf(stderr, "Cannot read file: %s", strerror(errno));
		return -1;
	}
	
	empty(message,255);
	
	
	
	
	
	
	
	int readBytes = read(socketfd, message, 255); //reads the number of bytes from server
	int bytes;
	sscanf(message, " %d", &bytes);
	empty(message, 255);
	
	
	
	
	int rea = read(socketfd, buff, 255); //reads the data read as void* buff from client
	
	
	return bytes;


}






ssize_t netwrite(int fildes, const void *buf, size_t nbyte){

	if(status == O_RDONLY){
		fprintf(stderr, "Request does not match: %s", strerror(errno));
		return -1;
	}
	
	char message[255];
	
	
	sprintf(message, "%d", WRITE_CODE); 
	ssize_t sendCode = write(socketfd, message, strlen(message)); //send code for write to server
	
	if(sendCode != strlen(message)){
		fprintf(stderr, "Cannot not send code to server: %s", strerror(errno));
		return -1;
	}
	
	
	
	
	
	
	sprintf(message, "%d", fildes);
	ssize_t sendPathname = write(socketfd, message, strlen(message)); //sends the file descriptor to server
	
	if(sendPathname != strlen(message)) {
		fprintf(stderr, "Cannot not send pathname to server: %s", strerror(errno));
		return -1;
	}
	
	
	
	sprintf(message, "%zu", nbyte);
	ssize_t sent = write(socketfd, message, strlen(message)); //sends the number of bytes to server
	
	if (sent != strlen(message)) {
		fprintf(stderr, "Cannot send flags to server: %s", strerror(errno));
		return -1;
	}
	
	empty(message,255);
	
	
	
	int sendData = write(socketfd, buf, nbyte); //sends the buffer to server
	
	
	
	
	
	
	
	
	
	
	
	
	int readCode = read(socketfd, message, 1); //reads a flag from server saying if write was successful or not
	int i = atoi(message);
	if(!i){
		fprintf(stderr, "Cannot write to file: %s", strerror(errno));
		return -1;
	}
	
	empty(message,255);
	
	
	
	
	
	
	int readBytes = read(socketfd, message, 255); //reads the numbers bytes from server
	int bytes;
	sscanf(message, " %d", &bytes);
	
	return bytes;

}







int netclose(int fd){

	
	char message[255];
	sprintf(message, "%d", fd);
	int send = write(socketfd, message, strlen(message)); //send fd to server
	empty(message, 255);
	
	int rec = read(socketfd, message, 1);
	if(!rec){
		fprintf(stderr, "Cannot close %s", strerror(errno));
		return -1;
	}
	
	return 0;
}



















