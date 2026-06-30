/* Homework 7 - task 2 - A Doubly-Linked List of Cities
 * 1. define a generic doubly-linked list node struct doubleNode, named "dNode".
 * 2. implement 6 functions to build a doubly-linked list including:
 *    create node, head node, nodes of city, tail node, delete nodes, length of the list.
 * 3. ask user for a command input
 * 4. print results on the screen based on various commands
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
 
/* create struct to store attributes from uscities.csv */
typedef struct {
    char city[100];   // buffer to city name, holds 100 characters
    char stateId[4];  // buffer to state ID, holds 3 characters: 2 digits + \0
    int population;   // integer variable for city population
} cityData;

/* the most important update */
/* create struct for doubly-linked list node with nickname dNode */
typedef struct doubleNode {
    void *data;
    struct doubleNode *next;
    struct doubleNode *prev;   // add *prev for doubly-lined list
} dNode;
 
/* Remove the newline from the end of a string */
void killNewline(char *str) {
    int len = strlen(str);
    if ((len > 0) && (str[len - 1] == '\n')) {
        str[len-1] = '\0';
    }
}
 
/* ===== Implement functions that do the following without crashing even with bad arguments  ===== */
/* Given a city * (that is, a struct cityData *), 
* create a sNode (struct singleNode) whose "data" field is that city * */
dNode *createNode(cityData *city) 
{
    if (city == NULL) { // if no data, return null
        return NULL;
    }

    dNode *newNode = malloc(sizeof(dNode)); //create a new node with the size of dNode

    if (newNode == NULL) { // no new node, return null
        return NULL;
    }

    newNode->data = city; // insert data to the newNode pointer
    newNode->next = NULL; // make the next node to null
    newNode->prev = NULL; // make the prev node to null
    return (newNode); // update new node
}
 
/* Add a dNode to the front of the list */
dNode *addHead(dNode *head, dNode *newNode) 
{
    if (newNode == NULL) {  // if no node, return head
        return (head);
    }

    newNode->next = head; // make the new node to the current head node
    newNode->prev = NULL;

    if (head != NULL) {
        head->prev = newNode;   //back-link the old head
    }
    return (newNode); // update prev node to the new node
}
 
/* Add a dNode to the end of the list */
dNode *addTail(dNode *head, dNode *newNode) {
    if (newNode == NULL) { //  if new node is NULL, do nothing.
        return (head);
    }
    if (head == NULL) {  // if list is empty, the new node becomes the head.
        newNode->prev = NULL; // update prev node to null
        return (newNode); 
    }

    dNode *current = head;  // start from head

    while (current->next != NULL) {
        current = current->next;
    }
    current->next = newNode;
    newNode->prev = current;  //back-link the new tail
    newNode->next = NULL;  // update next node to null
    return (head); // return the list from head
}
 
/* Get a pointer to the n-th dNode in the list (1-based) */
dNode *getAt(dNode *head, int i) {
    if (i <= 0) {  // validating i is in the bounds
        return NULL;
    }

    while ((head != NULL) && (i > 1)) {  //if input > 0, then return i-1, because the first city is 1
        head = head->next;
        i--;
    }
    return (head); // retun the (i-1)th node
}
 
/* Delete a given dNode from the list */
dNode *deleteNode(dNode *head, dNode *target) {
    if ((head == NULL) || (target == NULL)) { // if list or given node is empty, then return null
        return (head);
    }

    // update the previous note's next pointer */
    if (target->prev != NULL) {
        target->prev->next = target->next;
    } else {
        head = target->next; // update target to the head
    }

    // update next node's prev pointer
    if (target->next != NULL) {
        target->next->prev = target->prev;
    }

    // isolate target before freeing it later
    target->next = NULL;
    target->prev = NULL;
    return (head);
}
 
/* Get the length of the list */
int getLength(dNode *head) {
    int i = 0; // i is number of countted nodes and initialize node count from 0, head is the nodes no yet counted

    while (head != NULL) { // loop the list until null
        i++; // cumulate count
        head = head->next; // move to next node in the list and count it 
    }
    return (i);
}
 
/* ===== Helper functions for commands ===== */
/* Reverse the list and return the new head */
dNode *reverse(dNode *head) 
{
    dNode *newHead = NULL;
    dNode *current = head;

    while (current != NULL) {
        dNode *nextNode = current->next;
        // swap next and prev
        current->next = current->prev;
        current->prev = nextNode;
        newHead = current;
        current = nextNode;
    }
    return (newHead);
}
 
