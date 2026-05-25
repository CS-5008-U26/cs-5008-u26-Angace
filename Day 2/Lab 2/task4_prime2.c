/* Lab 2 - Task 4
* New prime checking algorithm that increments the trial divisors by 2, 
* and stops when it reaches the square root of the number being tested. 
*/

#include <stdio.h>
#include <time.h>
#include <math.h>

int main () {
    clock_t startTime = clock(); // Start the timer
    int i;  // integer variable to use as a loop counter
    int j;  // integer variables to use as loop counters
    int is_prime;  // integer variable to indicate whether a number is prime or not
   
    int sqrtI=(int)sqrt((double)i); // integer variable to store the square root of i
   
    printf("2\n"); // Print 2, the only even prime number, to the console

    for (i = 3; i <= 100; i += 2) { // Loop from 3 to 100, incrementing by 2
        
        is_prime = 1; // Assume that i is prime until we find a divisor

        for (j = 3; j * j < sqrtI; j += 2) { // Loop from 3 to the square root of i, incrementing by 2 for even number
           
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