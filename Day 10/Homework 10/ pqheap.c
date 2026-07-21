/* Homework 10 - Task 2 - Priority Queue Using A Heap
 * ask for a number to add, then generate random numbers to queue
 & store numbers in a heap, which is min-heap，
 & using heapifyUp and heapifyDown functions to put the smallest element at the top instead of the largest element.
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

/* Create and initialize an empty priority queue */
pq *createPQ(int initialSize) {
    pq *pQueue = malloc(sizeof(pq)); 
    pQueue->a = malloc(initialSize * sizeof(int));
    pQueue->n = 0;
    pQueue->aSize = initialSize;
    return (pQueue);
}

/* Expand backing array when full */
void expandPQ(pq *pQueue) {
    pQueue->aSize *= 2; // double the capacity when the queue is full
    int *newArray = malloc(pQueue->aSize * sizeof(int));

    for(int i = 0; i < pQueue->n; i++) {
        newArray[i]=pQueue->a[i];  // copy existing element into the new array
    }

    free(pQueue->a); // free the old array and replace it
    pQueue->a = newArray;
}

/* Restore min-heap after insertion */
void heapifyUp(pq *pQueue, int index) {
    if (index <= 0) {
        return;
    }
    else {
        int parent = (index-1)/2;
        if (pQueue->a[index] < pQueue->a[parent]) { //min heap is child < parent
            int temp = pQueue->a[index];
            pQueue->a[index] = pQueue->a[parent];
            pQueue->a[parent] = temp;
            
            heapifyUp(pQueue, parent);
        }
    }
}

/* Restore min-heap after deletion */
void heapifyDown(pq *pQueue, int index) {
    int left = (2*index) +1;     // find the left child
    int right = (2*index) +2;     // find the right child

    // assume current node is the smallest
    int smallest = index;

    // if left child is smaller than current
    if ((left < pQueue->n) && (pQueue->a[left] < pQueue->a[smallest]))
    {
        smallest = left;
    }

    // if right child is smaller than current smallest
    if ((right < pQueue->n) && (pQueue->a[right] < pQueue->a[smallest]))
    {
        smallest = right;
    }

    // swap if one child is smaller
    if (smallest != index)
    {
        int temp = pQueue->a[index];
        pQueue->a[index] = pQueue->a[smallest];
        pQueue->a[smallest] = temp;

        heapifyDown(pQueue, smallest);
    }
}

/* Enqueue and insert value to minheap */
void pqEnqueue(pq *pQueue, int value) {
    if (pQueue->n >= pQueue->aSize) {
        expandPQ(pQueue);
    }

    pQueue->a[pQueue->n] = value;
    pQueue->n++; // increase heap size
    heapifyUp(pQueue, pQueue->n - 1); // call heapifyUp
}

/* Dequeue, remove and return the smallest value*/
int pqDequeue(pq *pQueue) {
    // when queue is empty
    if(pQueue->n == 0) { 
        return (-1); // break the program
    }

    int value = pQueue->a[0];
    pQueue->a[0] = pQueue->a[pQueue->n - 1];
    pQueue->n--; 
    heapifyDown(pQueue, 0); // heapifyDown
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