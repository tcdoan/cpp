#include "manager.h"
#include <memory>

using namespace std;

void Manager::GarbageCollect()
{
	for (auto& mapEntry : mapEntities)
	{
		auto& entityVec(mapEntry.second);
		entityVec.erase(remove_if(entityVec.begin(), entityVec.end(), [](auto ptr) { return ptr->destroyed; }), entityVec.end());
	}
	entities.erase(remove_if(std::begin(entities), std::end(entities), [](const auto& uptr) { return uptr->destroyed; }), std::end(entities));	
}

void Manager::Clear()
{
	entities.clear();
	mapEntities.clear();
}

void Manager::Update()
{
	for (auto& entity : entities) entity->Update();
}

void Manager::Draw(RenderWindow & window)
{
	for (auto& entity : entities) entity->Draw(window);
}
