/* Day2 - Homework - Task 2.1
* Uisng IF and ELSE to show grade according to number from the user
*/

#include <stdio.h>

int main () {

    // Integer variable to store the grade entered by the user
    int grade;  // integer variable to store the grade entered by the user
    printf("Enter the number score from 1 to 10: ");  // Prompt the user to enter a grade from 1 to 10
    scanf("%d", &grade);  // Read the grade entered by the user and store

    // Check if the input is valid between 1 and 10
    if ((grade < 0)|| (grade > 10)) {  // Check if the input is valid between 1 and 10
        printf("Invalid grade entered. Please enter a grade from 1 to 10.\n");
        return 1;  // Exit the program if the input is invalid
    }

    // Print letter grade using if-else statements based on the numeric grade
    if ((grade == 9) || (grade == 10)){  
        printf("Your grade is: A\n"); // input 9 or 10, print A
    } else if (grade == 8){  
        printf("Your grade is: B\n");  // input 8, print B
    } else if (grade ==7){   
        printf("Your grade is: C\n");  // input 7, print C
    } else if (grade == 6){  
        printf("Your grade is: D\n");  // input 6, print D
    } else if ((grade == 4) || (grade == 5)){   
        printf("Your grade is: E\n");  // input 4 or 5, print E
    } else if ((grade >=1) && (grade <= 3)){  
        printf("Your grade is: F\n");  // input 1, 2 or 3, print F
    }

    return 0;  // Return 0 to indicate that the program ended successfully
}