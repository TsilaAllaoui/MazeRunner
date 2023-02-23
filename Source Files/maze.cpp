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

SDL_Texture* Maze::textures_[2] = {nullptr};

Maze::Maze(const Algorithm &algorithm)
{
	// Creating window
	window_ = SDL_CreateWindow("MazeRunner", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Maze::HEIGHT*Maze::SIZE, Maze::WIDTH*Maze::SIZE, SDL_WINDOW_INPUT_FOCUS);
	renderer_ = SDL_CreateRenderer(window_, NULL, 0);
	// Setting up randomness
	srand(time(0));

	// Loading textures
	Maze::textures_[Maze::Type::GROUND] = IMG_LoadTexture(renderer_, "./images/ground.png");
	Maze::textures_[Maze::Type::WALL] = IMG_LoadTexture(renderer_, "./images/wall.png");

	// Allocating grid
	grid_ = std::vector<std::vector<int>>(Maze::HEIGHT, std::vector<int>(Maze::WIDTH, Type::WALL));

	// Setting up the current cell
	auto x = (rand() % (Maze::WIDTH - 2)) - 1;
	auto y = (rand() % (Maze::HEIGHT - 2)) - 1;
	x += ((x % 2 == 0) ? ((x + 1 < Maze::WIDTH - 2) ? -1 : 1) : 0);
	y += ((y % 2 == 0) ? ((y + 1 < Maze::HEIGHT - 2) ? -1 : 1) : 0);
	currCellPosition_ = { float(x), float(y), Maze::SIZE, Maze::SIZE };

	// Setting up the trail
	useTrail_ = false;

	// Setting current algorithm
	algorithm_ = algorithm;
}

Maze::~Maze()
{
	// Releasing memory 
	for (auto& texture : Maze::textures_)
		SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer_);
	SDL_DestroyWindow(window_);
}

void Maze::run()
{
	// Generate the maze
	if (algorithm_ == Algorithm::BFS)
		generateBFS();
	else if (algorithm_ == Algorithm::RandomizedPrim)
		generateRandomizedPrim();

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
			SDL_RenderTexture(renderer_, Maze::textures_[grid_[i][j]], NULL, &pos);
		}
	}

	SDL_SetRenderDrawColor(renderer_, 0, 0, 255, 255);
	SDL_RenderFillRect(renderer_, &currCellPosition_);

	SDL_RenderPresent(renderer_);
	SDL_Delay(50);
}

void Maze::generateBFS(const bool& trailOn)
{
	// For the direction
	enum Direction {UP, DOWN, LEFT, RIGTH};

	// The queue to execute
	std::stack<std::pair<int, int>> q;

	// Adding the first point
	q.emplace(std::make_pair(currCellPosition_.x, currCellPosition_.y));

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

	bool oneAdjCell = false;

	while (!q.empty())
	{
		// Getting current front cell and pop it from queue
		auto pt = q.top();

		if (oneAdjCell)
		{
			oneAdjCell = false;
			q.pop();
		}

		// Setting current cell as GROUND
		grid_[pt.first][pt.second] = Type::GROUND;

		// Getting adjacents valid cells
		auto adjCells = getAdj(pt.first, pt.second);

		// Pop current top-most element if no adjacent valid cell found
		if (adjCells.size() == 0 && q.size() > 0)
		{
			q.pop();

			// Updating the current cell position
			if (trailOn)
			{
				currCellPosition_.y = pt.first * Maze::SIZE;
				currCellPosition_.x = pt.second * Maze::SIZE;
			}
		}


		// Append a random cell otherwise
		else 
		{
			auto randomCell = adjCells[rand() % (adjCells.size())];
			q.emplace(randomCell.first);
			grid_[randomCell.second.first][randomCell.second.second] = Type::GROUND;
			
			// Updating the current cell position
			currCellPosition_.y = randomCell.first.first * Maze::SIZE;
			currCellPosition_.x = randomCell.first.second * Maze::SIZE;
		}


		// If there is only one adjacent cell 
		if (adjCells.size() == 1)
			oneAdjCell = true;

		// Updating screen
		update();
	}
}

void Maze::generateRandomizedPrim()
{

}