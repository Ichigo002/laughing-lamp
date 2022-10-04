#include "BWood.h"
#include "../../utility/TextureManager.h"

BWood::BWood()
	:BBlock()
{
	name = "wood";
	category = "WALL";
	render_scale = 2;

	canPlaceover = true;
	canCollide = true;
}

BWood::~BWood()
{
}

void BWood::loadTex(SDL_Renderer* r)
{
	tex = TextureManager::load(r, "blocks", "build-blocks.png");
	srcR.x = 32;
	srcR.y = 0;
	srcR.w = 32;
	srcR.h = 32;

	destR.w = srcR.w * render_scale;
	destR.h = srcR.h * render_scale;
	destR.x = 0;
	destR.y = 0;
	colliderRect = destR;
}

void BWood::update()
{
}

void BWood::events(SDL_Event* eve)
{
}
