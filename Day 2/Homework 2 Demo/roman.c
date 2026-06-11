/* Opening comment here
*/

#include <stdio.h>

main () {
    char s[100];

    while (1) {
        int number;
        int thousands;
        int hundreds;
        int tens;
        int units;

        if (number <= 0) {
            break;
        }
        if (number >= 3000) {
            printf ("Number must be < 3000\n");
            continue;
        }

        // number is between 1 and 2999

        // break down the number
        thousands = (number / 1000);
        hundreds = (number / 100) % 10;
        tens = (number / 10) % 10;
        units = (number % 10);

        // print it out
        switch (thousands) {    // must be between 0 and 2
            case 0:
                break;
            case 1:
                printf("M");
                break;
            case 2:
                printf ("MM");
                break;
            default:
                ;
        }
        switch (hundreds) {     // must be between 0 and 9
            case 0:
                break;
            case 1:
                printf("C");
                break;
            case 2:
                printf ("CC");
                break;
            case 3:
                printf ("CCC");
                break;
            case 4:
                printf ("CD");
                break;
                
        }
    }


    fgets(s,100,stdin);
}