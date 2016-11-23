#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include <time.h>


int char_count(FILE* f) {  //method to count the number of characters in the file
	int count = 0;
	while (fgetc(f) != EOF) count++;
	rewind(f);
	return count;
}

typedef struct multi{	//creates a struct of the filename, thread number, start and stop indexes

	char* filename;
	int number;
	int start;
	int stop;

}multi;

void* compressfile(void* ptr){	//method for the child thread
	
	multi* args = (multi*) ptr;	//creates an instance of a struct multi pointer
	FILE* f = fopen(args->filename, "r");	//creates a file pointer and sets to read
	char* str = malloc(args->stop - args->start + 1 + 1);	//allocates enough space for the string
	fseek(f, args->start, SEEK_SET);	//moves the pointer to the wanted character
	fread(str, args->stop - args->start + 1, 1, f);	//reads the characters and store into a strings
	str[args->stop - args->start + 1] = '\0';
	fclose(f);		//closes the file pointer
	
	int l = strlen(str);		//stores the length of the string in l
	char* string = malloc(l + 1);		//mallocs space for string
	int e;
	int d = 0;
	for(e = 0; e < l; e++){		//iterates through the string to eliminate non-alphabetic characters
		
		if((str[e] >= 'A' && str[e] <= 'Z') || (str[e] >= 'a' && str[e] <= 'z')){	
			string[d] = str[e];
			d++;
		
		}
	
	}
	string[d] = '\0';
	
	int length = strlen(string);
	char* answer = malloc(length+1);
	answer[0] = '\0';
	int count = 0;
	int i;
	for(i = 0; i < length; i++){			//iterates through the tokenized string for LOLS compression
		
		if(i + 1 < length && string[i] == string[i+1]){	//checks if next character equals current character
			
			count++;		
			continue;
		
		}
		
		count++;
		if(count == 1){		//If count equals one, then the output is only the character
		
			sprintf(answer, "%s%c", answer, string[i]);
				
		}else if(count == 2){	//If count equals one, then the output is the two characters
		
			sprintf(answer, "%s%c", answer, string[i]);
			sprintf(answer, "%s%c", answer, string[i]);
				
		}else{				//If count is greater than 2, then the output is the number with the character next to it
		
			
			sprintf(answer, "%s%d", answer, count);
			sprintf(answer, "%s%c", answer, string[i]);
						
		}
		
		count = 0;
	
	}
	
	
	
	
	char newfile[255];				
	sprintf(newfile, "LOLS%d", args->number);		
	f = fopen(newfile, "w+");			//creates a new output file
	fprintf(f, "%s", answer);		
	fclose(f);						//closes the file
	free(args->filename);		//frees all the malloced variables
	free(args);
	pthread_exit(0);		//exits thread
}


int main(int argc, char** argv){
	
	
	FILE* f = fopen(argv[1], "r");		//creates a file pointer set to read only
	int num_threads = atoi(argv[2]);		
	pthread_t threads[num_threads];
	int length = char_count(f);
	
	if(length < num_threads){				//if length of the string is less than the input threads, then the program stops
	
		printf("Your inputs are invalid.");
		return 0;
	
	}else if(length == 0){
	
		printf("Your file does not contain any inputs");
		return 0;
	
	}
	
	
	int size;
	
	if(length % num_threads == 0){		//breaks the strings up according the input number of threads
	
		size = length/num_threads;
	
	}else{
		
		size = (length/num_threads) + 1;
	
	}
	
	int remaining = length;
	int i;
	for(i = 0; i < num_threads; i++){
		
		multi* mul = malloc(sizeof(multi));
		
		if(remaining >= size){				//populates the struct mul acconding to the input size
		
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
			
			pthread_create(&threads[i], NULL, compressfile, (void*)mul);	//creates a child thread
		
		}
	
	}
	
	int j;
	for(j = 0; j < num_threads; j++){			//waits on each thread until all the threads are completed before the parent thread closes
	
		pthread_join(threads[j], NULL);
	
	}
	
		
	return 0;
			
}








