#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>

int char_count(FILE* f) {
	int count = 0;
	while (fgetc(f) != EOF) count++;
	rewind(f);
	return count;
}

typedef struct multi{

	char* filename;
	int number;
	int start;
	int stop;

}multi;

void* compressfile(void* ptr){
	
	multi* args = (multi*) ptr;
	FILE* f = fopen(args->filename, "r");
	char* str = malloc(args->stop - args->start + 1);
	fseek(f, args->start, SEEK_SET);
	fread(str, args->stop - args->start + 1, 1, f);
	fclose(f);
	
	int l = strlen(str);
	char* string = malloc(l + 1);
	int e;
	int d = 0;
	for(e = 0; e < l; e++){
		
		if(isalpha(str[e]) == 1){
			
			string[d] = str[e];
			d++;
		
		}
	
	}
	
	int length = strlen(string);
	char* answer = malloc(length+1);
	int count = 0;
	int i;
	for(i = 0; i < length; i++){
		
		if(i + 1 < length && string[i] == string[i+1]){
			
			count++;		
			continue;
		
		}
		
		count++;
		if(count == 1){
		
			sprintf(answer, "%s%c", answer, string[i]);
				
		}else if(count == 2){
		
			sprintf(answer, "%s%c", answer, string[i]);
			sprintf(answer, "%s%c", answer, string[i]);
				
		}else{
		
			
			sprintf(answer, "%s%d", answer, count);
			sprintf(answer, "%s%c", answer, string[i]);
						
		}
		
		count = 0;
	
	}
	
	
	
	
	char newfile[255];
	sprintf(newfile, "LOLS%d", args->number);
	f = fopen(newfile, "w+");
	fprintf(f, "%s", answer);
	fclose(f);
	free(args->filename);
	free(args);
	pthread_exit(0);
}


int main(int argc, char** argv){
	
	FILE* f = fopen(argv[1], "r");
	int num_threads = atoi(argv[2]);
	pthread_t threads[num_threads];
	int length = char_count(f);
	int size;
	
	if(length % num_threads == 0){
	
		size = length/num_threads;
	
	}else{
		
		size = (length/num_threads) + 1;
	
	}
	
	int remaining = length;
	int i;
	for(i = 0; i < num_threads; i++){
		
		multi* mul = malloc(sizeof(multi));
		
		if(remaining >= size){
		
			mul->start = i * size;
			mul->stop = (i * size) + (size - 1);
			mul->number = i;
			mul->filename = malloc(strlen(argv[1] + 1));
			strcpy(mul->filename, argv[1]);
			
			remaining -= size;
			
			pthread_create(&threads[i], NULL, compressfile, (void*)mul);
			
		}else{
		
			mul->start = i * size;
			mul->stop = (i * size) + (remaining - 1);
			mul->number = i;
			mul->filename = malloc(strlen(argv[1] + 1));
			strcpy(mul->filename, argv[1]);
			
			pthread_create(&threads[i], NULL, compressfile, (void*)mul);
		
		}
	
	}
	
	int j;
	for(j = 0; j < num_threads; j++){
	
		pthread_join(threads[j], NULL);
	
	}
	
		
	return 0;
			
}








