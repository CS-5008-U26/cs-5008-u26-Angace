/* HELLO - Main Program
 * 
 * main() calls first() and second().  seond() calls first().
 * Executing hello will have this output:
 *    Hip Hip Hooray!
 *    Hello, world!
*/

#include <stdio.h>

#include "first.h"
#include "second.h"

int main () {
    char s[100];        // character buffer for stdin

    // Hip
    first("Hip");
    // Hip Hooray!
    second("Hooray!");

    printf ("Hello world!\n");

    fgets(s,100,stdin);
}