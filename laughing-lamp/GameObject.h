#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SDL.h>

class GameObject
{
public:
	GameObject();
	~GameObject();

	virtual void initRenderer(SDL_Renderer* r);
	virtual void update();
	virtual void draw();

private:
	SDL_Renderer* render;

};

#endif
