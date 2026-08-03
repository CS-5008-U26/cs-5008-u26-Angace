#ifndef PQUEUE_H
#define PQUEUE_H

#include <stdbool.h>

#define MAX_HEAP_SIZE 3000  /* Safe capacity accounting for multiple node pushes */

/* Priority queue entry node structure */
typedef struct {
    int row;        // row
    int col;        // column
    int priority;   // Lower priority value means popped first
} PQEntry;

/* Priority queue structure encapsulating static array and size */
typedef struct {
    PQEntry data[MAX_HEAP_SIZE];
    int size;  //size of queue
} PriorityQueue;

/* Function prototypes */
void pqInit(PriorityQueue *pq, int capacity);
void pqFree(PriorityQueue *pq);

void pqPush(PriorityQueue *pq, int row, int col, int priority);
PQEntry pqPop(PriorityQueue *pq);

int pqEmpty(const PriorityQueue *pq);
int pqSize(const PriorityQueue *pq);

/* UI rendering helper: Copies and extracts top N highest-priority entries for display */
void pqTopN(const PriorityQueue *pq, PQEntry *out, int n, int *outCount);

#endif
