#include "BWall.h"
#include "../../utility/TextureManager.h"

BWall::BWall()
	:BBlock()
{
	name = "wall";
	category = "WALL";
	render_scale = 1;
}

BWall::~BWall()
{
}

void BWall::loadTex(SDL_Renderer* r)
{
	tex = TextureManager::load(r, "assets/textures/wall.png");
	srcR.x = 0;
	srcR.y = 0;
	srcR.w = 32;
	srcR.h = 32;
	
	destR.w = srcR.w * render_scale;
	destR.h = srcR.h * render_scale;

	destR.x = 10;
	destR.y = 15;
}

void BWall::update()
{
}

void BWall::events(SDL_Event* eve)
{
}
