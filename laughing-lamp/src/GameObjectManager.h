#ifndef GAME_OBJECT_MANAGER_H
#define GAME_OBJECT_MANAGER_H

#include "GameObject.h"
#include <SDL.h>
#include <vector>

class GameObjectManager
{
public:
	GameObjectManager(SDL_Renderer* r);
	~GameObjectManager();

	template<class T> void add();

	void update();
	void events(SDL_Event* e);
	void draw();

private:

	std::vector<GameObject*> pool; // All Gameobjects
	SDL_Renderer* render;

};

#endif

template<class T>
inline void GameObjectManager::add()
{
	T* obj = new T(render);
	pool.emplace_back(obj);
	obj->loadTexture();
}
