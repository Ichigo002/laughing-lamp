#pragma once
#include "../include/sdl/SDL.h"
#include "../include/sdl/SDL_Image.h"

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

    SDL_Texture* tex;
    SDL_Rect srcRect, destRect;

    int FPS;
    int frame_delay;
    Uint32 frame_start;
    int frame_time;

};