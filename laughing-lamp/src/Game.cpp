#include "Game.h"
#include "TextureManager.h"
#include "Vector2Int.h"
#include <iostream>
#include "Player.h"
#include "Wall.h"
#include "GameObject.h"

Game::Game()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "SDL INIT EVERYTHING failed" << std::endl;
        running = false;
    }
    else
    {
        Uint32 flags = SDL_WINDOW_SHOWN;
        flags += SDL_WINDOW_RESIZABLE;
        // flags += SDL_WINDOW_FULLSCREEN;

        window = SDL_CreateWindow("Laughing Lamp", 2000, SDL_WINDOWPOS_CENTERED, 1920, 1080, flags);
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
        srand(time(NULL));
        int seed = rand() % 1000000000;
         std::cout << "New Seed: " << seed << std::endl;
        // std::cin >> seed;


        map = new HexMap(renderer, seed, "assets/tileset-terrain.png", 400, 400, Vector2Int(-HEX_WIDTH/2, -HEX_HEIGHT/2));

        gameObjectMng = new GameObjectManager(renderer);

        //Player p(renderer);

        gameObjectMng->add<Player>();
        gameObjectMng->add<Wall>(0, 100);
        gameObjectMng->add<Wall>(100, 100);
        gameObjectMng->add<Wall>(200, 720);
        gameObjectMng->add<Wall>(550, 400);
        gameObjectMng->add<Wall>(660, 150);
        gameObjectMng->add<Wall>(760, 520);

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
    gameObjectMng->update();
}

void Game::handleEvents()
{
    SDL_PollEvent(&_event);

    gameObjectMng->events(&_event);

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
    gameObjectMng->draw();

    SDL_RenderPresent(renderer);
}