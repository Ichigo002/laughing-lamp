#ifndef GAME_OBJECT_MANAGER_H
#define GAME_OBJECT_MANAGER_H

#include "GameObject.h"
#include "../utility/Camera.h"
#include <SDL.h>
#include <vector>
#include <bitset>
#include <boost/dynamic_bitset.hpp>
#include <utility>

constexpr size_t MAX_NUMBER_OBJECTS = 32;

/* You can add only the objects which inherit from GameObject class */
/* Main Manager of Objects. */
class GameObjectManager
{
public:
	GameObjectManager(SDL_Renderer* r, Camera* cam);
	~GameObjectManager();

	/* Add the new GameObject to the pool */
	/* mArgs: Additional arguments for initialized object if it has anything*/
	template<class T, typename... TArgs>
	T* add(TArgs&&... mArgs);

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

	GameObject* getObject(std::string tagname); // return first found or nullptr if not found
	std::vector<GameObject*> GetObjects(std::string tagname); // return the vector of objects
	GameObject* getObject(size_t uniq); // return the obejct or nullptr if not found

	// TODO 1: make method to get all array pointer
private:
	/* Returns the number of all objects */
	size_t getSizePool();

	/* Returns empty index for object */
	/* If there's no empty index, then returns the dbit.size() + 1 */
	size_t getEmptyIndex();

	boost::dynamic_bitset<> dbit; // keep info is empty the vector index or not
	std::vector<GameObject*> pool; // All Gameobjects
	std::size_t lastID;
	SDL_Renderer* render;
	Camera* camera;

};

#endif

template<class T, typename ...TArgs>
inline T* GameObjectManager::add(TArgs && ...mArgs)
{
	T* obj = new T(camera, std::forward<TArgs>(mArgs)...);
	size_t ix = getEmptyIndex();

	if (ix > dbit.size())
	{
		pool.emplace_back(obj);
		dbit.push_back(true);
	}
	else
	{
		pool[ix] = obj;
		dbit[ix] = true;
	}

	obj->__initUniq__(lastID);
	obj->loadTexture();

	lastID++;
	return obj;
}