// print in given format
void printCities(dNode *head, int i) 
{
    int printed = 0; // initialize print count form 0
    while ((head != NULL) && (printed < i)) {
        cityData *cityName = (cityData *)head->data;
        printf("%s %s, population %d\n",cityName->city, cityName->stateId, cityName->population);
        head = head->next;
        printed++;
    }
}
 

/* ===== Main function ===== */
int main() 
{
    char s[100];       /* buffer used to wait for Enter at the end */
    char line[5000];   /* buffer to hold each CSV line */
    dNode *head = NULL;
 
    /* ==== Read file ==== */
    FILE *inFile = fopen("../../Resources/uscities.csv", "r");
    
    // Check if the file was opened successfully, if not, print an error message and exit the program
    if (inFile == NULL) {
        printf("Error! Can not open file.\n");
        return 1;
    }

    // if the file is opened successfully
    else{
        fgets(line, 5000, inFile);  //skip header row
    }
    
    // loop to capture the first 20 cities from csv file
    for (int cityCount = 0; cityCount < 20; cityCount++) 
    {
        // if the current line is empty then break the loop
        if (fgets(line, 5000, inFile) == NULL) {
            break;
        }

        // call the function to remove the newline character from the end of line
        killNewline(line);
 
        // replace all quotes with spaces to simplify parsing
        for (int i = 0; line[i]; i++) {
            if (line[i] == '"') {
                line[i] = ' ';
            }
        }

        // create heap memory to store city data
        cityData *city = malloc(sizeof(cityData));

        // if not city data, print error message and stop the program
        if (city == NULL) {
            printf("Error.\n");
            return 1;
        }
 
        int fieldNumber = 1;  // initialize the current track of field number
        char *field = strtok(line, ",");  // pointer to hold the current field

        // loop to parse the fields in the line
        while (field != NULL) {
            if (fieldNumber == 2)  // city name 
            {   
                strncpy(city->city, field, sizeof(city->city) - 1);
                city->city[sizeof(city->city) - 1] = '\0';
            } 
            else if (fieldNumber == 3)   // state ID
            {
                strncpy(city->stateId, field, sizeof(city->stateId) - 1);
                city->stateId[sizeof(city->stateId) - 1] = '\0';
            } 
            else if (fieldNumber == 9) //population
            {
                city->population = atoi(field);
                break;
            }

            field = strtok(NULL, ","); // get the next field
            fieldNumber++; // increment the field number
        }
 
        dNode *node = createNode(city);  // create node for cities
        head = addTail(head, node);    // keep cities in file order
    }
    fclose(inFile);
 
    /* ==== User interaction command and print the result  ===== */
    while (1) {
        char command[100];  // buffer to hold user input/command, contains 100 charaters

        printf("size, delete, reverse, get, or print: ");  // get number from the user
 
        // if any invalid input, exist loop
        if (scanf("%s", command) != 1) {
            break;
        }
 
        // size command
        if (strcmp(command, "size") == 0) {
            printf("Size is %d\n", getLength(head));  //// print lenght of the existing list throug function getLength
            continue;
        }
        // delete command
        else if (strcmp(command, "delete") == 0) {
            int i;  // variable to hold integer that user input
            printf("Enter a number: ");

            // read pointed node to delete
            if (scanf("%d", &i) != 1) {
                break;
            }

            dNode *target = getAt(head, i);  // call function of getAt to find the value of i-th node

            if (target != NULL) {  // dete i-th node if it exits
                head = deleteNode(head, target);
            }
        }

        // reverse command
        else if (strcmp(command, "reverse") == 0) {
            head = reverse(head);  // reverse linked list and update the head node
        }

        // get command
        else if (strcmp(command, "get") == 0) {
            int g;  // innteger varainle to hold user input number
            printf("Enter a number: "); // get number from the user
            
            if (scanf("%d", &g) != 1) {
                break;
            }

            if (g == 1) {
                continue;   // already at head, nothing to do
            }

            dNode *target = getAt(head, g); // fine requested node

            if (target == NULL) { // if it's not exist, then ignore
                continue;
            }

            head = deleteNode(head, target); // remove target from its current position
            head = addHead(head, target); // move it to the front 
        }

        // print command
        else if (strcmp(command, "print") == 0) {
            int n;  // integer variable to hold user input number
            printf("Enter a number: ");  // get number from the user
            if (scanf("%d", &n) != 1) {
                break;
            }
            printCities(head, n); // print n counts of cities in the list
 
        }
        else {
            printf("Invalid input.\n"); // print error message
            break;
        }
    }
 
    /* free all remaining nodes */
    while (head != NULL) {
        dNode *next = head->next;
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