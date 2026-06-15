/* Day5,Lab5,Task2 - Palindrome Checker 
* print number of characters that user entered
*/

#include <stdio.h>
#include <string.h> /* add for Task 2 strlen function */

int main () {
    char s[100]; // buffer to hold the user input for the filename
    char inputBuffer [200];

    inputBuffer[0] = 'X';        // so we will do the loop at least once

    // fgets also reads the newline character, 
    // so we can check if the first character is a newline to determine 
    // if the user just pressed Enter without typing anything
    while (inputBuffer[0] != '\n') { 
        // print "Enter a string: " onto the console
        printf("Enter a string: ");

        // read one line from the console into inputBuffer
        fgets(inputBuffer, 200, stdin);

        if (inputBuffer[0] != '\n') 
        {
            // print inputBuffer onto the console
            printf("Entered: %s", inputBuffer);

            /* Task 2 */
            // calculate and print the number of characters in the input string, excluding the newline character
            int length = strlen(inputBuffer);
   
            printf("Number of characters entered: %d\n", length-1); // subtract 1 because strlen counts the newline character as well
        }
    }
    
    fgets(s, 100, stdin); // read one line from the console into s
    return 0;
}