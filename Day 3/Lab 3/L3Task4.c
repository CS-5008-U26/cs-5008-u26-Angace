/* Task 4 - Counting Random Numbers
   Generate p random numbers in range 0..q
   Return how many are in range 0..r
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int count(int p, int q, int r)
{
    int i;
    int randomNum;
    int count = 0;

    /* Check parameter validity */
    if ((p <= 0) || (q < 0) ||  (r < 0) || (r > q)){
        return -1;
    }

    for (i = 0; i < p; i++){
        randomNum = rand() % (q + 1);

        if (randomNum <= r)
        {
            count++;
        }
    }

    return count;
}

int main()
{
    char s[100];
    int p;
    int q;
    int r;
    int result;

    /* Seed random number generator */
    srand(time(NULL)); // Seed the random number generator with the current time
    int randomResult = rand() % (q+1); // Generate a random number between 0 and q

    printf("Let's check for negatives!\n"); 

    printf("Enter the number of random numbers to generate (p): ");
    printf("count(-1,10,5) = %d (expected -1)\n", count(-1,10,5));
    printf("count(10,-1,5) = %d (expected -1)\n", count(10,-1,5));
    printf("count(10,10,-1) = %d (expected -1)\n", count(10,10,-1));
    printf("count(10,5,10) = %d (expected -1)\n", count(10,5,10)); // validate r > q

    while (1) {

        printf(" Please input the number of random numbers to generate (p): ");
        scanf("%d", &p);

        if (p == 0) {
            break;
        }

        printf(" Please input the upper bound for random numbers (q): ");
        scanf("%d", &q);

        printf(" Please input the upper bound for counting (r): ");
        scanf("%d", &r);

        result = count(p, q, r);

        if (result == -1) {
            printf("Invalid input values.\n");
        }
        else {
            printf("Result = %d\n", result);
        }
    }

    fgets(s, 100, stdin);
    return 0;
}