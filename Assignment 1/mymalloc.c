#include <mymalloc.h>
#include <stdio.h>
#define MEMSIZE 5000
#define ENTRY_SIZE sizeof( MemEntry )

// Creating boolean data type
typedef enum {false =0, true} bool;

typedef enum {
        MALLOC_INSUFFICIENT,
        FREE_REDUNDANT,
        FREE_NOT_ALLOCATED,
        FREE_MIDDLE
} Error;

static char[MEMSIZE] = {'0'};

typedef struct MemEntry MemEntry;
typedef struct MemEntry* MemEntryPtr;

struct MemEntry {
        //Previous
        MemEntryPtr prev;

        //Next
        MemEntryPtr next;

        //Status of the block of memory
        bool isFree;

        // fileFree indicates the file containing the free command which frees the entry
        char *fileFree;

        // lineFree indicates the line containing the free command which frees the entry
        int lineFree;
        // Available size for or the size of the data
        // When isFree-d, it stores the available size for allocation
        // Otherwise, size is the size of memory allocated
        unsigned size;
};

// shows whether the head is made or not
static bool initialized = false;
// head pointer
static MemEntryPtr head;

void errorReport(char* file, int caller_line, Error error void* address){
        fprintf(stderr, "%s:%d: error: ", file, caller_line);
        switch (error) {
        case MALLOC_INSUFFICIENT:
                fprintf(stderr,"Memory is insufficient to malloc().");
                break;
        case FREE_REDUNDANT:
                fprintf(stderr,"Memory @%p is already free-d.", address);
                break;
        case FREE_NOT_ALLOCATED:
                fprintf(stderr,"Memory @%p is not pre-allocated.",address);
                break;
        case FREE_MIDDLE:
                fprintf(stderr,"Memory @%p is not the previously returned address by malloc().",address);
                break;
        }
        printf("\n");
}

void* myMalloc(unsigned size, char* file, int caller_line){
        if(!initialized) {
                //initialize the head
                head = (MemEntryPtr) mem;
                head->prev = NULL;
                head->next = NULL;
                head->isFree = true;
                head->fileFree = NULL;
                head->lineFree = 0;
                head->size = MEMSIZE - ENTRY_SIZE;
                initialized = true;
        }

        MemEntryPtr temp = head;

        //While the tracking node is not null
        while (temp != NULL) {
                //the node is freed
                if (temp->isFree && temp->size >= size + ENTRY_SIZE) {
                        MemEntryPtr newEntry = (MemEntryPtr)( ((char)temp) + ENTRY_SIZE + size);
                        newEntry->prev = temp;
                        newEntry->next = temp->next;
                        temp->next = newEntry;
                        if (newEntry->next!=NULL) {
                                newEntry->next->prev = newEntry;
                        }

                        newEntry->isFree = true;

                        //Adjust current available size of entry
                        newEntry->size = temp->size - size -ENTRY_SIZE;

                        temp->isFree = false;
                        temp->size = size;
                        return (void*) ((char*)temp)+ENTRY_SIZE;
                }
                temp = temp->next;
        }
        // Not enough space to malloc
        errorReport(file,caller_line, MALLOC_INSUFFICIENT, 0);
        return NULL;
}
