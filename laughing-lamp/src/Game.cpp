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

Game::Game()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "INIT failed" << std::endl;
        running = false;
    }
    else
    {
        int Screen_W = 1920;
        int Screen_H = 1080;

        Uint32 flags = SDL_WINDOW_SHOWN;
        flags += SDL_WINDOW_RESIZABLE;
       //  flags += SDL_WINDOW_FULLSCREEN;

        window = SDL_CreateWindow("Laughing Lamp", 1950, SDL_WINDOWPOS_CENTERED, Screen_W, Screen_H, flags);
        renderer = SDL_CreateRenderer(window, -1, 0);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        //FPS
        FPS = 60;
        frame_delay = 1000 / FPS;

                   //Here you can put seed to game
         srand(time(NULL));
        int seed = rand() % 1000000000;
         std::cout << "New Seed: " << seed << std::endl;
         //std::cin >> seed;

        cam = new Camera(renderer, Screen_W, Screen_H);

        static_game = this;
        cmd_init();
        
        map = new HexMap(cam, "assets/textures/terrain-v2.png");
        map->setChunkSize(16);
        map->setFactors(1, .5f);
        map->setSeed(seed);
        map->setupWorld();

        gom = new GameObjectManager(renderer, cam);

        cam->set(0, 0);

        gom->add<Player>();

        frames = 0;
        ticks = 0;
        running = true;
       
        // DEBUG TEXT INFO
        // DEBUG TEXT INFO
        debug_mode = false;

        SDL_Color clr = { 0, 0, 0 };
        debug_font = new FontAsset(renderer, "assets/fonts/Lato-Regular.ttf", 36, clr);

        debug_txt.push_back(new UIText(debug_font, "Laughing Lamp / v1.0.0"));
        debug_txt.push_back(new UIText(debug_font, "FPS: "));
        debug_txt.push_back(new UIText(debug_font, "======================"));
        debug_txt.push_back(new UIText(debug_font, "Player Pos 000/ 000"));
        debug_txt.push_back(new UIText(debug_font, "Chunk"));

        for (size_t i = 0; i < debug_txt.size(); i++)
        {
            debug_txt[i]->setStartingPos(5, i * 40);
        }
    }
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
                debug_txt[1]->setText("FPS: " + std::to_string(frames) + "  (SET: "+std::to_string(FPS)+")");

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
    //surf = TTF_RenderText_Solid(font, "Hello", txtc);
    //tex = SDL_CreateTextureFromSurface(renderer, surf);
    //SDL_FreeSurface(surf);

    //SDL_QueryTexture(tex, nullptr, nullptr, &txtR.w, &txtR.h);

    map->updateAnimation();
    map->updateGenerator();
    gom->update();

    if (debug_mode)
    {
        // Player pos dispalying
        Vector2Int p = cam->getPos();
        p.x += cam->getWHScreen().x / 2;
        p.y += cam->getWHScreen().y / 2;
        debug_txt[3]->setText("XY: " + std::to_string(p.x) + " / " + std::to_string(p.y));
        
        Vector2Int pch = map->getChunkForXY(p);

        debug_txt[4]->setText("Chunk: " + std::to_string(pch.x) + " / " + std::to_string(pch.y));
    }
}

void Game::handleEvents()
{
    SDL_PollEvent(&_event);

    gom->events(&_event);

    if (KeyboardHandler::pressedKey(SDLK_BACKQUOTE, &_event))
        cmd_execute();

    if (KeyboardHandler::pressedKey(SDLK_F8, &_event))
    {
        if(debug_mode)
            debug_mode = false;
        else
            debug_mode = true;

        map->debug_mode = debug_mode;
    }

    if(_event.type == SDL_QUIT)
        running = false;
}

void Game::render()
{
    SDL_RenderClear(renderer);
    //Draw

    map->draw();
    gom->draw();

    //UI
    if (debug_mode)
        for (auto& txt : debug_txt)
        {
            txt->draw();
        }

    SDL_RenderPresent(renderer);
}