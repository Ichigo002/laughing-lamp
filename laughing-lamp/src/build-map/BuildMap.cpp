#include "BuildMap.h"
#include "../utility/Utilities.h"
#include <iostream>

BuildMap::BuildMap(Camera* c, GameObjectManager* gom)
{
	this->gom = gom;
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

	// does player's argument exist?
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

	BPPointer* p = new BPPointer();
	p->bb = tob;
	p->lcl = pos;

	for (auto& b : bmap)
	{
		if (!b)
		{
			b = p;
			return 0;
		}
	}
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
	for (auto& b : bmap)
	{
		if (!b)
			continue;
		if (b->lcl == pos)
		{
			b = nullptr;
		}
	}
}

std::vector<BPPointer*> BuildMap::getBlockAt(Vector2Int pos)
{
	std::vector<BPPointer*> v;
	for (auto& bm : bmap)
	{
		if (!bm)
			continue;
		if (bm->lcl == pos)
			v.push_back(bm);
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
		if (!vblocks[i])
			continue;
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
	SDL_Rect block_col; // collider
	for (auto& obj : gom->getPool())
	{
		for (auto& ptr : bmap)
		{
			if (!ptr || !ptr->bb->get_canCollide())
				continue;
			block_col = ptr->bb->colliderRect;
			block_col.x = c->convertLCL_GLB(ptr->lcl).x + ptr->bb->destR.x;
			block_col.y = c->convertLCL_GLB(ptr->lcl).y + ptr->bb->destR.y;

			Vector2Int s = Util::AABB(obj->getCollider(), &block_col);
			if (obj->__lastpsh__.y != 0 || obj->__lastpsh__.x != 0)
			{
				obj->__lastpsh__.set(0, 0);
				continue;
			}
			// TODO 3 fix collision bug
			obj->addShift(s);
			obj->__lastpsh__ = s;
		}
	}
}

void BuildMap::events(SDL_Event* eve)
{
	if (placeByCursor)
	{
		if (eve->type == SDL_MOUSEBUTTONDOWN)
		{
			if (eve->button.button == 1)
			{
				if (amountPlacing != -1)
				{
					amountPlacing -= 1;
					if (amountPlacing == 0)
						placeByCursor = false;
				}
				put(Vector2Int(c->convertGLB_LCL(c->translateMouseToGLB())), indexCursorP);
			}
			if (eve->button.button == 3)
			{
				remove(c->convertGLB_LCL(c->translateMouseToGLB()));
			}
		}
	}
}

void BuildMap::draw()
{
	for (auto& ptr : bmap)
	{
		if (!ptr)
			continue;
		destR.w = ptr->bb->destR.w;
		destR.h = ptr->bb->destR.h;
		destR.x = c->convertLCL_GLB(ptr->lcl).x  + ptr->bb->destR.x;
		destR.y = c->convertLCL_GLB(ptr->lcl).y + ptr->bb->destR.y;

		if (hexmode && (ptr->lcl.y + 1) % 2 == 0)
		{
			destR.x += HEX_WIDTH / 2 * MAP_RENDER_SCALE;
		}

		c->drawDynamic(ptr->bb->tex, &ptr->bb->srcR, &destR);
	}
}

void BuildMap::initBlocks()
{
	inb<BWall>();
	inb<BCircle>();
}
