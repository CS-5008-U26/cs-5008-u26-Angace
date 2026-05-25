/* Day2 - Homework - Task 5
* prompt input from user from integer cents between 1 to 100,
* and then print the equivalent in quarters, dimes, nickels, and pennies.
* determine the punctuation between coins, and omit any coins that are not needed.
* bonus: using singular forms if the number is 1 and the pural form if it's more than 1
*/

#include <stdio.h>

int main() {

    // Variable to store the number of cents entered by the user
    int cents;  // integer variable to store the number of cents entered by the user
    printf("Enter an integer number of cents between 1 and 100: ");  // Prompt the user to enter an integer number of cents between 1 and 100
    scanf("%d", &cents);  // Read the number of cents entered by the user and store

    // Validate the input is within the valid range
    if ((cents < 1) || (cents > 100)) {
        printf("Invalide input! number must be between 1 and 100.\n");
        return 1;   // return 1 to indicate that the program ended with an error
    }

    // Calculate the number of quarters, dimes, nickels, and pennies
    int quarters = cents / 25; // calculate the number of quarters by dividing the total cents by 25
    int dimes = (cents % 25) / 10; // calculate the number of dimes by first getting the remainder after dividing by 25 and then dividing by 10
    int nickels = ((cents % 25) % 10) / 5; // calculate the number of nickels by first getting the remainder after dividing by 25, then getting the remainder after dividing by 10, and finally dividing by 5
    int pennies = ((cents % 25) % 10) % 5; // calculate the number of pennies by first getting the remainder after dividing by 25, then getting the remainder after dividing by 10, and finally getting the remainder after dividing by 5

    /* Print the equivalent in quarters, dimes, nickels, and pennies with singular or plural forms */
    printf("That requires "); // print intro of output

    /******* Quarter part *******/
    if (quarters == 1) {
        printf("%d quarter", quarters); // print singular form if it is equal to 1
    } else if (quarters > 1) {
        printf("%d quarters", quarters); // print plural form if it is not equal to 1
    } else {
        printf(""); // blank out when omit any coins that are not needed.
    }
    
    /******* Dime part *******/
    // check punctuation
    if ((quarters > 0) && (dimes > 0) && (nickels == 0) && (pennies == 0)){ 
        printf(" and ");  // print "，and“ if it's the last coin
    } else if ((quarters > 0) && (dimes > 0)) { 
        printf(", ");  // print a comma if this is not the last coin
    } else {
        printf(""); // blank out when omit any coins that are not needed.
    }

    // print dimes with singular or plural forms
    if (dimes == 1) {
        printf("%d dime", dimes); // print singular form if it is equal to 1
    } else if (dimes > 1) {
        printf("%d dimes", dimes); // print plural form if it is not equal to 1
    } else if (dimes == 0) {
        printf(""); // blank out when omit any coins that are not needed.
    }

    /******* Nickel part *******/
    // check punctuation
    if ((quarters > 0) && (dimes > 0) && (nickels > 0) && (pennies == 0)){ 
        printf(", and ");  // print "，and“ if it's the last coin
    } else if (((quarters > 0) || (dimes > 0)) && (nickels > 0)) { 
        printf(", ");   // print a comma if it's mot the last coin
    } else {
        printf(""); // blank out when omit any coins that are not needed.
    }

    // print nickels with singular or plural forms
    if (nickels == 1) {
        printf("%d nickel", nickels); // print singular form if it is equal to 1
    } else if (nickels > 1) {
        printf("%d nickels", nickels); // print plural form if it is not equal to 1
    } else {
        printf(""); // blank out when omit any coins that are not needed.
    }

    /******* Penny part *******/
    // check punctuation
    if ((quarters > 0) || (dimes > 0) || (nickels > 0) && (pennies > 0)) { 
        printf(", and "); // print "，and“ if it's the last coin   
    }  else {
        printf(""); // blank out when omit any coins that are not needed.
    }

    //  print pennies with singular or plural forms
    if (pennies == 1) {
        printf("%d penny", pennies); // print singular form if it is equal to 1
    } else if (pennies > 1) {
        printf("%d pennies", pennies); // print plural form if it is not equal to 1
    } else {
        printf(""); // blank out when omit any coins that are not needed.
    }

    // print a period at the end of the output
    printf(".\n");

    return 0; // return 0 to indicate that the program ended successfully
}
