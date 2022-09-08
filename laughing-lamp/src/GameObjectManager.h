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

	/* Add new game object to pool */
	template<typename T> 
	void add(T* obj);

	void update();
	void events(SDL_Event* e);
	void draw();

private:
	std::vector<GameObject> pool; // All Gameobjects
	SDL_Renderer* render;

};

#endif
