#include <iostream>
#include "Game.h"
#include "utility/TextureManager.h"
#include "utility/KeyboardHandler.h"
#include "utility/Vector2Int.h"
#include "game-objects/Player.h"
#include "game-objects/Wall.h"
#include "game-objects/GameObject.h"
#include <string>

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
        seed = 26313;
         std::cout << "New Seed: " << seed << std::endl;
         //std::cin >> seed;

        cam = new Camera(renderer, Screen_W, Screen_H);

        static_game = this;
        cmd_init();
        
        map = new HexMap(cam, "assets/textures/terrain-v2.png");
        map->setChunkSize(16);
        map->setFactors(2, .5f);
        map->setSeed(seed);
        map->generateWorld();

        gom = new GameObjectManager(renderer, cam);

        cam->set(0, 0);

        gom->add<Player>();

        running = true;
       
        // DEBUG TEXT INFO
        // DEBUG TEXT INFO
        debug_mode = false;

        const int fontpt = 36;

        debug_txts.push_back(new GUI_Text(cam, "Laughing Lamp / 1.0", 5, 0));
        debug_txts.push_back(new GUI_Text(cam, "60 FPS", 5, fontpt * 1));
        debug_txts.push_back(new GUI_Text(cam, "Player Pos XYZ:", 5, fontpt * 3));
        debug_txts.push_back(new GUI_Text(cam, "0000 / 0000", 5, fontpt * 4));

        for (auto& txt : debug_txts)
        {
            txt->setSize(fontpt - 4);
            txt->SetColor(255, 255, 255);
            txt->make();
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

        handleEvents();
        update();
        render();

        frame_time = SDL_GetTicks() - frame_start;

        if(frame_delay > frame_time)
        {
            SDL_Delay(frame_delay - frame_time);
        }
    }
    
}

void Game::update()
{
    map->updateAnimation();
    gom->update();

    if (debug_mode)
    {
        // Player pos dispalying
        Vector2Int p = cam->getPos();
        p.x += cam->getWHScreen().x / 2;
        p.y += cam->getWHScreen().y / 2;
        debug_txts[3]->setText((std::to_string(p.x) + " / " + std::to_string(p.y)).c_str());
        debug_txts[3]->make();
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

    if(debug_mode)
        for (auto& txt : debug_txts)
        {
            txt->draw();
        }

    SDL_RenderPresent(renderer);
}