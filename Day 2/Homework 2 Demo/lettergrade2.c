/* Opening comment here
*/

#include <stdio.h>

main () {
    char s[100];

    while (1) {
        int numberGrade;
        printf ("Number grade? ");
        scanf ("%d", &numberGrade);
        fgets (s,100, stdin);

        if (numberGrade <= 0) {
            break;
        }
        if (numberGrade > 100) {
            printf ("Must be between 1 and 100\n");
            continue;
        }

        // numberGrade is between 1 and 100

        if (numberGrade >= 91) {
            printf ("A");
        } else if (numberGrade >= 81) {
            printf ("B");
        } else if (numberGrade >= 71) {
            printf ("C");
        } else if (numberGrade >= 61) {
            printf ("D");
        } else {
            printf ("F");
        }

        if (numberGrade >= 61) {
            switch (numberGrade % 10) {
                case 1:
                case 2:
                case 3:
                    printf ("-");
                    break;
                case 8:
                case 9:
                case 0:
                    printf ("+");
                    break;
                default:
                    ;
            }
        }

        printf ("\n");
    }

    fgets(s,100,stdin);
}