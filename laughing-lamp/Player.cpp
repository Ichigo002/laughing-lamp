#include "Player.h"
#include "src/TextureManager.h"

Player::Player()
{
	tagname = "Player";
}

Player::~Player()
{
}

void Player::initRenderer(SDL_Renderer* r)
{
	render = r;
}

void Player::update()
{

}

void Player::draw()
{
	SDL_RenderCopy(render, tex, &srcR, &destR);
}
