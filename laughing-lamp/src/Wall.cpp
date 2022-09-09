#include "Wall.h"
#include "TextureManager.h"
#include "KeyboardHandler.h"

Wall::Wall(SDL_Renderer* r, int x, int y)
	:GameObject(r)
{
	tagname = "Wall";
	renderingScale = 2;
	pos.x = x;
	pos.y = y;
}

Wall::~Wall()
{
	SDL_DestroyTexture(tex);
}

void Wall::loadTexture()
{
	tex = TextureManager::load(render, "assets/wall.png");
	srcR.w = 32;
	srcR.h = 32;
	srcR.x = 0;
	srcR.y = 0;

	destR.w = srcR.w * renderingScale;
	destR.h = srcR.h * renderingScale;
}

void Wall::update()
{
	destR.x = pos.x;
	destR.y = pos.y;
}

void Wall::events(SDL_Event* eve)
{
}

void Wall::draw()
{
	SDL_RenderCopy(render, tex, &srcR, &destR);
}
