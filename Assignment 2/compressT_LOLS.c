#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

int main(){

  int i = 2;
  int pid;

  while (i>0) {
    pid = fork();
    i--;
  }

 if (pid == 0) {
    printf("I am the child\n");
 }
 else{
    printf("I am the parent and child is %d\n", pid);
 }

 return 0;
}
