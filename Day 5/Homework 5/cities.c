/* Homework 5 - Task 2 - Getting Data About American Cities
* 1. Read file "uscities.csv" 
* 2. Skip the header row 
* 3. Compute the total population of the first 20 cities,
* 4. Find the northernmost city among them.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Remove the newline from the end of a string */
void killNewline(char *str) {
    int len = strlen(str);
    if (len > 0 && str[len-1] == '\n')
        str[len-1] = '\0';
}

/* Main function */
int main() 
{
    char s[100]; // buffer to hold user input for waiting at the end of the program 

    // declare variables
    char line[5000]; // buffer to hold each line of the file
    int totalPopulation = 0; // variable to hold the total population, initialize to 0
    double maxLatitude = -100.0; // variable to hold the maximum latitude, initialize to the lowest value
    char northernmostCity[100] = ""; // buffer to hold the name of the northernmost city, initialize to empty string

    // Declare the file pointer
    FILE *inFile = fopen("/Users/angace/Desktop/cs-5008-u26-Angace/Resources/uscities.csv", "r"); 

    
    // Check if the file was opened successfully, if not, print an error message and exit the program
    if (inFile == NULL)
    {
        printf("Error! Can not open file.\n");
        return 1; 
    } 
    else    // if the file is opened successfully
    {
        fgets(line, 5000, inFile);  // Skip header row
    }

    // loop to read the first 20 cities
    for (int cityCount = 0; cityCount < 20; cityCount++) 
    {
        // if the current line is empty then break the loop
        if (fgets(line, 5000, inFile) == NULL)
        {
            break;
        }

        // Call the function to remove the newline character from the end of line
        killNewline(line); 

        // replace all quotes with space to simplify parsing
        for (int i = 0; line[i]; i++) 
        {
            if (line[i] == '"') 
            {
                line[i] = ' ';
            }
        }
            
        // varaibles to hold city name, latitude and population
        char cityName[100] = ""; // buffer to hold the city name, initialize to empty string
        double latitude = 0.0;   // variable to hold the latitude, initialize to 0.0
        int population = 0;      // variable to hold the population, initialize to 0
        int fieldNumber = 1;     // initialize the current track of field number

        char *field = strtok(line, ","); // pointer to hold the current field

        // loop to parse the fields in the line
        while (field != NULL)
        {
            if (fieldNumber == 2)
            {
                strcpy(cityName, field);
            } 
            else if (fieldNumber == 7) 
            {
                latitude = atof(field);
            }
            else if (fieldNumber == 9) 
            {
                population = atoi(field);
                break; 
            }

            field = strtok(NULL, ","); // get the next field
            fieldNumber++; // increment the field number
        }

        totalPopulation += population; // cumulate the population of 20 cities

        // check if the current city is the northernmost city
        if (latitude > maxLatitude) 
        {
            maxLatitude = latitude;
            strcpy(northernmostCity, cityName);
        }
    }
    fclose(inFile);

    // Print the results
    printf("Sum of the populations: %d\n", totalPopulation);
    printf("Northernmost city is %s\n", northernmostCity);

    fgets(s, 100, stdin);  // wait for user to press Enter
    return 0;
}