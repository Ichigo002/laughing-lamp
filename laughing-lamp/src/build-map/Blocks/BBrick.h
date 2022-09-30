#ifndef BBRICK_H
#define BBRICK_H

#include "../../utility/Vector2Int.h"
#include <SDL.h>
#include "BBlock.h"

class BBrick : public BBlock
{
public:
	BBrick();
	~BBrick();

	/* Load textures */
	virtual void loadTex(SDL_Renderer* r);

	/* Method called every time. You can put there different move algorithms etc.*/
	virtual void update();

	/*Handle all events for this object*/
	virtual void events(SDL_Event* eve);
};

#endif