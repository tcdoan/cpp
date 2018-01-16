#include "game.h"

using namespace std;


Game::Game()
{
	n = BoardSize;
	window.setFramerateLimit(60);
	arialFont.loadFromFile(R"(C:\Windows\Fonts\Arial.ttf)");
	textState.setFont(arialFont);
	textState.setPosition(10, 10);
	textState.setCharacterSize(15.f);
	textState.setFillColor(Color::Blue);
	Reset();
}

void Game::Reset()
{

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
	state = State::Blue;
}


void Game::BlueMove(size_t id)
{
	return;
}

void Game::RedMove()
{
	return;
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
		bool mousedPressed = false;
		while (window.pollEvent(evt))
		{
			if (evt.type == Event::Closed) {
				window.close();
			}
			if (evt.type == Event::MouseButtonPressed && evt.mouseButton.button == Mouse::Left && state == State::Blue) {
				mousedPressed = true;
			}
		}

		if (state == State::Blue)
		{
			textState.setString("Your turn: Blue");
			if (mousedPressed)
			{
				size_t hexId = GetClickedGrayHexId(evt);
				if (hexId != -1)
				{
					BlueMove(hexId);
				}
			}
		}

		if (state == State::RedWon)
		{
			textState.setString("Game Over!");
		}

		if (state == State::BlueWon)
		{
			textState.setString("You Won!");
		}

		if (state == State::Red)
		{
			textState.setString("computer's turn: Red");
			RedMove();
		}
		Draw();
	}
}

// private functions
void Game::PlaceHexes()
{
	hexes.clear();
	const size_t xmargin = 25;
	const size_t ymargin = 90;

	// row i, column j
	for (size_t i = 0; i < n; i++)
	{
		for (size_t j = 0; j < n; j++)
		{
			unique_ptr<Hex> hex = make_unique<Hex>(i*n + j, HexRadius);
			hex->SetPos(xmargin + i * HexRadius + j * HexRadius, ymargin + i * HexRadius * 2.0 / 3.0);
			hexes.push_back(std::move(hex));
		}
	}
}

void Game::Draw()
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
	window.draw(textState);
	window.display();
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

	if (edgeNode1 && edgeNode2 && player == Player::RED)
	{
		state = State::RedWon;
		return true;
	}

	if (edgeNode1 && edgeNode2 && player == Player::BLUE)
	{
		state = State::BlueWon;
		return true;
	}
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
