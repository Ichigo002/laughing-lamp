#include "Game.h"
#include <Windows.h>

int main(int argc, char* argv[])
{
    //ONLY FOR RELEASES
    HWND windowHandle = GetConsoleWindow();
    ShowWindow(windowHandle, SW_HIDE);
    //ONLY FOR RELEASES

    Game game;
    game.run();
    
    return 0;
}