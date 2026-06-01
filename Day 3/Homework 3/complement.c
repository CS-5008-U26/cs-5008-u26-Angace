/* Homework 3- Task 1 - Complement
* Prompt user for a non-negative integer，
* and then calculate the complement of an integer recursively.
* for each digit, replace it with 9 - digit.
*/

#include <stdio.h>

int complement(int x) // function to calculate the complement of an integer x
{
    // Single digit integer
    if (x < 10) // when x is a single digit then return its complement
    {
        return 9 - x;
    }
    // Multiple digit integer
    else 
    {
        return complement(x / 10) * 10 + (9 - (x % 10)); // calculate the complement of the remaining digits and append the complement of the last digit  
    }
}

int main()
{
    char s[100]; // s is used to "pause" the console so it doesn't exit too quickly
    int x; // variable x is the value entered by the user

    while (1) // loop to continuously prompt the user until a valid input is received
    {
        printf("Enter a non-negative integer number: "); // prompt user for a non-negative integer
        scanf("%d", &x);
        fgets(s, 100, stdin); // pause the console and wait for user input to prevent the console from vanishing immediately

        if (x < 0)  // validate the input, if x is negative, print an error message
        { 
            printf("Error! Please enter a non-negative integer number.\n");
        } 
        else 
        {
            break; // if the input is valid, exit the loop
        }
    }

    printf("The complement of %d is %d\n", x, complement(x)); // call the complement function and print the result

    fgets(s, 100, stdin); // pause the console to prevent it from closing immediately
    return 0; // return 0 to indicate that the program ended successfully
}