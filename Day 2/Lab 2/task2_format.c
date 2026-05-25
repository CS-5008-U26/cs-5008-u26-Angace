/* Lab 2 - Task 2
* print all the numbers from 0 to 1500 that are multiples of 63,
* and print them in a column, right-justified.
*/

#include <stdio.h>

int main () {
    int i;   // integer variable to use as a loop counter

    for (i = 0; i <= 1500; i += 63) { // Loop from 0 to 1500, incrementing i by 63 each time
        printf("%5d\n\n", i);  // Print the current value of i, right-justified in a field of width 5, followed by two newlines
    }

    return 0;  // Return 0 to indicate that the program ended successfully
}