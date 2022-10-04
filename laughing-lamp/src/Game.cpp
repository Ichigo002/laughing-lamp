#include <iostream>
#include "Game.h"
#include "utility/TextureManager.h"
#include "utility/KeyboardHandler.h"
#include "utility/Vector2Int.h"
#include "game-objects/Player.h"
#include "game-objects/Wall.h"
#include "game-objects/GameObject.h"
#include <string>
#include <SDL_ttf.h>

#include "build-map/BuildMap.h"

int Game::_init_SDL()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        return -1;


    Uint32 flags = SDL_WINDOW_SHOWN;
    flags += SDL_WINDOW_RESIZABLE;
    
    //iScreen_W = 1920; iScreen_H = 1080; flags += SDL_WINDOW_FULLSCREEN_DESKTOP;
    iScreen_W = 1200; iScreen_H = 720;


    window = SDL_CreateWindow("Laughing Lamp", 2100, SDL_WINDOWPOS_CENTERED, iScreen_W, iScreen_H, flags);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

    if (window == NULL)
        return -2;
    if (window == NULL)
        return -3;

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    return 0;
}

int Game::_init_objects()
{
    // Camera
    cam = new Camera(renderer, iScreen_W, iScreen_H);
    //Game Obejct Manager
    gom = new GameObjectManager(renderer, cam);
    gom->add<Player>();
    //Inventory System
    invsys = new InventorySystem();

    invsys->setCurrentSlot(PSlot(4, 4));
    invsys->add<Item_BrickBlock>(40);
    invsys->add<Item_Wood>(10);
    invsys->move(PSlot(0, 0), PSlot(4, 4));
    invsys->del("wood", 5);

    invsys->printCMD();

    uinv = new UIInventory(cam, invsys);

    return 0;
}

int Game::_init_maps()
{
                //Here you can put seed to game
    srand(time(NULL));
    int seed = rand() % 1000000000;

    // HexMap
    hexmap = new HexMap(cam, "assets/textures/terrain-v2.png");
    hexmap->setChunkSize(16);
    hexmap->setFactor(.2f);
    hexmap->setSeed(seed);
    hexmap->setupWorld();

    // BuildMap
    buildmap = new BuildMap(cam, gom);
    buildmap->hexmode = false;

    return 0;
}

int Game::_init_debug()
{
    debug_mode = false;

    SDL_Color clr = { 0, 0, 0 };
    debug_font = new FontAsset(renderer, "assets/fonts/Lato-Regular.ttf", 36, clr);

    debug_txt.push_back(new UIText(debug_font, "Laughing Lamp / v1.0.0"));
    debug_txt.push_back(new UIText(debug_font, "Seed: " + std::to_string(hexmap->getSeed())));
    debug_txt.push_back(new UIText(debug_font, "FPS: "));
    debug_txt.push_back(new UIText(debug_font, "==================="));
    debug_txt.push_back(new UIText(debug_font, "GLB"));
    //debug_txt.push_back(new UIText(debug_font, "GLBR"));
    debug_txt.push_back(new UIText(debug_font, "LCL"));
    debug_txt.push_back(new UIText(debug_font, "Chunk"));

    for (size_t i = 0; i < debug_txt.size(); i++)
    {
        debug_txt[i]->setStartingPos(5, i * 40);
    }

    return 0;
}

int Game::_init_FPS()
{
    FPS = 60;
    frame_delay = 1000 / FPS;
    frames = 0;
    ticks = 0;
    return 0;
}

Game::Game()
{
    int err = 0;

    err = _init_SDL();
    if (err != 0)
        std::cout << "Error " << err << " occurred!" << std::endl;

    err = _init_objects();
    if (err != 0)
        std::cout << "Error " << err << " occurred!" << std::endl;

    err = _init_maps();
    if (err != 0)
        std::cout << "Error " << err << " occurred!" << std::endl;

    err = _init_FPS();
    if (err != 0)
        std::cout << "Error " << err << " occurred!" << std::endl;

    err = _init_debug();
    if (err != 0)
        std::cout << "Error " << err << " occurred!" << std::endl;

    running = true;
}

Game::~Game()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::run()
{
    while (running)
    {
        frame_start = SDL_GetTicks();
        frames++;

        handleEvents();
        update();
        render();

        frame_time = SDL_GetTicks() - frame_start;
        ticks += frame_time;

        if (ticks >= 1000)
        {
            if (debug_mode)
                debug_txt[2]->setText("FPS: " + std::to_string(frames) + "  (SET: "+std::to_string(FPS)+")");

            ticks = 0;
            frames = 0;
        }


        if (frame_delay > frame_time)
        {
            SDL_Delay(frame_delay - frame_time);
            ticks += frame_delay - frame_time;
        }
    }
    
}

