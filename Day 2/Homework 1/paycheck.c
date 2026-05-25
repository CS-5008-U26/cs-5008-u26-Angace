/* Day2 - Homework - Task 1
* Prompt the user to enter hourly rate and number of hours with floating-point numbers,
* condition 1: less than 40 hours, just hourly rate * hours,
* condition 2: more than 40 hours, (hourly rate * 40) + (hourly rate * 1.5) * (hours - 40).
* There is a loop and ask user for two more numbers.
* If user ever enter a number less than or equal to 0, the program should exit,
* and the program should exit without asking for more input.
*/

#include <stdio.h>

int main () {

    // Variables to store user input and calculated paycheck
    double hourlyRate;  // floating-point variable to store the hourly rate entered by the user
    double hours;       // floating-point variable to store the number of hours entered by the user
    double paycheck;    // floating-point variable to store the calculated paycheck
    
    // Infinite loop to continuously prompt the user for input until they enter a number less than or equal to 0
    for (;;) {  // Infinite loop to continuously prompt the user for input until they enter a number less than or equal to 0
        /* Ask user to input values*/
        printf("Enter an hourly rate: ");  // Prompt the user to enter the hourly rate
        scanf("%lf", &hourlyRate);  // Read the hourly rate entered by the user
        
        if (hourlyRate <= 0) {  // If the hourly rate is less than or equal to 0, exit the program
            break;  // Break out of the loop to exit the program
        }

        printf("Enter the number of hours worked: ");  // Prompt the user to enter the number of hours worked
        scanf("%lf", &hours);       // Read the number of hours entered by the user
       
        if (hours <= 0) {  // If the number of hours is less than or equal to 0, exit the program
            break;  // Break out of the loop to exit the program
        }
    
        /* loop to check whether user input is below or over 40 hours*/
        if (hours <= 40) {  // If the number of hours is less than or equal to 40
            paycheck = hourlyRate * hours;  // Calculate the paycheck as hourly rate multiplied by hours
        } else {  // If the number of hours is greater than 40
            paycheck = (hourlyRate * 40) + (hourlyRate * 1.5) * (hours - 40);  // Calculate the paycheck using the formula for overtime
        }

        printf("You should be paid %.2lf\n", paycheck);  // Print the calculated paycheck to the console, rounded to two decimal places
    }
    
    return 0;  // Return 0 to indicate that the program ended successfully
}