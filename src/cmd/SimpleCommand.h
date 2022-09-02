#include <iostream>

#ifndef SIMPLECOMMAND_H
#define SIMPLECOMMAND_H

class SimpleCommand
{
public:
    SimpleCommand();
    virtual ~SimpleCommand();

    std::string overloads = "";
    std::string description = "";

    virtual int process(std::string argv[], int argc);
};

#endif