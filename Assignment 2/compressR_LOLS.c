#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int char_count(FILE* f) {
	int count = 0;
	while (fgetc(f) != EOF) count++;
	rewind(f);
	return count;
}

int main(int argc, char** argv){
	
	FILE* f = fopen(argv[1], "r");
	int num_processes = atoi(argv[2]);
	int length = char_count(f);
	
	if(length < num_threads){				//if length of the string is less than the input threads, then the program stops
	
		printf("Your inputs are invalid.");
		return 0;
	
	}else if(length == 0){
	
		printf("Your file does not contain any inputs");
		return 0;
	
	}
	
	int size;
	if(length % num_processes == 0){		//breaks the strings up according the input number of processes
	
		size = length/num_processes;
	
	}else{
		
		size = (length/num_processes) + 1;
	
	}
	
	int remaining = length;
	int i;
	for(i = 0; i < num_processes; i++){		//breaks the strings up according the input number of processes
		printf("%d \n", size);
		if(remaining >= size){
		
			char start[255];
			sprintf(start, "%d", i * size);
			
			char stop[255];
			sprintf(stop, "%d", (i * size) + (size - 1));
			
			char number[255];
			sprintf(number, "%d", i);
			
			remaining -= size;
			
			if (fork() == 0) { //creates a new child process if fork equals 0
				execl("./compressR_worker_LOLS", "./compressR_worker_LOLS", argv[1], start, stop, number); //creates a new process and links to the worker file
			}
			
		}else{
		
			char start[255];
			sprintf(start, "%d", i * size);
			
			char stop[255];
			sprintf(stop, "%d", (i * size) + (remaining - 1));
			
			char number[255];
			sprintf(number, "%d", i);
			
			if (fork() == 0) {		//creates a new child process if fork equals 0
				execl("./compressR_worker_LOLS", "./compressR_worker_LOLS", argv[1], start, stop, number); //creates a new process and links to the worker file
			}
			
		
		}
	
	}
	
	while(wait(NULL) != -1){	//waits until all processes are completed before the program ends
	
		continue;
	
	}

	return 0;
			
}
