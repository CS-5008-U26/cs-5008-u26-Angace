/* Day5,Lab5,Task4 - Recognizing Palindromes
* check if a string is a palindrome after conditioning
* int palindrome (char *in)
* This function will take a string, condition it, and then return TRUE if it is a palindrome, and FALSE if it is not.
* if left >= right, then the string is a palindrome
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

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

int palindrome(char *in) 
{
    char conditionedString[200];
    condition(in, conditionedString);

    int left = 0;
    int right = (int)(strlen(conditionedString) - 1);

    while (left < right) 
    {
        if (conditionedString[left] != conditionedString[right]) 
        {
            return 0; // not a palindrome
        }
        left++;
        right--;
    }
    return 1; // is a palindrome
}

int main () {
    char s[100]; // buffer to hold the user input for the filename
    char inputBuffer [200];

    inputBuffer[0] = 'X';        // so we will do the loop at least once

    // fgets also reads the newline character, 
    // so we can check if the first character is a newline to determine 
    // if the user just pressed Enter without typing anything
    while (1) { 
        // print "Enter a string: " onto the console
        printf("Enter a string: ");

        // read one line from the console into inputBuffer
        fgets(inputBuffer, 200, stdin);
        
        inputBuffer[strcspn(inputBuffer, "\n")] = '\0';

        if (strlen(inputBuffer) == 0)
        {
            break;
        }

        if (palindrome(inputBuffer))
        {
            printf("%s\n", inputBuffer);
        }
    }
    
    fgets(s, 100, stdin); // read one line from the console into s
    return 0;
}