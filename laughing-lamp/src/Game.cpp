#include <iostream>
#include "Game.h"
#include "utility/TextureManager.h"
#include "utility/KeyboardHandler.h"
#include "utility/Vector2Int.h"
#include "game-objects/Player.h"
#include "game-objects/Wall.h"
#include "game-objects/GameObject.h"

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
        // flags += SDL_WINDOW_FULLSCREEN;

        window = SDL_CreateWindow("Laughing Lamp", 2000, SDL_WINDOWPOS_CENTERED, Screen_W, Screen_H, flags);
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

        debug_txts.push_back(new GUI_Text(cam, "assets/fonts/Lato-Regular.ttf", 200));
        debug_txts.push_back(new GUI_Text(cam, "assets/fonts/Lato-Regular.ttf", 200));
        debug_txts.push_back(new GUI_Text(cam, "assets/fonts/Lato-Regular.ttf", 200));

        debug_txts[0]->setText("Laughing Lamp / 1.0");
        debug_txts[0]->setRect(10, 0, 40 * TXT_RATIO, 40);

        debug_txts[1]->setText("60 FPS");
        debug_txts[1]->setRect(10, 85, 40 * TXT_RATIO, 40);

        debug_txts[2]->setText("XYZ: ");
        debug_txts[2]->setRect(10, 130, 40 * TXT_RATIO, 40);




        for (auto& txt : debug_txts)
        {
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

    for (auto& txt : debug_txts)
    {
        txt->draw();
    }

    SDL_RenderPresent(renderer);
}