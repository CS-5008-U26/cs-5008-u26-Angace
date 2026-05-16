/* A First C Program - for Homework 1
 *
 * This code will start you off.  Modify it as instructed in Homework 1.
 * 
 * Put your name here: Yang Huang
 * CS-5008 Summer 2026
 */

/* Standard Libraries */
#include <stdio.h>

/**** MAIN PROGRAM ****/

int main() {

    int x, y;                        // x and y will be the values entered by the user
    char s[100];                    // s is used to "pause" the console so it doesn't exit too quickly

    /* Ask for a number */
    printf("Enter a number: ");     // prompt the user
    scanf("%d", &x);                // read a number from the console ("stdin")
    fgets(s,100,stdin);             // sadly, we have to remove the \n that scanf leaves in stdin
    
    /* Normally I would not put a comment on every line of code.
       I just did it above because you are learning C for the first time.
       I would only put a comment on a line if it was hard to understand or required that you
       know something that is not entirely obvious by looking at the code.
    */

    /* HW 1 - Task 3 */
    /* Ask for another number */
    printf("Enter another number: ");     // prompt the user
    scanf("%d", &y);                // read a number from the console ("stdin")
    fgets(s,100,stdin);             // pause the console and still see it before it disappears

    /* Print the sum */
    printf("The sum is %d\n", x + y);  // tell the user the sum of the two numbers

    /* Pause the console so we can look at it before it vanishes */
    fgets(s,100,stdin);
}