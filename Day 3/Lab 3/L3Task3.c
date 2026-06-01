/* Task 3 - Fibonacci Numbers Again
* don't use recursion instead use a loop
*/

# include <stdio.h>
# include <time.h>

int fibonacci(int fibNumber, int fibOldResult, int fibOldOldResult) { // fibNumber is used to remember which Fibonacci number we are calculating, fibOldResult is Fibonacci(n-1), and fibOldOldResult is Fibonacci(n-2)
    int result = 0;
    result = fibOldResult + fibOldOldResult; // static varaible Fibonacci(n) = Fibonacci(n-1) + Fibonacci(n-2)
    return result;
}

int main (){
    char s[100];
    int fibCounter = 0;
    int fibResult = 1; // Start with Fibonacci(0) = 1
    int fibOldResult = 0; // This will hold the result of Fibonacci(n-1) for the next iteration
    int fibOldOldResult = 0; // This will hold the result of Fibonacci(n-2) for the next iteration
    clock_t startTime = clock();

    printf("Fibonacci %d = %d\n", fibCounter, fibResult);
    fibOldResult = fibResult; // Update Fibonacci(n-1) for the next iteration

    while (1){
        fibResult = fibonacci(fibCounter,fibOldResult,fibOldOldResult);
        fibOldOldResult = fibOldResult; // Update Fibonacci(n-2) for the next iteration
        fibOldResult = fibResult; // Update Fibonacci(n-1) for the next iteration
        printf("Fibonacci %d = %d\n", fibCounter, fibResult);
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