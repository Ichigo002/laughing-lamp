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

    noise_scale = 2;
    chunk_size = 16;

    anim_delay = 300;
    anim_once = false;

    current_water_anim = 0;
    generating_edge_offset = 600;
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

void HexMap::setFactor(float noise_scale)
{
    this->noise_scale = noise_scale;
}

void HexMap::setChunkSize(int size)
{
    chunk_size = size;
}

Vector2Int HexMap::convertGLB_Chunk(Vector2Int pos)
{
    if (pos.x < 0)
        pos.x -= w_chunk;
    if (pos.y < 0)
        pos.y -= h_chunk;
    return Vector2Int(pos.x / (HEX_WIDTH * chunk_size * MAP_RENDER_SCALE), pos.y / (HEX_HEIGHT * RATIOHEX_H * chunk_size * MAP_RENDER_SCALE));
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
        SDL_Rect rc = { chunk->pos.x, chunk->pos.y, chunk_size * HEX_WIDTH * MAP_RENDER_SCALE, chunk_size * HEX_HEIGHT * .75f * MAP_RENDER_SCALE };
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

// TODO 1 During refreshng F7 the map, There sometimes are sightable not generated space
void HexMap::updateGenerator()
{
    Vector2Int pp(camera->getPos());
    Vector2Int edge_sc(camera->getPos().x + camera->getWHScreen().x + generating_edge_offset, camera->getPos().y + camera->getWHScreen().y + generating_edge_offset);
    pp.x -= generating_edge_offset;
    pp.y -= generating_edge_offset;

    while (pp.x < edge_sc.x)
    {
        while (pp.y < edge_sc.y)
        {
            if (!existChunk(pp))
            {
                Vector2Int crch = convertGLB_Chunk(pp);
                crch.x *= w_chunk;
                crch.y *= h_chunk;
                generateChunk(crch);
            }
            pp.y += h_chunk;
        }
        pp.x += w_chunk;
        pp.y = camera->getPos().y;
    }
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

void HexMap::setupWorld()
{
    // Setup for generating
    map.clear();
    encoded_tiles.clear();

    srcR.w = HEX_WIDTH;
    srcR.h = HEX_HEIGHT;

    destR.w = HEX_WIDTH * MAP_RENDER_SCALE;
    destR.h = HEX_HEIGHT * MAP_RENDER_SCALE;

    w_chunk = HEX_WIDTH * chunk_size * MAP_RENDER_SCALE;
    h_chunk = HEX_HEIGHT * RATIOHEX_H * chunk_size * MAP_RENDER_SCALE;
}

void HexMap::generateChunk(Vector2Int pos)
{
    PerlinNoise pn(seed);
    Chunk* c = new Chunk(pos, chunk_size);
    
    if(debug_mode)
        std::cout << "---\nNew Chunk at: " << pos << std::endl;

    double rel_x = 0;
    double rel_y = 0;

    double pxs = 0;
    double pys = 0;

    int _r = 0, _c = 0; // r row, c col

    if (pos.x != 0) { pxs = static_cast<double>(pos.x) / w_chunk * chunk_size; }
    if (pos.y != 0) { pys = static_cast<double>(pos.y) / h_chunk * chunk_size; }

    for (size_t y = 0; y < c->size; y++)
    {
        for (size_t x = 0; x < c->size; x++)
        {
            rel_x = x + pxs;
            rel_y = y + pys;

            double px = rel_x / ((double)chunk_size);
            double py = rel_y / ((double)chunk_size);

            double n = pn.noise(noise_scale * px, noise_scale * py, .8f);

            drawRules(&n, &_r, &_c);
            c->map[y][x] = encodeTile(&_r, &_c);
        }
    }
    map.push_back(c);
}

bool HexMap::existChunk(Vector2Int pos)
{
    if (pos.x < 0)
        pos.x -= w_chunk;
    if (pos.y < 0)
        pos.y -= h_chunk;

    pos.x /= w_chunk;
    pos.y /= h_chunk;

    pos.x *= w_chunk;
    pos.y *= h_chunk;

    for (auto& ch : map)
    {
        if (ch->pos == pos)
            return true;
    }
    return false;
}

bool HexMap::existChunk(int x, int y)
{
    return existChunk(Vector2Int(x, y));
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
    SDL_Rect rc = { chunk->pos.x, chunk->pos.y, chunk_size * HEX_WIDTH * MAP_RENDER_SCALE, chunk_size * HEX_HEIGHT * RATIOHEX_H * MAP_RENDER_SCALE};
    if (!camera->isIntoViewport(&rc))
        return;

    for (size_t y = 0; y < chunk->size; y++)
    {
        for (size_t x = 0; x < chunk->size; x++)
        {
            TileEncode t = decodeTile(chunk->map[y][x]);
            srcR.x = t.srcX;
            srcR.y = t.srcY;

            destR.x = x * HEX_WIDTH * MAP_RENDER_SCALE + chunk->pos.x;
            destR.y = y * (HEX_HEIGHT * RATIOHEX_H) * MAP_RENDER_SCALE + chunk->pos.y;

            if ((y + 1) % 2 == 0)
            {
                destR.x += HEX_WIDTH / 2 * MAP_RENDER_SCALE;
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