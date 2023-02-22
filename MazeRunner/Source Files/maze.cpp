#include <SDL3/SDL_image.h>
#include <SDL3/SDL.h>
#include <algorithm>
#include <random>
#include <ctime>
#include <stack>

#include "maze.h"

const int Maze::WIDTH = 29;
const int Maze::HEIGHT = 29;
const int Maze::SIZE = 16;

SDL_Texture* Maze::textures[2] = {nullptr};

Maze::Maze()
{
	// Creating window
	window_ = SDL_CreateWindow("MazeRunner", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Maze::HEIGHT*Maze::SIZE, Maze::WIDTH*Maze::SIZE, SDL_WINDOW_INPUT_FOCUS);
	renderer_ = SDL_CreateRenderer(window_, NULL, 0);
	// Setting up randomness
	srand(time(0));

	// Loading textures
	Maze::textures[Maze::Type::GROUND] = IMG_LoadTexture(renderer_, "./images/ground.png");
	Maze::textures[Maze::Type::WALL] = IMG_LoadTexture(renderer_, "./images/wall.png");

	// Allocating grid
	grid_ = std::vector<std::vector<int>>(Maze::HEIGHT, std::vector<int>(Maze::WIDTH, Type::WALL));
}

Maze::~Maze()
{
	// Releasing memory 
	for (auto& texture : Maze::textures)
		SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
}

void Maze::run()
{
	// Generate the maze
	generate(Algorithm::BFS);

	SDL_Delay(5000);
}

void Maze::update()
{
	// Filling grid
	for (int i = 0; i<Maze::HEIGHT; i++)
	{
		for (int j = 0; j<Maze::WIDTH; j++)
		{
			SDL_FRect pos;
			pos.x = j * 16;
			pos.y = i * 16;
			pos.h = pos.w = 16;
			SDL_RenderTexture(renderer_, Maze::textures[grid_[i][j]], NULL, &pos);
		}
	}
	SDL_RenderPresent(renderer_);
	SDL_Delay(50);
}

void Maze::generate(const Algorithm &algorithm)
{
	// For the direction
	enum Direction {UP, DOWN, LEFT, RIGTH};

	// The queue to execute
	std::stack<std::pair<int, int>> q;

	// Random first point
	std::pair<int, int> pt = std::make_pair((rand() % (Maze::WIDTH - 1)) - 1 ,(rand() % (Maze::HEIGHT - 1)) - 1);
	q.emplace(std::make_pair(1, 1));

	/**
	* \brief For getting adjacents valid cells from cell (i, j)
	* \param i, j The indexes of the current cell to find valid adjacent cells for
	* \return a list of pair of indexes (first: a valid adjacent cell at +-2 distance of the givel cell, second: the cell at +-2 distance of the givel cell)
	*/
	auto getAdj = [&](int i, int j) -> std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>>
	{
		std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> output;
		int direction = rand() % 4;
		if ((i-2) > 0 && (i-2) < Maze::WIDTH && grid_[i - 2][j] != Maze::Type::GROUND && (i - 2) > 0 && (i - 2) < Maze::HEIGHT && j > 0 && j < Maze::WIDTH)
			output.emplace_back(std::make_pair(std::make_pair(i - 2, j), std::make_pair(i - 1, j)));
		if ((i + 2) > 0 && (i + 2) < Maze::WIDTH && grid_[i + 2][j] != Maze::Type::GROUND && (i + 2) > 0 && (i + 2) < Maze::HEIGHT && j > 0 && j < Maze::WIDTH)
			output.emplace_back(std::make_pair(std::make_pair(i + 2, j), std::make_pair(i + 1, j)));
		if ((j - 2) > 0 && (j - 2) < Maze::WIDTH && grid_[i ][j - 2] != Maze::Type::GROUND && (j - 2) > 0 && (j - 2) < Maze::HEIGHT && i > 0 && i < Maze::WIDTH)
			output.emplace_back(std::make_pair(std::make_pair(i , j - 2), std::make_pair(i, j - 1)));
		if ((j + 2) > 0 && (j + 2) < Maze::WIDTH && grid_[i][j + 2] != Maze::Type::GROUND && (j + 2) > 0 && (j + 2) < Maze::HEIGHT && i > 0 && i < Maze::WIDTH)
			output.emplace_back(std::make_pair(std::make_pair(i, j + 2), std::make_pair(i, j + 1)));
	
		return output;

	};

	while (!q.empty())
	{
		// Getting current front cell and pop it from queue
		auto pt = q.top();
		//q.pop();

		// Setting current cell as GROUND
		grid_[pt.first][pt.second] = Type::GROUND;

		// Getting adjacents valid cells
		auto adjCells = getAdj(pt.first, pt.second);

		// Pop current top-most element if no adjacent valid cell found
		if (adjCells.size() == 0 && q.size() > 0)
			q.pop();
		
		// Append a random cell otherwise
		else 
		{
			auto randomCell = adjCells[rand() % (adjCells.size())];
			q.emplace(randomCell.first);
			grid_[randomCell.second.first][randomCell.second.second] = Type::GROUND;
		}
		
		// Updating screen
		update();
	}
}