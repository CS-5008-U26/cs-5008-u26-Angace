/* Day2 - Homework - Task 3
*  ask user input a number from 0 to 100,
print grade based on tens digit
print + or - based on units digit
*/

#include <stdio.h>

int main() {

    // Variable to store the score entered by the user
    int score; // vraible to store the score
    printf("Enter the number score: "); 
    scanf("%d", &score);  

    // check if the input is valid
    if ((score < 0) || (score > 100)) {
        printf("Invalid input! Please enter a number between 0 and 100.\n");
        return 1; // exit with error code
    }

    // determine letter grade based on tens digit
    char letter; // variable to store the letter grade
    if (score <= 60){ letter = 'F';
    } else if (score <= 70) { letter = 'D';
    } else if (score <= 80) { letter = 'C';
    } else if (score <= 90) { letter = 'B';
    } else { letter = 'A';
    }       

    // Check sign + and - when score >=60
    if (score <= 60) {
        printf("Your grade is %c\n", letter); //print letter grade only when score <= 60
    } else {
        int lastDigit = score % 10; // variable to store and calculate the last digit of the score by getting the remainder after dividing by 10
        if ((lastDigit >= 1) && (lastDigit <= 3))
            printf("Your grade is %c-\n", letter); //print letter grade with -
        else if ((lastDigit >= 8) || (lastDigit == 0))
            printf("Your grade is %c+\n", letter); //print letter grade with +
        else
            printf("Your grade is %c\n", letter); //print letter grade only
    }

    return 0; // return 0 to indicate that the program ended successfully
}