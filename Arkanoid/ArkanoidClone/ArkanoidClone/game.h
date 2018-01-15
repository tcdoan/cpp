#pragma once
#include "manager.h"

class Game
{
public:
	enum class State { Running, Paused, Over, Won };
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
		if (!isOverlapping(paddle, ball)) return;

		ball.velocity.y = -ball.defaultVelocity;
		ball.velocity.x = ball.x() < paddle.x() ? -ball.defaultVelocity : ball.defaultVelocity;
	}

	void handleBrickBallCollision(Brick& brick, Ball& ball)
	{
		if (!isOverlapping(brick, ball)) return;

		--brick.strength;
		if (brick.strength <= 0) brick.destroyed = true;

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
	const Color BallColor = Color::Red;
	const Color PaddleColor = Color::Red;

	Font arialFont;
	Text textState;

	int remainingBalls;
	Text textBalls;

	State state;
	RenderWindow window{ { windowWidth, windowHeight }, "Arkanoid game demo" };
	Manager manager;
	
	// is the player paused game
	bool paused;
};