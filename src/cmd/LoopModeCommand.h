#include "SimpleCommand.h"

class LoopModeCommand : public SimpleCommand
{
public:
    LoopModeCommand()
    {
        command_name = "loop_mode";

        overl_count = 1;
        overloads = new std::string[overl_count];
        overloads[0] = "(bool active)";

        description = "If true then after every call of command, console keeps running.";
    }

    virtual int process(const std::string argv[], int argc) override
    {
        if(argc != 2)
            return CM_ERROR_INVALID_OVERLOAD;

        cmdManager->t = 4;

        return CM_SUCCESS;
    }
};