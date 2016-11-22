#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int c, char** argv){
	printf("executed");
	char* filename = argv[1];
	FILE* f = fopen(filename, "r");
	
	int start = atoi(argv[2]);
	int stop = atoi(argv[3]);
	int number = atoi(argv[4]);
	
	char* str = malloc(stop - start + 1);
	
	fseek(f, start, SEEK_SET);
	fread(str, stop - start + 1, 1, f);
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
	sprintf(newfile, "LOLS%d", number);
	f = fopen(newfile, "w+");
	fprintf(f, "%s", answer);
	fclose(f);
	exit(0);
	
	//return 0;

}


