#include <stdio.h>
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

int main(void){
    char str[10000];
    printf("Enter anything to be tokenized : ");
    scanf("%[^\n]s", str);
    char *token;
    for(token = strtok_t(str, isalpha); token ; token = strtok_t(NULL, isalpha)){
        printf("%s\n", token);
    }
    return 0;
}
