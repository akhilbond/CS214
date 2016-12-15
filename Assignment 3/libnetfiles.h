#ifndef _CLIENTMETHODS
#define _CLIENTMETHODS

#define OPEN_CODE 1
#define CLOSE_CODE 2
#define READ_CODE 3
#define WRITE_CODE 4

#define O_RDONLY 0
#define O_WRONLY 1
#define O_RDWR 2

#include <unistd.h>

int status;

int netserverinit(const char *pathname);
int netopen(const char* pathname, int flags);
ssize_t netread(int filedes, void* buff, size_t nbyte);
ssize_t netwrite(int fildes, const void *buf, size_t nbyte);
int netclose(int fd);


void netserverdestroy();

#endif







