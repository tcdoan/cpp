#include "game.h"
#include "ai.h"

#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include <iostream>
#include  <future>
#include <thread>
#include <functional>

using namespace std;

Game::Game()
{
	n = BoardSize;
	window.setFramerateLimit(60);
	arialFont.loadFromFile(R"(C:\Windows\Fonts\Arial.ttf)");
	textState.setFont(arialFont);
	textState.setFillColor(Color::Black);
	textState.setCharacterSize(16);
	textState.setPosition(10, 10);

	textMidle.setFont(arialFont);
	textMidle.setFillColor(Color::Black);
	textMidle.setCharacterSize(16);
	textMidle.setString("Turn: your turn");
	FloatRect midTextRect = textMidle.getLocalBounds();
	textMidle.setOrigin(midTextRect.left + midTextRect.width / 2.0f, midTextRect.top + midTextRect.height / 2.0f);
	textMidle.setPosition(windowWidth / 2.0f, 10);
}

void Game::Reset()
{
	srand((unsigned int)time(0));
	adj = vector<vector<size_t>>(n*n);
	players = vector<Player>(n*n);
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			// Create and store adjacency nodes
			adj[i*n + j] = MakeAdjList(i, j);
			players[i*n + j] = Player::GRAY;
		}
	}
	PlaceHexes();
	pieRule = PieRule::Offered;
	state = State::Blue;
}


// return true of move to postion id is valid
// return false otherwise
bool Game::BlueMove(size_t id)
{
	state = State::Blue;
	if (!IsValidMove(id))
	{
		return false;
	}
	players[id] = Player::BLUE;
	if (IsGameOver(Player::BLUE, id))
	{
		state = State::BlueWon;
	}
	else
	{
		state = State::Red;
	}	
	return true;
}

size_t Game::RedMove()
{
	size_t pieRuleScore = 0;
	if (pieRule == PieRule::Offered)
	{
		players[lastBlueHex] = Player::GRAY;
		Ai pieRuleEval(n, TRIALS, players, adj);
		pieRuleScore = pieRuleEval.score(lastBlueHex).second;
		players[lastBlueHex] = Player::BLUE;
		pieRule = PieRule::Rejected;
	}

	state = State::Red;
	Ai eval(n, TRIALS, players, adj);

	vector<std::future<std::pair<size_t, size_t>>> futures;
	for (auto& hex : hexes)
	{
		size_t id = hex->id;
		if (Player::GRAY == players[id])
		{
			//auto ftr = std::async(std::launch::async, eval.score, i);
			auto ftr = std::async(std::launch::async, &Ai::score, &eval, id);
			futures.push_back(std::move(ftr));
		}
	}

	// hex id coresponding to above maxScore
	size_t maxScore = 0;
	size_t maxHex = 0;
	for (size_t i = 0; i < futures.size(); i++)
	{
		std::pair<size_t, size_t> result = futures[i].get();
		size_t hexId = result.first;
		size_t score = result.second;
		if (score > maxScore)
		{
			maxScore = score;
			maxHex = hexId;
		}
	}

	if (maxScore < pieRuleScore)
	{
		maxScore = pieRuleScore;
		maxHex = lastBlueHex;
		pieRule = PieRule::Accepted;
		state = State::PieRuleAccepted;
	}

	players[maxHex] = Player::RED;
	return maxHex;
}

