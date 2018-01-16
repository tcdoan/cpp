#include "entity.h"

Hex::Hex(size_t id, float radius) : id(id)
{
	shape = CircleShape(radius, sides);
	shape.setRadius(radius);
	shape.setFillColor(Gray);
}


void Hex::SetColor(Color color)
{
	shape.setFillColor(color);
}

void Hex::SetPos(size_t x, size_t y)
{
	shape.setPosition(x, y);
}

Color Hex::GetColor()
{
	return shape.getFillColor();
}

void Hex::Draw(RenderWindow& target)
{ 
	target.draw(shape); 
}

FloatRect Hex::GetBound()
{
	return shape.getGlobalBounds();
}

