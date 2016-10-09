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

    char *input = argv[1]; //stores the input from the user as a string variable

    if(strcmp(input, "") == 0){ //if the input is a blank string, the following message is printed out.

    	printf("Input does not contain any alphabetical characters and therefore cannot be sorted \n");
    	return 0;

    }

    char *token;
    int number = 1;
    char **strings = (char **)malloc(number*sizeof(char **));


    //The following loop runs through the string and splits the string according to the delimiters.  Then it saves each string into an expandable array.
    for(token = strtok_t(input, isalpha); token ; token = strtok_t(NULL, isalpha)){

    	strings = (char **)realloc(strings, number*sizeof(char **));
    	strings[number - 1] = token;
    	number++;

    }


    char **sorted = (char **)malloc(number*sizeof(char **)); //declared a new array which has a size of the array of the tokenized strings
    int index = 0;
    int temp;
    int counter;
    for(counter = 0; counter < number - 1; counter++){ //iterates through the array of strings

    	temp = 0;

    	while(strings[temp] == NULL){ //checks if a particular element of an array is null; if, so it will continue to the next element

    		temp++;

    	}
    	int i;

    	//The following loop is to make alphabetic comparisons
    	for(i = 0; i < number - 1; i++){

    		if(strings[i] == NULL){

    			continue;

    		}

    		char test1[strlen(strings[temp])]; //creates a temporary string
    		char test2[strlen(strings[i])];

    		int a;
    		for(a = 0; a < strlen(strings[temp]); a++){ // converts the a particular string of an unsorted array to all lower case
    			test1[a] = tolower(strings[temp][a]);
    		}
    		for(a = 0; a < strlen(strings[i]); a++){
    			test2[a] = tolower(strings[i][a]);
    		}

    		if(strcmp(test1, test2) > 0){ // compares 2 two strings alphabetic-wise
    									//If test2 is alphabetically higher than test1, then the pointer will switch to test1.
    			temp = i;

    		}

    	}

    	sorted[index] = strings[temp]; //stores the string into the sorted array
    	strings[temp] = NULL; //
    	index++;


    }

    free(strings);
    int print;
    for(print = 0; print < number - 1; print++){ //Prints out the alphabetically sorted results of the string

    	printf("%s \n", sorted[print]);

    }

	free(sorted);


    return 0;
}
