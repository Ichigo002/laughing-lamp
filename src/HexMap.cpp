#include "HexMap.h"
#include <iostream>

HexMap::HexMap(SDL_Renderer* r, int seed)
{
    this->r = r;

    createEmptyMap(500, 200);

    generateNoiseMap(seed);

    loadTileset("assets/tileset.png");
}

HexMap::~HexMap()
{
    for (size_t i = 0; i < mapHeight; i++)
    {
        delete [] map[i];
    }
    delete [] map;
}

void HexMap::draw()
{
    int srcRow, srcCol;
    for (size_t y = 0; y < mapHeight; y++)
    {
        for (size_t x = 0; x < mapWidth; x++)
        {
            srcRow = 0;
            srcCol = 0;
            drawRules(map[y][x], &srcRow, &srcCol);
            drawSingleHex(x, y, srcCol, srcRow);
        }
        
    }
    
}

void HexMap::editMapValue(size_t row, size_t col, const float v)
{
    if(row < mapHeight && col < mapWidth)
    {
        if(v <= 1.0f && v >= 0.0f)
        {
            map[row][col] = v;
        }
        else
        {
            std::cout << "HexMap::editMapValue -> ERROR: Value is incorrect" << std::endl;
            return; 
        }
    }
    else 
    { 
        std::cout << "HexMap::editMapValue -> ERROR: Arguments of position are out of range" << std::endl;
        return; 
    }
}

float HexMap::getMapValue(size_t row, size_t col)
{
    if(row < mapHeight && col < mapWidth)
    {
        return map[row][col];
    }
    else 
    { 
        std::cout << "HexMap::getMapValue -> ERROR: Arguments of position are out of range" << std::endl;
        return 0; 
    }
}

void HexMap::drawSingleHex(size_t out_col, size_t out_row, int input_col, int input_row)
{
    srcR.x = input_col * HEX_WIDTH;
    srcR.y = input_row * HEX_HEIGHT;
    srcR.w = HEX_WIDTH;
    srcR.h = HEX_HEIGHT;

    destR.x = out_col * HEX_WIDTH * MAP_SCALE;
    destR.y = out_row * HEX_HEIGHT * MAP_SCALE;
    destR.w = HEX_WIDTH * MAP_SCALE;
    destR.h = HEX_HEIGHT * MAP_SCALE;

    SDL_RenderCopy(r, tileset, &srcR, &destR);
}

void HexMap::loadTileset(const char* filename)
{
    tileset = TextureManager::load(r, filename);
}

void HexMap::createEmptyMap(size_t x, size_t y)
{
    if(map != nullptr)
    {
        std::cout << "HexMap::createEmptyMap -> WARNING: Map has been already created" << std::endl;
        return;
    }

    mapWidth = x;
    mapHeight = y;

    map = new float*[y];

    for (size_t i = 0; i < y; i++)
    {
        map[i] = new float[x];
    }
}

void HexMap::generateNoiseMap(const int seed)
{
    if(map == nullptr)
    {
        std::cout << "HexMap::generateNoiseMap -> ERROR: Map is not created" << std::endl;
        return;
    }

    PerlinNoise pn(seed);

    for (size_t y = 0; y < mapHeight; y++)
    {
        for (size_t x = 0; x < mapWidth; x++)
        {
            double px = (double)x/((double)mapWidth);
            double py = (double)y/((double)mapHeight);

            double n = pn.noise(MAP_NOISE * px, MAP_NOISE * py, .8f);

            map[y][x] = n;
        }
    }
}

// src_row, src_col - tiles in the tilest.png file
// rules for value from noise map
void HexMap::drawRules(const float tmpV, int* src_row, int* src_col)
{
    if(tmpV <= .3f)
    {
        *src_row = 1;
    }
    else if(tmpV > .7f)
    {
        *src_col = 1;
    } 
    else if(tmpV > .3f)
    {
        *src_col = 1;
        *src_row = 1;
    }
    // etc conditions
}