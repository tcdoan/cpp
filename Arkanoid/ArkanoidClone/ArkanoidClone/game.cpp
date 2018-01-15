#include "game.h"

Game::Game() 
{
	remainingBalls = 7;
	paused = false;
	state = State::Over;
	window.setFramerateLimit(60);

	arialFont.loadFromFile(R"(C:\Windows\Fonts\Arial.ttf)");

	textState.setFont(arialFont);
	textState.setPosition(10, 10);
	textState.setCharacterSize(35.f);
	textState.setFillColor(Color::White);
	textState.setString("Paused");

	textBalls.setFont(arialFont);
	textBalls.setPosition(10, 10);
	textBalls.setCharacterSize(15.f);
	textBalls.setFillColor(sf::Color::White);
}

void Game::Reset()
{
	remainingBalls = 7;
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
			auto& brick(manager.Create<Brick>(x + marginX, y + marginY));
			brick.strength= 1 + ((i * j) % 3);
		}
	}

	manager.Create<Ball>(windowWidth / 2.f, windowHeight / 2.f, BallColor);
	manager.Create<Paddle>(windowWidth / 2, windowHeight - 50, PaddleColor);
}

void Game::Start()
{
	while (window.isOpen())
	{
		window.clear(sf::Color::Black);

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

		if (state != State::Running)
		{
			if (state == State::Paused) textState.setString("Paused");
			else if (state == State::Over)	textState.setString("Game Over!");
			else if (state == State::Won) textState.setString("You Won!");
			window.draw(textState);
		}
		else
		{

			// if there are no more ball, spawn a new one and remove the died one
			if (manager.GetAll<Ball>().empty())
			{
				manager.Create<Ball>(windowWidth / 2.f, windowHeight / 2.f, BallColor);
				--remainingBalls;
			}

			// if there are no more bricks, the player won.
			if (manager.GetAll<Brick>().empty()) state = State::Won;

			// If there are more remaining balls, it's game over.
			if (remainingBalls <= 0) state = State::Over;

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

			manager.Draw(window);

			// Update lives string and draw it.
			textBalls.setString("Remains: " + std::to_string(remainingBalls));
			window.draw(textBalls);
		}
		window.display();

	}
}