#include "SimpleCommand.h"

class LoopModeCommand : public SimpleCommand
{
public:
    LoopModeCommand()
    {
        command_name = "debug";

        overl_count = 1;
        overloads = new std::string[overl_count];
        overloads[0] = "(bool mode)";

        description = "Activate debug mode for developers";
    }

    virtual int process(const std::string argv[], int argc) override
    {
        if(argc != 2)
            return CM_ERROR_INVALID_OVERLOAD;

        return CM_SUCCESS;
    }
};