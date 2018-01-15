#include "entity.h"

float Circle::x() const noexcept { return shape.getPosition().x; }
float Circle::y() const noexcept { return shape.getPosition().y; }
float Circle::r() const noexcept { return shape.getRadius(); }
float Circle::left() const noexcept { return x() - r(); }
float Circle::right() const noexcept { return x() + r(); }
float Circle::top() const noexcept { return y() - r(); }
float Circle::bottom() const noexcept { return y() + r(); }

float Retangle::x() const noexcept { return shape.getPosition().x; }
float Retangle::y() const noexcept { return shape.getPosition().y; }
float Retangle::w() const noexcept { return shape.getSize().x; }
float Retangle::h() const noexcept { return shape.getSize().y; }
float Retangle::left() const noexcept { return x() - w() / 2.f; }
float Retangle::right() const noexcept { return x() + w() / 2.f; }
float Retangle::top() const noexcept { return y() - h() / 2.f; }
float Retangle::bottom() const noexcept { return y() + h() / 2.f; }


Ball::Ball(float x, float y, Color color)
{
	velocity = Vector2f{ -defaultVelocity, -defaultVelocity };
	shape.setPosition(x, y);
	shape.setRadius(defaultRadius);
	shape.setFillColor(color);
	shape.setOrigin(defaultRadius, defaultRadius);
}

void Ball::Update() 
{
	shape.move(velocity);
	handleBoundCollision();
}

void Ball::Draw(RenderWindow& drawTarget) 
{
	drawTarget.draw(shape);
}

void Ball::handleBoundCollision() noexcept
{

	if (left() < 0)
		velocity.x = defaultVelocity;
	else if (right() > windowWidth)
		velocity.x = -defaultVelocity;

	if (top() < 0)
		velocity.y = defaultVelocity;
	else if (bottom() > windowWidth)
		destroyed = true;
}

Paddle::Paddle(float x, float y, Color color)
{
	shape.setPosition(x, y);
	shape.setSize({ defaultWidth, defaultHeight });
	shape.setFillColor(color);
	shape.setOrigin(defaultWidth / 2.f, defaultHeight / 2.f);
}

void Paddle::Update() 
{
	handleInput();
	shape.move(velocity);
}

void Paddle::Draw(RenderWindow& drawTarget)
{
	drawTarget.draw(shape);
}

void Paddle::handleInput()
{
	if (Keyboard::isKeyPressed(Keyboard::Key::Left) && left() > 0)
	{
		velocity.x = -defaultVelocity;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Key::Right) && right() < windowWidth)
	{
		velocity.x = defaultVelocity;
	}
	else
	{
		velocity.x = 0;
	}
}

Brick::Brick(float x, float y)
{
	shape.setPosition(x, y);
	shape.setSize({ defaultWidth, defaultHeight });
	shape.setOrigin(defaultWidth / 2.f, defaultHeight / 2.f);
}

void Brick::Update()
{
	shape.setFillColor(colors[strength]);
}

void Brick::Draw(RenderWindow& drawTarget)
{
	drawTarget.draw(shape);
}
