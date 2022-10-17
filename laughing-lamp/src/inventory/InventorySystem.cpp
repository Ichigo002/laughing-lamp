#include "InventorySystem.h"
#include <iostream>

InventorySystem::InventorySystem(DroppingSystem* dropsys, BuildMap* buildmap)
{
	this->dropsys = dropsys;
	this->buildmap = buildmap;
	// New table
	set = new InventoryItemData ** [NO_FIELDS_Y];
	for (size_t i = 0; i < NO_FIELDS_Y; i++)
	{
		set[i] = new InventoryItemData * [NO_FIELDS_X];
	}
	// Set nullptrs
	for (size_t y = 0; y < NO_FIELDS_Y; y++)
	{
		for (size_t x = 0; x < NO_FIELDS_X; x++)
		{
			set[y][x] = nullptr;
		}
	}

	initItems();
}

void InventorySystem::initItems()
{
	mapitem.add<Item_BrickBlock>();
	mapitem.add<Item_Wood>();
}

InventorySystem::~InventorySystem()
{
	for (size_t i = 0; i < NO_FIELDS_Y; i++)
	{
		delete[] set[i];
	}
	delete[] set;
}

bool InventorySystem::add(std::string nameitem, int amount)
{
	InventoryItemData* _n = mapitem.make(nameitem);
	PSlot fs = getFreeStackSlot(_n->getName()); // free space
	if (fs.isNeg() || _n == nullptr)
		return false;

	if (set[fs.y][fs.x] == nullptr)
	{
		set[fs.y][fs.x] = _n;
		return add(nameitem, amount - 1);
	}

	int extant = set[fs.y][fs.x]->getExtantSpace();
	amount -= extant;

	if (amount > 0)
	{
		set[fs.y][fs.x]->addToStack(extant);
		return add(nameitem, amount);
	}
	else
	{
		set[fs.y][fs.x]->addToStack(amount + extant);
	}
	return true;
}

bool InventorySystem::add(InventoryItemData* item)
{
	if (item == nullptr)
		return false;
	return add(item->getName(), item->getSizeStack());
}

bool InventorySystem::del(std::string item_name, int amount)
{
	for (int y = NO_FIELDS_Y-1; y >= 0; y--)
	{
		for (int x = NO_FIELDS_X-1; x >= 0; x--) 
		{
			if (set[y][x] != nullptr && set[y][x]->getName() == item_name)
			{
				int dell = set[y][x]->getSizeStack();
				amount -= dell;
				if (amount > 0)
				{
					amount--;
					set[y][x] = nullptr;
					if (amount > 0)
						amount++;
					else
						return true;
				}
				else
				{
					if (amount == 0)
						set[y][x] = nullptr;
					else
						set[y][x]->removeFromStack(amount + dell);
					return true;
				}
				
			}
		}
	}
	return false;
}

bool InventorySystem::move_direct(PSlot _old, PSlot _new)
{
	if (!validateSlot(_old) || !validateSlot(_new))
		return false;
	if (set[_old.y][_old.x] == nullptr || set[_new.y][_new.x] != nullptr)
		return false;
	set[_new.y][_new.x] = set[_old.y][_old.x];
	set[_old.y][_old.x] = nullptr;
}

void InventorySystem::move_init(PSlot f, int amount)
{
	if (mov_item != nullptr)
		return;

	if (!(validateSlot(f)) || (set[f.y][f.x] == nullptr))
		return;

	mov_old_slot = f;
	if (amount <= 0)
	{
		mov_item = set[f.y][f.x];
		set[f.y][f.x] = nullptr;
		return;
	}
	else
	{
		InventoryItemData* d = new InventoryItemData(*set[f.y][f.x]);
		mov_item = d;
		mov_item->removeAllFromStack();
		mov_item->addToStack(amount-1);

		if (set[f.y][f.x]->getSizeStack() == amount)
			set[f.y][f.x] = nullptr;
		else
			set[f.y][f.x]->removeFromStack(amount);
	}
}

void InventorySystem::move_exec(PSlot dest)
{
	if (mov_item == nullptr || !validateSlot(dest))
		return;

	if (set[dest.y][dest.x] == nullptr)
	{
		set[dest.y][dest.x] = mov_item;
		mov_item = nullptr;
	}
	else if (set[dest.y][dest.x]->getName() == mov_item->getName())
	{
		int s = set[dest.y][dest.x]->getSizeStack();
		int mxs = set[dest.y][dest.x]->getMaxSizeStack()+1;
		if (s == mxs)
			return;

		int rt = set[dest.y][dest.x]->addToStack(mov_item->getSizeStack());
		if(rt > 0)
		{
			mov_item->removeFromStack(mxs - s);
			return;
		}
		mov_item = nullptr;
	}
}

