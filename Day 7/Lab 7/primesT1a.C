/* Lab7 - Task 1A
 * Find prime numbers for approximately 0.5 seconds.
 * Use trial division up to the square root of the candidate.
 */

#include <stdio.h>
#include <time.h>

int main(void)
{
    char s[100];
    clock_t startTime = clock();

    long long i;
    long long j;
    int isPrime;

    long long lastPrime = 2;

    /* Keep searching until 0.5 seconds have elapsed */
    for (i = 3; ; i += 2) {

        isPrime = 1;

        /* Test divisibility up to sqrt(i) */
        for (j = 3; j * j <= i; j += 2) {

            if (i % j == 0) {

                isPrime = 0;
                break;
            }
        }

        if (isPrime) {

            lastPrime = i;

            clock_t endTime = clock();

            double elapsed =
                (double)(endTime - startTime) / CLOCKS_PER_SEC;

            if (elapsed >= 0.5)
                break;
        }
    }

    printf("Largest prime found in 0.5 seconds: %lld\n", lastPrime);

    fgets(s, 100, stdin); 
    return 0;
}