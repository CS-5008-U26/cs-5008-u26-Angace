#include <stdio.h>
#include <stdlib.h>
#include "pqueue.h"

/*
 * Priority Queue (Min-Heap) Implementation: An array-based Min-Heap implementation of a Priority 
 * Queue used for A* and Dijkstra's pathfinding algorithms.
 */

void pqInit(PriorityQueue *pq, int capacity)
{
    (void)capacity;
    pq->size = 0;
}

void pqFree(PriorityQueue *pq)
{
    pq->size = 0;
}

static void pqSwap(PQEntry *a, PQEntry *b)
{
    PQEntry tmp = *a;
    *a = *b;
    *b = tmp;
}

/* Restore min-heap property upward from a given index */
static void heapifyUp(PQEntry *a, int here)
{
    int parent = (here - 1) / 2;

    if (here != 0 && a[here].priority < a[parent].priority) {

        pqSwap(&a[here], &a[parent]);
        heapifyUp(a, parent);

    }
}

/* Restore min-heap property downward from a given index */
static void heapifyDown(PQEntry *a, int n, int here)
{
    int child1 = 2 * here + 1;
    int child2 = 2 * here + 2;
    int smallest = here;

    if (child1 < n && a[child1].priority < a[smallest].priority) {
        smallest = child1;
    }
    if (child2 < n && a[child2].priority < a[smallest].priority) {
        smallest = child2;
    }

    if (smallest != here) {
        pqSwap(&a[here], &a[smallest]);
        heapifyDown(a, n, smallest);
    }
}

/* Enqueue operation */
void pqPush(PriorityQueue *pq, int row, int col, int priority)
{
    if (pq->size >= MAX_HEAP_SIZE) {
        return;
    }

    pq->data[pq->size].row = row;
    pq->data[pq->size].col = col;
    pq->data[pq->size].priority = priority;

    pq->size++;
    heapifyUp(pq->data, pq->size - 1);
}

/* Dequeue operation */
PQEntry pqPop(PriorityQueue *pq)
{
    PQEntry min = pq->data[0];

    pq->data[0] = pq->data[pq->size - 1];
    pq->size--;

    if (pq->size > 0) {
        heapifyDown(pq->data, pq->size, 0);
    }

    return min;
}

int pqEmpty(const PriorityQueue *pq)
{
    return pq->size == 0;
}

int pqSize(const PriorityQueue *pq)
{
    return pq->size;
}

/* Extract top N entries for UI preview without modifying the priority queue */
void pqTopN(const PriorityQueue *pq, PQEntry *out, int n, int *outCount)
{
    int count = (pq->size < n) ? pq->size : n;
    
    if (count == 0) {
        *outCount = 0;
        return;
    }

    PQEntry copy[MAX_HEAP_SIZE];
    for (int i = 0; i < pq->size; i++) {
        copy[i] = pq->data[i];
    }

    /* Selection sort to collect top N elements for display */
    for (int i = 0; i < count; i++) {
        int minIdx = i;
        for (int j = i + 1; j < pq->size; j++) {
            if (copy[j].priority < copy[minIdx].priority) {
                minIdx = j;
            }
        }
        pqSwap(&copy[i], &copy[minIdx]);
        out[i] = copy[i];
    }

    *outCount = count;
}
