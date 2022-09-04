#include "../include/sdl/SDL.h"
#include "../include/sdl/SDL_Image.h"
#include "Vector2Int.h"
#include <cstdlib>

#ifndef HEXMAP_H
#define HEXMAP_H

#define HEX_WIDTH 28
#define HEX_HEIGHT 32
#define MAP_SCALE 1
#define MAP_NOISE 40

class HexMap
{
public:
    HexMap(SDL_Renderer* r, int seed, const char* filename, size_t w, size_t h, Vector2Int offset);
    ~HexMap();

    void reinit(int seed, const char* tileset_file, size_t w, size_t h, Vector2Int offset);
    void draw();
    void editMapValue(size_t row, size_t col, float v);
    float getMapValue(size_t row, size_t col);

private:

    void drawSingleHex(size_t out_row, size_t out_col, int input_row, int input_col);
    void loadTileset(const char* filename);
    void destroyMap();
    void createEmptyMap(size_t x, size_t y);
    void generateNoiseMap(int seed);
    void drawRules(const float* tmpV, int* src_row, int* src_col);
    void getRandSrcRow(int* src_row, int* src_col, int dest_col, int leng);

    SDL_Renderer* r;
    SDL_Texture* tileset;
    SDL_Rect srcR, destR;

    float **map = nullptr;
    size_t mapWidth;
    size_t mapHeight;

    Vector2Int offset;
};

#endif