void InventorySystem::move_cancel()
{
	if (set[mov_old_slot.y][mov_old_slot.x] == nullptr)
	{
		set[mov_old_slot.y][mov_old_slot.x] = mov_item;
	}
	else
	{
		set[mov_old_slot.y][mov_old_slot.x]->addToStack(mov_item->getSizeStack());
	}
	mov_item = nullptr;
}

bool InventorySystem::move_ready()
{
	return mov_item != nullptr;
}

void InventorySystem::move_reset()
{
	mov_item = nullptr;
}

InventoryItemData* InventorySystem::move_getItem()
{
	return mov_item;
}

bool InventorySystem::drop(PSlot s, int amount)
{
	if (!validateSlot(s) || set[s.y][s.x] == nullptr || !set[s.y][s.x]->attr(DT_DROPABLE))
		return false;

	if (amount < 0 || set[s.y][s.x]->getSizeStack()-1 < amount)
	{
		dropsys->drop(set[s.y][s.x]);
		set[s.y][s.x] = nullptr;
		return true;
	}
	else
	{
		InventoryItemData* it = new InventoryItemData(*set[s.y][s.x]);
		set[s.y][s.x]->removeFromStack(amount);
		it->removeAllFromStack();
		it->addToStack(amount-1);
		dropsys->drop(it);
	}
}

int InventorySystem::placeFocusedItem()
{
	return buildmap->settleCursor(set[current_item_slot.y][current_item_slot.x]);
}

DroppingSystem* InventorySystem::getDroppingSystem()
{
	return dropsys;
}

void InventorySystem::update()
{
	if (InventoryItemData* iid = dropsys->tryPickUp(); iid != nullptr)
	{
		add(iid);
	}
}

bool InventorySystem::checkFull()
{
	return getFreeSlot().isNeg();
}

InventoryItemData* InventorySystem::getItem(PSlot s)
{
	if (!validateSlot(s))
		return nullptr;
	return set[s.y][s.x];
}

InventoryItemData*** InventorySystem::getSet()
{
	return set;
}

bool InventorySystem::contains(std::string item_name, int amount)
{
	return count(item_name) >= amount;
}

int InventorySystem::count(std::string item_name)
{
	int c = 0;
	for (size_t y = 0; y < NO_FIELDS_Y; y++)
	{
		for (size_t x = 0; x < NO_FIELDS_X; x++)
		{
			if (set[y][x] != nullptr && set[y][x]->getName() == item_name)
				c++;
		}
	}
	return c;
}

void InventorySystem::setCurrentSlot(PSlot slot)
{
	if (!validateSlot(slot))
		return;
	current_item_slot = slot;
}

InventoryItemData* InventorySystem::getCurrentItem()
{
	return set[current_item_slot.y][current_item_slot.x];
}

void InventorySystem::printCMD()
{
	std::cout << "Inventory with size of set["<<NO_FIELDS_Y<<"]["<<NO_FIELDS_X<<"]:\n";
	for (size_t y = 0; y < NO_FIELDS_Y; y++)
	{
		std::cout << y << ".";
		for (size_t x = 0; x < NO_FIELDS_X; x++)
		{
			if (set[y][x] == nullptr)
			{
				std::cout << "  [0x NULL]";
			}
			else
			{
				std::cout << "  ["<<set[y][x]->getSizeStack()<<"x "<<set[y][x]->getName()<<"]";
			}
		}
		std::cout << std::endl;
	}
}

PSlot InventorySystem::getFreeSlot()
{
	for (size_t y = 0; y < NO_FIELDS_Y; y++)
	{
		for (size_t x = 0; x < NO_FIELDS_X; x++)
		{
			if (set[y][x] == nullptr)
			{
				return PSlot(x, y);
			}
		}
	}
	return PSlot().setNeg();
}

PSlot InventorySystem::getFreeStackSlot(std::string item_name)
{
	PSlot nullspace;
	nullspace.setNeg();

	for (size_t y = 0; y < NO_FIELDS_Y; y++)
	{
		for (size_t x = 0; x < NO_FIELDS_X; x++)
		{
			if (set[y][x] == nullptr)
			{
				if (nullspace.isNeg())
				{
					nullspace.x = x;
					nullspace.y = y;
					nullspace.unsetNeg();
				}
			}
			else if (set[y][x]->getName() == item_name && set[y][x]->attr(DT_STACKABLE) && !set[y][x]->isStackFull())
			{
				return PSlot(x, y);
			}
		}
	}
	return nullspace;
}

bool InventorySystem::validateSlot(PSlot s)
{
	return s.x < NO_FIELDS_X&& s.y < NO_FIELDS_Y;
}
