#include "game.h"

Game::Game() 
{
	paused = false;
	state = State::Running;
	window.setFramerateLimit(60);
}

void Game::Reset()
{
	state = State::Paused;
	manager.Clear();

	const int brickColumnCount = 15;
	const int brickRowCount = 5;
	const int marginX = 60;
	const int marginY = 20;
	const int spacing = 4;

	for (int i = 0; i < brickColumnCount; ++i)
	{
		for (int j = 0; j < brickRowCount; ++j)
		{
			float x = i * (Brick::defaultWidth + spacing);
			float y = j * (Brick::defaultHeight + spacing);
			manager.Create<Brick>(x + marginX, y + marginY, BrickColor);
		}
	}

	manager.Create<Ball>(windowWidth / 2.f, windowHeight / 2.f, BallColor);
	manager.Create<Paddle>(windowWidth / 2, windowHeight - 50, PaddleColor);
}

void Game::Start()
{
	while (window.isOpen())
	{
		window.clear(sf::Color::White);

		Event evt;
		while (window.pollEvent(evt))
		{
			switch (evt.type)
			{
			case Event::Closed:
				window.close();
				break;
			default:
				break;
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
		{
			window.close();
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		{
			if (!paused)
			{
				if (state == State::Paused)
					state = State::Running;
				else if (state == State::Running)
					state = State::Paused;
			}
			paused = true;
		} else paused = false;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::R)) Reset();

		if (State::Paused != state)
		{
			manager.Update();
			manager.ApplyEach<Ball>([this](auto& ball)
			{
				manager.ApplyEach<Brick>([this, &ball](auto& brick)
				{
					handleBrickBallCollision(brick, ball);
				});

				manager.ApplyEach<Paddle>([this, &ball](auto& paddle)
				{
					handlePaddleBallCollision(paddle, ball);
				});
			});

			manager.GarbageCollect();
		}

		manager.Draw(window);
		window.display();

	}
}