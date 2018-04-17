#ifndef OBJECTPOOL_H
#define OBJECTPOOL_H

#include <vector>

template <typename T>
class ObjectPool
{
public:
	ObjectPool() {};
	ObjectPool(T* objectToStore, int numberOfObjectsInPool);
	T* getObject();
	T* getCurrentObject();
	~ObjectPool() {};

protected:
	typedef T type;
	std::vector<typedef T*> pool;
	int index;
};

template <typename T>
ObjectPool<T>::ObjectPool(T *object, int numberOfObjectsInPool) :
	index(-1)
{
	pool.push_back(object);
	for (int i = 1; i< numberOfObjectsInPool; i++)
	{
		pool.push_back(new T(object));
	}
}
template <typename T>
T* ObjectPool<T>::getObject()
{
	if ((index + 1) >= pool.size())
	{
		index = -1;
	}
	index++;
	return pool.at(index);
}

template <typename T>
T* ObjectPool<T>::getCurrentObject()
{
	return pool.at(index);
}

#endif
