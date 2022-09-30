#ifndef BWOOD_H
#define BWOOD_H

#include "../../utility/Vector2Int.h"
#include <SDL.h>
#include "BBlock.h"

class BWood : public BBlock
{
public:
	BWood();
	~BWood();

	/* Load textures */
	virtual void loadTex(SDL_Renderer* r);

	/* Method called every time. You can put there different move algorithms etc.*/
	virtual void update();

	/*Handle all events for this object*/
	virtual void events(SDL_Event* eve);
};

#endif