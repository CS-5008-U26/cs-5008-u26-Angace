/* Homework 10 - Task 1 - Priority Queue using a Sorted Array
 * ask for a number to add, then generate random numbers to queue
 * ask for a number to remove 
 * show removed number from priority list in order from the lowest value
 * when user just hits ENTER instead of giving a number, the program stops
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TO_PRINT 100      // max number of elements to print
#define MAX_VALUE 1000000     // max value in randomly generated data

/* Create struct of priority queue */
typedef struct pqStruct {
    int *a;          // the backing store
    int n;           // number of values
    int aSize;       // the size of the backing store
} pq;

/* create and initialize an empty priority queue */
pq *createPQ(int initialSize) {
    pq *pQueue = malloc(sizeof(pq)); 
    pQueue->a = malloc(initialSize * sizeof(int));
    pQueue->n = 0;
    pQueue->aSize = initialSize;
    return (pQueue);
}

/* expand backing array when full */
void expandPQ(pq *pQueue) {
    pQueue->aSize *= 2; // double the capacity when the queue is full
    int *newArray = malloc(pQueue->aSize * sizeof(int));

    for(int i = 0; i < pQueue->n; i++) {
        newArray[i]=pQueue->a[i];  // copy existing element into the new array
    }

    free(pQueue->a); // free the old array and replace it
    pQueue->a = newArray;
}

/* Enqueue and sort value to array */
void pqEnqueue(pq *pQueue, int value) {
    if (pQueue->n >= pQueue->aSize) {
        expandPQ(pQueue);
    }

    int i = pQueue->n - 1;

    // switch larger values one position to the right
    while ((i >= 0) && (pQueue->a[i] > value)){
        pQueue->a[i + 1] = pQueue->a[i];
        i--;
    }

    pQueue->a[i + 1] = value; // insert the new value into its correct position
    pQueue->n++; // accumulate enqueue
}

/* Dequeue, remove and return the smallest value*/
int pqDequeue(pq *pQueue) {
    // when queue is empty
    if(pQueue->n == 0) { 
        return (-1); // break the program
    }

    int value = pQueue->a[0];

    //move remaining elements left by one position
    for(int i=1; i<pQueue->n; i++) {
        pQueue->a[i-1] = pQueue->a[i];
    }

    pQueue->n--; 
    return (value);
}

/* Generate random values and insert them into the priority queue */
void addRandomValues( pq *pQueue, int count) {
    for(int i=0; i<count; i++) {
        int value = rand() % MAX_VALUE;  // range [0, MAX_VALUE)
        pqEnqueue(pQueue, value);
    }
}

/* Remove values and print value in ascending order */
void removeValues(pq *pQueue, int count) {
    for(int i=0; i<count; i++) {
        if(pQueue->n == 0) {   //stop if the queue becomes empty
            break;
        }

        printf("%d ",pqDequeue(pQueue)); //Remove and display the smallest value
    }
}


/* ====== Main Function ======= */
int main()
{
    char s[100];
    srand(time(NULL));  // seed the random number generator

    // Create empty queue
    pq *pQueue = createPQ(100); // assign createPQ
    char input[100]; // buffer to hold user input

    while (1)
    {
        /* Ask user to add numbers  */
        printf("How many numbers to add: ");

        // break when user input nothing
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        // break when user just presses ENTER
        if (strcmp(input, "\n") == 0) {
            break;
        }

        int addCount = atoi(input); // convert the input string to an integer

        clock_t startTime = clock(); // get the start time
        addRandomValues(pQueue, addCount); // call addRandomValue function
        clock_t endTime = clock(); // get the end time
        double elapsedTime = (double)(endTime - startTime)/CLOCKS_PER_SEC;
        printf("Elapsed time: %.3f seconds\n\n", elapsedTime); // print the sorted time


        /* Ask user to remove number */
        printf("How many numbers to remove: ");
        
        // break if user input nothing
        if (fgets(input, sizeof(input), stdin) == NULL){
            break;
        }

        // break when user just presses ENTER
        if (strcmp(input, "\n") == 0){
            break;
        }

        int removeCount = atoi(input); // convert the input string to an integer

        clock_t startTimeRe = clock(); // get the start time
        removeValues(pQueue, removeCount); // call removeValues function
        clock_t endTimeRe = clock(); // get the end time
        double elapsedTimeRe = (double)(endTimeRe - startTimeRe)/CLOCKS_PER_SEC;
        printf("\nElapsed time: %.3f seconds\n\n", elapsedTimeRe); // print the sorted time
    }

    /* Free Memory */
    free(pQueue->a);
    free(pQueue);

    fgets(s, 100, stdin);
    return 0;
}