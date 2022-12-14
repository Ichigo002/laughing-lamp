#ifndef CMDMANAGER_H
#define CMDMANAGER_H

#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include "../Game.h"

#include "SimpleCommand.h"

#define CM_SUCCESS 0
#define CM_ERROR_NOT_FOUND 1
#define CM_ERROR_INVALID_OVERLOAD 2
#define CM_ERROR_INVALID_PARAMETERS 3
#define CM_ERROR_GENERAL 4

class CmdManager
{
public:
    CmdManager();
    ~CmdManager();

    int processInput(const std::string* cmd);
    void start();
    void end();

    int t;
private:
    void initCmds();
    void errorHandler(int code);
    void printHelp();
    void printCmdHelp(SimpleCommand* cmd);

    std::vector<SimpleCommand*> vec_cmd;
};

static CmdManager* cmd;

static void cmd_init()
{
    cmd = new CmdManager();
}

static void cmd_execute()
{
    cmd->start();
}

#endif