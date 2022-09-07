#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "Vector2Int.h"
#include <iostream>

class Player : public GameObject
{
public:
	explicit Player(SDL_Renderer* r);
	~Player();
	
	void loadTexture() override;
	void update() override;
	void events(SDL_Event* eve) override;
	void draw() override;

private:
	Vector2Int velocity;
	Vector2Int pos;
	float speed;
};

#endif

