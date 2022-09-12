#include "HexMap.h"
#include "TextureManager.h"
#include "PerlinNoise.h"
#include <iostream>

HexMap::HexMap(Camera* camera, const char* tileset_path)
{
    this->camera = camera;
    tileset = TextureManager::load(camera->getRender(), tileset_path);

    srand(time(NULL));
    seed = rand() % 9000000000;

    render_scale = 2;
    noise_scale = 40;
    chunk_size = 16;
}

HexMap::~HexMap()
{
    map.clear();
    encoded_tiles.clear();
}

void HexMap::setSeed(int seed)
{
    this->seed = seed;
}

void HexMap::setFactors(float render_scale, float noise_scale)
{
    this->render_scale = render_scale;
    this->noise_scale = noise_scale;
}

void HexMap::setChunkSize(int size)
{
    chunk_size = size;
}

void HexMap::updateAnimation()
{
    // TO DO
}

void HexMap::draw()
{
    for (auto& chunk : map)
    {
        drawChunk(chunk);
    }
}

void HexMap::generateWorld()
{
    // Setup for generating
    map.clear();
    encoded_tiles.clear();

    //Generate Chunks
    generateChunk(Vector2Int(0,0));
    generateChunk(Vector2Int(HEX_WIDTH * chunk_size * render_scale * 1, HEX_HEIGHT * chunk_size * render_scale * 0));

}

void HexMap::generateChunk(Vector2Int pos)
{
    PerlinNoise pn(seed);
    Chunk* c = new Chunk(pos, chunk_size);

    for (size_t y = 0; y < chunk_size; y++)
    {
        for (size_t x = 0; x < chunk_size; x++)
        {
            double px = (double)x / ((double)chunk_size);
            double py = (double)y / ((double)chunk_size);

            double n = pn.noise(noise_scale * px, noise_scale * py, .8f);

            c->map[y][x] = encodeTileFor(&n);
        }
    }

    map.push_back(c);
}

int HexMap::encodeTileFor(const double* tmpV)
{
    int r = 0, c = 0; // r row, c col
    drawRules(tmpV, &r, &c);

    r *= HEX_HEIGHT;
    c *= HEX_WIDTH;

    for (size_t i = 0; i < encoded_tiles.size(); i++)
    {
        if (encoded_tiles[i].srcX == c && encoded_tiles[i].srcY == r)
        {
            return i;
        }
    }
    TileEncode t;
    t.srcX = c;
    t.srcY = r;

    encoded_tiles.push_back(t);
    return encoded_tiles.size()-1;
}

inline TileEncode HexMap::decodeTile(int v)
{
    return encoded_tiles[v];
}

// src_row, src_col - tiles in the tilest.png file
// rules for value from noise map
void HexMap::drawRules(const double* v, int* row, int* col)
{
    /* Water */
    if (*v < .3f)
    {
        *col = 5;
    }
    /* Sand */
    else if (*v < .42f)
    {
        *col = 3;
    }
    /* Grass Transition */
    else if (*v < .46f)
    {
        *col = 1;
        *row = 3;
    }
    /* Grass Std */
    else if (*v < .7f)
    {
        *col = 1;
        *row = 0;
    }
    /* Dirt before Mountain */
    else if (*v <= .78f)
    {
        *col = 2;
        *row = 0;
    }
    /* Stone */
    else if (*v <= 1.0f)
    {
        *col = 4;
        *row = 1;
    }
    // etc conditions
}

void HexMap::drawChunk(const Chunk* chunk)
{
    for (size_t y = 0; y < chunk->size; y++)
    {
        for (size_t x = 0; x < chunk->size; x++)
        {
            TileEncode t = decodeTile(chunk->map[y][x]);
            srcR.x = t.srcX;
            srcR.y = t.srcY;
            srcR.w = HEX_WIDTH;
            srcR.h = HEX_HEIGHT;

            destR.x = x * HEX_WIDTH * render_scale + chunk->pos.x;
            destR.y = y * (HEX_HEIGHT * .75f) * render_scale + chunk->pos.y;

            if ((y + 1) % 2 == 0)
            {
                destR.x += HEX_WIDTH / 2 * render_scale;
            }

            destR.w = HEX_WIDTH * render_scale;
            destR.h = HEX_HEIGHT * render_scale;

            camera->drawDynamic(tileset, &srcR, &destR);
        }
    }
}

/*void HexMap::drawHex(size_t out_col, size_t out_row, int input_col, int input_row)
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
}*/

void HexMap::getRandSrcRow(int* src_row, int* src_col, int dest_col, int leng)
{
    *src_col = dest_col;
    *src_row = rand() % leng;
}