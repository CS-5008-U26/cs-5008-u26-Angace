/* Opening comment here
*/

#include <stdio.h>

main () {
    char s[100];

    double hours;
    double rate;
    double pay;

    while (1) {
        printf ("Hourly rate? ");
        scanf ("%lf", &rate);
        fgets (s, 100, stdin);
        if (rate <= 0.0) {
            break;
        }
        printf ("Number of hours? ");
        scanf ("%lf", &hours);
        fgets (s, 100, stdin);
        if (hours <= 0.0) {
            break;
        }

        // both rate and hours are positive
        pay = hours * rate;
        if (hours > 40.0) {
            pay += ((hours - 40.0) / 2.0) * rate;
        }
        printf ("Pay is %.2f\n", pay);
    }


    fgets(s,100,stdin);
}