/* catfile - copy a file to standard output
*/


#include <stdio.h>

main () {
    char s[100];
    char *filename = "catfile.c";

    FILE *f = fopen (filename, "r");
	char buffer[1000];

	if (f == NULL) {
        printf ("Whoops!  Can't open %s\n", filename);
    }
	else {
		while (fgets(buffer, 1000, f) != NULL) {
			printf("%s", buffer);
		}
		fclose(f);
	}

    fgets(s,100,stdin);
}