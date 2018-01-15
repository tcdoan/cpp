#pragma once
#include "entity.h"
#include <memory>
#include <vector>
#include <map>
#include <typeinfo>

using namespace std;

// Game entity manager 
// Use to manage entity objects 
class Manager
{
public:
	// Create a heap-allocated object of type T
	template<typename T, typename ...TArgs>
	T & Create(TArgs && ...args)
	{
		static_assert(is_base_of<Entity, T>::value, "Type T is not derived from Entity");

		auto uPointer(make_unique<T>(forward<TArgs>(args)...));
		auto ptr(uPointer.get());

		mapEntities[typeid(T).hash_code()].emplace_back(ptr);
		entities.emplace_back(std::move(uPointer));

		return *ptr;
	}

	// Get all game objects belong to a specific type T
	template<typename T>
	vector<Entity*> GetAll()
	{
		return mapEntities[typeid(T).hash_code()];
	}

	//Run arbitrary function for each game object of type T
	template <typename T, typename TFun>
	void ApplyEach(const TFun & func)
	{
		vector<Entity*> entityVec = GetAll<T>();
		for (auto pt : entityVec)
		{			
			func((*reinterpret_cast<T*>(pt)));
		}
	}

	void GarbageCollect();
	void Clear();
	void Update();
	void Draw(RenderWindow& window);
private:
	vector<unique_ptr<Entity>> entities;
	map<size_t, vector<Entity*>> mapEntities;
};

