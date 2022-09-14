#include "../map/HexMap.h"
#include "../utility/TextureManager.h"
#include "../perlin-noise/PerlinNoise.h"
#include <math.h>
#include <iostream>

HexMap::HexMap(Camera* camera, const char* tileset_path)
{
    this->camera = camera;
    tileset = TextureManager::load(camera->getRender(), tileset_path);

    srand(time(NULL));
    seed = rand() % 9000000000;

    render_scale = 2;
    noise_scale = 2;
    chunk_size = 16;
    ratioAtoB = .75f;

    anim_delay = 300;
    anim_once = false;

    current_water_anim = 0;
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
    if (static_cast<int>((SDL_GetTicks() / anim_delay) % 2) == 0)
    {
        anim_once = true;
        return;
    }

    if (!anim_once)
        return;

    anim_once = false;

    int r = 0, c = 5;
    int water_id1 = encodeTile(&r, &c);
    r = 1;
    int water_id2 = encodeTile(&r, &c);
    r = 2;
    int water_id3 = encodeTile(&r, &c);

    for (auto& chunk : map)
    {
        SDL_Rect rc = { chunk->pos.x, chunk->pos.y, chunk_size * HEX_WIDTH * render_scale, chunk_size * HEX_HEIGHT * .75f * render_scale };
        if (camera->isIntoViewport(&rc))
        {
            for (size_t y = 0; y < chunk->size; y++)
            {
                for (size_t x = 0; x < chunk->size; x++)
                {
                    if (chunk->map[y][x] == water_id1 ||
                        chunk->map[y][x] == water_id2 || 
                        chunk->map[y][x] == water_id3)
                    {
                        r = current_water_anim;
                        chunk->map[y][x] = encodeTile(&r, &c);
                    }
                }
            }
        }
    }

    current_water_anim++;
    if (current_water_anim > 2) current_water_anim = 0;
}

void HexMap::draw()
{
    for (auto& chunk : map)
    {
        drawChunk(chunk);
    }
    if (debug_mode)
    {
        srcR.x = 0;
        srcR.y = HEX_HEIGHT * 3;
        destR.x = 0;
        destR.y = 0;
        camera->drawDynamic(tileset, &srcR, &destR);
    }
}

void HexMap::generateWorld()
{
    // Setup for generating
    map.clear();
    encoded_tiles.clear();

    srcR.w = HEX_WIDTH;
    srcR.h = HEX_HEIGHT;

    destR.w = HEX_WIDTH * render_scale;
    destR.h = HEX_HEIGHT * render_scale;

    int w = HEX_WIDTH * chunk_size * render_scale;
    int h = HEX_HEIGHT * ratioAtoB * chunk_size * render_scale;
    //Generate Chunks
    for (int y = -10; y < 10; y++)
    {
        for (int x = -10; x < 10; x++)
        {
            generateChunk(Vector2Int(w * x, h * y));
        }
    }

}

void HexMap::generateChunk(Vector2Int pos)
{
    PerlinNoise pn(seed);
    pos.y += 200;
    Chunk* c = new Chunk(pos, chunk_size);

    int xWidth = HEX_WIDTH * chunk_size * render_scale;
    int yHeight = HEX_HEIGHT * ratioAtoB * chunk_size * render_scale;

    if(debug_mode)
        std::cout << "Chunk at: " << pos << std::endl;

    double rel_x = 0;
    double rel_y = 0;

    double pxs = 0;
    double pys = 0;

    int _r = 0, _c = 0; // r row, c col

    if (pos.x != 0) { pxs = static_cast<double>(pos.x) / xWidth * chunk_size; }
    if (pos.y != 0) { pys = static_cast<double>(pos.y) / yHeight * chunk_size; }

    for (size_t y = 0; y < c->size; y++)
    {
        for (size_t x = 0; x < c->size; x++)
        {
            rel_x = x + pxs;
            rel_y = y + pys;

            if (debug_mode && x == 0 && y == 0)
            {
                std::cout << "| rel_x = " << rel_x << std::endl;
                std::cout << "| rel_y = " << rel_y << std::endl << std::endl;
            }
            double px = rel_x / ((double)chunk_size);
            double py = rel_y / ((double)chunk_size);

            double n = pn.noise(noise_scale * px, noise_scale * py, .8f);

            drawRules(&n, &_r, &_c);
            c->map[y][x] = encodeTile(&_r, &_c);
        }
    }

    map.push_back(c);
}

int HexMap::encodeTile(const int* row, const int* col)
{
    int r = *row, c = *col;

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
    *row = 0;
    *col = 0;
    /* Water */
    if (*v < .3f)
    {
        *col = 5;
        *row = 0;
    }
    /* Sand */
    else if (*v < .42f)
    {
        getRandSrcRow(row, col, 3, 3);
    }
    /* Grass Transition */
    /*else if (*v < .46f)
    {
        *col = 1;
        *row = 3;
    }*/
    /* Grass Std */
    else if (*v < .7f)
    {
        getRandSrcRow(row, col, 1, 6);
    }
    /* Dirt before Mountain */
    else if (*v <= .78f)
    {
        getRandSrcRow(row, col, 2, 1);
    }
    /* Stone */
    else if (*v <= 1.0f)
    {
        getRandSrcRow(row, col, 4, 3);
    }
    // etc conditions
}

void HexMap::drawChunk(const Chunk* chunk)
{
    SDL_Rect rc = { chunk->pos.x, chunk->pos.y, chunk_size * HEX_WIDTH * render_scale, chunk_size * HEX_HEIGHT * .75f * render_scale};
    if (!camera->isIntoViewport(&rc))
        return;

    for (size_t y = 0; y < chunk->size; y++)
    {
        for (size_t x = 0; x < chunk->size; x++)
        {
            TileEncode t = decodeTile(chunk->map[y][x]);
            srcR.x = t.srcX;
            srcR.y = t.srcY;

            destR.x = x * HEX_WIDTH * render_scale + chunk->pos.x;
            destR.y = y * (HEX_HEIGHT * .75f) * render_scale + chunk->pos.y;

            if ((y + 1) % 2 == 0)
            {
                destR.x += HEX_WIDTH / 2 * render_scale;
            }


            camera->drawDynamic(tileset, &srcR, &destR);

            if (debug_mode)
            {
                if (y % 2 == 0 && x == 0)
                {
                    srcR.x = 0;
                    srcR.y = HEX_HEIGHT * 2;
                    camera->drawDynamic(tileset, &srcR, &destR);
                }
                if (y == 0 && x % 2 == 0)
                {
                    srcR.x = 0;
                    srcR.y = HEX_HEIGHT * 1;
                    camera->drawDynamic(tileset, &srcR, &destR);
                }
            }
        }
    }
}

void HexMap::getRandSrcRow(int* src_row, int* src_col, int dest_col, int leng)
{
    *src_col = dest_col;
    *src_row = rand() % leng;
}