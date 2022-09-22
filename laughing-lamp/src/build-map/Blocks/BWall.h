#ifndef BWALL_H
#define BWALL_H

#include "../../utility/Vector2Int.h"
#include <SDL.h>
#include "BBlock.h"

class BWall : public BBlock
{
public:
	BWall();
	~BWall();

	/* Load textures */
	virtual void loadTex(SDL_Renderer* r);

	/* Method called every time. You can put there different move algorithms etc.*/
	virtual void update();

	/*Handle all events for this object*/
	virtual void events(SDL_Event* eve);
};

#endif