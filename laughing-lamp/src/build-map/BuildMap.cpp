#include "BuildMap.h"
#include <iostream>

BuildMap::BuildMap(Camera* c)
{
	this->c = c;
	hexmode = true;
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
	std::vector<BPPointer*> exsptr = getBlockAt(pos);
	BBlock* tob = getBlockAt(id);

	// does player argument exist?
	if (tob == nullptr) return -1;
	// did it find any blocks?
	if (exsptr.size() != 0)
	{
		BBlock* exsb = exsptr.at(exsptr.size() - 1)->bb;

		// does player try place on block with no placeover?
		if (!exsb->get_canPlaceover())
		{
			if (debug_mode)
				std::cout << "BuildMap: Block '" << tob->getName() << "' at " << pos << " cannot be placed because There has already exist block.\n";
			return -2;
		}
		if (exsb == tob)
		{
			if (debug_mode)
				std::cout << "BuildMap: 2 identic blocks with name '" << tob->getName() << "' cannot be placed in the same position " << pos << std::endl;
			return -3;
		}
	}

	BPPointer p = { tob , pos };
	bmap.push_back(p);
	return 0;
	// TODO 1 check does place where you want put block is empty
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
	// TODO 1 remove method 
}

std::vector<BPPointer*> BuildMap::getBlockAt(Vector2Int pos)
{
	std::vector<BPPointer*> v;
	for (auto& bm : bmap)
	{
		if (bm.lcl == pos)
			v.push_back(&bm);
	}
	return v;
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
	// TODO 2 Collisions AABB as separated class
	// TODO 2 Detecting AABB between buildmap & game objects manager
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

		if (hexmode && (ptr.lcl.y + 1) % 2 == 0)
		{
			destR.x += HEX_WIDTH / 2 * MAP_RENDER_SCALE;
		}

		c->drawDynamic(ptr.bb->tex, &ptr.bb->srcR, &destR);
	}
}

void BuildMap::initBlocks()
{
	inb<BWall>();
	inb<BCircle>();
}
