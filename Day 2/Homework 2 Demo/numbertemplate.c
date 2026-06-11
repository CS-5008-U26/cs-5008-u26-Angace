/* Opening comment here
 */

#include <stdio.h>

main()
{
    char s[100];

    int number;

    while (1)
    {
        printf("Enter a number: ");
        scanf("%d", &number);

        if (number <= 0) {
            break;
        }
        if (number > max) {
            printf ("Number too big");
            continue;
        }

        // process the number
    }

    number = 1;                 // make sure we do the loop at least once
    while (number > 0)
    {
        printf("Enter a number: ");
        scanf("%d", &number);

        if (number > 0) {

            if (number > max) {
                printf ("Number too big");
            } else {

                // process the number

            }

        }
    }

    number = 1;                 // make sure we do the loop at least once
    while (number > 0)
    {
        printf("Enter a number: ");
        scanf("%d", &number);

        if (number > max) {
            printf ("Number too big");
        } else if (number > 0) {

            // process the number

        }
    }

    fgets(s, 100, stdin);
}