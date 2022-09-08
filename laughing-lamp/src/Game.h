#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>

#include <cstdlib>
#include "HexMap.h"

class Game;

static Game* st_game;
static HexMap* map;

class Game
{
public:
    Game();
    ~Game();

    /*Main loop game*/
    void run();
    void handleEvents();
    void update();
    void render();

    void setRunning(bool i) { running = i; }
    void setFPS(int fps) { FPS = fps; }

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event _event;
    bool running;

    SDL_Texture* tex;
    SDL_Rect srcRect, destRect;

    int FPS;
    int frame_delay;
    Uint32 frame_start;
    int frame_time;

};

#endif