/* Day2 - Homework - Task 6
* accepts an integer from the user, between 1 and 4000, 
* and then prints it as a Roman numeral.
*/

#include <stdio.h>

int main() {

    // Variable to store the number entered by the user
    int num;  // integer variable to store the number entered by the user
    printf("Enter a number between 1 and 4000: ");  // prompt the user to enter a number between 1 and 4000
    scanf("%d", &num); // read the number entered by the user and store

    // Validate the number is within the valid range
    if ((num < 1) || (num > 4000)) {
        printf("Error: number must be between 1 and 4000.\n");
        return 1;   // return 1 to indicate that the program ended with an error
    }

    // Print the number as a Roman numeral
    printf("The Roman Numeral for %d is: ", num);

     // Thousannds
    int t = num / 1000; // calculate the number of thousands by dividing the number by 1000
    if (t == 3) { printf("MMM");
    } else if (t == 2) { printf("MM");
    } else if (t == 1) { printf("M");
    } else if (t == 0) { printf(""); // missing place just print nothing
    }

    // Hundres
    int h = (num % 1000) / 100; // calculate the number of hundreds by first getting the remainder after dividing by 1000 and then dividing by 100  
    if (h == 9) { printf("CM");
    } else if (h == 8) { printf("DCCC");
    } else if (h == 7) { printf("DCC");
    } else if (h == 6) { printf("DC");
    } else if (h == 5) { printf("D");
    } else if (h == 4) { printf("CD");
    } else if (h == 3) { printf("CCC");
    } else if (h == 2) { printf("CC");
    } else if (h == 1) { printf("C");
    } else if (h == 0) { printf(""); // missing place just print nothing
    }

    // Tens
    int ten = (num % 100) / 10; // calculate the number of tens by first getting the remainder after dividing by 100 and then dividing by 10
    if (ten == 9) { printf("XC"); 
    } else if (ten == 8) { printf("LXXX");
    } else if (ten == 7) { printf("LXX");
    } else if (ten == 6) { printf("LX");
    } else if (ten == 5) { printf("L");
    } else if (ten == 4) { printf("XL");
    } else if (ten == 3) { printf("XXX");
    } else if (ten == 2) { printf("XX");
    } else if (ten == 1) { printf("X");
    } else if (ten == 0) { printf(""); // missing place just print nothing
    }

    // Units
    int u = num % 10; // calculate the number of units by getting the remainder after dividing by 10
    if (u == 9) { printf("IX");
    } else if (u == 8) { printf("VIII");
    } else if (u == 7) { printf("VII");
    } else if (u == 6) { printf("VI");
    } else if (u == 5) { printf("V");
    } else if (u == 4) { printf("IV");
    } else if (u == 3) { printf("III");
    } else if (u == 2) { printf("II");
    } else if (u == 1) { printf("I");
    } else if (u == 0) { printf(""); // missing place just print nothing
    }

    printf("\n");  // Print a newline character after the Roman numeral

    return 0;    // Return 0 to indicate that the program ended successfully
}