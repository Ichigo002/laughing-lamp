#ifndef SIMPLECOMMAND_H
#define SIMPLECOMMAND_H

#include <iostream>
#include "../Game.h"

class SimpleCommand
{
public:
    SimpleCommand() { }
    virtual ~SimpleCommand() { }

    std::string* overloads = new std::string();
    size_t overl_count = 0;
    std::string description = "";
    std::string command_name = "";

    virtual int process(const std::string argv[], int argc) { return -1; }
};

#endif