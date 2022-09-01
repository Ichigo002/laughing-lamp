#include "../include/sdl/SDL.h"
#include "../include/sdl/SDL_Image.h"
#include "TextureManager.h"
#include "PerlinNoise.h"
#include "Vector2Int.h"

#ifndef HEXMAP_H
#define HEXMAP_H

#define HEX_WIDTH 32
#define HEX_HEIGHT 32
#define MAP_SCALE 0.125f
#define MAP_NOISE 10

class HexMap
{
public:
    HexMap(SDL_Renderer* r, int seed);
    ~HexMap();

    void draw();
    void editMapValue(size_t row, size_t col, const float v);
    float getMapValue(size_t row, size_t col);

private:

    void drawSingleHex(size_t out_row, size_t out_col, int input_row, int input_col);
    void loadTileset(const char* filename);
    void createEmptyMap(size_t x, size_t y);
    void generateNoiseMap(const int seed);
    void drawRules(const float tmpV, int* src_row, int* src_col);

    SDL_Renderer* r;
    SDL_Texture* tileset;
    SDL_Rect srcR, destR;

    float **map = nullptr;
    size_t mapWidth;
    size_t mapHeight;
};

#endif