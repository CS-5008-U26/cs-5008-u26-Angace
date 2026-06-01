/* Task 1 - Harshad Numbers
*  a function called isHarshad that accepts an int argument,
*  and returns a boolean (int) true if the argument is a Harshad number,
*  and false if it is not.
*/

#include <stdio.h>

int isHarshad(int candidate) {
    int temp = candidate;
    int result = 0;

    while (temp > 0) {
        result += temp % 10;
        temp /= 10;
    }

    return (candidate % result == 0);
}

int main() {
    char s[100];

    printf("Here is all the two-digit Harshad numbers: \n");


    for (int i = 10; i < 100; i++) { // Check for Harshad numbers between 10 and 99
        if (isHarshad(i)) {
            printf("%d\n", i);
        }
    }

    fgets(s, 100, stdin);
    return 0;
}