#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//asks user to enter integer to be used by program

struct Node
{
    int data;
    struct Node *next;
};

static int getInt(int min, int max)
{
    int userInput = 0;
    int invalid = 1;
    do {
        scanf("%d", &userInput);
        if(userInput < min || userInput > max)
        {
            printf("Error. Enter a number between or including %d and %d\n", min, max);
        }
        else
        {
            invalid = 0;
        }
    } while(invalid);
    return userInput;
}

//returns the last index of the linked list
static int getLastIndex(struct Node *head)
{
    if(head == NULL)
    {
        return -1;
    }
    else
    {
        struct Node *temp;
        temp = head;
        int count = 0;
        while(temp->next != NULL)
        {
            temp = temp->next;
            count++;
        }
    return count;
    }
}


//prints the data of every node in the list in order
void printList(struct Node* head)
{
    if(head == NULL)
    {
        printf("List is empty");
    }
    while(head != NULL)
    {
        printf("%d-> ", head->data);
        head = head->next;
    }
    printf("\n");
}

//connects a linked list to the end of this linked list
void join(struct Node* head, struct Node *otherHead)
{
    if(head == NULL || otherHead == NULL)
    {
        printf("At least one of the two Nodes passed in are null.");
        return;
    }
    struct Node *temp;
    temp = head;
    while(temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = otherHead;
}

//adds a new node to the head of the list
void addHead(struct Node** head, int newData)
{
    struct Node *n = (struct Node*) malloc(sizeof(struct Node));
    n->data = newData;
    n->next = *head;
    *head = n;
}

//adds a new node to the tail of the list
void addTail(struct Node** head, int newData)
{
    struct Node* newTail = (struct Node*) malloc(sizeof(struct Node));
    struct Node* temp = *head;
    newTail->next = NULL;
    newTail->data = newData;

    if(*head == NULL)
    {
        *head = newTail;
        return;
    }
    else
    {
        while(temp->next != NULL)
        {
            temp = temp->next;
        }

        temp->next = newTail;
        return;
    }
}

//adds a node to a user specified index of the list
void addToIndex(struct Node** head, int newData, int index)
{
    struct Node *befTemp = *head;

    struct Node *newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->data = newData;

    int befIndex = 0;
    if(index < 0)
    {
        printf("Invalid Index.\n");
        return;
    }
    else if(index == 0)
    {
        newNode->next = *head;
        *head = newNode;
        return;
    }
    else if(index > 0 )
    {
        while(befIndex < (index - 1) && befTemp->next != NULL)
        {
            befTemp = befTemp->next;
            befIndex++;
        }

        if(befIndex != (index - 1) && befTemp->next == NULL)
        {
            printf("Invalid Index.\n");
            return;
        }
        else
        {
            newNode->next = befTemp->next;
            befTemp->next = newNode;
        }
        return;
    }
    else
    {
        return;
    }
}

//deletes a node based on user specified index ONLY THING NOT WORKING AS OF RIGHT NOW
void deleteNodeIndex(struct Node** head, int index)
{
    struct Node *befTemp = *head;

    int befIndex;

    if(index < 0)
    {
        printf("Invalid Index.");
        return;
    }
    else if(index == 0)
    {
        struct Node * temp = *head;
        *head = temp->next;
        free(temp);
    }
    else if(index > 0)
    {
        while(befIndex < (index - 1) && befTemp->next != NULL)
        {
            befTemp = befTemp->next;
            befIndex++;
        }
        if(befIndex != (index - 1) && befTemp->next == NULL)
        {
            printf("Invalid Index.\n");
            return;
        }
        befTemp = befTemp->next;
        struct Node *toDelete = befTemp->next;
        befTemp->next = toDelete->next;
        free(toDelete);
    }
    
}

//deletes first instance of a user specified value within the list
void delteNodeValue(struct Node** head, int deleteValue)
{
    struct Node *temp = *head, *prev;

    if(temp != NULL && temp->data == deleteValue)
    {
        *head = temp->next;
        free(temp);
        return;
    }

    while(temp->next != NULL && temp->data != deleteValue)
    {
        prev = temp;
        temp = temp->next;
    }

    if(temp->data != deleteValue)
    {
        printf("The number %d is not stored in the list\n", deleteValue);
        return;
    }

    prev->next = temp->next;
    free(temp);
}

//returns the data at a specified index in the list
void viewIndex(struct Node *head, int index)
{
    struct Node *temp;
    temp = head;

    if(index > getLastIndex(head))
    {
        printf("Invalid Index. Index must be between or including 0 and %d\n", getLastIndex(head));
        return;
    }
    int i;
    for(i = 0; i < index; i++)
    {
        temp = temp->next;
    }
    printf("Value at index %d: %d\n", index, temp->data);
}

static int getIndex(struct Node* head, int data)
{
    struct Node* temp;
    temp = head;
    int count = 0;

    while(count < getLastIndex(head) && data != temp->data)
    {
        count++;
        temp = temp->next;
    }
    if(count == getLastIndex(head) && data != temp->data)
    {
        return -1;
    }
    return count;
}


int main()
{
    struct Node* head = NULL;

    int input = -1;
    while(input != 0)
    {
    printf("Enter 1 to add node to end of the list\n");
    printf("Enter 2 to add node to specified location in list\n");
    printf("Enter 3 to remove a Node from a specified location in list\n");
    printf("Enter 4 to remove the first instance of a node with a specific value\n");
    printf("Enter 5 to view the value of a node at a specified position (0 indexed)\n");
    printf("Enter 6 to view the entire List\n");
    printf("Enter 0 to exit the program\n");
    printf("XXXX===================================XXXXXXXX===================================XXXX\n");
    input = getInt(0, 6);
    // if(input != 0)
    // {
    //     printf("XXXX===================================XXXX\nXXXX===================================XXXX\n");
    // }

        switch (input)
        {
        case 1:
            printf("Enter a numerical value to store in a node that will be added to the end of the list\n");
            int data = 0;
            int index = -1;
            data = getInt(-1000000, 1000000);
            addTail(&head, data); //add Node to end of list
            index = getLastIndex(head); //get last index of current list
            printf("Current List: ");
            printList(head);
            printf("XXXX===================================XXXXXXXX===================================XXXX\n");
            break;
        case 2:
            int data2 = 0;
            int index2 = -1;
            int maxIndex2 = 1000000;
            printf("Enter a numerical value to store in a node that will be added to a specified index of the list\n");
            data2 = getInt(-1000000, 1000000);
            maxIndex2 = getLastIndex(head); // maxIndex = Call a function that traverses the tree and finds last index 
            printf("Enter a number between or including 0 and %d indicating the index of the new element\n", maxIndex2);
            index2 = getInt(0, maxIndex2);
            addToIndex(&head, data2, index2); //add node to specified index
            printf("Current List: ");
            printList(head);
            printf("XXXX===================================XXXXXXXX===================================XXXX\n");
            break;
        case 3:
            int maxIndex3 = 10000000;
            int index3 = -1;
            //int data3 = -1;
            maxIndex3 = getLastIndex(head); //maxIndex = call function setting maxIndex
            printf("Enter a numerical value between or including 0 and %d\n", maxIndex3);
            index3 = getInt(0, maxIndex3);
            //data3 = viewIndex(head, index3); //data = call function getting value of Node at specified index
            deleteNodeIndex(&head, index3); //call function removing node at specified index
            printf("Current List: ");
            printList(head);
            printf("XXXX===================================XXXXXXXX===================================XXXX\n");
            break;
        case 4:
            int data4 = -1;
            int index4 = -1;
            printf("Enter a number indicating the value of the node that you want to remove the first instance of\n");
            data4 = getInt(-1000000, 1000000);
            index4 = getIndex(head, data4); //index = call function retrieving index of node based on value stored at node
            delteNodeValue(&head, data4); //call function removing first instance of node with specified value
            printf("Current List: ");
            printList(head);
            printf("XXXX===================================XXXXXXXX===================================XXXX\n");
            break;
        case 5: 
            int index5 = -1;
            int maxIndex5 = 100000000;
            maxIndex5 = getLastIndex(head); // maxIndex = call a function finding the max index of the list
            printf("Enter a number between or including 0 and %d to view the value of the node stored at that index\n", maxIndex5);
            index5 = getInt(0, maxIndex5);
            viewIndex(head, index5); //data = Function returning the value at specified index
            printf("Current List: ");
            printf("XXXX===================================XXXXXXXX===================================XXXX\n");
            break;
        case 6:
            printf("Current List: ");
            printList(head);
            printf("XXXX===================================XXXXXXXX===================================XXXX\n");
        case 0:
        default:
            break;
        }
    }
    return 1;
}

