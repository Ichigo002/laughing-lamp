#include "DroppingSystem.h"
#include "../../utility/TextureManager.h"

DroppingSystem::DroppingSystem(Camera* c, Player* pl)
{
	destR = { 0,0,0,0 };
	this->c = c;
	this->pl = pl;
	drp.clear();
}

DroppingSystem::~DroppingSystem()
{
}

void DroppingSystem::drop(InventoryItemData* item)
{
	if (item == nullptr)
		return;

	DropItem* dip = new DropItem();
	dip->i = item;
	dip->p = getNewPosItem();

	int room = getFreeRoom();
	if (room == -1)
	{
		drp.push_back(dip);
		return;
	}
	drp[room] = dip;
}

InventoryItemData* DroppingSystem::pickUp(size_t which)
{
	return nullptr;
}

void DroppingSystem::update()
{
}

// TODO 2 Add rotating animation if dropped
void DroppingSystem::draw()
{
	for (auto& d : drp)
	{
		if (d == nullptr)
			continue;
		drawItem(d);
	}
}

// TODO 2 Make better setting position
Vector2Int DroppingSystem::getNewPosItem()
{
	Vector2Int npp = pl->getPos();
	npp += 20;
	return npp;
}

void DroppingSystem::drawItem(const DropItem* di)
{
	if (di->i->getItemTex() == nullptr)
	{
		di->i->__setTex(TextureManager::load(c, "items", di->i->getName() + ".png"));
		if (di->i->getItemTex() == nullptr)
		{
			std::cout << "DroppingSystem::drawItem(const DropItem* di): Couldn't load item texture from '" << DEF_PATH_TEX << "items/" << di->i->getName() << ".png' " << std::endl;
			return;
		}
	}

	destR.x = di->p.x;
	destR.y = di->p.y;
	destR.w = item_size.w * item_dropped_rsc;
	destR.h = item_size.h * item_dropped_rsc;

	c->drawDynamic(di->i->getItemTex(), NULL, &destR);
}

int DroppingSystem::getFreeRoom()
{
	for (int i = 0; i < drp.size(); i++)
	{
		if (drp[i] == nullptr)
			return i;
	}
	return -1;
}
