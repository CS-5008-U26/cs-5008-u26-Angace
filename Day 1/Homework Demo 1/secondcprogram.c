/* Second C Program
*
* Things we fixed:
* 1. changed fgets target from s to t
* 2. changed printf source from t to s
* 3. added fgets to keep console window on the screen
* 4. added newline at end of printf string
* 5. Added comments
*/

#include <stdio.h>
int main() {
    char s[100];
    char t[100];

    printf ("What is your name? ");
    scanf("%s", s);
    fgets(t,100,stdin);

    printf("%s? That's a funny name!\n", s);

    fgets (t, 100, stdin);
}
