#pragma once
#include "../include/sdl/SDL.h"

class Game
{
public:
    Game();
    ~Game();

    void run();
    void handleEvents();
    void update();
    void render();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event event;
    bool running;

    int FPS;
    int frame_delay;
    Uint32 frame_start;
    int frame_time;

};