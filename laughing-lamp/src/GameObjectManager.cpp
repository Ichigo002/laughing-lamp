#include "GameObjectManager.h"

GameObjectManager::GameObjectManager(SDL_Renderer* r)
{
	render = r;
	lastID = 0;
}

GameObjectManager::~GameObjectManager()
{
}

void GameObjectManager::update()
{
	for (auto& obj : pool)
	{
		if (obj != nullptr)
			obj->update();
	}
}

void GameObjectManager::events(SDL_Event* e)
{
	for (auto& obj : pool)
	{
		if(obj != nullptr)
			obj->events(e);
	}
}

void GameObjectManager::draw()
{
	for (auto& obj : pool)
	{
		if (obj != nullptr)
			obj->draw();
	}
}

void GameObjectManager::cleanPool()
{
	for (auto& obj : pool)
	{
		delete obj;
	}

	pool.clear();
}

int GameObjectManager::eraseAllBy(std::string tagname)
{
	int rmv = 0;
	for (auto& obj : pool)
	{
		if (obj == nullptr)
			break;
		if (obj->getTag() == tagname)
		{
			eraseObject(obj->getUniqueID());
			rmv++;
		}
	}
	return rmv;
}

void GameObjectManager::eraseObject(GameObject* obj)
{
	eraseObject(obj->getUniqueID());
}

void GameObjectManager::eraseObject(size_t uniq)
{
	for (size_t i = 0; i < pool.size(); i++)
	{
		if (pool[i] == nullptr)
			break;
		if (pool[i]->getUniqueID() == uniq)
		{
			pool[i] = nullptr;
			dbit.set(i, false);

			return;
		}
	}
}

size_t GameObjectManager::getSizePool()
{
	return dbit.count();
}

bool GameObjectManager::checkIndex(size_t id)
{
	return !(id > dbit.size()) && dbit[id] == true;
}
