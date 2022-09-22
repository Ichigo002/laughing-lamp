#include "BuildMap.h"
#include <iostream>

BuildMap::BuildMap(Camera* c)
{
	this->c = c;
	initBlocks();

	for (auto& b : vblocks)
	{
		b->loadTex(c->getRender());
	}
}

BuildMap::~BuildMap()
{
	for (auto& b : vblocks)
	{
		delete b;
	}
	vblocks.clear();
	bmap.clear();
}

int BuildMap::put(Vector2Int pos, std::string block_name)
{
	return put(pos, findIndexBy(block_name));
}

int BuildMap::put(Vector2Int pos, size_t id)
{
	BBlock* bb = getBlockAt(id);
	if (bb == nullptr) return -1;
	BPPointer p = { bb , pos };
	bmap.push_back(p);
	return 0;
}

void BuildMap::enableCursorPlacing(std::string block_name, int amount)
{
	placeByCursor = true;
	amountPlacing = amount;
	indexCursorP = findIndexBy(block_name);
	if (indexCursorP == size_t())
		indexCursorP = 0;
}

void BuildMap::disableCursorPlacing()
{
	placeByCursor = false;
}

void BuildMap::remove(Vector2Int pos)
{
	// TO DO
}

BBlock* BuildMap::getBlockAt(Vector2Int pos)
{
	for (auto& bm : bmap)
	{
		if (bm.lcl == pos)
			return bm.bb;
	}
	return nullptr;
}

BBlock* BuildMap::getBlockAt(size_t index)
{
	if (verifyIndex(index))
	{
		return vblocks[index];
	}
	return nullptr;
}

BBlock* BuildMap::getBlockAt(std::string name)
{
	return getBlockAt(findIndexBy(name));
}

size_t BuildMap::findIndexBy(std::string block_name)
{
	for (size_t i = 0; i < vblocks.size(); i++)
	{
		if (vblocks.at(i)->getName() == block_name)
			return i;
	}
	return size_t();
}

inline bool BuildMap::verifyIndex(size_t index)
{
	return index < vblocks.size() && index >= 0;
}

void BuildMap::update()
{

}

void BuildMap::events(SDL_Event* eve)
{
	if (placeByCursor)
	{
		if (eve->type == SDL_MOUSEBUTTONDOWN && eve->button.button == 1)
		{
			if (amountPlacing != -1)
			{
				amountPlacing -= 1;
				if (amountPlacing == 0)
					placeByCursor = false;
			}
			put(Vector2Int(c->convertGLB_LCL(c->translateMouseToGLB())), indexCursorP);
			
		}
	}
}

void BuildMap::draw()
{
	for (auto& ptr : bmap)
	{
		destR.w = ptr.bb->destR.w;
		destR.h = ptr.bb->destR.h;
		destR.x = ptr.lcl.x * (HEX_WIDTH * MAP_RENDER_SCALE) + ptr.bb->destR.x;
		destR.y = ptr.lcl.y * (HEX_HEIGHT * MAP_RENDER_SCALE * RATIOHEX_H) + ptr.bb->destR.y;

		if ((ptr.lcl.y + 1) % 2 == 0)
		{
			destR.x += HEX_WIDTH / 2 * MAP_RENDER_SCALE;
		}

		c->drawDynamic(ptr.bb->tex, &ptr.bb->srcR, &destR);
	}
}

void BuildMap::initBlocks()
{
	//inb<BWall>();
	BWall* w = new BWall();
	vblocks.push_back(w);
}
