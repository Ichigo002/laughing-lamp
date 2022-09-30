#include "BFun.h"
#include "../../utility/TextureManager.h"

BFun::BFun()
	:BBlock()
{
	name = "funny";
	category = "PLAY";
	render_scale = 2;

	canPlaceover = true;
	canCollide = true;
}

BFun::~BFun()
{
}

void BFun::loadTex(SDL_Renderer* r)
{
	tex = TextureManager::load(r, "assets/textures/build-blocks.png");
	srcR.x = 64;
	srcR.y = 0;
	srcR.w = 32;
	srcR.h = 32;

	destR.x = 0;
	destR.y = 0;
	colliderRect = destR;
}

void BFun::update()
{
}

void BFun::events(SDL_Event* eve)
{
}
