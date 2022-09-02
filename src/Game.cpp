#include "Game.h"
#include <iostream>

SDL_Texture* tex;

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
        cmdManager = new CmdManager();

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

}

void Game::handleEvents()
{
    SDL_PollEvent(&event);

    switch (event.type)
    {
    case SDL_QUIT:
        running = false;
        break;
    case SDL_KEYDOWN:
        switch (event.key.keysym.sym)
        {
        case SDLK_BACKQUOTE:
            cmdManager->start();
            break;
        
        default:
            break;
        }
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
    SDL_RenderCopy(renderer, tex, NULL, &destRect);


    SDL_RenderPresent(renderer);
}