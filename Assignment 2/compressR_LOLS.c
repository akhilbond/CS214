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
	int size;
	if(length % num_processes == 0){
	
		size = length/num_processes;
	
	}else{
		
		size = (length/num_processes) + 1;
	
	}
	
	int remaining = length;
	int i;
	for(i = 0; i < num_processes; i++){
		printf("%d \n", size);
		if(remaining >= size){
		
			char start[255];
			sprintf(start, "%d", i * size);
			
			char stop[255];
			sprintf(stop, "%d", (i * size) + (size - 1));
			
			char number[255];
			sprintf(number, "%d", i);
			
			remaining -= size;
			
			if (fork() == 0) {
				execl("./compressR_worker_LOLS", "./compressR_worker_LOLS", argv[1], start, stop, number);
			}
			
		}else{
		
			char start[255];
			sprintf(start, "%d", i * size);
			
			char stop[255];
			sprintf(stop, "%d", (i * size) + (remaining - 1));
			
			char number[255];
			sprintf(number, "%d", i);
			
			if (fork() == 0) {
				execl("./compressR_worker_LOLS", "./compressR_worker_LOLS", argv[1], start, stop, number);
			}
			
		
		}
	
	}
	
	while(wait(NULL) != -1){
	
		continue;
	
	}

	return 0;
			
}
