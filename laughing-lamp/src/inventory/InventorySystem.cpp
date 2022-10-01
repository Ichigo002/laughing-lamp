#include "InventorySystem.h"

InventorySystem::InventorySystem()
{
	
}

bool InventorySystem::add(InventoryItemData* _new)
{
	return false;
}

bool InventorySystem::del(std::string item_name, unsigned int amount)
{
	return false;
}

bool InventorySystem::move(PSlot _old, PSlot _new)
{
	return false;
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
	return false;
}

InventoryItemData* InventorySystem::getItem(PSlot s)
{
	return nullptr;
}

void InventorySystem::setCurrentSlot(PSlot slot)
{
}

void InventorySystem::printCMD()
{
}

PSlot InventorySystem::getFreeSlot()
{
	return PSlot();
}

bool InventorySystem::validateSlot(PSlot s)
{
	return false;
}

void InventorySystem::createTable()
{
}
