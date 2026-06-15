/* Day5,Lab5,Task1 - Palindrome Checker 
* prompt user to enter a string
* read the string from the user
* show the input string back to the user
* keeping prompting the user to enter for a newline until the user just presses Enter without typing anything
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>


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
        printf("You entered: %s", inputBuffer);
        }
    }
    
    fgets(s, 100, stdin); // read one line from the console into s
    return 0;
}