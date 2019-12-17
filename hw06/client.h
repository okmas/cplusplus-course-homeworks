#ifndef CLIENT_H
#define CLIENT_H

#include "queue.h"
#include "command.h"
#include "virtualMachine.h"
#include <vector>

class Client
{
    Queue<Command> cmds;
public:
    Client() {}
    void add(Command *command);
    void add(std::vector<Command*> comm);
    void run();
    void clear();
    int load(const std::string &path, VirtualMachine *v);
private:
    void runCmd();
    bool validCmd(std::string cmd_name, bool has_argument);
};

#endif // CLIENT_H
