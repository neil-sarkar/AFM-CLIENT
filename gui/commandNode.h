#ifndef COMMANDNODE_H
#define COMMANDNODE_H

class commandNode
{
    char m_commandName;
    char m_sendByteSize;
    char m_recByteSize;

  public:
    commandNode(char commandName, char sendByteSize, char recByteSize)
          : m_commandName(commandName), m_sendByteSize(sendByteSize), m_recByteSize(recByteSize) {}
    ~commandNode() {}

    char getcommandName() { return m_commandName; }
    int getsendByteSize() { return m_sendByteSize; }
};

#endif // COMMANDNODE_H
