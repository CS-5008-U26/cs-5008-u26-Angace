/* Lab 2 - Task 5
* Floating-point number from the user,
* calculate the tax of its digits in dollars,
* and print the result to round up to two decimal places.
*/

#include <stdio.h>

int main () {
    char s[100];  // s is used to "pause" the console so it doesn't exit too quickly
    double n;      // floating-point variable to store the number entered by the user
    float tax = 0.08;  // floating-point variable to store the tax percent

    printf("Enter a floating-point number: ");  // Prompt the user to enter a floating-point number
    scanf("%lf", &n);  // Read the floating-point number entered by the user and store it in variable n

    fgets(s,100,stdin);

    float total = n * (1 + tax);  // Calculate the tax by multiplying n by the tax percent

    printf("The tax is: %.2lf\n", total);  // Print the tax to the console, rounded to two decimal places

    fgets(s,100,stdin);  // Wait for the user to press Enter before closing the console

    return 0;  // Return 0 to indicate that the program ended successfully
}