#include "InventorySystem.h"
#include <iostream>

InventorySystem::InventorySystem()
{
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
}

InventorySystem::~InventorySystem()
{
	for (size_t i = 0; i < NO_FIELDS_Y; i++)
	{
		delete[] set[i];
	}
	delete[] set;
}

// TODO 5 make del method for stacking
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

bool InventorySystem::move(PSlot _old, PSlot _new)
{
	if (!validateSlot(_old) || !validateSlot(_new))
		return false;
	if (set[_old.y][_old.x] == nullptr || set[_new.y][_new.x] != nullptr)
		return false;
	set[_new.y][_new.x] = set[_old.y][_old.x];
	set[_old.y][_old.x] = nullptr;
}

bool InventorySystem::drop(PSlot s, int amount)
{
	return false;
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
			else if (set[y][x]->getName() == item_name && set[y][x]->isStackable() && !set[y][x]->isStackFull())
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
