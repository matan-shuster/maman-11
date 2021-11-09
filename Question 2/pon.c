// We want to read from a file line by line?
#include <stdio.h>  
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define LINE_SIZE (101)
#define TRUE 1
#define FALSE 0

/* Global Variables */
int isInComment = FALSE;
int isInQuotes = FALSE;
int notBalancedCount = 0;
int isBalanced = TRUE;

// structure of a stack node
struct sNode {
    char data;
    struct sNode* next;
};
 
// Function to push an item to stack
void push(struct sNode** top_ref, int new_data);
 
// Function to pop an item from stack
int pop(struct sNode** top_ref);
 

int isSingleCurlyBracket(char line[])
{
    int count = 0;
    int i = 0;
    while(line[i]){
        count++;
        if(count>1){
            break;
        }
    }
    if(count != 1){
        return FALSE;
    }
    else{
        return TRUE;
    }
}

// Returns 1 if character1 and character2 are matching left
// and right Brackets
int isMatching(char char1, char char2)
{
    if ('(' == char1 && ')' == char2)
        return TRUE;
    else if ('{' == char1 && '}' == char2)
        return TRUE;
    else if ('[' == char1 && ']' == char2)
        return TRUE;
    else
        return FALSE;
}
 
// Checks if brackets are balanced and returns FALSE or TRUE
int CheckBalance(char line[])
{
    int i = 0;
 
    // Declare an empty stack
    struct sNode* stack = NULL;
 
    //Check if each line is balanced or not. 
    while (line[i]){
        if(('{' == line[i] || '}' == line[i]) && TRUE == isSingleCurlyBracket(line)){
            return(FALSE);
            continue;
        }
        if('/' == line[i] && '*' == line[i+1]){
            i+=2;
            isInComment = TRUE;
            continue;
        }

        if('*' == line[i] && '/' == line[i+1] && TRUE == isInComment){
            i +=2;
            isInComment = FALSE;
            continue;
        }

        if( '"' == line[i] && FALSE == isInQuotes)
        {
            isInQuotes = TRUE;
            continue;
        }

        if('"' == line[i] && TRUE == isInQuotes)
        {
            isInQuotes = FALSE;
        }

        if(TRUE == isInQuotes){
            return TRUE;
            continue;
        }
        if ('{' == line[i] || '(' == line[i] || '[' == line[i]){
            push(&stack, line[i]);
        }
               
        if ('}' == line[i] || ')' == line[i] || ']' == line[i]) {
 
            // If we see an ending bracket without a pair
            // then return false
            if (NULL == stack ){
                return FALSE;
            }

            // Pop the top element from stack, if it is not
            // a pair bracket of character then there is a
            // mismatch.
            // his happens for lineressions like {(})
            else if (!isMatching(pop(&stack), line[i])){
                isBalanced = FALSE;
                return FALSE;
            }
            
        }
        i++;
    }
 
    // If there is something left in lineression then there
    // is a starting bracket without a closing
    // bracket
    if (stack == NULL)
        return TRUE; // balanced
    else
        return FALSE; // not balanced
}

int main(void) {
    char buffer[LINE_SIZE];
    printf("enter the file you want to print line by line:\n");
    while (fgets(buffer, LINE_SIZE, stdin)) {
        printf("\nThe line is:  %s\n", buffer);
        if (TRUE == CheckBalance(buffer)){
            printf("Line is Balanced \n");
          }
        
        else{
            printf("Line is not balanced \n");
        }
              memset(buffer, 0, sizeof(buffer));

    }
    if(TRUE == isBalanced)
    {
        printf("The text is balanced");
    }
    
    if(FALSE == isBalanced)
    {
        printf("The text is not balanced");
    }
    return 0;

}
// Function to push an item to stack
void push(struct sNode** top_ref, int new_data)
{
    // allocate node
    struct sNode* new_node
        = (struct sNode*)malloc(sizeof(struct sNode));
 
    // put in the data
    new_node->data = new_data;
 
    // link the old list off the new node
    new_node->next = (*top_ref);
 
    // move the head to point to the new node
    (*top_ref) = new_node;
}
 
// Function to pop an item from stack
int pop(struct sNode** top_ref)
{
    char res;
    struct sNode* top;
 
    // If stack is empty then error
    if (NULL == *top_ref) {
        printf("Stack overflow n");
        getchar();
        exit(0);
    }
    else {
        top = *top_ref;
        res = top->data;
        *top_ref = top->next;
        free(top);
        return res;
    }
}