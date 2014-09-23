#ifndef COMMANDQUEUE_H
#define COMMANDQUEUE_H

typedef struct commandNode{
    char commandName;
    char sendByteSize;
    char recByteSize;
    commandNode *next;
}commandNode;

class commandqueue{

public:
    explicit commandqueue();
    void push(char command,char sendByteSize, char recByteSize);
    commandNode pop();
    bool isEmpty();
    commandNode *head;
private:

};

#endif // COMMANDQUEUE_H
