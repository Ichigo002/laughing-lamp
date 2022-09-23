#ifndef BCIRCLE_H
#define BCIRCLE_H

#include <SDL.h>
#include "BBlock.h"

class BCircle : public BBlock
{
public:
	BCircle();
	~BCircle();

	/* Load textures */
	virtual void loadTex(SDL_Renderer* r);

	/* Method called every time. You can put there different move algorithms etc.*/
	virtual void update();

	/*Handle all events for this object*/
	virtual void events(SDL_Event* eve);
};

#endif