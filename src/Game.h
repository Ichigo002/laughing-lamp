#ifndef GAME_H
#define GAME_H

#include "../include/sdl/SDL.h"
#include "../include/sdl/SDL_Image.h"
#include <cstdlib>
#include "HexMap.h"
#include "cmd/CmdManager.h"

class Game;

static Game* st_game;
static HexMap* map;
static CmdManager* cmdManager;

class Game
{
public:
    Game();
    ~Game();

    void run();
    void handleEvents();
    void update();
    void render();

    void setRunning(bool i) { running = i; }
    void setFPS(int fps) { FPS = fps; }

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

#endif