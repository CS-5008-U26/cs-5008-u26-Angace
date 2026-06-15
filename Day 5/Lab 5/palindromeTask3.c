/* Day5,Lab5,Task3 - Palindrome Checker 
* conditioning strings:
* 1. remove non-alphanumeric characters 
* 2. conditoning all characters to lowercase 
* 3. analyze if the string is a palindrome 
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* Task 3 */ 
void condition(char *in, char *out) 
{
    // while loop
        // check if alphabetical
            // add lower-case letter to out
            // increment out
        //increment in
    // anything else?
    while (*in != '\0') 
    {
        if (isalpha(*in)) 
        {
            *out = tolower(*in);
            out++;
        }
        in++;
    }
    *out = '\0'; // null-terminate the conditioned string

}

int main () {
    char s[100]; // buffer to hold the user input for the filename
    char inputBuffer [200];
    char conditionedString[200];

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
            printf("You entered: %s", inputBuffer);
        }

        // calculate and print the number of characters in the input string, excluding the newline character
        int length = strlen(inputBuffer);
        printf("Number of characters entered: %d\n", length-1); // subtract 1 because strlen counts the newline character as well

        /* Task 3 */ 
        // call the condition function to remove non-alphanumeric characters 
        // and condition all characters to lowercase, 
        // then print the conditioned string
        condition(inputBuffer, conditionedString);
        printf("Conditioned string: %s\n", conditionedString);
    }
    
    fgets(s, 100, stdin); // read one line from the console into s
    return 0;
}