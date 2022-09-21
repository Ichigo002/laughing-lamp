#include "Player.h"
#include "../utility/TextureManager.h"
#include "../utility/KeyboardHandler.h"

Player::Player(Camera* cam)
	:GameObject(cam)
{
	tagname = "Player";
	renderingScale = 2;

	std_speed = 5;
	ctrl_speed = 10;

	setPos(1000, 500);

	velocity.x = velocity.y = 0;
	animation = new MotionAnimation(&srcR, 3, 200);
	_spd = std_speed;
}

Player::~Player()
{
	SDL_DestroyTexture(tex);
}

void Player::loadTexture()
{
	tex = TextureManager::load(camera->getRender(), "assets/textures/player.png");
	srcR.w = 41;
	srcR.h = 55;
	srcR.x = 0;
	srcR.y = 0;

	destR.w = srcR.w * renderingScale;
	destR.h = srcR.h * renderingScale;
	destR.x = camera->getWHScreen().x / 2;
	destR.y = camera->getWHScreen().y / 2;
}

void Player::update()
{
	animation->update();
	camera->move(pos);
}

void Player::events(SDL_Event* eve)
{
	// W
	if (KeyboardHandler::pressedKey(SDLK_w, eve)) velocity.y = -1;  
	// S
	if (KeyboardHandler::pressedKey(SDLK_s, eve)) velocity.y = 1;
	// A
	if (KeyboardHandler::pressedKey(SDLK_a, eve)) velocity.x = -1;
	// D
	if (KeyboardHandler::pressedKey(SDLK_d, eve)) velocity.x = 1;
	//Ctrl
	if (KeyboardHandler::pressedKey(SDLK_LCTRL, eve)) _spd = ctrl_speed;

	//releases
	if (KeyboardHandler::releasedKey(SDLK_LCTRL, eve)) _spd = std_speed;
	if (KeyboardHandler::releasedKey(SDLK_w, eve) || KeyboardHandler::releasedKey(SDLK_s, eve)) velocity.y = 0;
	if (KeyboardHandler::releasedKey(SDLK_a, eve) || KeyboardHandler::releasedKey(SDLK_d, eve)) velocity.x = 0;

	// ANIMATION PLAYING
	if (velocity.y > 0)
	{
		animation->setDelays(150);
		animation->start(0, 0);
	}
	if (velocity.y < 0)
	{
		animation->setDelays(200);
		animation->start(1, 0);
	}
	if (velocity.x > 0)
	{
		animation->setDelays(150);
		animation->start(3, 0);
	}
	if (velocity.x < 0)
	{
		animation->setDelays(150);
		animation->start(2, 0);
	}
	if (velocity.x == 0 && velocity.y == 0)
	{
		animation->setDelays(600);
		animation->start(4, 0);
	}

	pos.x = _spd * velocity.x;
	pos.y = _spd * velocity.y;
}

void Player::draw()
{
	camera->drawStatic(tex, &srcR, &destR);
}

void Player::setPos(Vector2Int pos)
{
	camera->set(pos.x, pos.y);
}

void Player::setPos(int x, int y)
{
	setPos(Vector2Int(x, y));
}
