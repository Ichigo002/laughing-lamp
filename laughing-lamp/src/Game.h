#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <SDL_image.h>
#include <vector>

#include <cstdlib>
#include "map/HexMap.h"
#include "game-objects/GameObjectManager.h"
#include "utility/Camera.h"
#include "GUI/UIText.h"
#include "GUI/FontAsset.h"
#include "build-map/BuildMap.h"

class Game
{
private:
    int _init_SDL();
    int _init_objects();
    int _init_maps();
    int _init_debug();
    int _init_FPS();
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
    HexMap* hexmap;
    BuildMap* buildmap;
    GameObjectManager* gom;
    Camera* cam;

    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Event _event;
    bool running;

    bool debug_mode;
    std::vector<UIText*> debug_txt;
    FontAsset* debug_font;

    int FPS;
    int frame_delay;
    Uint32 frame_start;
    int frame_time;
    float ticks;
    int frames;

    int iScreen_W;
    int iScreen_H;
};

#endif