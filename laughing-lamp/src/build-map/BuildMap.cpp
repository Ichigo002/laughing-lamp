#include "BuildMap.h"

BuildMap::BuildMap(Camera* c, GameObjectManager* gom)
{
	this->c = c;
	this->gom = gom;

	top_layer = 0;

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

	int tlayer = getTopLayerByLCL(_new->lcl);
	_new->layer = tlayer+1;

	if (tlayer != -1 && !item->attr(DT_PLACEOVERABLE))
		return -1;

	if (_new->layer > top_layer)
		top_layer = _new->layer;

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
	for (size_t i = 0; i < top_layer+1; i++)
	{
		for (auto& _block : map_block)
		{
			if (_block != nullptr && _block->layer == i)
				drawBlock(_block);
		}
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

int BuildMap::getTopLayerByLCL(Vector2Int lclp)
{
	int tl = -1;
	for (auto& _block : map_block)
	{
		if (_block->lcl == lclp && _block->layer > tl)
			tl = _block->layer;
	}
	return tl;
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

	destR.x = c->convertLCL_GLB(b->lcl).x;
	destR.y = c->convertLCL_GLB(b->lcl).y;

	if ((b->lcl.y+1) % 2 == 0)
	{
		destR.x += HEX_WIDTH / 2 * MAP_RENDER_SCALE;
	}

	c->drawDynamic(b->item->getItemTex(), NULL, &destR);
}
