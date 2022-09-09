#include "GameObjectManager.h"

GameObjectManager::GameObjectManager(SDL_Renderer* r)
{
	render = r;
}

GameObjectManager::~GameObjectManager()
{
}

void GameObjectManager::update()
{
	for (auto& obj : pool)
	{
		obj->update();
	}
}

void GameObjectManager::events(SDL_Event* e)
{
	for (auto& obj : pool)
	{
		obj->events(e);
	}
}

void GameObjectManager::draw()
{
	for (auto& obj : pool)
	{
		obj->draw();
	}
}
