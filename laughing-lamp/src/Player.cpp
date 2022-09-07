#include "Player.h"
#include "TextureManager.h"
#include "KeyboardHandler.h"

Player::Player(SDL_Renderer* r)
	:GameObject(r)
{
	render = r;
	tagname = "Player";
	renderingScale = 2;
	speed = 3;

	velocity.x = velocity.y = 0;
	pos.x = 100;
	pos.y = 100;

	animation = new MotionAnimation(&srcR, 3, 200);
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
}

void Player::update()
{
	animation->update();

	destR.x = pos.x;
	destR.y = pos.y;
}

void Player::events(SDL_Event* eve)
{
	if (KeyboardHandler::pressedKey(SDLK_w, eve)) { velocity.y = -1; animation->start(); }
	if (KeyboardHandler::releasedKey(SDLK_w, eve)) { velocity.y = 0; }

	if (KeyboardHandler::pressedKey(SDLK_s, eve)) { velocity.y = 1; }
	if (KeyboardHandler::releasedKey(SDLK_s, eve)) { velocity.y = 0; }

	if (KeyboardHandler::pressedKey(SDLK_a, eve)) { velocity.x = -1; }
	if (KeyboardHandler::releasedKey(SDLK_a, eve)) { velocity.x = 0; }

	if (KeyboardHandler::pressedKey(SDLK_d, eve)) { velocity.x = 1; }
	if (KeyboardHandler::releasedKey(SDLK_d, eve)) { velocity.x = 0; }


	pos.x += speed * velocity.x;
	pos.y += speed * velocity.y;
}

void Player::draw()
{
	SDL_RenderCopy(render, tex, &srcR, &destR);
}
