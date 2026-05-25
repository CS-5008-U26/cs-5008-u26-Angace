/* Day2 - Homework - Task 2.2
* Uisng SWITCH instead to show grade according to number from the user
*/

#include <stdio.h>

int main () {

    // Integer variable to store the grade entered by the user
    int grade;  // integer variable to store the grade entered by the user
    printf("Enter the number score from 1 to 10: ");  // Prompt the user to enter a grade from 1 to 10
    scanf("%d", &grade);  // Read the grade entered by the user and store

    // Check if the input is valid between 1 and 10
    if ((grade < 0) || (grade > 10)) {  
        printf("Invalid grade entered. Please enter a grade from 1 to 10.\n");
        return 1;  // Exit the program if the input is invalid
    }

    // Print letter grade using a switch statement based on the numeric grade
    switch (grade) {
        case 9:
        case 10:  // input 9 or 10, print A
            printf("Your grade is: A\n");
            break;

        case 8:   // input 8, print B
            printf("Your grade is: B\n");
            break;

        case 7:   // input 7, print C
            printf("Your grade is: C\n");
            break;

        case 6:   // input 6, print D
            printf("Your grade is: D\n");
            break;

        case 4:
        case 5:   // input 4 or 5, print E
            printf("Your grade is: E\n");
            break;

        case 1:
        case 2:
        case 3:   // input 1, 2, or 3, print F
            printf("Your grade is: F\n");
            break;
    }

    return 0;  // Return 0 to indicate that the program ended successfully
}