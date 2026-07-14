/* Homework 9 - Task 3.4 quick sort */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_TO_PRINT 100        // max number of elements to print
#define MAX_VALUE 100000000     // max value in randomly generated data

/* T E S T   C A S E   D A T A */

int test1[] =       { 3 };
int expected1[] =   { 3 };
int n1 =            1;
int test2[] =       { 5, 3 };
int expected2[] =   { 3, 5 };
int n2 =            2;
int test3[] =       { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
int expected3[] =   { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
int n3 =            10;
int test4[] =       { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
int expected4[] =   { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
int n4 =            10;
int test5[] =       { 2, 4, 6, 8, 10, 1, 3, 5, 7, 9 };
int expected5[] =   { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
int n5 =            10;
int test6[] =       { 1, 2, 3, 2, 2 };
int expected6[] =   { 1, 2, 2, 2, 3 };
int n6 =            5;

/* Y O U R   S O R T   F U N C T I O N */
/* Partition the array using the last element as the pivot */
int partition(int a[], int start, int end)
{
    int pivot = a[end]; // choose the last element as the pivot
    int separator = start - 1; //  last postion contains a value smaller than the pivot

    for (int i = start; i < end; i++){ //move the small element to the left side
        if (a[i] < pivot){
            separator++;

            int temp = a[separator];
            a[separator] = a[i];
            a[i] = temp;
        }
    }

    // put the pivot into its correct postion
    int temp = a[separator + 1];
    a[separator + 1] = a[end];
    a[end] = temp;

    return separator + 1;     // return the pivot position
}

/* Recursively sort the array from start to end */
void quicksort_helper(int a[], int start, int end)
{
    if (start >= end) { // base case
        return;
    }

    int pivotIndex = partition(a, start, end); // partition the array around the pivot

    quicksort_helper(a, start, pivotIndex - 1); // sort the left half
    quicksort_helper(a, pivotIndex + 1, end); // sort the right half
}

void sortarray(int a[], int n)
{
    /* Quick Sort */
    quicksort_helper(a, 0, n - 1);
}

/* U T I L I T Y   F U N C T I O N S */

// printarray = print an array of ints
// a is the array, n is the number of elements

void printarray(int a[], int n) {
    int numberToPrint = ((n < MAX_TO_PRINT) ? n : MAX_TO_PRINT);
    for (int i=0; i < numberToPrint; i++) {
        printf ("%d ", a[i]);
    }
    printf ("\n");
}

// genarray - return an array of random ints on the heap
// numberofelements is how many elements in the array
// the array is returned
// don't forget to free the array when you are finished using it

int *genarray(int numberofelements) {
    int *result = malloc (numberofelements * sizeof(int));
    if (result == NULL) {
        printf ("malloc failed");
    } else {
        // fill the result array with random numbers between 0 and MAX_VALUE
        for (int i=0; i<numberofelements; i++) {
            // we have a problem
            // On Windows the rand() function only gives a 15-bit random number
            // This will be between 0 and 32767
            // So we will fix this with a crude trick
            // We will generate two random numbers, one for the high-order bits and the other
            // for the low-order 14 bits
            long long int r1 = rand();
            long long int r2 = rand();
            long long int randomValue = (r1 << 14) + (r2 & 0x3fff);
            result[i] = (int)(randomValue % MAX_VALUE);
        }
    }   
    return (result);
}

// timedsort - runs a sort and records the elapsed time
// a is the array, n is how many elements

void timedsort (int a[], int n) {
    clock_t startTime = clock();        // get the start time
    sortarray (a, n);
    clock_t endTime = clock();          // get the end time
    double elapsedTime = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    printf ("Result: ");                // print the sorted data
    printarray(a, n);
    printf ("Elapsed time: %f seconds\n\n", elapsedTime);   // print the elapsed time
}

// testsort - runs a sort on a test case with known results
// a is the array, n is how many elements
// expected is the array with the expected correct values after sorting

void testsort (int a[], int n, int expected[]) {
    printf ("Test case: ");             // print the test data
    printarray(a, n);
    sortarray(a, n);
    printf ("Result: ");                // print the result of sorting
    printarray(a, n);
    int ok = 1;                         // print whether the result is correct
    for (int i=0; ok && (i<n); i++) {
        ok = (a[i] == expected[i]);
    }
    printf ("%s\n\n", (ok ? "PASSED" : "FAILED"));
}

/* M A I N   F U N C T I O N */
int main () {
    char s[100];
    char buffer[100];
    int nelements;
    int maxvalue;
    int *randomdata;

    srand(time(NULL));  // seed the random number generator

    // run test cases
    testsort(test1, n1, expected1);
    testsort(test2, n2, expected2);
    testsort(test3, n3, expected3);
    testsort(test4, n4, expected4);
    testsort(test5, n5, expected5);
    testsort(test6, n6, expected6);

    // run timed sorts
    int keepgoing = 1;
    while (keepgoing) {
        printf ("How many elements? ");
        fgets(buffer, 100, stdin);
        if (buffer[0] == '\n') {
            keepgoing = 0;
        } else {
            nelements = atoi(buffer);
            if (nelements <= 0) {
                printf ("Must be a positive number of elements\n");
            } else {
                randomdata = genarray(nelements);
                if (randomdata != NULL) {
                    timedsort(randomdata, nelements);
                    free (randomdata);
                }
            }
        }
    }

    // run timed sorts on sorted data.
    keepgoing = 1;
    while (keepgoing){
        printf("How many sorted elements? ");
        fgets(buffer, 100, stdin);

        if (buffer[0] == '\n'){
            keepgoing = 0;
        } else {
            nelements = atoi(buffer);

            if (nelements <= 0){
                printf("Must be a positive number of elements\n");
            } else {
                randomdata = malloc(nelements * sizeof(int));
                if (randomdata != NULL){
                    for (int i = 0; i < nelements; i++) {
                        randomdata[i] = i;
                    }

                    timedsort(randomdata, nelements);
                    free(randomdata);
                }
            }
        }
    }

    // run timed sorts on reverse sorted data.
    keepgoing = 1;
    while (keepgoing) {
        printf("How many reverse sorted elements? ");
        fgets(buffer, 100, stdin);

        if (buffer[0] == '\n'){
            keepgoing = 0;
        } else{
            nelements = atoi(buffer);

            if (nelements <= 0) {
                printf("Must be a positive number of elements\n");
            } else {
                randomdata = malloc(nelements * sizeof(int));
                if (randomdata != NULL) {
                    for (int i = 0; i < nelements; i++){
                        randomdata[i] = nelements - 1 - i;
                    }

                    timedsort(randomdata, nelements);
                    free(randomdata);
                }
            }
        }
    }

    fgets(buffer, 100, stdin);
    return 0;
}