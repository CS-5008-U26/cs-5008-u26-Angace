/* Homework 5 - Task 1 - Printing The Fields Of A CSV File
* prompt the user to enter the path to a CSV file
* read the CSV file and print its contents to the console
* This program reads a CSV file and prints its contents to the console.
*/
 
#include <stdio.h>
#include <string.h>

/* Remove the newline from the end of a string */
void killNewline (char *str) 
{
    int len = strlen(str); // Get the length of the string
    if (len > 0 && str[len - 1] == '\n') { // if the string has 1 or more characters and the last character is a newline("\n")
        str[len - 1] = '\0'; // replace that newline with the end-of-string("\0")
    }
}

/* Splitting the fields on each line */
char *getNextField (char *start, char separator, char *out) 
{
    //if there is nothing to read, return NULL
    if (*start == '\0') {
        return NULL;
    }

    //find the next occurrence of the separator in the string starting from 'start'
    char *sepPointer = strchr(start, separator); 

    // if there is the last field, return NULL
    if (sepPointer == NULL) {
        strcpy(out, start);
        return start + strlen(start);
    }

    // calculate the length of the field by finding the difference between the position of the separator and the starting position
    // copy the field into the output buffer and add a null terminator at the end
    int length = sepPointer - start; 

    strncpy(out, start, length);
    out[length] = '\0';

    return sepPointer + 1;
}


/* Main function */
int main ()
{
    char s[100]; // buffer to hold the user input for the filename
    char filename[1000]; // buffer to hold the filename input by the user

    // Prompt the user to enter the file name and read it into the filename buffer
    printf("Enter the file name: ");
    fgets(filename, sizeof(filename), stdin);
    killNewline(filename); // call the killNewline function to remove the newline character from the end of the filename string

    // Open the file with read mode and check if it was opened successfully
    FILE *inFile = fopen(filename, "r");

        // Print error message if the file cannot be opened, otherwise read and print the contents of the file line by line
        if (inFile == NULL) 
        {
            printf("Whoops! Can't open the file %s.\n", filename);
            return 1;
        }
        else
        {
            char inputLine[1000]; // the line that got from fgets (with the newline removed)
            int keepReading = 1; // initialize reading to 1 to start reading for the loop

            while (keepReading) 
            {
                char *whatWasRead = fgets(inputLine, 1000, inFile);

                keepReading = (whatWasRead != NULL);

                if (keepReading) {

                    killNewline(inputLine);

                    /* Print entire line */
                    printf(">%s<\n", inputLine);

                    /* Print each field */
                    char nextField[1000]; // buffer to hold the next field extracted from the line
                    char *p = inputLine; // pointer to the current position in the input line, initialized to the start of the line

                    while (p != NULL) { // loop until there are no more fields to extract
                        p = getNextField(p, ',', nextField);

                        if (p != NULL) {  // if there is another field to extract, print it
                            printf(">%s<\n", nextField);
                        }
                    }
                }           
            }
        }
    fclose(inFile);

    fgets(s, 100, stdin);
    return 0;
}
