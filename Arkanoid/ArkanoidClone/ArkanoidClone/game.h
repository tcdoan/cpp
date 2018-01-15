#pragma once
#include "manager.h"

class Game
{
public:
	enum class State { Running, Paused };
	Game();
	void Reset();
	void Start();

	template <typename A, typename B>
	bool isOverlapping(const A& a, const B& b)
	{
		return a.right() >= b.left() && a.left() <= b.right() &&
			a.bottom() >= b.top() && a.top() <= b.bottom();
	}

	void handlePaddleBallCollision(const Paddle& paddle, Ball& ball)
	{
		if (!isOverlapping(paddle, ball))
		{
			return;
		}

		ball.velocity.y = -ball.velocity.y;
		ball.velocity.x = ball.x() < paddle.x() ? -ball.defaultVelocity : ball.defaultVelocity;
	}

	void handleBrickBallCollision(Brick& brick, Ball& ball)
	{
		if (!isOverlapping(brick, ball)) return;
		brick.destroyed = true;

		float overlapLeft = ball.right() - brick.left();
		float overlapRight = brick.right() - ball.left();
		float overlapTop = ball.bottom() - brick.top();
		float overlapBottom = brick.bottom() - ball.top();

		bool ballFromLeft = std::abs(overlapLeft) < std::abs(overlapRight);
		bool ballFromTop = std::abs(overlapTop) < std::abs(overlapBottom);

		float overlapX = ballFromLeft ? overlapLeft : overlapRight;
		float overlapY = ballFromTop ? overlapTop : overlapBottom;

		if (std::abs(overlapX) < std::abs(overlapY))
		{
			ball.velocity.x = ballFromLeft ? -ball.defaultVelocity : ball.defaultVelocity;
		}
		else
		{
			ball.velocity.y = ballFromTop ? -ball.defaultVelocity : ball.defaultVelocity;
		}
	}
private:
	const Color BallColor = Color::Cyan;
	const Color PaddleColor = Color::Cyan;
	const Color BrickColor = Color::Cyan;

	State state;
	RenderWindow window{ { windowWidth, windowHeight }, "Arkanoid game demo" };
	Manager manager;
	
	// is the player paused game
	bool paused;
};