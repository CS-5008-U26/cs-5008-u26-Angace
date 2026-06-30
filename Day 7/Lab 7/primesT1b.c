/* Lab7 - Task 1B
 * Find prime numbers for approximately 0.5 seconds.
 * Use trial division up to the square root of the candidate.
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Linked list node */

typedef struct intNode {
    long long value;
    struct intNode *next;
} node;

/* Create a new node */

node *createNode(long long x)
{
    node *newNode = malloc(sizeof(node));

    if (newNode == NULL) {
        return NULL;
    }

    newNode->value = x;
    newNode->next = NULL;

    return newNode;
}

int main(void)
{
    char s[100];
    clock_t startTime = clock();

    /* Linked list of primes */

    node *primes = NULL;

    long long i;
    long long lastPrime = 2;

    /* Put the first prime into the list */

    node *newNode = createNode(2);

    if (newNode == NULL) {
        return 1;
    }

    primes = newNode;

    /* Search odd numbers forever (until time expires) */

    for (i = 3; ; i += 2) {

        int isPrime = 1;

        node *current = primes;

        /* Test only prime divisors */

        while (current != NULL) {

            if (i % current->value == 0) {

                isPrime = 0;
                break;
            }

            current = current->next;
        }

        if (isPrime) {

            lastPrime = i;

            newNode = createNode(i);

            if (newNode == NULL) {
                break;
            }

            /* Insert at the FRONT of the list */

            newNode->next = primes;
            primes = newNode;

            clock_t endTime = clock();

            double elapsed =
                (double)(endTime - startTime) / CLOCKS_PER_SEC;

            if (elapsed >= 0.5) {
                break;
            }
        }
    }

    while (primes != NULL) {
        node *next = primes->next;
        free(primes);
        primes = next;
    }

    printf("Largest prime found in 0.5 seconds: %lld\n", lastPrime);

    fgets(s, 100, stdin); 
    return 0;
}