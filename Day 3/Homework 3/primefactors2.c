/* Homework 1- Task 3 - prime factors recursive
* Ask user for a positive integer and print all of its prime factors.
* Print the factors in order from smallest to largest, and separate by *.
*/

# include <stdio.h>

int primeFactors(int n) 
{
    /* Validate input */
    if (n <= 1) 
    {
        return 0; // no prime factors for numbers less than or equal to 1
    }
    /* Recursive case: find the smallest prime factor and print it, 
    then recursively call with the reduced number */
    for (int i = 2; i <= n; i++) 
    {
        if (n % i == 0)  // If i is a factor of n
        { 
            printf("%d", i); // Print the prime factor
            if ((n / i) > 1) 
            {
                printf(" * "); // Print the separator if there are more factors to come
            }
            return primeFactors(n / i); // Recursive call with the reduced number
        }
    }
    return 0;
}

int main()
{
    char s[100]; // s is used to "pause" the console so it doesn't exit too quickly
    int number; // variable number is the value entered by the user
    
    /* Prompt user for input*/
    printf("Enter a positive integer: ");
    scanf("%d", &number);
    fgets(s, 100, stdin); // pause the console to prevent it from closing immediately
    
    /* Validate input*/
    if (number <= 1)  // if number is less than or equal to 1, print an error message
    {
        printf("Error input! Please enter an integer greater than 1.\n");
    } 
    /* If input is valid, print the prime factors */
    else 
    {
        printf("The prime factors of %d are: ", number);
        primeFactors(number); // call the function to print prime factors
        printf("\n"); // print a newline after all factors have been printed
    }

    fgets(s, 100, stdin);   // Pause the console to prevent it from closing immediately 
    return 0;  // Return 0 to indicate that the program ended successfully
}