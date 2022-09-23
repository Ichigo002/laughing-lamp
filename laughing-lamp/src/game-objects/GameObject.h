#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SDL.h>
#include <iostream>
#include "../utility/Camera.h"
#include "../utility/Vector2Int.h"

/*Abstract class*/
class GameObject
{
public:
	GameObject(Camera* cam) 
	{
		camera = cam;
	}
	~GameObject() { }

	/* Here you can load all needed textures*/
	virtual void loadTexture() { }

	/* Method called every time. You can put there different move algorithms etc.*/
	virtual void update() { }

	/*Handle all events for this object*/
	virtual void events(SDL_Event* eve) { }

	/* Called on every global draw to display on screen */
	virtual void draw() { }

	/* Returns the tagname of object. */
	std::string getTag() { return tagname;  }

	Vector2Int getPos() { return pos; }

	void setPos(Vector2Int p) { pos = p; }

	/* Set the uniq id in the pool */
	void __initUniq__(size_t q) 
	{ 
		if (!uniq_def)
		{
			uniq_def = true;
			uniq_id = q;
		}
		else
		{
			std::cout << "ERROR: void GameObject::__initUniq__(size_t q): Cannot initialize the uniq id of object again\n";
		}
	}

	/* get the uniq id of the object in the pool */
	size_t getUniqueID() 
	{
		if (uniq_def)
		{
			return uniq_id;
		}
		else
		{
			std::cout << "ERROR: size_t GameObject::__getUniq__(): Uniq id is not initialized.\n";
			return 0;
		}

	}

	SDL_Rect* getCollider() { return &colliderRect; }

	void addShift(Vector2Int sh) { pos.x += sh.x; pos.y += sh.y; }

	Vector2Int __lastpsh__; // last position after mtv
protected:
	Camera* camera;
	SDL_Texture* tex;
	SDL_Rect srcR, destR;
	SDL_Rect colliderRect;

	std::string tagname;
	float renderingScale;
	Vector2Int pos;

private:
	size_t uniq_id;
	bool uniq_def = false;
};

#endif
