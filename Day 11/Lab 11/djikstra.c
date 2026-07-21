/* djikstra.c - Implementation of Djikstra's algorithm
* 
* You will fill in the parts as described in Lab 11
* to implement Djikstra's algorithm for finding shortest
* paths between the 10 largest cities in the US
*
* This code assumes a maximum number of cities and links per city
* (just to keep things simple)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

/***   D A T A   ***/

#define MAX_CITIES 100
#define MAX_LINKS 10

// FOR EACH CITY
typedef struct cityStruct {
    char *name;             // the name of the city
    
    // Links to other cities
    int nLinks;                         // number of links
    struct cityStruct *linkCity[MAX_LINKS];    // pointer to the linked city node
    int linkMinutes [MAX_LINKS];               // times to get to the cities linked to
    // linkMinutes[i] is the time required to reach linkCity[i]

    // Data used in running Djikstra's algorithm
    int visited;                        // have you visited this city yet?
    int timeToGetHere;                  // the minimum time you have discovered to get here
    struct cityStruct *cityBeforeThis;  // the city that got you here with minimum time
} city;

city *cityList [MAX_CITIES];    // the list of city nodes
int nCities;            // how many cities are in the list

/***  S E T   U P   C I T Y   L I S T   ***/

// create a city node
void setupCity (char *name) {
    // create city node
    city *c = malloc (sizeof(city));
    c->name = strdup(name);
    c->nLinks = 0;
    // insert into list of cities
    cityList[nCities] = c;
    nCities++;
}

// look up a city by name
city *lookupCity (char *name) {
    for (int i=0; i<nCities; i++) {
        if (strcmp(cityList[i]->name, name) == 0) {
            // found
            return (cityList[i]);
        }
    }
    // not found
    return (NULL);
}

// convert hours:minutes into minutes
int toMinutes (int hours, int minutes) {
    return ((60 * hours) + minutes);
}

// print a city
void printCity (city *c) {
    printf ("%s\n", c->name);
    for (int i=0; i<c->nLinks; i++) {
        printf ("    to %s: %d minutes\n", c->linkCity[i]->name, c->linkMinutes[i]);
    }
    printf ("\n");
}

// add a link from a given city to another city
void addLink (city *from, city *to, int minutes) {
    from->linkCity[from->nLinks] = to;
    from->linkMinutes[from->nLinks] = minutes;
    from->nLinks++;
}

// add links between two cities, in both directions
void link2Cities (char *cityAName, char *cityBName, int hours, int minutes) {
    int totalMinutes = toMinutes(hours, minutes);
    city *cityA = lookupCity (cityAName);
    city *cityB = lookupCity (cityBName);
    addLink (cityA, cityB, totalMinutes);
    addLink (cityB, cityA, totalMinutes);
}

// set up the city list
void setupCityList () {
    /* cities */
    nCities = 0;
    setupCity("New York");
    setupCity("Los Angeles");
    setupCity("Chicago");
    setupCity("Miami");
    setupCity("Houston");
    setupCity("Dallas");
    setupCity("Philadelphia");
    setupCity("Atlanta");
    setupCity("Washington");
    setupCity("Boston");
    /* links = city names, hours, minutes */
    link2Cities("Los Angeles", "Chicago", 29, 0);
    link2Cities("Los Angeles", "Dallas", 20, 29);
    link2Cities("Los Angeles", "Houston", 22, 18);
    link2Cities("Dallas", "Houston", 3, 16);
    link2Cities("Dallas", "Chicago", 13, 45);
    link2Cities("Dallas", "Atlanta", 11, 05);
    link2Cities("Houston", "Atlanta", 11, 11);
    link2Cities("Chicago", "Atlanta", 10, 42);
    link2Cities("Atlanta", "Miami", 9, 43);
    link2Cities("Atlanta", "Washington", 9, 19);
    link2Cities("Miami", "Washington", 14, 48);
    link2Cities("Washington", "Philadelphia", 2, 43);
    link2Cities("New York", "Philadelphia", 1, 11);
    link2Cities("Chicago", "New York", 11, 49);
    link2Cities("Boston", "New York", 3, 50);
    link2Cities("Chicago", "Boston", 14, 48);
}

/***   D J I K S T R A ' S   A L G O R I T H M   ***/

// prepare the city data for running Dijkstra's Algorithm
void prepareForDijkstra () {

}

// get the next city to visit
city *nextToVisit() {

}

// visit the indicated city
void visit (city *c) {

}

// trace back the path from the indicated city
void traceBack (city *c) {
    
}

// Compute the shortest path from the start city to the end city
void dijkstra (char *startName, char *endName) {

}

/***   M A I N   ***/

void main () {
    char buffer[100];

    setupCityList();

    /* for debugging of the city list setup */
    /* for (int i=0; i<nCities; i++) {
        printCity(cityList[i]);
    } */

    fgets(buffer,100,stdin);
}