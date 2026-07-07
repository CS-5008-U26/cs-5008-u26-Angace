/* Lab 8 
1. Create a zooNode struct for node in the tree
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 

/* ====  Task 1 ===== 
* Define node and struct
*/
# define ANIMAL_NODE 0
# define QUESTION_NODE 1

typedef struct zooNode_struct
{
    int type; //Set to either ANIMAL_NODE or QUESTION_NODE
    char *animalName; // only used when type is ANIMAL_NODE, otherwise NULL
    char *questionText; // only used when type is QUESTION_NODE, otherwise NULL
    struct zooNode_struct *yesChild; // only used when type is QUESTION_NODE, otherwise NULL
    struct zooNode_struct *noChild; // only used when type is QUESTION_NODE, otherwise NULL
} zooNode;

zooNode *createAnimalNode(char *animalName)
{
    zooNode *node = malloc(sizeof(zooNode));
    if (node == NULL) {
        return NULL;
    }
    node->type = ANIMAL_NODE;
    node->animalName = strdup(animalName);
    node->questionText = NULL;
    node->yesChild = NULL;
    node->noChild = NULL;
    return node;
}

zooNode *createQuestionNode(char *questionText, zooNode *noAnimal, zooNode *yesAnimal) {
    zooNode *node = malloc(sizeof(zooNode));
    if (node == NULL) {
        return NULL;
    }
    node->type = QUESTION_NODE;
    node->animalName = NULL;
    node->questionText = strdup(questionText);
    node->noChild = noAnimal;
    node->yesChild = yesAnimal;
    return node;
}

/* ====  Task 2 ===== 
* Build the zoo tree
*/

void killNewLine(char *str) 
{
    int len = strlen(str);
    if ((len > 0) && (str[len-1] == '\n'))
    {
        str[len-1] = '\0';
    }
}


void interact (zooNode *node)
{
    char inputBUffer[200]; // buffer to hold user input

    if(node->type == QUESTION_NODE)
    {
        printf("%s", node->questionText);
        char answer[10];
        fgets(inputBUffer, 200, stdin);
        killNewLine(inputBUffer);

        if (inputBUffer[0] == 'y')
        {
            interact(node->yesChild);
        } 
        else if (inputBUffer[0] == 'n') 
        {
            interact(node->noChild);
        } 
        else {
            printf("Invalid input. Please answer with 'y' or 'n'.\n");
            interact(node); // ask the question again
            return;
        } 
    } 
    
    else if (node->type == ANIMAL_NODE) 
    {
        printf("Is it a %s (y/n)? ", node->animalName);

        if (fgets(inputBUffer, 200, stdin) == NULL)
        {
            return; // handle EOF or error
        }
        else if (inputBUffer[0] == 'n')
        {
            char animalName[100];
            char difference[200];
            char questionStr[300];

            printf("What is your new animalcalled? ");
            fgets(animalName, 200, stdin);
            killNewLine(animalName);
            printf("How would you tell a %s from a %s ? A %s (has or is):", animalName, node->animalName, animalName);
            fgets(difference, 200, stdin);
            killNewLine(difference);

            if (strncmp(difference, "is", 3) == 0 ) 
            {
                sprintf(questionStr, "Is it %s?", difference + 3);
            }
            else if (strncmp(difference, "has", 4) == 0 ) 
            {
                sprintf(questionStr, "Does it have %s?", difference + 4);
            }

            zooNode *newAnimalNode = createAnimalNode(animalName);
            zooNode *newQuestionNode = createQuestionNode(questionStr, node, newAnimalNode);            
        } 
    }
}


int main (){
    char s[100]; // buffer to hold user input for waiting at the end of the program

    topNode = createQuestionNode("Lion");
    printf("Think of an animal.\n");
    interact(topNode);


    fgets(s, 100, stdin);
    return 0;
}