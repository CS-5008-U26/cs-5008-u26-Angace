/* Lab 2 - Task 3
* Print the prime numbers up to 100
* divide by every integer, starting with 2
*/

#include <stdio.h>
#include <time.h>

int main () {
    clock_t startTime = clock(); // Start the timer

    /*** we do our work ***/
    int i;  // integer variable to use as a loop counter
    int j;  // integer variables to use as loop counters
    int is_prime;  // integer variable to indicate whether a number is prime or not

    for (i = 2; i <= 100; i++) { // Loop from 2 to 100

        is_prime = 1; // Assume that i is prime until we find a divisor

        for (j = 2; j < i; j++) { // Loop from 2 to i-1
            if (i % j == 0) { // If i is divisible by j, then it is not prime
                is_prime = 0; // Set is_prime to 0 to indicate that i is not prime
                break; // Break out of the inner loop since we have found a divisor
            }
        }

        if (is_prime) { // If is_prime is still 1, then i is prime
            printf("%d\n", i); // Print the prime number to the console
        }
    }
    
    clock_t endTime = clock(); // End the timer
    double timeTaken = (double)((endTime - startTime) / CLOCKS_PER_SEC); // Calculate the CPU time used
    printf("Time taken: %f seconds\n", timeTaken); // Print the time taken to the console
    
    return 0; // Return 0 to indicate that the program ended successfully
}