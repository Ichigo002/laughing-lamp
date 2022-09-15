#include "GameObjectManager.h"

GameObjectManager::GameObjectManager(SDL_Renderer* r, Camera* cam)
{
	render = r;
	camera = cam;
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

int GameObjectManager::eraseByTag(std::string tagname)
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

void GameObjectManager::eraseObject(size_t uniq)
{
	for (size_t i = 0; i < dbit.size(); i++)
	{
		if (dbit[i] == true)
		{
			if (pool[i]->getUniqueID() == uniq)
			{
				dbit[i] = false;
				pool[i] = nullptr;

			}
		}
	}
}

GameObject* GameObjectManager::getObject(std::string tagname)
{
	for (auto& obj : pool)
	{
		if (obj->getTag() == tagname)
			return obj;
	}
	return nullptr;
}

std::vector<GameObject*> GameObjectManager::GetObjects(std::string tagname)
{
	std::vector<GameObject*> v;

	for (auto& obj : pool)
	{
		if (obj->getTag() == tagname)
			v.push_back(obj);
	}

	return v;
}

GameObject* GameObjectManager::getObject(size_t uniq)
{
	for (auto& obj : pool)
	{
		if (obj->getUniqueID() == uniq)
			return obj;
	}
	return nullptr;
}

size_t GameObjectManager::getSizePool()
{
	return dbit.count();
}

size_t GameObjectManager::getEmptyIndex()
{
	for (size_t i = 0; i < dbit.size(); i++)
	{
		if (dbit[i] == false)
			return i;
	}
	return dbit.size() + 1;
}
