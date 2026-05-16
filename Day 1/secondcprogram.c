/* HW 1 - Task 5 */

/* Standard Libraries */
#include <stdio.h>

/**** MAIN PROGRAM ****/
int main() {
    char s[100];        // s is used to "pause" the console so it doesn't exit too quickly
    char t[100];        // t is used to store the user's name

    printf ("What is your name?");     // prompt the user to enter the name
    scanf("%s", t);         // read the user's name from the console ("stdin")
    fgets(s,100,stdin);     // pause the console and still see it before it disappears

    printf("%s? That's a funny name!",t);  // tell the user that their name is funny

    fgets(s,100,stdin);     // pause the console and still see it before it disappears

    return 0;   // return 0 to the operating system to indicate that the program finished successfully

    /*
    Changes made:
    1. Add proper comments to the program
    2. Change scanf("%s", s) to scanf("%s", t)，s is to handle the console pause, so we want to read user input into t  
    3. Add one more fgets(s,100,stdin) after printf to pause the console, so the window stay on the screen until hit Enter to make it go away
    4. Add "return 0" at the end to indicate that the program finished successfully
    */
}