/* SECOND - calls first to print "Hip ", then prints the string it is given
*/

#include <stdio.h>

#include "first.h"

void second (char *moreText) {
    first ("Hip");
    printf ("%s\n", moreText); 
}