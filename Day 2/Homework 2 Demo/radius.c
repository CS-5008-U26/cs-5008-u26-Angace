/* Opening comment here
*/

#include <stdio.h>
#include <math.h>

main () {
    char s[100];
    double pi = acos(-1);

    while (1) {
        int radius;
        int area;

        printf ("Enter the radius (integer): ");
        scanf ("%d", &radius);
        fgets (s,100,stdin);

        if (radius <= 0) {
            break;
        }

        area = (int) (pi * (radius * radius));
        printf ("Area is %d\n", area);
    }

    fgets(s,100,stdin);
}