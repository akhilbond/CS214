#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int c, char** argv){	
	
	char* filename = argv[1];
	FILE* f = fopen(filename, "r");
	
	int start = atoi(argv[2]);
	int stop = atoi(argv[3]);
	int number = atoi(argv[4]);
	
	char* str = malloc(stop - start + 1 + 1); //mallocs the str variable accordingly
	
	fseek(f, start, SEEK_SET);
	fread(str, stop - start + 1, 1, f);
	str[stop - start + 1] = '\0';
	fclose(f);
	
	int l = strlen(str);
	char* string = malloc(l + 1);
	
	int e;
	int d = 0;
	for(e = 0; e < l; e++){
		
		if((str[e] >= 'A' && str[e] <= 'Z') || (str[e] >= 'a' && str[e] <= 'z')){	//iterates through the string to eliminate non-alphabetic characters
		
			string[d] = str[e];
			d++;
		
		}
	
	}
	
	int length = strlen(string);
	char* answer = malloc(length+1);
	answer[0] = '\0';
	int count = 0;
	int i;
	for(i = 0; i < length; i++){		//iterates through the tokenized string for LOLS compression
		
		if(i + 1 < length && string[i] == string[i+1]){
			
			count++;		
			continue;
		
		}
		
		count++;
		if(count == 1){		//If count equals one, then the output is only the character
		
			sprintf(answer, "%s%c", answer, string[i]);
				
		}else if(count == 2){		//If count equals one, then the output is the two characters
		
			sprintf(answer, "%s%c", answer, string[i]);
			sprintf(answer, "%s%c", answer, string[i]);
				
		}else{		//If count is greater than 2, then the output is the number with the character next to it
		
			
			sprintf(answer, "%s%d", answer, count);
			sprintf(answer, "%s%c", answer, string[i]);
						
		}
		
		count = 0;
	
	}
	
	
	
	
	char newfile[255];
	sprintf(newfile, "LOLS%d", number);
	f = fopen(newfile, "w+");		//creates a new output file and writes to it
	fprintf(f, "%s", answer);
	fclose(f);		//closes the file
	exit(0);		//exits the process
	
	//return 0;

}


