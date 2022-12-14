#ifndef HEXMAP_H
#define HEXMAP_H

#include <SDL.h>
#include <SDL_image.h>
#include "../utility/Vector2Int.h"
#include "../utility/Camera.h"
#include "Chunk.h"
#include <vector>
#include <cstdlib>
#include "../GEV.h"

using namespace GEV;

/* Direct position to source to take the hex picture */
struct TileEncode
{
    int srcX;
    int srcY;
};

class HexMap
{
public:
    /// <param name="camera">Camera for rendering</param>
    /// <param name="tileset_path">Path or filename to tileset picture (*.png)</param>
    HexMap(Camera* camera);
    ~HexMap();

    /* Set seed for map */
    /* If seed is not set then it generates randomly */
    void setSeed(int seed);

    int getSeed() { return seed; }

    /* Set parameters for map */
    /// <param name="render_scale">Rendering scale of hexagons</param>
    /// <param name="noise_scale">Perlin Noise value generating of map</param>
    void setFactor(float noise_scale = 2);

    /* Set size of single Chunk of map*/
    void setChunkSize(int size);

    /* Converts the GLB position into Chunk number*/
    Vector2Int convertGLB_Chunk(Vector2Int pos);

    /* Updates animations of water, lava, grass etc... */
    void updateAnimation();

    /* Generates new terrain for new camera position */
    void updateGenerator();

    /* Draw map */
    void draw();

    /* Changing the values or seed of map after generate map makes no changes because there are used only during baking map */
    void setupWorld();

    bool debug_mode = false;
private:
    /* Generate single chunk */
    void generateChunk(Vector2Int pos);

    /* Check position for chunk if exists there returns true else false */
    bool existChunk(Vector2Int pos);
    bool existChunk(int x, int y);
    
    /* Encode Tile into int number */
    int encodeTile(const int* row, const int* col);

    /* Decode value into source Rect x and y */
    inline TileEncode decodeTile(int v);

    /* Draw rules what tile should be used*/
    void drawRules(const double* v, int* src_row, int* src_col);

    /* Draw single Chunk */
    void drawChunk(const Chunk* chunk);

    /* Draw Simple Hexagon */
   // void drawHex(size_t out_row, size_t out_col, int input_row, int input_col);

    /* Get Random source from file to make mixed terrain*/
    void getRandSrcRow(int* src_row, int* src_col, int dest_col, int leng);

    int seed;

    std::vector<Chunk*> map;
    std::vector<TileEncode> encoded_tiles;

    Camera* camera;
    SDL_Texture* tileset;
    SDL_Rect srcR, destR;

    int anim_delay;
    bool anim_once;

    int current_water_anim;

    int w_chunk;
    int h_chunk;
};

#endif