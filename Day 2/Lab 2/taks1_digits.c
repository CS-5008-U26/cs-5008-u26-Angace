/* Lab 2 - Task 1
* Takes in a number from the user, 
* calculates the sum of its digits, 
* and prints the result to the console.
*/

#include <stdio.h>

int main () {
    char s[100];   // s is used to "pause" the console so it doesn't exit too quickly
    int n;         //integer variable to store the number entered by the user
    int total = 0;    //integer variable to store the sum of the digits
    printf("Enter a number: ");     // Prompt the user to enter a number
    scanf("%d", &n);     // Read the number entered by the user and store it in variable n
   
    fgets(s,100,stdin);
   
    while (n > 0) {
        total += (n % 10);   // Add the last digit of n to total
        n /= 10;          // Remove the last digit from n
    }
   
    printf("The sum of the digits of %d is: %d\n", n, total);   // Print the sum of the digits to the console

    fgets(s,100,stdin);  // Wait for the user to press Enter before closing the console
}