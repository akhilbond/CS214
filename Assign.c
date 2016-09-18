#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char *strtok_t(char *str, int (*test)(int ch)){
  //Initalize pointers and variables
    static char *word = NULL;
    char *token;

    //If str is not null, they word pointer is at first character
    if(str != NULL){
        word = str;
    }

    if(word == NULL) return NULL; // if input string is empty, return NULL
    while(*word && !test(*word)){//skip delimiter if found
        ++word;
    }

    if(*word == '\0') return NULL; //If pointer reaches end of a word(delimiter), return NULL
    token=word; // assign current address of word to token

    //Keeps moving word pointer forward if the character is not a delimiter
    while(*word && test(*word)){
        ++word;
    }

    //Return NULL when the word pointer reaches the end of input string
    if(*word == '\0'){
        word = NULL;
    } else {
        *word++ = '\0';
    }
    return token;//Return the memory indexes of where the word was found
}

int main(int argc, char **argv){

    char *input = argv[1];
    char *token;
    int number = 1;
    char **strings = (char **)malloc(number*sizeof(char **));
    for(token = strtok_t(input, isalpha); token ; token = strtok_t(NULL, isalpha)){

    	strings = (char **)realloc(strings, number*sizeof(char **));
    	strings[number - 1] = token;
    	number++;

    }

    char **sorted = (char **)malloc(number*sizeof(char **));
    int index = 0;
    int temp;
    for(int counter = 0; counter < number - 1; counter++){

    	temp = 0;

    	while(strings[temp] == NULL){

    		temp++;

    	}

    	for(int i = 0; i < number - 1; i++){

    		if(strings[i] == NULL){

    			continue;

    		}

    		char test1[strlen(strings[temp])];
    		char test2[strlen(strings[i])];

    		for(int a = 0; a < strlen(strings[temp]); a++){
    			test1[a] = tolower(strings[temp][a]);
    		}
    		for(int a = 0; a < strlen(strings[i]); a++){
    			test2[a] = tolower(strings[i][a]);
    		}

    		if(strcmp(test1, test2) > 0){

    			temp = i;

    		}

    	}

    	sorted[index] = strings[temp];
    	strings[temp] = NULL;
    	index++;


    }

    free(strings);

    for(int a = 0; a < number - 1; a++){ //Prints out the alphabetically sorted results of the string

    	printf("%s \n", sorted[a]);

    }

	free(sorted);


    return 0;
}
