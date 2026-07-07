/* Homework 8 - Task 1 - Vector of Cities
* 1. ask the user for a number
* 2. read that many cities from the uscities.csv file into a vector
* 3. generic vector (voide *)
* 4. print the cities in the vector to the screen
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* create struct to store attributes from uscities.csv*/
typedef struct
{
    char city[100];    // buffer to city name and holds 100 charactors
    char stateId[4];   // buffer to state ID and holds 3 charactors，2 digits + \0 + space
    int countyFIPS; // integer variable for county code, 5 digits + \0 + space
    double latitude;   // double variable for city latitude
    double longitude;  // double variable for city longitude
    int population;    // integer varaible for city popultation
} cityData;

/* ===== Vector Functions ===== */
/* Generic vector functions */
typedef struct vector3Method
{
    int size;    // allocated size
    int used;    // number of elements currently used
    void **data; // generic array
} vector;

/* Create Vector3 */
vector *createVector()
{
    vector *v = malloc(sizeof(vector));  // allocate memory for the vector
    v->size = 1;    // initial capacity
    v->used = 0;    // initialize used count from 0
    v->data = malloc(sizeof(void *) * v->size);  // allocate memory for the data array
    return (v);
}

/* Insert a new element at the end of the Vector */
void insertLast(vector *v, void *item)
{
    // grow the backing store if full
    if (v->used == v->size) {
        int newSize = v->size * 2; // multiply the current size by 2 to double the size
		void **newData = malloc(newSize * sizeof(void *));
       
        // copy the old data to the new data array
        for(int i=0; i<v->used; i++) {
            newData[i]=v->data[i];
        }

        v->size = newSize;
        free(v->data);
        v->data = newData;
    }
    v->data[v->used] = item;  // v[0] to v[v->used-1] are full of data
    v->used++;
}

/* Return the pointer stored at index i */
void *get(vector *v, int i)
{
    if (v == NULL) { // return null if the vector or data is NULL
        return NULL; 
    }
    if (i < 0 || i >= v->used){ // rerurn null if the index is out of bounds
        return NULL;
    }
    return (v->data[i]); // else return the pointer stored at index i
}


/* ======= Helper Functions ===== */
/* Remove the newline from the end of a string */
void killNewline(char *str) 
{
    int len = strlen(str);
    if ((len > 0) && (str[len-1] == '\n')){
        str[len-1] = '\0';
    }
}

/* Remove all quotation marks */
void removeQuotes(char *str)
{
    int i, j = 0;
    for (i = 0; str[i] != '\0'; i++)
    {
        if (str[i] != '"')
        {
            str[j] = str[i];
            j++;
        }
    }
    str[j] = '\0';
}

/* Read city data from a line of text */
cityData *readCity(char *line)
{
    cityData *city = malloc(sizeof(cityData));
    if (city == NULL)
    {
        return NULL;
    }

    int fieldNumber = 1;
    char *field = strtok(line, ",");

    while (field != NULL) // loop through each field in the line
    {
        switch (fieldNumber)
        {
            case 2: // get city name
                strncpy(city->city, field, sizeof(city->city) - 1);
                city->city[sizeof(city->city) - 1] = '\0';
                break; 
            case 3: // get state ID
                strncpy(city->stateId, field, sizeof(city->stateId) - 1);
                city->stateId[sizeof(city->stateId) - 1] = '\0';
                break;
            case 5: // get county FIPS code
                city->countyFIPS = atoi(field);
                break;
            case 7: // get latitude
                city->latitude = atof(field);
                break; 
            case 8: // get longitude
                city->longitude = atof(field);
                break;
            case 9:  // get population
                city->population = atoi(field);
                return (city); // return the city data after reading population
        }
        field = strtok(NULL, ",");
        fieldNumber++;
    }
    return (city);
}

/* ======= Task 2 binary tree node and linear search===== */
/* creat tree node */
typedef struct treeNode
{
    cityData *city;  //pointer to city data
    struct treeNode *left;  // left child pointer
    struct treeNode *right; // right child pointer
} tNode;

/* Create a new tree node with the given city data */
tNode *createTreeNode(cityData *city)
{
    if (city == NULL) {
        return NULL;
    }

    tNode *newNode = malloc(sizeof(tNode));

    if (newNode == NULL) {
        return NULL;
    }

    newNode->city = city;
    newNode->left = NULL;
    newNode->right = NULL;
    return (newNode);
}

/* Insert a city into the binary search tree based on latitude */
tNode *insertTreeNode(tNode *root, cityData *city)
{
    // empty tree
    if (root == NULL) {  
        return createTreeNode(city);
    }
    // smaller latitude goes left
    if (city->latitude < root->city->latitude) {
        root->left = insertTreeNode(root->left, city);
    } 
    // equal and larger latitude goes right
    else {
        root->right = insertTreeNode(root->right, city);
    }
    return (root);
}

/* Fill an array with city pointers using inorder traversal */
int fillArray(tNode *t, cityData **a, int start)
{
    int nextIndex = start; // initialize the next index to start
    // if the left child exists, recursively fill the left subtree
    if (t->left != NULL) 
    {
        nextIndex = fillArray(t->left, a, nextIndex);
    }

    a[nextIndex] = t->city; // store the city pointer in the array
    nextIndex++; // increment the index for the next city

    // if the right child exists, recursively fill the right subtree
    if (t->right != NULL) 
    {
        nextIndex = fillArray(t->right, a, nextIndex);
    }
    return (nextIndex);
}

/* linear search function*/
int linearSearch(cityData **array, int size)
{
    // loop through the array to find the index of New York
    for (int i = 0; i < size; i++)
    {
        if (strcmp(array[i]->city, "New York") == 0) // compare the city name with "New York"
        {
            return (i);
        }
    }
    return -1;
}

