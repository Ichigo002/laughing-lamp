#include "Game.h"
#include <iostream>
#include "Vector2Int.h"

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

        window = SDL_CreateWindow("Laughing Lamp", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, flags);
        renderer = SDL_CreateRenderer(window, -1, 0);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        //FPS
        FPS = 60;
        frame_delay = 1000 / FPS;

        SDL_Surface* sur = IMG_Load("src/player.png");
        tex = SDL_CreateTextureFromSurface(renderer, sur);
        SDL_FreeSurface(sur);
        destRect.x = 10;
        destRect.y = 10;
        destRect.w = 32;
        destRect.h = 32;

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
    default:
        break;
    }
}

void Game::render()
{
    SDL_RenderClear(renderer);
    //Draw

    SDL_RenderCopy(renderer, tex, NULL, &destRect);


    SDL_RenderPresent(renderer);
}