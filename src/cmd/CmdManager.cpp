#include "CmdManager.h"

CmdManager::CmdManager()
{
    isLoopMode = false;
}

CmdManager::~CmdManager()
{

}

int CmdManager::processInput(const std::string* cmd)
{
    return CM_SUCCESS;
}

void CmdManager::start()
{
    std::string out;

    std::cout << "$: ";
    std::getline(std::cin, out);

    if(out == "")
    {
        start();
        return;
    }

    int code;

    code = processInput(&out);

    errorHandler(code);
}

void CmdManager::end()
{

}

void CmdManager::initCmds()
{

}

void CmdManager::addCommand(SimpleCommand cmd)
{

}

void CmdManager::errorHandler(int code)
{
    std::string msg;

    switch (code)
    {
    case CM_SUCCESS:
        return;
    case CM_ERROR_NOT_FOUND:
        msg = "ERROR: The command has not been found in the internal commands. Type 'help' for more commands.";
        break;
    case CM_ERROR_INVALID_OVERLOAD:
        msg = "ERROR: Invalid overload for command. Type command without parameters to know what are overloads.";
        break;
    case CM_ERROR_INVALID_PARAMETERS:
        msg = "ERROR: Invalid parameters.";
        break;
    case CM_ERROR_GENERAL:
        msg = "ERROR: Unspecified error.";
        break;
    default:
        msg = "The Error code " + std::to_string(code) + " is undefined.";
        break;
    }
}