void Game::Start()
{
	while (window.isOpen())
	{
		window.clear(Color::White);
		if (Keyboard::isKeyPressed(Keyboard::Key::Escape))
		{
			window.close();
		}

		if (Keyboard::isKeyPressed( Keyboard::Key::R)) Reset();

		Event evt;
		while (window.pollEvent(evt))
		{
			if (evt.type == Event::Closed) {
				window.close();
			}
			if (state == State::Blue && evt.type == Event::MouseButtonPressed && evt.mouseButton.button == Mouse::Left && state == State::Blue) {
				size_t hexId = GetClickedGrayHexId(evt);
				if (hexId != -1)
				{
					if (BlueMove(hexId))
					{
						lastBlueHex = hexId;
					}
				}
			}
		}

		if (state == State::Red)
		{
			textState.setString("Computer color: Red");
			textMidle.setString("Computer's turn: thinking...");
			DrawHexes();
			window.draw(textState);
			window.draw(textMidle);
			window.display();

			std::future<size_t> redMoveFuture = std::async(std::launch::async, &Game::RedMove, this);
			size_t  id = redMoveFuture.get();

			if (IsGameOver(Player::RED, id))
			{
				state = State::RedWon;
			}
			else
			{
				state = State::Blue;
			}
		}

		if (state == State::Blue)
		{
			if (pieRule == PieRule::Accepted)
			{
				textState.setString("Computer took Pie Rule");
				textMidle.setString("Who's turn: your turn");
			}
			else
			{
				textState.setString("Your color: Blue");
				textMidle.setString("Who's turn: your turn");
			}
		}
		if (state == State::RedWon)
		{
			textState.setString("Game Over!");
			textMidle.setString("You lost :(");
		}
		if (state == State::BlueWon)
		{
			textState.setString("Game Over!");
			textMidle.setString("You Won!");
		}

		DrawHexes();
		window.draw(textState);
		window.draw(textMidle);
		window.display();
	}
}

// private functions
void Game::PlaceHexes()
{
	hexes.clear();
	const size_t xmargin = 20;
	const size_t ymargin = 80;
	const size_t xspacing = 10;
	const size_t yspacing = 10;

	// row i, column j
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			unique_ptr<Hex> hex = make_unique<Hex>(i*n + j, HexRadius);
			hex->SetPos(xmargin + i * HexRadius + j * HexRadius*1.8, ymargin + i * HexRadius * 1.6);
			hexes.push_back(std::move(hex));
		}
	}
}

void Game::DrawHexes()
{
	for (auto& hex : hexes)
	{
		Player color = players[hex->id];
		if (color == Player::RED)
		{
			hex->SetColor(Color::Red);
		}
		else if (color == Player::BLUE)
		{
			hex->SetColor(Color::Blue);
		}
		else
		{
			hex->SetColor(Gray);
		}
		hex->Draw(window);
	}
}

size_t Game::GetClickedGrayHexId(Event evt)
{
	for (auto& hex : hexes)
	{
		if (players[hex->id] == Player::GRAY && hex->GetBound().contains(window.mapPixelToCoords(Vector2i(evt.mouseButton.x, evt.mouseButton.y))))
		{
			return hex->id;
		}
	}
	return -1;
}

bool Game::IsValidMove(size_t id)
{
	if (id >= Size() || id < 0 || players[id] != Player::GRAY)
	{
		return false;
	}

	return true;
}

bool Game::IsGameOver(Player player, size_t id)
{
	// for dfs search
	vector<bool> marked(Size(), false);

	// Game over when dfs connect from one edge to another.
	bool edgeNode1 = false;
	bool edgeNode2 = false;
	Dfs(marked, id, player, edgeNode1, edgeNode2);

	if (edgeNode1 && edgeNode2)
		return true;
	else
		return false;
}

vector<size_t> Game::MakeAdjList(size_t i, size_t j)
{
	vector<size_t> adjList;

	if (i > 0)
	{
		adjList.push_back((i - 1)*n + j);
		if (j < n - 1) adjList.push_back((i - 1)*n + j + 1);
	}

	if (i < n - 1)
	{
		if (j > 0) adjList.push_back((i + 1)*n + j - 1);
		adjList.push_back((i + 1)*n + j);
	}

	if (j > 0)
	{
		adjList.push_back(i*n + j - 1);
	}

	if (j < n - 1)
	{
		adjList.push_back(i*n + j + 1);
	}

	return adjList;
}

void Game::Dfs(vector<bool> marked, size_t node, Player player, bool & beginNodeVisited, bool & endNodeVisited)
{
	// for checking game over we can quit ealier.
	if (beginNodeVisited && endNodeVisited)
	{
		return;
	}

	marked[node] = true;
	if (Player::BLUE == player)
	{
		if (node % n == 0) beginNodeVisited = true;
		if (node % n == n - 1) endNodeVisited = true;
	}
	else if (Player::RED == player)
	{
		if (node / n == 0) beginNodeVisited = true;
		if (node / n == n - 1) endNodeVisited = true;
	}

	vector<size_t> adjList = adj[node];
	for (int x : adjList)
	{
		if (!marked[x] && players[x] == player)
		{
			Dfs(marked, x, player, beginNodeVisited, endNodeVisited);
		}
	}
}
