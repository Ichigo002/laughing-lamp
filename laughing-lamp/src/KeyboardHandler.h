#ifndef KEYBOARD_HANDLER_H
#define KEYBOARD_HANDLER_H

#include <SDL.h>

class KeyboardHandler
{
public:

	inline static bool pressedKey(SDL_KeyCode key, SDL_Event* e)
	{
		return (e->type == SDL_KEYDOWN) && (e->key.keysym.sym == key);
	}

	inline static bool releasedKey(SDL_KeyCode key, SDL_Event* e)
	{
		return (e->type == SDL_KEYUP) && (e->key.keysym.sym == key);
	}
};

#endif 

