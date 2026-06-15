/* Day5,Lab5,Task5 - Command Line Arguments
*/


#include <stdio.h>

int main(int argc, char **argv)
{
    char s[100]; // buffer to hold the user input for the filename
    for (int i = 0; i < argc; i++)
    {
        printf("%s\n", argv[i]);
    }

    fgets(s, 100, stdin); // read one line from the console into s
    return 0;
}