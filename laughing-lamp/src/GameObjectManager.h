#ifndef GAME_OBJECT_MANAGER_H
#define GAME_OBJECT_MANAGER_H

#include "GameObject.h"
#include <SDL.h>
#include <vector>
#include <bitset>
#include <boost/dynamic_bitset.hpp>
#include <utility>

constexpr size_t MAX_NUMBER_OBJECTS = 64;

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

	/* Erease all objects with the same tagnames */
	/* Returns the number of deleted objects */
	int eraseByTag(std::string tagname);

	/* Erase Object by unique ID of object. */
	/* You can get the unique ID by method GameObject::getUniqueID(); */
	void eraseObject(size_t uniq);

	/* Returns the number of all objects */
	size_t getSizePool();

	/* Check is the index empty */
	/* If index is out of range then returns false*/
	bool checkIndex(size_t id);
private:

	boost::dynamic_bitset<> dbit; // keep info is empty the vector index or not
	std::vector<GameObject*> pool; // All Gameobjects
	std::size_t lastID;
	SDL_Renderer* render;

};

#endif

template<class T, typename ...TArgs>
inline T& GameObjectManager::add(TArgs && ...mArgs)
{
	T* obj = new T(render, std::forward<TArgs>(mArgs)...);
	pool.emplace_back(obj);
	dbit.push_back(true);
	obj->__initUniq__(lastID);
	lastID++;

	obj->loadTexture();
	return *obj;
}
