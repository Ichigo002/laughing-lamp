#include "Player.h"
#include "TextureManager.h"

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
	if (eve->type == SDL_KEYDOWN)
	{
		switch (eve->key.keysym.sym)
		{
		case SDLK_w:
			velocity.y = -1;
			break;
		case SDLK_s:
			velocity.y = 1;
			break;
		case SDLK_a:
			velocity.x = -1;
			break;
		case SDLK_d:
			velocity.x = 1;
			break;
		}
	}

	if (eve->type == SDL_KEYUP)
	{
		switch (eve->key.keysym.sym)
		{
		case SDLK_w:
			velocity.y = 0;
			break;
		case SDLK_s:
			velocity.y = 0;
			break;
		case SDLK_a:
			velocity.x = 0;
			break;
		case SDLK_d:
			velocity.x = 0;
			break;
		}
	}

	destR.x += speed * velocity.x;
	destR.y += speed * velocity.y;
}

void Player::draw()
{
	SDL_RenderCopy(render, tex, &srcR, &destR);
}
