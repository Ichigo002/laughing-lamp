#include "BuildMap.h"

BuildMap::BuildMap(Camera* c, GameObjectManager* gom)
{
	this->c = c;
	this->gom = gom;

	destR.w = HEX_WIDTH * MAP_RENDER_SCALE;
	destR.h = HEX_HEIGHT * MAP_RENDER_SCALE;
}

BuildMap::~BuildMap()
{
}

int BuildMap::settleCursor(InventoryItemData* item)
{
	if (item == nullptr)
		return -2;
	if (!item->attr(DT_BUILDABLE))
		return -1;

	Block* _new = new Block();
	_new->item = item;
	_new->lcl = c->convertGLB_LCL(c->translateMouseToGLB());

	pushBlock(_new);

	return 0;
}

InventoryItemData* BuildMap::unsettleCursor()
{
	return nullptr;
}

void BuildMap::fixedUpdate()
{
}

void BuildMap::draw()
{
	for (auto& _blocks : map_block)
	{
		if (_blocks != nullptr)
			drawBlock(_blocks);
	}
}

void BuildMap::pushBlock(Block* b)
{
	if (b == nullptr)
		return;
	for(auto& _block : map_block)
	{
		if (_block == nullptr)
		{
			_block == b;
			return;
		}
	}
	map_block.push_back(b);
}

Block* BuildMap::popBlockByLCL(Vector2Int lclp)
{
	for (auto& _block : map_block)
	{
		if (_block->lcl == lclp)
		{
			Block* tmp_b = _block;
			_block = nullptr;
			return tmp_b;
		}
	}
	return nullptr;
}

void BuildMap::drawBlock(Block* b)
{
	b->item->_initTex(c);

	destR.x = HEX_WIDTH * MAP_RENDER_SCALE + c->convertLCL_GLB(b->lcl).x;
	destR.y = HEX_HEIGHT * RATIOHEX_H * MAP_RENDER_SCALE + c->convertLCL_GLB(b->lcl).y;

	//if (destR.y % destR.y - b->lcl.y == 0)
	//{
	//	destR.x += HEX_WIDTH / 2 * MAP_RENDER_SCALE;
	//}

	c->drawDynamic(b->item->getItemTex(), NULL, &destR);
}