/* ======= Task 3 Functions ===== */
/* Insert a city into the binary search tree based on county FIPS code */
tNode *insertFIPSNode(tNode *root, cityData *city)
{
    // if the tree is empty, create a new node
    if (root == NULL){
        return createTreeNode(city);
    }
    // smaller county FIPS goes left
    if (city->countyFIPS < root->city->countyFIPS){
        root->left = insertFIPSNode(root->left, city);
    }
    // equal and larger county FIPS goes right
    else{
        root->right = insertFIPSNode(root->right, city);
    }
    return (root);
}

/* Binary search function to find the index of a city by county FIPS code   */
int binarySearch(cityData **array, int size, int target)
{
    int left = 0; // initialize left index to 0
    int right = size - 1; // initialize right index to size - 1

    // loop until left index is less than or equal to right index
    while (left <= right) 
    {
        int middle = (left + right) / 2;
        if (array[middle]->countyFIPS == target)
        {
            return middle;
        }

        if (target < array[middle]->countyFIPS)
        {
            right = middle - 1;
        }
        
        else
        {
            left = middle + 1;
        }
    }
    return -1;
}


/* ====== Main function ====== */
int main()
{
    char s[100]; // buffer to hold user input for waiting at the end of the program
    char line[5000]; // buffer to hold each line read from the file
    int numberCity; // integer variable to hold user input for number of cities to read

    /* ======= Task1 ======== */
    /* prompt user for input */
    printf("How many cities: "); 
    if (scanf("%d", &numberCity) != 1) { // read user
        printf("Invalid input.\n"); // print error message
        return 1; // exit if invalid input
    } 

    /* create a vector to hold the city data */
    vector *cities = createVector(); // call createVector to create a new vector
    if (cities == NULL) { // check if the vector was created successfully
        printf("Error creating vector.\n");
        return 1; // exit if vector creation failed
    }

    /* open the file for reading */
     FILE *inFile = fopen("../../Resources/uscities.csv", "r");

    if (inFile == NULL) { // check if the file was opened successfully
        printf("Error! Can not open file.\n");
        return 1;
    }

    /* Skip the header row */
    fgets(line, sizeof(line), inFile);

    /* Read the specified number of cities */
    for (int cityCount = 0; cityCount < numberCity; cityCount++)
    {
         // if the current line is empty then break the loop
        if (fgets(line, 5000, inFile) == NULL){
            break;
        }

        // call the function to remove the newline character from the end of line
        killNewline(line); 

        // call the function to replace quotes with spaces
        removeQuotes(line);

        // read the city data from the line and create a cityData struct
        cityData *city = readCity(line);
        if (city != NULL)
        {
            insertLast(cities, city);
        }
    }
    fclose(inFile); // close the file after reading

    /* Show results on the screen */
    for(int i = 0; i < cities->used; i++)
    {
        cityData *city = get(cities, i);
        printf("%s %s, population %d, at (%.4lf, %.4lf)\n",
                city->city,
                city->stateId,
                city->population,
                city->latitude,
                city->longitude);
    }


    /* ===== Task 2 command ===== */
    /* Create BST by latitude */
    tNode *root = NULL;  // initialize the root of the BST to null
    
    // loop through the vector of cities and insert each city into the BST
    for (int i = 0; i < cities->used; i++)
    {
        cityData *city = get(cities, i);
        root = insertTreeNode(root, city);
    }

    cityData **sortedCities = malloc(sizeof(cityData *) * cities->used); // allocate memory for an array of cityData pointers to hold the sorted cities
    fillArray(root, sortedCities, 0);   // fill the array with city pointers using inorder traversal of the BST

    // print the sorted array of cities by latitude
    printf("\nSorted latitude array:\n");
    for (int i = 0; i < cities->used; i++)
    {
        printf("%d  %-20s %.4lf\n", i, sortedCities[i]->city, sortedCities[i]->latitude);
    }

    // when array is completed, find the index of the New York entry in array
    int nycIndex = linearSearch(sortedCities, cities->used);
  
    // show results on the screen
    printf("By latitude, New York is index %d \n", nycIndex);


    /* ===== Task 3 command===== */
    /* Create BST ordered by county FIPS */
    tNode *rootFIPS = NULL; // initialize the root of the BST ordered by county FIPS to null
    // loop through the vector of cities and insert each city into the BST ordered by county FIPS
    for (int i = 0; i < cities->used; i++)
    {
        cityData *city = get(cities, i);
        rootFIPS = insertFIPSNode(rootFIPS, city);
    }

    cityData **sortedFIPS = malloc(sizeof(cityData *) * cities->used); // allocate memory for an array of cityData pointers to hold the sorted cities by FIPS
    fillArray(rootFIPS, sortedFIPS, 0); // fill the array with city pointers using inorder traversal of the BST ordered by FIPS

    // print the sorted array of cities by FIPS code
    printf("\nSorted FIPS array:\n");
    for (int i = 0; i < cities->used; i++)
    {
        printf("%d  %-20s %d\n", i, sortedFIPS[i]->city, sortedFIPS[i]->countyFIPS);
    }

    // find the index of New York in the sorted FIPS array using binary search
    int cityIndex = binarySearch(sortedFIPS, cities->used, 36081);
   
    // show results on the screen
    printf("By FIPS code, New York is index %d\n", cityIndex);


    /* ===== Frree memory ===== */
    /* Free city structs */
    for (int i = 0; i < cities->used; i++){
        free(cities->data[i]);
    }

    /* Free vector */
    free(cities->data);
    free(cities);
    free(sortedCities);
    free(sortedFIPS);

    fgets(s, sizeof(s), stdin); // wait for user input before exiting the program
    return 0;
}