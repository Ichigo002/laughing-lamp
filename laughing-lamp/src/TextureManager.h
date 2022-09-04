#include "../include/sdl/SDL.h"
#include "../include/sdl/SDL_image.h"

#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

class TextureManager
{
public:
    static SDL_Texture* load(SDL_Renderer* renderer, const char* filename)
    {
        SDL_Surface* tmpSrf = IMG_Load(filename);
        return SDL_CreateTextureFromSurface(renderer, tmpSrf);
    }
};

#endif