#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>

#include <cstdlib>
#include "map/HexMap.h"
#include "game-objects/GameObjectManager.h"
#include "utility/Camera.h"
#include "cmd/CmdManager.h"

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

    HexMap* getHexMap() { return map; }
    Camera* getCamera() { return cam; }
    GameObjectManager* getGameObjectManager() { return gom; }
private:
    HexMap* map;
    GameObjectManager* gom;
    Camera* cam;
    

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

static Game* static_game;

#endif