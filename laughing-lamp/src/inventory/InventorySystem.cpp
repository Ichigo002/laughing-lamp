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

	current_item = nullptr;
}

InventorySystem::~InventorySystem()
{
	for (size_t i = 0; i < NO_FIELDS_Y; i++)
	{
		delete[] set[i];
	}
	delete[] set;
}

// TODO 2 Improve method for stacking the items in the future
bool InventorySystem::add(InventoryItemData* _new)
{
	PSlot freeslot = getFreeSlot();
	if (freeslot.isNeg())
	{
		return false;
	}
	else
	{
		set[freeslot.y][freeslot.x] = _new;
		return true;
	}
}

bool InventorySystem::del(std::string item_name, unsigned int amount)
{
	for (int y = NO_FIELDS_Y-1; y >= 0; y--)
	{
		for (int x = NO_FIELDS_X-1; x >= 0; x--) 
		{
			if (set[y][x] != nullptr && set[y][x]->getName() == item_name)
			{
				set[y][x] = nullptr;
				amount--;
			}
			if (amount <= 0)
				return true;
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

bool InventorySystem::drop(PSlot s, unsigned int amount)
{
	return false;
}

bool InventorySystem::drop(std::string item_name, unsigned int amount)
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

void InventorySystem::setCurrentSlot(PSlot slot)
{
	if (!validateSlot(slot))
		return;
	current_item = set[slot.y][slot.x];
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
				std::cout << "  [NULL]";
			}
			else
			{
				std::cout << "  ["<<set[y][x]->getName()<<"]";
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

bool InventorySystem::validateSlot(PSlot s)
{
	return s.x < NO_FIELDS_X&& s.y < NO_FIELDS_Y;
}
