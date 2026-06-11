/* exists - print whether a file exists or not
*/

#include <stdio.h>
#include <errno.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>

	

main () {
    char s[100];
    char *filename = "exists.z";

    struct stat fileStat;			// we’ll study struct next week
	if (stat(filename, &fileStat) < 0) {
		printf ("Whoops!  %s does not exist\n", filename);
        // we could examine errno at this point
	} else {
		printf ("Oh yeah!  %s exists all right!!!\n", filename);
        // fileStat has the stat information about the file
	}

    fgets(s,100,stdin);
}