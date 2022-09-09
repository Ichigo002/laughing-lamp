#ifndef GAME_OBJECT_MANAGER_H
#define GAME_OBJECT_MANAGER_H

#include "GameObject.h"
#include <SDL.h>
#include <vector>
#include <utility>

/* You can add only the objects which inherit from GameObject class */
/* Main Manager of Objects. */
class GameObjectManager
{
public:
	GameObjectManager(SDL_Renderer* r);
	~GameObjectManager();

	/* Add the new GameObject ot the pool */
	/* mArgs: Additional arguments for initialized object if it has anything*/
	template<class T, typename... TArgs>
	T& add(TArgs&&... mArgs);

	/* Update all objects */
	void update();
	/* Handle SDL events in all objects */
	void events(SDL_Event* e);
	/* Draw all objects */
	void draw();

	/* WARNING! */
	/* !!! This method delete and clean all current objects !!!*/
	/* WARNING! */
	void cleanPool();

private:

	std::vector<GameObject*> pool; // All Gameobjects
	SDL_Renderer* render;

};

#endif

template<class T, typename ...TArgs>
inline T& GameObjectManager::add(TArgs && ...mArgs)
{
	T* obj = new T(render, std::forward<TArgs>(mArgs)...);
	pool.emplace_back(obj);
	obj->loadTexture();

	return *obj;
}
