#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include <iostream>

class Player : public GameObject
{
public:
	Player();
	~Player();
	
	void initRenderer(SDL_Renderer* r) override;
	void update() override;
	void draw() override;

private:

};

#endif // !PLAYER_H

