/* HW 1 - Task 5 */

/* Standard Libraries */
#include <stdio.h>

/**** MAIN PROGRAM ****/
int main() {
    int x, y, z;                        // x, y and z will be the values entered by the user
    char s[100];                    // s is used to "pause" the console so it doesn't exit too quickly

    /* Ask for a number */
    printf("Enter a number: ");     // prompt the user
    scanf("%d", &x);                // read a number from the console ("stdin")
    fgets(s,100,stdin);             // sadly, we have to remove the \n that scanf leaves in stdin

    /* Ask for another number */
    printf("Enter another number: ");     // prompt the user
    scanf("%d", &y);                // read a number from the console ("stdin")
    fgets(s,100,stdin);             // pause the console and still see it before it disappears

    /* Print the sum */
    printf("The sum is %d\n", x + y);  // tell the user the sum of the two numbers

    /*======================*/
    /* Ask for the third number */
    printf("Enter the third number: ");     // prompt the user
    scanf("%d", &z);                // read a number from the console ("stdin")
    fgets(s,100,stdin);             // pause the console and still see it before it disappears

    /* Print the sum */
    printf("The sum is %d\n", (x + y) * z);  // tell the user the total of the three numbers

    /* Pause the console so we can look at it before it vanishes */
    fgets(s,100,stdin);
    
    return 0;   // return 0 to the operating system to indicate that the program finished successfully
}