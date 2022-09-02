#include <iostream>

#ifndef SIMPLECOMMAND_H
#define SIMPLECOMMAND_H

class SimpleCommand
{
public:
    SimpleCommand() { }
    virtual ~SimpleCommand() { }

    std::string* overloads;
    size_t overl_count;
    std::string description;
    std::string command_name;

    virtual int process(const std::string argv[], int argc) { return -1; }
};

#endif