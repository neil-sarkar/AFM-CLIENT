#include "commandqueue.h"
#include <stdlib.h>


commandqueue::commandqueue()
{
    head = (commandNode*)malloc(sizeof(commandNode));
    head->next = 0;
}

commandNode commandqueue::pop(){

    commandNode *temp;
    temp = (commandNode*)malloc(sizeof(commandNode));
    temp = head;
    head = temp->next;
    return *temp;
    free(temp);
}
void commandqueue::push(char command,char sendByteSize, char recByteSize){

    commandNode *temp1;                         // create a temporary node
    temp1=(commandNode*)malloc(sizeof(commandNode));   // allocate space for node
    temp1 = head;

    commandNode *temp;
    temp = (commandNode*)malloc(sizeof(commandNode));
    temp->commandName = command;
    temp->recByteSize = recByteSize;
    temp->sendByteSize = sendByteSize;
    temp->next = NULL;

    while(temp1->next!=0) // go to the last node
          temp1 = temp1->next;

    temp1->next = temp;
}
bool commandqueue::isEmpty(){
    if(head == nullptr){ return true; }
    else{ return false; }
}
