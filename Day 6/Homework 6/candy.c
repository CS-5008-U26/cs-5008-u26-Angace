/* Homework 6 - Reading The Candy File
* ==== Task 1 ====
* 1.1 open and read candy-data.csv file, 
* 1.2 define a struct to store this data, then close file
* 1.3 print name of candies.
* ==== Task 2 ====
* 2.1 list chocolate 
* 2.2 if candy has caramel show uppercase, if not show lowercase
* 2.3 calc choclate percentage: (# of choclate & caramel)/ # of choclate
* === Task 3 ===
* 3.1 print attribute of feild 2 - 10: average sugar percent, price percent, and win percent
* 3.2 print the summary values of overall candies higher than average sugar percent
* 3.3 print the summary value of overall candies higher than average price percent
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  //task2 - case convert

/* cany struct & virables */
typedef struct candy_struct 
{
    char *competitorname;
    int chocolate;
    int fruity;
    int caramel;
    int peanutalmondy;
    int nougat;
    int crispedricewafer;
    int hard;
    int bar;
    int pluribus;
    double sugarpercent;
    double pricepercent;
    double winpercent;
} candyData;

/* Remove newline if present */
void killNewline(char *str) 
{
    int len = strlen(str);   // vraible to hold the length of the string
    if (len > 0 && str[len - 1] == '\n') { // if string has charactor and the last character is newline
        str[len - 1] = '\0';  // then replace the newline with the end-of-string \0
    }
}

