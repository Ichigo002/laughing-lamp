#include "DroppingSystem.h"
#include "../../utility/TextureManager.h"
#include <string>

DroppingSystem::DroppingSystem(Camera* c, Player* pl)
{
	destR = { 0,0,0,0 };
	this->c = c;
	this->pl = pl;
	drp.clear();

	font = new FontAsset(c, item_font_path, item_pt_font_size * item_dropped_rsc * 1.7, item_font_color, "1234567890");
	text = new TextAsset(font, false);
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

	int st = di->i->getSizeStack();
	if (st == 1)
		return;
	if (st < 10)
		destR.x += item_pt_font_size * item_dropped_rsc / 2;

	text->setStartingPos(destR.x + destR.w / 2 + item_dropped_no_offset.x, destR.y + destR.h / 2 + item_dropped_no_offset.y);
	text->setText(std::to_string(st));

	text->draw();
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
