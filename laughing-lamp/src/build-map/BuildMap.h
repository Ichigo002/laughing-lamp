#ifndef BUILD_MAP_H
#define BUILD_MAP_H

#include <SDL.h>
#include <vector>
#include "../utility/Camera.h"
#include "Blocks/Blocks.h"

struct BPPointer
{
	BBlock* bb; // pointer to block
	Vector2Int lcl; // position of block
};

class BuildMap
{
public:
	BuildMap(Camera* c, int whex, int hhex, float render_Scale, float ratio);
	~BuildMap();

	/// <summary>
	/// Put new block on the map
	/// </summary>
	/// <param name="pos">position of block. [LCL units]</param>
	/// <param name="block_name">name of block</param>
	/// <returns>Returns -1 on fail and 0 on success</returns>
	int put(Vector2Int pos, std::string block_name);

	/// <summary>
	/// Put new block on the map
	/// </summary>
	/// <param name="pos">position of block. [LCL units]</param>
	/// <param name="id">id of block</param>
	/// <returns>Returns -1 on fail and 0 on success</returns>
	int put(Vector2Int pos, size_t id);

	/// <summary>
	/// Give access for cursor to place blocks
	/// </summary>
	/// <param name="block_name">what block can place</param>
	/// <param name="amount">amount of blocks which user can place. if you want place blocks with no limits set -1</param>
	/// <returns>Returns -1 on fail and 0 on success</returns>
	void enableCursorPlacing(std::string block_name, int amount = 1);
	
	/// <summary>
	/// Disables posibility placing with cursor
	/// </summary>
	/// <returns></returns>
	void disableCursorPlacing();

	/// <summary>
	/// Removes the object from pos
	/// </summary>
	/// <param name="pos">position of block. [LCL units]</param>
	void remove(Vector2Int pos);

	//If not found returns nullptr
	BBlock* getBlockAt(Vector2Int pos);
	BBlock* getBlockAt(size_t index);
	BBlock* getBlockAt(std::string name);

	/// <summary>
	/// Look for the vector of all blocks 
	/// </summary>
	/// <returns>Returns the BBlock's index or size_t()</returns>
	size_t findIndexBy(std::string block_name);

	/// <summary>
	/// Verify index existence.
	/// </summary>
	inline bool verifyIndex(size_t index);

	/// <summary>
	/// Updates all map
	/// </summary>
	void update();

	/// <summary>
	/// Updates events on map
	/// </summary>
	/// <param name="eve"></param>
	void events(SDL_Event* eve);

	/// <summary>
	/// Draw map
	/// </summary>
	void draw();
private:
	//Init default blocks into vblocks vector
	void initBlocks();

	//Init new block of class T
	template<class T>
	T* inb()
	{
		T* obj = new T();
		if (findIndexBy(obj->getName()) == size_t())
		{
			vblocks.emplace_back(obj);
			return obj;
		}
		return nullptr;
	}

	Camera* c;
	std::vector<BBlock*> vblocks; // All blocks on the map
	std::vector<BPPointer> bmap; // Map of pointers into

	int whex; // width of hexagon
	int hhex; // height of hexagon
	float render_scale;
	float ratioAtoB;

	bool placeByCursor;
	int amountPlacing;
	size_t indexCursorP;

	SDL_Rect destR;
};

#endif
