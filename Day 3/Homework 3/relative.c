/* Homework 1- Task 4 - prime factors recursive
* Ask user for an integer n 
* and prints the ET-function for each integer from 2 to n.
* The ET-function int et(x) is the number of integers less than x, that are relatively prime with x. 
*/

#include <stdio.h>
 
int et(int x) 
{
    int count = 0; // variable count is used to count the number of integers less than x that are relatively prime with x

    for (int i = 1; i < x; i++)  // loop through all integers less than x
    {
        int a = x; // variable a is used to inherit the x value for the calculation of the greatest common divisor of x and i
        int b = i; // variable b is used to calculate the greatest common divisor of x and i
        while (b)
        { 
            int temp = b;  // variable temp is used to temporarily store the value of b during the calculation of the greatest common divisor
            b = a % b;  // update b to be the remainder of a divided by b, which is part of the Euclidean algorithm for finding the greatest common divisor
            a = temp;      // update a to be the previous value of b, which is part of the Euclidean algorithm for finding the greatest common divisor
        }
            if (a == 1) // if the greatest common divisor of x and i is 1, then they are relatively prime,   
            {
             count++; //so accmulate the count
            }
    }
    return count;
}
 
int main() 
{
    char s[100]; // s is used to "pause" the console so it doesn't exit too quickly
    int n; // variable n is the value entered by the user
   
    /* Prompt user for input */
    printf("Enter an integer n: ");
    scanf("%d", &n);
    fgets(s, 100, stdin); // pause the console and wait for user input to prevent the console from vanishing immediately
    
    /* Validate input */
    if (n < 2) 
    {
        printf("Error input! Please enter an integer greater than or equal to 2.\n");
        return 1; // return 1 to indicate that the program ended with an error
    }
    /* Print ET-function values for each integer from 2 to n */
    else
    {
    for (int number = 2; number <= n; number++) // loop from 2 to n
        printf("et(%d) = %d\n", number, et(number)); // call the et function and print the result
    }

    fgets(s, 100, stdin); // pause the console to prevent it from closing immediately
    return 0; // return 0 to indicate that the program ended successfully   
}
 