/* Homework 1- Task 2 - prime factors loop
* Ask user for a positive integer and print all of its prime factors.
* Print the factors in order from smallest to largest, and separate by *.
* program should use iteration (looping) without any function calls.
*/

#include <stdio.h>

int main()
{
    char s[100]; // s is used to "pause" the console so it doesn't exit too quickly
    int number;  // varaible number is the value entered by the user
    int factor = 2; // initalize factor to 2, which is the smallest prime number
    int first = 1; // variable first is used to determine whether to print " * " before the factor

    /* Prompt user for input */
    printf("Enter a positive integer number: "); // prompt user for a positive integer
    scanf("%d", &number); // read a number from the console ("stdin")
    fgets(s, 100, stdin); // pause the console and wait for user input to prevent the console from vanishing immediately

    /* Validate input */
    if (number <= 1) // validate the input, if number is less than or equal to 1, print an error message
    {
        printf("Error input! Please enter an integer greater than 1.\n");
    }
    /* If input is valid, print the prime factors */
    else
    {
        printf("The prime factors of %d are: ", number); // print the prompt for the prime factors

        while (number > 1) // loop until number is reduced to 1 or factor exceeds number
        {
            if (number % factor == 0) // if factor is a factor of number
            {
                printf("%d", factor); // print the factor

                number /= factor; // divide number by factor to reduce it for the next iteration

                if (number > 1) // if there are more factors to come, print the separator " * "
                {
                    printf(" * ");
                }
            }
            else
            {
                factor++; // if factor is not a factor of number, increment factor to check the next potential factor
            }
        }

        printf("\n"); // print a newline after all factors have been printed
    }

    fgets(s, 100, stdin); // pause the console to prevent it from closing immediately
    return 0; // return 0 to indicate that the program ended successfully
}