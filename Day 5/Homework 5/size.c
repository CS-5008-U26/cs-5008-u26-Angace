/* Homework 5 - Task 3 - Finding the Size of a File 
* Step1. check if has an argument for the file name, 
* Step2. if not, prompt the user to enter a file name.
* Step3. open the file, prompt error if cannot open,
* Step4. otherwise print the size of the file.
*/

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    char s[100]; // buffer to hold user input for waiting at the end of the program
    char filename[200]; // buffer to hold the filename input by the user

    // Check if a filename was provided as a command-line argument，
    //if so, copy it to the filename buffer, 
    if (argc >= 2) { 
        strcpy(filename, argv[1]);
    } 
    // otherwise prompt the user to enter a filename
    else {
        printf("Enter the name of a file: ");
        scanf("%s", filename);
    }

    struct stat fileStat;
    // print an error message and exit the program if file cannot be opened
    if (stat(filename, &fileStat) < 0) {
        printf("Error! Cannot open file.\n");
        return 1; // end the program
    }
    // if the file exists and can be accessed, print the size of the file in bytes
    else {
        int fileSize = fileStat.st_size; // variable to hold the size of the file in bytes
        printf("%s has %d bytes\n", filename, fileSize);
    }

    fgets(s, 100, stdin); // wait for user input before closing the program
    return 0; // end the program
}