#include "CmdManager.h"
#include "../utility/Utilities.h"

#include "LoopModeCommand.h"

CmdManager::CmdManager()
{
   // isLoopMode = false;
    initCmds();
}

CmdManager::~CmdManager()
{
    std::vector<SimpleCommand*>::iterator sc_iter;
    for (sc_iter = vec_cmd.begin(); sc_iter < vec_cmd.end(); sc_iter++)
    {
       delete [] *sc_iter;
    }
    vec_cmd.clear();
}

int CmdManager::processInput(const std::string* cmd)
{
    std::vector<std::string> vec = Utilities::split(" ", *cmd);

    int argc = vec.size();
    std::string *argv = new std::string[argc];

    std::vector<std::string>::iterator iter;
    std::string *p = &argv[0];
    for (iter = vec.begin(); iter < vec.end(); iter++)
    {
        *p = *iter;
        p++;
    }

    if(argv[0] == "help")
    {
        printHelp();
        delete [] argv;
        return CM_SUCCESS;
    }
    
    int code = CM_ERROR_NOT_FOUND;
    std::vector<SimpleCommand*>::iterator sc_iter;
    for (sc_iter = vec_cmd.begin(); sc_iter < vec_cmd.end(); sc_iter++)
    {
        SimpleCommand* sc = (*sc_iter);

        if(sc->command_name == argv[0])
        {
            if(argc > 1)
            {
                code = sc->process(argv, argc);
            }
            else
            {
                std::cout << "Overloads of '" << sc->command_name << "':" << std::endl;
                printCmdHelp(sc);
                std::cout << std::endl;
                code = CM_SUCCESS;
            }
            
        }
    }

    delete [] argv;
    return code;
}

void CmdManager::printHelp()
{
    std::cout << "All available internal commands in the game: " << std::endl;
    
    for (std::vector<SimpleCommand*>::iterator iter = vec_cmd.begin(); iter < vec_cmd.end(); iter++)
    {
        printCmdHelp(*iter);
    }
    
}

void CmdManager::printCmdHelp(SimpleCommand* cmd)
{
    std::string *strp = &cmd->overloads[0];

    std::cout << " > " << cmd->command_name << std::endl;
    std::cout << "   |> Description: " << cmd->description << std::endl;
    std::cout << "   |> Overloads: " << std::endl;

    for (size_t i = 0; i < cmd->overl_count; i++)
    {
        std::cout << "      |> "<< i+1 <<"/" << cmd->overl_count << ": " << *strp << std::endl;
        strp++;
    }
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

  //  if(isLoopMode) start(); else end();
}

void CmdManager::end()
{
    std::cout << "END!" << std::endl;
}

void CmdManager::initCmds()
{
    vec_cmd.push_back(new LoopModeCommand());
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

    std::clog << msg << std::endl;
}