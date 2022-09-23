#include "Player.h"
#include "../utility/TextureManager.h"
#include "../utility/KeyboardHandler.h"

Player::Player(Camera* cam)
	:GameObject(cam)
{
	tagname = "Player";
	renderingScale = 3;

	std_speed = 5;
	ctrl_speed = 10;

	setPos(Vector2Int(0,0));
	cam->set(0, 0);

	velocity.x = velocity.y = 0;
	animation = new MotionAnimation(&srcR, 3, 200);
	_spd = std_speed;

	animation->setFrames(2);
	animation->setDelays(600);
	animation->start(0, 0);
}

Player::~Player()
{
	SDL_DestroyTexture(tex);
}

void Player::loadTexture()
{
	tex = TextureManager::load(camera->getRender(), "assets/textures/geralt.png");
	srcR.w = 24;
	srcR.h = 48;
	srcR.x = 0;
	srcR.y = 0;

	destR.w = srcR.w * renderingScale;
	destR.h = srcR.h * renderingScale;
}

void Player::update()
{
	animation->update();
	destR.x = pos.x;
	destR.y = pos.y;
	colliderRect = destR;

	camera->set(destR.x + destR.w / 2, destR.y + destR.h / 2);
}

void Player::events(SDL_Event* eve)
{
	// W
	if (KeyboardHandler::pressedKey(SDLK_w, eve)) velocity.y = -1;  
	if (KeyboardHandler::releasedKey(SDLK_w, eve))
	{
		velocity.y = 0;
		animation->setFrames(2);
		animation->setDelays(600);
		animation->start(2, 2);
	}
	// S
	if (KeyboardHandler::pressedKey(SDLK_s, eve)) velocity.y = 1;
	if (KeyboardHandler::releasedKey(SDLK_s, eve))
	{
		velocity.y = 0;
		animation->setFrames(2);
		animation->setDelays(600);
		animation->start(0, 0);
	}
	// A
	if (KeyboardHandler::pressedKey(SDLK_a, eve)) velocity.x = -1;
	if (KeyboardHandler::releasedKey(SDLK_a, eve))
	{
		velocity.x = 0;
		animation->setFrames(2);
		animation->setDelays(600);
		animation->start(2, 4);
	}
	// D
	if (KeyboardHandler::pressedKey(SDLK_d, eve)) velocity.x = 1;
	if (KeyboardHandler::releasedKey(SDLK_d, eve))
	{
		velocity.x = 0;
		animation->setFrames(2);
		animation->setDelays(600);
		animation->start(1, 4);
	}
	//Ctrl
	if (KeyboardHandler::pressedKey(SDLK_LCTRL, eve)) _spd = ctrl_speed;

	//releases
	if (KeyboardHandler::releasedKey(SDLK_LCTRL, eve)) _spd = std_speed;

	// ANIMATION PLAYING
	if (velocity.y > 0) // down
	{
		animation->setFrames(2);
		animation->setDelays(150);
		animation->start(0, 3);
	}
	if (velocity.y < 0) // top
	{
		animation->setFrames(2);
		animation->setDelays(200);
		animation->start(2, 0);
	}
	if (velocity.x > 0) // right
	{
		animation->setFrames(2);
		animation->setDelays(150);
		animation->start(1, 0);
	}
	if (velocity.x < 0) // left
	{
		 animation->setFrames(2);
		animation->setDelays(150);
		animation->start(1, 2);
	}

	pos.x += _spd * velocity.x;
	pos.y += _spd * velocity.y;
}

void Player::draw()
{
	camera->drawDynamic(tex, &srcR, &destR);
}
