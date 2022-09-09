#ifndef WALL_H
#define WALL_H

#include "GameObject.h"
#include "Vector2Int.h"
#include "MotionAnimation.h"
#include <iostream>

class Wall : public GameObject
{
public:
	explicit Wall(SDL_Renderer* r, int x, int y);
	~Wall();
	
	void loadTexture() override;
	void update() override;
	void events(SDL_Event* eve) override;
	void draw() override;

private:
	Vector2Int pos;
};

#endif

