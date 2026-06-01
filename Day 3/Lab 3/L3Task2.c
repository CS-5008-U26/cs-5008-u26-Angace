/*Task 2 - Fibonacci Numbers
* 
*/

# include <stdio.h>
# include <time.h>

int fibonacci(int fibNumber) {
    int result = 0;
    if (fibNumber < 2) {
        result = 1;
    } else {
        result = fibonacci(fibNumber - 1) + fibonacci(fibNumber - 2);
    }
    return result;
}

int main (){
    char s[100];
    int fibCounter = 0;
    int fibResult = 0;
    clock_t startTime = clock();

    while (1){
        fibResult = fibonacci(fibCounter);
        printf("Fibonacci %d = %d\n", fibCounter, fibResult);

        // *** ADDED: check again after computation, in case it overshot 5s ***
        double elapsed = (double)(clock() - startTime) / CLOCKS_PER_SEC;
        if (elapsed >= 5.0) {
            break;
        } 
        fibCounter++;
    }

    printf("Highest fib reached: Fibonacci %d = %d\n", fibCounter, fibResult);
    fgets(s, 100, stdin);

    clock_t endTime = clock();
    double timeTaken = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    printf("Time taken: %f seconds\n", timeTaken);

    return 0;
}