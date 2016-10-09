#ifndef MALLOC_H
#define MALLOC_H

#ifndef NULL
#define NULL 0
#endif

#define malloc(x) myMalloc(x,__FILE__,__LINE__);
#define free(x) myFree(x,__FILE__,__LINE__);

/*
 *  My malloc implementation
 */
void* myMalloc(unsigned , char*, int);
/*
 *  My free implementation
 */
void myFree(void*, char*, int);

#endif
