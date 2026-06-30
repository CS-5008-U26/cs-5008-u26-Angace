/* Homework 7 - task 1 - A Linked List of Cities
* 1. define a genric signly-linked list node struct singleNode.
* 2. implelement 6 functions to build a singly-linked list node include: 
*    create node, head node, nodes of city, tail node，delete nodes，length of the list.
* 3. ask user for a command input
* 4. print results on the screen based on various commands
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 

/* create struct to store attributes from uscities.csv*/
typedef struct {
    char city[100];   // buffer to city name and holds 100 charactors
    char stateId[4]; // buffer to state ID and holds 3 charactors，2 digits + \0 + space
    int population;   // integer varaible for city popultation
} cityData;

/* crate struct for singly-linked list node with nickname sNode */
typedef struct singleNode {
    void *data;
    struct singleNode *next;
} sNode;

/* Remove the newline from the end of a string */
void killNewline(char *str) {
    int len = strlen(str);
    if ((len > 0) && (str[len-1] == '\n')){
        str[len-1] = '\0';
    }
}

/* ===== Implement functions that do the following without crashing even with bad arguments  ===== */
/* Given a city * (that is, a struct cityData *), 
* create a sNode (struct singleNode) whose "data" field is that city * */
sNode *createNode(cityData *city)
{
    if (city == NULL){ // if no data, return null
        return NULL;
    }

    sNode *newNode = malloc(sizeof(sNode)); //create a new node with the size of sNode

    if (newNode == NULL){ // no new node, return null
        return NULL;
    } 
    
    newNode->data = city; // insert data to the newNode pointer
    newNode->next = NULL; // make the next node to null
    return (newNode); // update new node
}

/* Add a sNode to the front of the list */
sNode *addHead(sNode *head, sNode *newNode)
{
    if (newNode == NULL){ // if no node, return head
        return (head);
    }

    newNode->next = head; // make the new node to the current head node
    return (newNode); // update head node to the new node
}

/* Add a sNode to the end of the list */
sNode *addTail(sNode *head, sNode *newNode)
{
    if (newNode == NULL){ //  if new node is NULL, do nothing.
        return (head);
    }

    if (head == NULL){
        return (newNode); // if list is empty, the new node becomes the head.
    }

    sNode *current = head; // start from head

    while (current->next != NULL){ // traverse list until the last node which is null
        current = current->next; // move current to next node
    }
    
    current->next = newNode; // link new node after the current node
    return (head);  // return the list from head node
}

/* Get a pointer to the n-th sNode in the list */
sNode *getAt(sNode *head, int i )
{
    if (i <= 0){  // validating i is in the bounds
        return NULL;
    }
    
    while ((head != NULL) && (i > 1)) { //if input > 0, then return i-1, because the first city is 1
        head = head->next;
        i--;
    }
    return (head); // retun the (i-1)th node
}

/* Delete a given sNode from the list */
sNode *deleteNode (sNode *head, sNode *target) {
    if (head == NULL ) { // if list is empty, then return null
        return NULL; 
    }

    if (head == target){ // delete the first node
        return (head->next); 
    }	

    sNode *pBefore = head; // search for previous node

    while ((pBefore != NULL) && (pBefore->next != target)) // if previous node is not null and next node is not the current
    {
        pBefore = pBefore->next; // move previous one to next
    }

    if (pBefore->next == NULL){  // newnode not found in the list
        return (head); 
    }

    pBefore->next = target->next; // remove pointed newnode from the list
    return (head);
}	

/* Get the length of the list */
int getLength(sNode *head)
{
    int i = 0; // i is number of countted nodes and initialize node count from 0, head is the nodes no yet counted

    while (head != NULL){ // loop the list until null
        i++; // cumulate count
        head = head->next; // move to next node in the list and count it 
    }
    return (i);
}

/* ==== Helper functions for commans ===== */
// reverde the list and retune a new head
sNode *reverse(sNode *head)
{
    sNode *pBefore = NULL;
    sNode *current = head;
 
    while (current != NULL) {
        sNode *next = current->next;
        current->next = pBefore;
        pBefore = current;
        current = next;
    }
    return (pBefore);   //update tail to head
}

// print in given format
void printCities(sNode *head, int i)
{
    int printed = 0; // initialize print count form 0
    while ((head != NULL) && (printed < i)) {
        cityData *cityName = (cityData *)head->data;
        printf("%s %s, population %d\n", cityName->city, cityName->stateId, cityName->population);
        head = head->next;
        printed++;
    }
}


