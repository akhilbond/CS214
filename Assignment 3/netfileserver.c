#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>

#define OPEN_CODE 1
#define CLOSE_CODE 2
#define READ_CODE 3
#define WRITE_CODE 4

#define PORT 12345

int counter = 0;

void empty(char* str, int len) {
	int i;
	for (i = 0; i < len; i++) {
		str[i] = '\0';
	}
}

void clientOpen(int fd){

	char pathname[256];
	int readpathname = read(fd, pathname, 255); //reads pathname from client
	
	char message[255];
	empty(message, 255);
	int rea = read(fd, message, 1); //reads flags from client
	int flag = atoi(message);
	
	int fileopen = open(pathname, flag); //opens the file
	
	if(fileopen == -1){
		message[0] = '0';
		int sendopen = write(fd, message, 1);//sends if the open was successful or not
	}else{
		message[0] = '1';
		int sendopen = write(fd, message, 1);//sends if the open was successful or not
		sprintf(message, "%d", fileopen);
		sendopen = write(fd, message, strlen(message));
	}	

}


void clientClose(int fd){

	char filedescriptor[256];
	int readfiledescriptor = read(fd, filedescriptor, 255); //reads file descriptor from client	
	int file = atoi(filedescriptor);
	int cl = close(file);
	if(cl != -1){
		char response[1];
		response[0] = '1';
		int res = write(fd, response, 1);
	}else{
		char response[1];
		response[0] = '0';
		int res = write(fd, response, 1);
	}


}


void clientRead(int fd){

	char filedescriptor[256];
	int readfiledescriptor = read(fd, filedescriptor, 255); //reads file descriptor from client
	int textFD = atoi(filedescriptor);
	
	char message[255];
	int rea = read(fd, message, 1); //reads number of bytes from client
	int bytes = atoi(message);
	empty(message, 255);
	
	void* buff[bytes];
	int fileread = read(textFD, buff, bytes); //reads the file
	
	if(fileread == -1){
		message[0] = '0';
		int sendread = write(fd, message, 1);//sends if the read was successful or not
	}else{
		message[0] = '1';
		int sendread = write(fd, message, 1);//sends if the read was successful or not
		sprintf(message, "%d", sendread);
		sendread = write(fd, message, strlen(message));
	}
	empty(message, 255);
	
	
	
	
	
	sprintf(message, "%d", bytes);
	int sendbytes = write(fd, message, 1);//sends number of bytes to client
	
	int sendData = write(fd, buff, bytes);//sends void* buffer to client
	

}

void clientWrite(int fd){



	char filedescriptor[256];
	int readfiledescriptor = read(fd, filedescriptor, 255); //reads file descriptor from client
	int textFD = atoi(filedescriptor);
	
	
	
	
	
	
	char message[255];
	int rea = read(fd, message, 1); //reads number of bytes from client
	int bytes = atoi(message);
	empty(message, 255);
	
	
	
	
	void *buf[bytes];
	rea = read(fd, buf, bytes);//receives the buffer from the client
	
	


	int filewrite = write(textFD, buf, bytes); //writes to the file
	
	
	
	
	
	if(filewrite == -1){
		message[0] = '0';
		int sendwrite = write(fd, message, 1);//sends if the read was successful or not
	}else{
		message[0] = '1';
		int sendwrite = write(fd, message, 1);//sends if the read was successful or not
		sprintf(message, "%d", sendwrite);
		sendwrite = write(fd, message, strlen(message));
	}
	empty(message, 255);
	
	
	
	
	
	sprintf(message, "%d", bytes);
	int sendbytes = write(fd, message, 1);//sends number of bytes to client

}









void *handle(void* ptr){
	int *i = (int*)ptr;
	if(*i < 0){
		fprintf(stderr, "Cannot not send code to server %s", strerror(errno));
	}
	
	char code[1];
	int coderead = read(*i, code, 1); //reads the code for command
	int codes = atoi(code);
	if(codes == 0){
		clientOpen(*i);
	}else if(codes == 2){
		clientClose(*i);
	}else if(codes == 3){
		clientRead(*i);
	}else if(codes == 4){
		clientWrite(*i);
	}
	
	pthread_exit(0);
	counter--;

}







int main(){
	
	struct sockaddr_in socketAddress;
	
	//memset(&socketAddress, '0', sizeof(sockaddr_in));
	
	socketAddress.sin_family = AF_INET;
	socketAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	socketAddress.sin_port = htons(PORT);
	
	
	int socketfd = socket(AF_INET, SOCK_STREAM, 0);
	
	
	
	int bindfd = bind(socketfd, (struct sockaddr*)&socketAddress, sizeof(socketAddress)); 
	
	int listenfd = listen(socketfd, 10);
	
	struct sockaddr_in client_addr;
	unsigned int addrlen = sizeof(client_addr);
	
    while(1) {
    
    	int acceptfd = accept(socketfd, (struct sockaddr*)&client_addr, &addrlen);
    	
		int* parameter = malloc(sizeof(int));
		*parameter = acceptfd;
		
		pthread_t thread;
		if(counter < 10){
		
			counter++;
			pthread_create(&thread, NULL, handle,(void*)parameter);
    		
    	
    	}
    	
	}

	
	return 0;


};

//send
