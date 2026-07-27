/* Homework 11 - Aliens Attack
* read in the 200 largest cities from uscities.csv
* using Knapsack Dynamic Programming to find the set of cities with the maximum total population, 
whose names add up to a total of 200 characters or less.
* population = value, city name = size, capacity <=200
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/***   D A T A   ***/
#define MAXCITY 200
#define LIMIT 200

/* Created struct*/
typedef struct uscities {
    char city[100];
    long long population;
    int length;
} City;

/* ==== Helper functions to read csv file ==== */
/* Remove the newline from the end of a string */
void killNewline(char *str) {
    int len = strlen(str);
    if ((len > 0) && (str[len-1] == '\n')){
        str[len-1] = '\0';
    }
}

/* Remove all quotation marks */
void removeQuotes(char *str) {
    int i, j = 0;
    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] != '"')  {
            str[j] = str[i];
            j++;
        }
    }
    str[j] = '\0';
}

/* Read city data from a line of text */
City *readCity(char *line) {
    City *city = malloc(sizeof(City));

    // if no city data, print error message and stop the program
    if (city == NULL) {
        return NULL;
    }
        
    int fieldNumber = 1; // initialize the current track of field number
    char *field = strtok(line, ","); // pointer to hold the current field

    while (field != NULL) { // loop through each field in the line
        switch(fieldNumber) {
            case 2:     // city name
                strcpy(city->city, field);
                removeQuotes(city->city);
                break;

            case 9:     // population
                city->population = atoll(field);
                city->length = strlen(city->city);
                return (city);
        }

        field = strtok(NULL, ","); // get the next field
        fieldNumber++; // increment the field number
    }
    return (city);
}

/******  MAIN FUNCTION *******/
int main (){
    char s[100]; // buffer to hold user input for waiting at the end of the program 

    City cities[MAXCITY]; // initialize cities to MAXCITY
    char line[500];  // initialize line to upto 500

    /* ==== Read file ===== */
    FILE *inFile = fopen("../../Resources/uscities.csv", "r"); 

    // Check if the file was opened successfully, if not, print an error message and exit the program
    if (inFile == NULL){
        printf("Error! Can not open file.\n");
        return (1); 
    } 

    // if the file is opened successfully
    else {    
        fgets(line, 500, inFile);  // Skip header row
    }

    // loop to capture the first 200 cities from csv file
    for (int cityCount = 0; cityCount < MAXCITY; cityCount++) {

        // if the current line is empty then break the loop
        if (fgets(line, 500, inFile) == NULL){
            break;
        }

        // call the function to remove the newline character from the end of line
        killNewline(line); 

        // call the function replace all quotes with space to simplify parsing
        removeQuotes(line);

        // call the function to read each city
        City *temp = readCity(line);
        cities[cityCount] = *temp;
        free(temp);
    }
    fclose(inFile); // close the file after reading

    /* ==== DP functions ===== */
    // define dynamic programming table
    long long dp[MAXCITY+1][LIMIT+1]; 

    // define selected cities
    int keep[MAXCITY+1][LIMIT+1];

    // imitialize dp and keep to 0
    for (int i = 0; i <= MAXCITY; i++) {
        for (int j = 0; j <= LIMIT; j++){
            dp[i][j] = 0;
            keep[i][j] = 0;
        }
    }

    /* Build DP table */
    for (int i = 1; i <= MAXCITY; i++) {
        for (int capacity = 0; capacity <= LIMIT; capacity++)
        {
            // city name length should <= 200
            if (cities[i - 1].length > capacity){
                dp[i][capacity] = dp[i - 1][capacity];
            }
            else
            {
                // pop if include this city = current city pop + max pop obtained from the prev city with remaining capacity. */
                long long include = cities[i - 1].population + dp[i - 1][capacity - cities[i - 1].length]; 

                //  pop if exclude this city
                long long exclude = dp[i - 1][capacity];

                // compare better resul, choose this city if pop is greater
                if (include > exclude){
                    dp[i][capacity] = include;
                    keep[i][capacity] = 1;
                }
                else {
                    dp[i][capacity] = exclude;
                    keep[i][capacity] = 0;
                }
            }
        }
    }

    /* Print answer */
    printf("Maximum population saved: %lld\n\n", dp[MAXCITY][LIMIT]);
    
    // Print selected cities
    printf("Cities to rescue:\n");

    int nameLength = LIMIT;
    for (int i = MAXCITY; i >= 1; i--) {
        if (keep[i][nameLength]) {
            printf("%s  %lld  %d\n", 
                cities[i-1].city, 
                cities[i-1].population, 
                cities[i-1].length);
            nameLength -= cities[i-1].length;
        }
    }
    
    fgets(s, 100, stdin);
    return 0;
}

