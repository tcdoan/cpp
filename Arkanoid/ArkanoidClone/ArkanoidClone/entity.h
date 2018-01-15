#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

const unsigned int windowWidth = 1024;
const unsigned int windowHeight = 768;

class Entity
{
public:
	bool destroyed{false};
	virtual ~Entity() {}
	virtual void Update() {}
	virtual void Draw(RenderWindow& drawTarget) {}
};

class Circle
{
public:
	CircleShape shape;
	float x() const noexcept;
	float y() const noexcept;
	float r() const noexcept;
	float left() const noexcept;
	float right() const noexcept;
	float top() const noexcept;
	float bottom() const noexcept;
};

class Retangle
{
public:
	RectangleShape shape;
	float x() const noexcept;
	float y() const noexcept;
	float w() const noexcept;
	float h() const noexcept;

	float left() const noexcept;
	float right() const noexcept;
	float top() const noexcept;
	float bottom() const noexcept;
};

class Ball : public Entity, public Circle
{
public:
	const float defaultRadius = 12.0f;
	const float defaultVelocity = 7.0f;

	Vector2f velocity;
	Ball(float x, float y, Color color);
	void Update() override;
	void Draw(RenderWindow& drawTarget) override;
private:
	Color color;
	void handleBoundCollision() noexcept;
};

class Paddle : public Entity, public Retangle
{
public:	
	Vector2f velocity;
	Paddle(float x, float y, Color color);
	void Update() override;
	void Draw(RenderWindow& drawTarget) override;
private:
	const float defaultWidth{ 100.0f };
	const float defaultHeight{ 25.0f };
	const float defaultVelocity{ 7.5f };
	Color color;
	void handleInput();
};

class Brick : public Entity, public Retangle
{
public:
	const Color ColorStrength0{ 255, 255, 0, 80 };
	const Color ColorStrength1{ 255, 255, 0, 80 };
	const Color ColorStrength2{ 255, 255, 0, 170 };
	const Color ColorStrength3{ 255, 255, 0, 255 };

	const std::vector<Color> colors{ ColorStrength0, ColorStrength1, ColorStrength2, ColorStrength3 };

	static constexpr float defaultWidth =  60.0f;
	static constexpr float defaultHeight = 20.0f;

	// brick would be destroyed when hits = strength
	int strength = 1;

	Brick(float x, float y);
	void Update() override;
	void Draw(RenderWindow& drawTarget) override;
private:
	const float defaultVelocity = 9.0f;
	Color color;
};
