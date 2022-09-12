#ifndef CHUNK_H
#define CHUNK_H

#include "Vector2Int.h"

/* Element of world generating*/
class Chunk
{
public:
    Chunk(Vector2Int pos, int size)
    {
        this->pos = pos;
        this->size = size;

        map = new int*[size];
        for (int i = 0; i < size; i++)
        {
            map[i] = new int[size];
        }
    }
    ~Chunk()
    {
        for (int i = 0; i < size; i++)
        {
            delete [] map[i];
        }
        delete map;
    }

    Vector2Int pos;
    int** map;
    int size;
};

#endif

