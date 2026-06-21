/* Lab 6 - city struct 4 tasks
* task 1: open uscities.c from Reource folder, skip the header row, read the first 20 cities
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* City struct & virables */
typedef struct city_struct{
    char *name; // using * to not limit string size
    char *cityAscii;
    char *stateId;
    char *stateName;
    char *countyFlips;
    char *countyName;
    double latitude; // number doesn't need *
    double longitude;
    int population;
}city;

/* Remove newline if present */
void killNewline(char *str) 
{
    int len = strlen(str);   // vraible to hold the length of the string
    if (len > 0 && str[len - 1] == '\n') { // if string has charactor and the last character is newline
        str[len - 1] = '\0';  // then replace the newline with the end-of-string \0
    }
}


char *getNextField(char *start, char  separator, char *out)
{
    if (*start == '\0'){
        return NULL;
    }
}

char *sepPointer = strchr(start, separator);

if (sepPointer != NULL){
    int fieldLen = sepPointer - start;
    strncpy 
}

city *stringToCity (char *textLine)
{
    char fieldBuffer[1000];
    char *p = textLine;
    int fieldNum = 0;
    city *c = malloc(sizeof(city));
    while (p != NULL)
    {
        p = getNextField(p,',', fiedlBuffer);
        if (p == NULL){
            break;
        }
        fieldNum++;
        c->name = strdup(fieldBuffer);
        switch (fieldNum){
            case 1: c->name = strdup(fieldBuffer); break;
            case 2: c->cityAscii = strdup(fieldBuffer); break;
            case 3: c->stateName = strdup(fieldBuffer); break;
            case 4: c->stateName = strdup(fieldBuffer); break;
            case 5: c->countyFlips = strdup(fieldBuffer); break;
            case 6: c->countyName = strdup(fieldBuffer); break;
            case 7: c->latitude = strdup(fieldBuffer); break;
            case 8: c->longitude = strdup(fieldBuffer); break;
            case 9: c->population = strdup(fieldBuffer); break;
        }

        if (fieldNum >= 9) {
            break;
        }
    }
}

city** readCityList (char *filename)
{

}

/* Main function */
int main () {
    char s [100];

    char lineBuffer[2000];
    char fieldBuffer[2000];
    
    // open file
    FILE *inFile = fopen("/Users/angace/Desktop/cs-5008-u26-Angace/Resources/uscities.csv", "r");

    // error msg if cant open the filr
    if (index == NULL) {
        printf("Error! Cannot open the file\n");
        return 1;
    }

    while {

    }
    fclose{inFile};



    fgets(s, 100, stdin);
    return 0;
}