/* Main function */
int main() 
{
    char s[100]; // buffer to hold the user input for the filename

    // Open file thro absolute path
    FILE *candyFile = fopen("/Users/angace/Desktop/cs-5008-u26-Angace/Resources/candy-data.csv", "r");

    // Show error msg if the file cant be openned
    if (candyFile == NULL) {
        printf("Error! Cannot open the file\n");
        return 1; // end the program
    }

    candyData *candies[1000]; // arrary and buffer of candy structs

    int count = 0; // variable to keep track of the number of candies read from the file

    char line[1000]; // buffer to hold each line read from the file

    fgets(line, 1000, candyFile); // skip the first line of the file

    /* Loop to read data */
    while (fgets(line, 1000, candyFile) != NULL) 
    {
        killNewline(line); // call function to kill newline

        candyData *candyPoint = malloc(sizeof(candyData)); // create struct 'candyData' on heap

        // check memory on the heap
        if (candyPoint == NULL) { 
            printf("Out of memory\n");
            return 1;
        }

        char *feild; // pointer to receive feilds

        feild = strtok(line, ",");
        candyPoint->competitorname = strdup(feild); // save name to heap

        feild = strtok(NULL, ",");
        candyPoint->chocolate = atoi(feild); // atoi converts string to integer

        feild = strtok(NULL, ",");
        candyPoint->fruity = atoi(feild);

        feild = strtok(NULL, ",");
        candyPoint->caramel = atoi(feild);

        feild = strtok(NULL, ",");
        candyPoint->peanutalmondy = atoi(feild);

        feild = strtok(NULL, ",");
        candyPoint->nougat = atoi(feild);

        feild = strtok(NULL, ",");
        candyPoint->crispedricewafer = atoi(feild);

        feild = strtok(NULL, ",");
        candyPoint->hard = atoi(feild);

        feild = strtok(NULL, ",");
        candyPoint->bar = atoi(feild);

        feild = strtok(NULL, ",");
        candyPoint->pluribus = atoi(feild);

        feild = strtok(NULL, ",");
        candyPoint->sugarpercent = atof(feild); // atof converts string to float

        feild = strtok(NULL, ",");
        candyPoint->pricepercent = atof(feild);

        feild = strtok(NULL, ",");
        candyPoint->winpercent = atof(feild);

        candies[count] = candyPoint; // save data to candies array opinter
        count++; //cumulate count of candy/row for the loop
    }
    fclose(candyFile); // close file

    /* Task 1 - Show candy names on the screen */
    printf("\n =====  Task 1: Candy Names =====\n"); // print title

    for (int i = 0; i < count; i++) {  // loop to print candy name from array one by one
        printf("%s\n", candies[i]->competitorname);
    }


    /* Task 2 - Chocolate candies */
    printf("\n ===== Task 2: Chocolate Candies  =====\n");

    int chocolateCount = 0; // initialize choco count for loop
    int caramelChocoCount = 0; // initialize caramel chco count for loop

    for (int chocoN = 0; chocoN < count; chocoN++) // search chcolate candy by looping candy count 
    {
        if (candies[chocoN]->chocolate == 1) // show candies if chocolate column = 1
        {
            chocolateCount++;

            char *chocoName = candies[chocoN]->competitorname;

            // show uppercase if candy contains caramel，ie caramel column = 1
            if (candies[chocoN]->caramel == 1)
            {
                caramelChocoCount++;
                for (int x = 0; chocoName[x] != '\0'; x++) 
                {
                    printf("%c", toupper(chocoName[x]));
                }
                printf("\n");
            }
            // show lowercase if candy doesn't contain caramel
            else 
            {
                for (int x = 0; chocoName[x] != '\0'; x++)
                {
                    printf("%c", tolower(chocoName[x]));
                }
                printf("\n");
            }
        }
    }

    // Print the percent of chocolate candies that also have caramel to screen
    double caramelPercent = 0.0; // initalize caramel percent

    if (chocolateCount > 0)  // print result if has a chocolate candy
    {
        caramelPercent = ((double)caramelChocoCount / (double)chocolateCount) * 100;

        printf("\n# of Chocolate candies: %d\n", chocolateCount);
        printf("# of Chocolate candies with caramel: %d\n", caramelChocoCount);
        printf("Percent with caramel: %.2f%%\n", caramelPercent);
    } 
    else // show error msg
    {
        printf("\nThere is no chocolate candy.\n");
        return 1;
    }

    /* Task 3 - Summary and average info */
    printf("\n ===== Task 3: Summary Infomation  =====\n");

    // create 9 attribute names
    char *attributeNames[] = {"Chocolate",
                                "Fruity",
                                "Caramel",
                                "PeanutAlmondy",
                                "Nougat",
                                "CrispedRiceWafer",
                                "Hard",
                                "Bar",
                                "Pluribus"
    };

    // for loop to read each attribute of 9
    for (int attribute = 0; attribute < 9; attribute++)
    {
        int attributeCount = 0; // initialize attribute count from 0
        double sugarTotal = 0;  // intialize the total of sugar count from 0
        double priceTotal = 0;  // initialize the total of price from 0
        double winTotal = 0;    // initialize the total of win from 0

        for (int attr = 0; attr < count; attr++) 
        {
            int checkAttribute = 0; // initialize attribute count from 0

            switch (attribute) // using while loop to save attribute to struct field
            {
                case 0: checkAttribute = candies[attr]->chocolate; break;
                case 1: checkAttribute = candies[attr]->fruity; break;
                case 2: checkAttribute = candies[attr]->caramel; break;
                case 3: checkAttribute = candies[attr]->peanutalmondy; break;
                case 4: checkAttribute = candies[attr]->nougat; break;
                case 5: checkAttribute = candies[attr]->crispedricewafer; break;
                case 6: checkAttribute = candies[attr]->hard; break;
                case 7: checkAttribute = candies[attr]->bar; break;
                case 8: checkAttribute = candies[attr]->pluribus; break;
            }
 
            if (checkAttribute) // summarize attributes' counts
            {
                attributeCount++;
                sugarTotal += candies[attr]->sugarpercent; // sum of sugarpercent
                priceTotal += candies[attr]->pricepercent; // sum of pricepercent
                winTotal += candies[attr]->winpercent;     // sum of winpricent
            }   
        }

        // calculate percent
        float avgSugar = ((float)sugarTotal / attributeCount) * 100;
        float avgPrice = ((float)priceTotal / attributeCount) * 100;
        float avgWin = (float) winTotal / attributeCount;

        // print each attribute's results to the screen
        printf("\n%s\n", attributeNames[attribute]);
        printf("Average sugar percent: %.2f%%\n", avgSugar);
        printf("Average price percent: %.2f%%\n", avgPrice);
        printf("Average win: %.2f\n", avgWin);
    }

    /* summary of sugar above average */ 
    double totalSugar = 0; // initialize total of dugar percent to 1
    double totalPrice = 0; // initialize total of price to 1

    for (int total = 0; total < count; total++) // loop to cummulate total
    {
        totalSugar += candies[total]->sugarpercent;
        totalPrice += candies[total]->pricepercent;
    }

    // calculate percent for averages
    double avgAllSugar = totalSugar / count;
    double avgAllPrice = totalPrice / count;

    // Summarize sugar above average
    int sugarCount = 0;
    double fieldSugar = 0;
    double fieldPrice = 0;
    double fieldWin = 0;

    for (int s = 0; s < count; s++)
    {
        if (candies[s]->sugarpercent > avgAllSugar)
        {
            sugarCount++;

            fieldSugar += candies[s]->sugarpercent;
            fieldPrice += candies[s]->pricepercent;
            fieldWin += candies[s]->winpercent;
        }
    }

    // calculate average percent
    float avgSumSugar = ((float)fieldSugar / sugarCount) * 100;
    float avgSumPrice = ((float)fieldPrice / sugarCount) * 100;
    float avgSumWIn = (float)fieldWin / sugarCount;

    // print results to the screen
    printf("\n ***** Sugar above average summary ***** \n");
    printf("Average sugar percent: %.2f%%\n", avgSumSugar);
    printf("Average price percent: %.2f%%\n", avgSumPrice);
    printf("Average win percent: %.2f\n", avgSumWIn);  

    // Summarize price above average
    int priceCount = 0;      // iniitalize price count from 0
    double priceSugar = 0;   // initialize sugar price from 0
    double pricePrice = 0;   // initialize price price from 0
    double priceWin = 0;     // initialize win price from 0

    for (int p = 0; p < count; p++)
    {
        if (candies[p]->pricepercent > avgAllPrice)
        {
            priceCount++;

            priceSugar += candies[p]->sugarpercent;
            pricePrice += candies[p]->pricepercent;
            priceWin += candies[p]->winpercent;
        }
    }

    // calc price average percent
    float avgPriceSugar = ((float)priceSugar / priceCount) * 100;
    float avgPricePrice = ((float)pricePrice / priceCount) * 100;
    float avgPriceWin = (float)priceWin / priceCount;

    // show resilts on the screen
    printf("\n ***** Price Above Average Summary ***** \n");
    printf("Average sugar percent: %.2f%%\n", avgPriceSugar);
    printf("Average price percent: %.2f%%\n", avgPricePrice);
    printf("Average win percent: %.2f\n", avgPriceWin);

    /* free memory */
    for (int i = 0; i < count; i++)  // loop to free candy name from array one by one
    {   
        free(candies[i]->competitorname);
        free(candies[i]);
    }

    fgets(s, 100, stdin); // wait for user input before exiting
    return 0; // end the program
}