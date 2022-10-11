#include <string>
#include <iostream>
#include <vector>
#include <SDL.h>

#ifndef UTILITIES_H
#define UTILITIES_H
 
namespace Util
{
    /* Split the string into vector of strings each time when it finds splitter sign */
    std::vector<std::string> split(const std::string splitter, std::string line)
    {
        std::vector<std::string> arr;
        int spacePos;
        int currPos = 0;
        int k = 0;
        int prevPos = 0;

        do
        {
            spacePos = line.find(splitter, currPos);

            if(spacePos >= 0)
            {
            
                currPos = spacePos;
                arr.push_back(line.substr(prevPos, currPos - prevPos));
                currPos++;
                prevPos = currPos;
                k++;
            }
        }while( spacePos >= 0);

        arr.push_back(line.substr(prevPos,line.length()));
        return arr;
    }

    float lerp(float t, float a, float b) {
        return a + t * (b - a);
    }

    inline std::string printRect(const SDL_Rect r)
    {
        return "(x: " + std::to_string(r.x) + ", y: " + std::to_string(r.y) + ", w: " + std::to_string(r.w) + ", h: " + std::to_string(r.h) + ")";
    }

    /// <summary>
    /// Detect Collision AABB [GLB units in rects]
    /// </summary>
    /// <param name="t">Target who move to touch object</param>
    /// <param name="o">Static object in game</param>
    /// <returns>On detect returns MTV</returns>
    Vector2Int AABB(const SDL_Rect* t, const SDL_Rect* o)
    {
        //MTV (overlap) -> Penetretion Depth
        Vector2Int mtv(0, 0);
        Vector2Int proj, overlap;

        // test overlap in x axis
        proj.x = std::max(t->x + t->w, o->x + o->w) - std::min(t->x, o->x);
        if (proj.x < t->w + o->w)
        {
            overlap.x = t->w + o->w - proj.x;

            // test overlap in y axis
            proj.y = std::max(t->y + t->h, o->y + o->h) - std::min(t->y, o->y);
            if (proj.y < t->h + o->h)
            {
                //calculate mtv in y
                overlap.y = t->h + o->h - proj.y;
                //mtv.x = mtv.y = 0;

                //choose minimum overlap
                if (overlap.x < overlap.y)
                {
                    mtv.x = overlap.x * (t->x < o->x ? -1 : 1);
                }
                else
                {
                    mtv.y = overlap.y * (t->y < o->y ? -1 : 1);
                }
            }
        }


        return mtv;
    }
}

#endif