#include "HexMap.h"
#include <iostream>

HexMap::HexMap(SDL_Renderer* r, int seed, const char* filename, size_t w, size_t h, Vector2Int offsetxy)
{
    this->r = r;

    reinit(seed, filename, w, h, offsetxy);
}

HexMap::~HexMap()
{
    destroyMap();
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
            drawRules(&map[y][x], &srcRow, &srcCol);
            drawSingleHex(x, y, srcCol, srcRow);
        }
        
    }
    
}

void HexMap::reinit(int seed, const char* tileset_file, size_t w, size_t h, Vector2Int offset)
{
    srand(seed);
    this->offset = offset;

    destroyMap();
    createEmptyMap(w, h);
    generateNoiseMap(seed);
    loadTileset(tileset_file);

}

void HexMap::editMapValue(size_t row, size_t col, float v)
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
    int x = out_col * HEX_WIDTH * MAP_SCALE;
    int y = out_row * (HEX_HEIGHT * .75f) * MAP_SCALE;

    if((out_row + 1) % 2 == 0)
    {
        x += HEX_WIDTH / 2 * MAP_SCALE;
    }

    destR.x = x + offset.x;
    destR.y = y + offset.y;
    destR.w = HEX_WIDTH * MAP_SCALE;
    destR.h = HEX_HEIGHT * MAP_SCALE;

    srcR.x = input_col * HEX_WIDTH;
    srcR.y = input_row * HEX_HEIGHT;
    srcR.w = HEX_WIDTH;
    srcR.h = HEX_HEIGHT;

    SDL_RenderCopy(r, tileset, &srcR, &destR);
}

void HexMap::loadTileset(const char* filename)
{
    tileset = TextureManager::load(r, filename);
}

void HexMap::destroyMap()
{
    if(map == nullptr)
    {
        return;
    }

    for (size_t i = 0; i < mapHeight; i++)
    {
        delete [] map[i];
    }
    delete [] map;
    map = nullptr;
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

void HexMap::generateNoiseMap(int seed)
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
void HexMap::drawRules(const float* v, int* src_row, int* src_col)
{
    /* Water */
    if(*v < .3f)
    {
        *src_col = 5;
    }
    /* Sand */
    else if(*v < .42f)
    {
        *src_col = 3;
    }
    /* Grass Transition */
    else if(*v < .46f)
    {
        *src_col = 1;
        *src_row = 3;
    }
    /* Grass Std */
    else if(*v < .7f)
    {
        *src_col = 1;
        *src_row = 0;
    }
    /* Dirt before Mountain */
    else if (*v <= .78f)
    {
        *src_col = 2;
        *src_row = 0;
    }
    /* Stone */
    else if (*v <= 1.0f)
    {
        *src_col = 4;
        *src_row = 1;
    }
    // etc conditions
}

void HexMap::getRandSrcRow(int* src_row, int* src_col, int dest_col, int leng)
{
    *src_col = dest_col;
    *src_row = rand() % leng;
}