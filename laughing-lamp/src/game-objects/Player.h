#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "../utility/Vector2Int.h"
#include "../animations/MotionAnimation.h"
#include "../utility/Camera.h"
#include <iostream>

class Player : public GameObject
{
public:
	explicit Player(SDL_Renderer* r, Camera* cam);
	~Player();
	
	void loadTexture() override;
	void update() override;
	void events(SDL_Event* eve) override;
	void draw() override;

private:
	void idleAnimation();

	MotionAnimation* animation;
	Vector2Int velocity;
	Vector2Int pos;
	float speed;
};

#endif

