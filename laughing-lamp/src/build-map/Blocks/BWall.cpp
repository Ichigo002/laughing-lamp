#include "BWall.h"
#include "../../utility/TextureManager.h"

BWall::BWall()
	:BBlock()
{
	name = "Walle";
	category = "WALL";
}

BWall::~BWall()
{
}

void BWall::loadTex(SDL_Renderer* r)
{
	tex = TextureManager::load(r, "assets/textures/wall.png");
	srcR.x = 0;
	srcR.y = 0;
	srcR.w = destR.w = 32;
	srcR.h = destR.h = 32;

	destR.x = 0;
	destR.y = 0;
}

void BWall::update()
{
}

void BWall::events(SDL_Event* eve)
{
}
