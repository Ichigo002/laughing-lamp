#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <SDL.h>
#include <SDL_image.h>

class TextureManager
{
public:
    /* Load Surfae by filename & create the texture with renderer */
    static SDL_Texture* load(SDL_Renderer* renderer, const char* filename)
    {
        SDL_Surface* tmpSrf = IMG_Load(filename);

        return SDL_CreateTextureFromSurface(renderer, tmpSrf);
    }
};

#endif