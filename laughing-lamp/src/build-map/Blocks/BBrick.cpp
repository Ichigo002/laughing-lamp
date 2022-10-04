#include "BBrick.h"
#include "../../utility/TextureManager.h"

BBrick::BBrick()
	:BBlock()
{
	name = "brick";
	category = "WALL";
	render_scale = 2;

	canPlaceover = true;
	canCollide = true;
}

BBrick::~BBrick()
{
}

void BBrick::loadTex(SDL_Renderer* r)
{
	tex = TextureManager::load(r, "blocks", "build-blocks.png");
	srcR.x = 0;
	srcR.y = 0;
	srcR.w = 32;
	srcR.h = 32;

	destR.w = srcR.w * render_scale;
	destR.h = srcR.h * render_scale;
	destR.x = 0;
	destR.y = 0;
	colliderRect = destR;
}

void BBrick::update()
{
}

void BBrick::events(SDL_Event* eve)
{
}
