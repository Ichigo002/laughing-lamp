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
}

Player::~Player()
{
	SDL_DestroyTexture(tex);
}

void Player::loadTexture()
{
	tex = TextureManager::load(render, "assets/player.png");
	srcR.w = 12;
	srcR.h = 32;
	srcR.x = 0;
	srcR.y = 0;

	destR.w = srcR.w * renderingScale;
	destR.h = srcR.h * renderingScale;
	destR.x = 100;
	destR.y = 150;
}

void Player::update()
{
	
}

void Player::events(SDL_Event* eve)
{
	if (KeyboardHandler::pressedKey(SDLK_w, eve)) { velocity.y = -1; }
	if (KeyboardHandler::releasedKey(SDLK_w, eve)) { velocity.y = 0; }

	if (KeyboardHandler::pressedKey(SDLK_s, eve)) { velocity.y = 1; }
	if (KeyboardHandler::releasedKey(SDLK_s, eve)) { velocity.y = 0; }

	if (KeyboardHandler::pressedKey(SDLK_a, eve)) { velocity.x = -1; }
	if (KeyboardHandler::releasedKey(SDLK_a, eve)) { velocity.x = 0; }

	if (KeyboardHandler::pressedKey(SDLK_d, eve)) { velocity.x = 1; }
	if (KeyboardHandler::releasedKey(SDLK_d, eve)) { velocity.x = 0; }


	destR.x += speed * velocity.x;
	destR.y += speed * velocity.y;
}

void Player::draw()
{
	SDL_RenderCopy(render, tex, &srcR, &destR);
}
