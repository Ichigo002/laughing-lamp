#include "Game.h"
#include "utility/TextureManager.h"
#include "utility/KeyboardHandler.h"
#include "utility/Vector2Int.h"
#include <iostream>
#include "game-objects/Player.h"
#include "game-objects/Wall.h"
#include "game-objects/GameObject.h"

Game::Game()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "SDL INIT EVERYTHING failed" << std::endl;
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

        tex = TextureManager::load(renderer, "assets/player.png");
        destRect.x = 10;
        destRect.y = 10;
        destRect.w = 32;
        destRect.h = 32;

                   //Here you can put seed to game
       // srand(time(NULL));
        //int seed = rand() % 1000000000;
       //  std::cout << "New Seed: " << seed << std::endl;
        // std::cin >> seed;

        cam = new Camera(renderer, Screen_W, Screen_H);

        static_game = this;
        cmd_init();

        map = new HexMap(cam, "assets/tileset-terrain.png");
        map->debug_mode = false;
        map->setChunkSize(16);
        map->setFactors(3, .6f);
        map->generateWorld();

        gom = new GameObjectManager(renderer, cam);

        cam->set(0, 0);

        //Player p(renderer);

        gom->add<Player>();

       /* 
        gom->add<Wall>(0, 100);
        gom->add<Wall>(100, 100);
        gom->add<Wall>(200, 720);
        gom->add<Wall>(550, 400);
        gom->add<Wall>(660, 150);
        gom->add<Wall>(760, 520);
       */

        running = true;
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

    switch (_event.type)
    {
    case SDL_QUIT:
        running = false;
        break;
    default:
        break;
    }
}

void Game::render()
{
    SDL_RenderClear(renderer);
    //Draw

    map->draw();
    gom->draw();

    SDL_RenderPresent(renderer);
}