void Game::update()
{
    hexmap->updateAnimation();
    hexmap->updateGenerator();
    gom->update();
    buildmap->update();
    uinv->update();

    if (debug_mode)
    {
        // Player pos dispalying
        Vector2Int p = dynamic_cast<Player*>(gom->getObject("Player"))->getPos();
        debug_txt[4]->setText("GLB XY: " + std::to_string(p.x) + " / " + std::to_string(p.y) + " (R)");
        
        Vector2Int p1 = cam->convertGLB_LCL(p);
        debug_txt[5]->setText("LCL XY: " + std::to_string(p1.x) + " / " + std::to_string(p1.y));
        
        p1 = hexmap->convertGLB_Chunk(p);
        debug_txt[6]->setText("Chunk: " + std::to_string(p1.x) + " / " + std::to_string(p1.y));
    }
}

void Game::handleEvents()
{
    SDL_PollEvent(&_event);
    switch (_event.type)
    {
    case SDL_QUIT:
        running = false;
        break;
    }

    cam->update(&_event);
    buildmap->events(&_event);
    gom->events(&_event);
    uinv->events(&_event);

   // if (KeyboardHandler::pressedKey(SDLK_BACKQUOTE, &_event))
    //    cmd_execute();

    if (KeyboardHandler::pressedKey(SDLK_F8, &_event))
    {
        if(debug_mode)
            debug_mode = false;
        else
            debug_mode = true;

        hexmap->debug_mode = debug_mode;
        buildmap->debug_mode = debug_mode;
    }
    if (KeyboardHandler::pressedKey(SDLK_F9, &_event))
    {
        buildmap->enableCursorPlacing("brick", -1);
    }
    if (KeyboardHandler::pressedKey(SDLK_F10, &_event))
    {
        buildmap->enableCursorPlacing("wood", -1);
    }

    if (KeyboardHandler::pressedKey(SDLK_F7, &_event))
    {
        int seed = rand() % 1000000000;
        hexmap->setSeed(seed);
        hexmap->setupWorld();
        debug_txt[1]->setText("Seed: " + std::to_string(seed));
    }

    

    if (debug_mode && _event.type == SDL_WINDOWEVENT) {
        switch (_event.window.event) {
        case SDL_WINDOWEVENT_SHOWN:
            SDL_Log("Window %d shown", _event.window.windowID);
            break;
        case SDL_WINDOWEVENT_HIDDEN:
            SDL_Log("Window %d hidden", _event.window.windowID);
            break;
        case SDL_WINDOWEVENT_EXPOSED:
            SDL_Log("Window %d exposed", _event.window.windowID);
            break;
        case SDL_WINDOWEVENT_MOVED:
            SDL_Log("Window %d moved to %d,%d",
                _event.window.windowID, _event.window.data1,
                _event.window.data2);
            break;
        case SDL_WINDOWEVENT_RESIZED:
            SDL_Log("Window %d resized to %dx%d",
                _event.window.windowID, _event.window.data1,
                _event.window.data2);
            break;
        case SDL_WINDOWEVENT_SIZE_CHANGED:
            SDL_Log("Window %d size changed to %dx%d",
                _event.window.windowID, _event.window.data1,
                _event.window.data2);
            break;
        case SDL_WINDOWEVENT_MINIMIZED:
            SDL_Log("Window %d minimized", _event.window.windowID);
            break;
        case SDL_WINDOWEVENT_MAXIMIZED:
            SDL_Log("Window %d maximized", _event.window.windowID);
            break;
        case SDL_WINDOWEVENT_RESTORED:
            SDL_Log("Window %d restored", _event.window.windowID);
            break;
        case SDL_WINDOWEVENT_ENTER:
            SDL_Log("Mouse entered window %d",
                _event.window.windowID);
            break;
        case SDL_WINDOWEVENT_LEAVE:
            SDL_Log("Mouse left window %d", _event.window.windowID);
            break;
        case SDL_WINDOWEVENT_FOCUS_GAINED:
            SDL_Log("Window %d gained keyboard focus",
                _event.window.windowID);
            break;
        case SDL_WINDOWEVENT_FOCUS_LOST:
            SDL_Log("Window %d lost keyboard focus",
                _event.window.windowID);
            break;
        case SDL_WINDOWEVENT_CLOSE:
            SDL_Log("Window %d closed", _event.window.windowID);
            break;
#if SDL_VERSION_ATLEAST(2, 0, 5)
        case SDL_WINDOWEVENT_TAKE_FOCUS:
            SDL_Log("Window %d is offered a focus", _event.window.windowID);
            break;
        case SDL_WINDOWEVENT_HIT_TEST:
            SDL_Log("Window %d has a special hit test", _event.window.windowID);
            break;
#endif
        default:
            SDL_Log("Window %d got unknown event %d",
                _event.window.windowID, _event.window.event);
            break;
        }
    }
}

void Game::render()
{
    SDL_RenderClear(renderer);
    //Draw

    hexmap->draw();
    buildmap->draw();
    gom->draw();

    //UI
    uinv->draw();

    if (debug_mode)
        for (auto& txt : debug_txt)
        {
            txt->draw();
        }

    SDL_RenderPresent(renderer);
}