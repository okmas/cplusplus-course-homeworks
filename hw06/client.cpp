#include "client.h"
#include <algorithm>
//#include <ios>
//#include <iostream>
#include <fstream>
#include <string>

void Client::add(Command *command)
{
    if (cmds.size() > cmds.maxSize())
    {
        runCmd();
    }
    cmds.enque(command);
}

void Client::add(std::vector<Command *> comm)
{
    std::for_each(comm.begin(), comm.end(), add);
}

void Client::runCmd()
{
    cmds.deque()();
}

void Client::run()
{
    while (cmds.size() > 0)
    {
        runCmd();
    }
}

void Client::clear()
{
    if (cmds.size() > 0)
    {
        cmds.deque();
    }
}

int Client::load(const std::string &path, VirtualMachine *v)
{
    std::ifstream in(path.c_str());
    std::string line;

    while (in.good())
    {
        std::getline(in, line);

        std::string cmd_name;
        int space_pos = line.find(' ');
        bool has_argument;

        if (space_pos == std::string::npos) // no argument
        {
            cmd_name = line;
            has_argument = false;
        }
        else // one argument
        {
            cmd_name = line.substr(0, space_pos);
            has_argument = true;
            // nacitat argument - bacha aby tam bol, vtedy
            // je to nevalidne
        }

        if (validCmd(cmd_name, has_argument))
        {
            add(new Comm)
        }
        else
        {

        }
    }

    return 0;
}

bool Client::validCmd(std::string cmd_name, bool has_argument)
{
    return ((cmd_name == "add") && (has_argument)) ||
           (!has_argument);
}
