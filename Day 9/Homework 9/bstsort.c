/* Homework 9 - Task 3.5 BST sort */

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
/* create BST node struct */
typedef struct bstNode_srtuct
{
    int value; // integer value of the node
    struct bstNode_srtuct *left; // pointer to the left child node
    struct bstNode_srtuct *right; // pointer to the right child node
} bstNode;

/* Create BST node */
bstNode *createBSTNode(int value)
{
    bstNode *node = malloc(sizeof(bstNode));  // allocate memory for the node
    node->value = value;    // set the value
    node->left = NULL;    // initialize left child to NULL
    node->right = NULL;   // initialize right child to NULL
    return (node);
}

/* Insert a value into the BST */
bstNode *bstInsert(bstNode *root, int x)
{
    if (root == NULL) {
        return createBSTNode(x); // create a new node if the root is NULL
    }
    if (x < root->value) {
        root->left = bstInsert(root->left, x); // insert into the left subtree
    } 
    else {
        root->right = bstInsert(root->right, x); // insert into the right subtree
    }
    return root; // return the unchanged root pointer
}

/* Inorder traversal of the BST to fill an array with sorted values */
void bstInOrder(bstNode *root, int a[], int *index)
{
    if (root == NULL) {
        return; // return if the root is NULL
    }
    else {
        bstInOrder(root->left, a, index); // traverse the left subtree
        a[*index] = root->value; // store the self value in the array, deference the index pointer to get the current index
        (*index)++; // increment the index
        bstInOrder(root->right, a, index); // traverse the right subtree
    }
}

/* Free the memory used by the BST */
void freeBST(bstNode *root)
{
    if (root == NULL) {
        return; // return if the root is NULL
    }
    else {
        freeBST(root->left); // free the left subtree
        freeBST(root->right); // free the right subtree
        free(root); // free the current node
    }
}

void sortarray (int a[], int n) {
    /* This is a BST sort*/

    /* create some bst root node, null */
    bstNode *root = NULL; // initialize the root of the BST to null

    /* insert each element into the bst */
    for (int i=0; i<n; i++) 
    {
        root = bstInsert(root, a[i]); // insert the element into the BST   
    }

    /* refill array with sorted values out of the BST */
    int index = 0; // initialize the index for filling the array
    bstInOrder (root, a, &index); // fill the array with sorted values
    
    freeBST(root); // free the memory used by the BST
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
                printf("Allocated %d elements\n", nelements);

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