/* ===== Main function ===== */
int main()
{
    char s[100]; // buffer to hold user input for waiting at the end of the program 
    char line[5000]; // buffer to hold each line of the file
    sNode *head = NULL; // initialize the head to empty

    /* ==== Read file ===== */
    FILE *inFile = fopen("/Users/angace/Desktop/cs-5008-u26-Angace/Resources/uscities.csv", "r"); 

    // Check if the file was opened successfully, if not, print an error message and exit the program
    if (inFile == NULL){
        printf("Error! Can not open file.\n");
        return 1; 
    } 

    // if the file is opened successfully
    else {    
        fgets(line, 5000, inFile);  // Skip header row
    }

    // loop to capture the first 20 cities from csv file
    for (int cityCount = 0; cityCount < 20; cityCount++) 
    {
        // if the current line is empty then break the loop
        if (fgets(line, 5000, inFile) == NULL){
            break;
        }

        // call the function to remove the newline character from the end of line
        killNewline(line); 

        // replace all quotes with space to simplify parsing
        for (int i = 0; line[i]; i++) {
            if (line[i] == '"') {
                line[i] = ' '; 
            }
        }
            
        // create heap memory to store city data
        cityData *city = malloc(sizeof(cityData));

        // if not city data, print error message and stop the program
        if (city == NULL){
            printf("Error.\n");
            return 1;
        }

        int fieldNumber = 1;     // initialize the current track of field number
        char *field = strtok(line, ","); // pointer to hold the current field

        // loop to parse the fields in the line
        while (field != NULL)
        {
            if (fieldNumber == 2) // city name
            {
                strncpy(city->city, field, sizeof(city->city) - 1);
                city->city[sizeof(city->city) - 1] = '\0';
            } 
            else if (fieldNumber == 3)  // state ID
            {
                strncpy(city->stateId, field, sizeof(city->stateId) - 1);
                city->stateId[sizeof(city->stateId) - 1] = '\0';

            }
            else if (fieldNumber == 9)  // poputation
            {
                city->population = atoi(field);
                break; 
            }

            field = strtok(NULL, ","); // get the next field
            fieldNumber++; // increment the field number
        }

        sNode *node = createNode(city); // create node for cities
        head = addTail(head, node);   // keep cities in file order
    }
    fclose(inFile);

    /* ==== User interaction command and print the result  ===== */
    // command loop
    while (1) {
        char command[100];   // buffer to hold user input/command, contains 100 charaters

        printf("size, delete, reverse, get, or print: "); // get number from the user

        // if any invalid input, exist loop
        if (scanf("%s", command) != 1){
            break;
        }

        // size command
        if (strcmp(command, "size") == 0) {
            printf("Size is %d\n", getLength(head));  // print lenght of the existing list throug function getLength
            continue;
        }
        
        // delete command
        else if (strcmp(command, "delete") == 0) {
            int i; // variable to hold integer that user input
            printf("Enter a number: ");  // get number from the user

            // read pointed node to delete
            if (scanf("%d", &i) != 1) {
                break;
            }

            sNode *target = getAt(head, i); // call function of getAt to find the value of i-th node

            if (target != NULL) {  // dete i-th node if it exits
                head = deleteNode(head, target);
            }
        } 

        // reverse command
        else if (strcmp(command, "reverse") == 0) {
            head = reverse(head); // reverse linked list and update the head node
        } 
       
        // get commant
        else if (strcmp(command, "get") == 0) {
            int g; // innteger varainle to hold user input number
            printf("Enter a number: "); // get number from the user
            scanf("%d", &g); 

            if (g == 1){ // continue next function when the first node exists
                continue;
            }
        
            sNode *target = getAt(head, g); // fine requested node

            if (target == NULL) { // if it's not exist, then ignore
                continue;
            } 

            sNode *prev=getAt(head,g-1); // find the privous node of the requested node

            if(prev!=NULL){ // if previus node exists, 
                prev->next=target->next;  //remove the target node from the current position
                head=addHead(head,target);  // move the target node as the head node
            }
        }
 
        // print command
         else if (strcmp(command, "print") == 0) {
            int n; // integer variable to hold user input number
            printf("Enter a number: "); // get number from the user
            if (scanf("%d", &n) != 1) {
                break;
            }

            printCities(head, n); // print n counts of cities in the list
 
        } else {
            printf("Invalid input.\n"); // print error message
            break;
        }
    }
 
    /* free all remaining nodes */
    while (head != NULL) {
        sNode *next = head->next;
        free(head->data);
        free(head);
        head = next;
    }

    printf("\nPress Enter to exit."); // promt use to exit program
    getchar(); // remove leftover \n
    getchar(); // wait for entering

    fgets(s, 100, stdin); 
    return 0;
}
