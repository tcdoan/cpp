#pragma once

#include "constants.h"

class Entity
{
public:
	virtual ~Entity() {}
	virtual void Update() {}
	virtual void Draw(RenderWindow& drawTarget) {}
};

class Hex : public Entity
{
public:
	size_t id;
	Hex(size_t id, float radius);
	void SetColor(Color color);
	void SetPos(size_t x, size_t y);
	Color GetColor();
	FloatRect GetBound();
	void Draw(RenderWindow& target) override;
private:
	const int sides = 6;
	// default color is gray	
	CircleShape shape;
};
