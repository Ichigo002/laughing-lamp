#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include "Camera.h"

#define DEF_PATH_TEX "assets/textures/" // Default path to texture : "assets/textures/"

class TextureManager
{
public:

    /* Load Surface by filename & create the texture with renderer */
    ///[OBSOLETE]
    static SDL_Texture* loadf(SDL_Renderer* renderer, const char* filename)
    {
        SDL_Surface* tmpSrf = IMG_Load(filename);

        return SDL_CreateTextureFromSurface(renderer, tmpSrf);
    }

    /// <summary>
    /// Loads the texture from file
    /// </summary>
    /// <param name="c">camera to render</param>
    /// <param name="cat_dir">category folder of texture</param>
    /// <param name="filename">name of file to load</param>
    /// <returns>Ready texture pointer</returns>
    static SDL_Texture* load(Camera* c, std::string cat_dir, std::string filename)
    {
        return load(c->getRender(), cat_dir, filename);
    }

    /// <summary>
    /// Loads the texture from file
    /// </summary>
    /// <param name="c">camera to render</param>
    /// <param name="cat_dir">category folder of texture</param>
    /// <param name="filename">name of file to load</param>
    /// <returns>Ready texture pointer</returns>
    static SDL_Texture* load(SDL_Renderer* r, std::string cat_dir, std::string filename)
    {
        std::string s = DEF_PATH_TEX + cat_dir + "/" + filename;
        SDL_Surface* tmpSrf = IMG_Load(s.c_str());
        return SDL_CreateTextureFromSurface(r, tmpSrf);
    }

};

#endif