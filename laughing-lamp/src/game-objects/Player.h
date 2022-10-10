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
	Player(Camera* cam);
	~Player();
	
	virtual void loadTexture();
	virtual void update();
	virtual void events(SDL_Event* eve);
	virtual void draw();

	/// <summary>
	/// Returns direction:
	/// pos x = right;
	/// neg x = left;
	/// pos y = bottom;
	/// neg y = top;
	/// </summary>	
	Vector2Int getDir();

	bool isMoving();

private:
	/// <summary>
	/// Resets the direction to 0
	/// </summary>
	void resetDir();

	MotionAnimation* animation;
	Vector2Int velocity;

	/// <summary>
	/// pos x = right;
	/// neg x = left;
	/// pos y = bottom;
	/// neg y = top;
	/// </summary>
	Vector2Int dir;

	float _spd;
	float std_speed;
	float ctrl_speed;
};

#endif

