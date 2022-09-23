#include "BCircle.h"
#include "../../utility/TextureManager.h"

BCircle::BCircle()
	:BBlock()
{
	name = "circle";
	category = "GEOMETRIC";
	render_scale = 1;

	canPlaceover = false;
	canCollide = true;
}

BCircle::~BCircle()
{
}

void BCircle::loadTex(SDL_Renderer* r)
{
	tex = TextureManager::load(r, "assets/textures/circle.png");
	srcR.x = 0;
	srcR.y = 0;
	srcR.w = 30;
	srcR.h = 30;

	destR.w = srcR.w * render_scale;
	destR.h = srcR.h * render_scale;

	destR.x = 14;
	destR.y = 16;
}

void BCircle::update()
{
}

void BCircle::events(SDL_Event* eve)
{
}
