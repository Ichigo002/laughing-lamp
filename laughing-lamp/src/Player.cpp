#include "Player.h"
#include "TextureManager.h"
#include "KeyboardHandler.h"

Player::Player(SDL_Renderer* r, Camera* cam)
	:GameObject(r, cam)
{
	tagname = "Player";
	renderingScale = 2;
	speed = 5;

	velocity.x = velocity.y = 0;
	pos.x = cam->getWHScreen().x / 2;
	pos.y = cam->getWHScreen().y / 2;
	animation = new MotionAnimation(&srcR, 3, 200);
	idleAnimation();
}

Player::~Player()
{
	SDL_DestroyTexture(tex);
}

void Player::loadTexture()
{
	tex = TextureManager::load(render, "assets/player-animation.png");
	srcR.w = 41;
	srcR.h = 55;
	srcR.x = 0;
	srcR.y = 0;

	destR.w = srcR.w * renderingScale;
	destR.h = srcR.h * renderingScale;
	destR.x = pos.x;
	destR.y = pos.y;
}

void Player::update()
{
	animation->update();
	//std::cout << "Player pos: " << pos << std::endl;
	camera->set(pos);
}

void Player::events(SDL_Event* eve)
{
	// W
	if (KeyboardHandler::pressedKey(SDLK_w, eve)) 
	{ 
		velocity.y = -1; 
		animation->setDelays(200);
		animation->start(1,0); 
	}
	if (KeyboardHandler::releasedKey(SDLK_w, eve)) 
	{ 
		velocity.y = 0;
		idleAnimation();
	}
	// S
	if (KeyboardHandler::pressedKey(SDLK_s, eve)) 
	{ 
		velocity.y = 1;
		animation->setDelays(150);
		animation->start(0, 0); 
	}
	if (KeyboardHandler::releasedKey(SDLK_s, eve)) 
	{
		velocity.y = 0;
		idleAnimation();
	}
	// A
	if (KeyboardHandler::pressedKey(SDLK_a, eve)) 
	{ 
		velocity.x = -1;
		animation->setDelays(150);
		animation->start(2, 0);
	}
	if (KeyboardHandler::releasedKey(SDLK_a, eve)) 
	{ 
		velocity.x = 0;
		idleAnimation();
	}
	// D
	if (KeyboardHandler::pressedKey(SDLK_d, eve)) 
	{ 
		velocity.x = 1;
		animation->setDelays(150);
		animation->start(3, 0);
	}
	if (KeyboardHandler::releasedKey(SDLK_d, eve)) 
	{
		velocity.x = 0;
		idleAnimation();
	}


	pos.x += speed * velocity.x;
	pos.y += speed * velocity.y;
}

void Player::idleAnimation()
{
	animation->setDelays(600);
	animation->start(4, 0);
}

void Player::draw()
{
	SDL_RenderCopy(render, tex, &srcR, &destR);
}
