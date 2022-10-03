//Not complete
// Not usable in current version ;<
#ifndef POOL_OBJECT_H
#define POOL_OBJECT_H

#include <vector>

/// <summary>
/// Pool for objects
/// </summary>
template<class T>
class PoolObject
{
public:
	PoolObject();
	~PoolObject();

	/// <summary>
	/// Reset adn delete all
	/// </summary>
	void reset();

	/// <summary>
	/// Pushes object into pool
	/// </summary>
	/// <param name="pv">value to push</param>
	/// <returns>Returns the current index of item</returns>
	size_t push(const T pv);

	/// <summary>
	/// Pop element at index
	/// </summary>
	/// <param name="index"></param>
	void pop(size_t index);


	friend T& operator[](int v);

	/// <summary>
	/// Verifies does index exist
	/// </summary>
	/// <returns></returns>
	bool verifyIndex();

	/// <summary>
	/// Returns true if object at index is not out of range and not nullptr
	/// </summary>
	bool nnull(size_t index);
private:
	std::vector<T> vec;
};

#endif
