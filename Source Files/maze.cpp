#include <SDL3/SDL_image.h>
#include <SDL3/SDL.h>
#include <algorithm>
#include <random>
#include <ctime>
#include <stack>

#include "runner.h"
#include "maze.h"

const int Maze::WIDTH = 9;
const int Maze::HEIGHT = 9;
const int Maze::SIZE = 16;

SDL_Texture* Maze::textures_[2] = {nullptr};

Maze::Maze(const Algorithm &algorithm, const bool &isMonochrome)
{
	// Creating window
	window_ = SDL_CreateWindow("MazeRunner", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Maze::HEIGHT*Maze::SIZE, Maze::WIDTH*Maze::SIZE, SDL_WINDOW_INPUT_FOCUS);
	renderer_ = SDL_CreateRenderer(window_, NULL, 0);

	// Setting up randomness
	srand(time(0));

	// Loading textures
	if (isMonochrome)
	{
		SDL_Surface *surface = SDL_CreateSurface(Maze::SIZE, Maze::SIZE, SDL_PixelFormatEnum::SDL_PIXELFORMAT_RGBA8888);
		SDL_FillSurfaceRect(surface, NULL, 0xFFFFFFFF);
		Maze::textures_[Maze::Type::GROUND] = SDL_CreateTextureFromSurface(renderer_, surface);
		SDL_FillSurfaceRect(surface, NULL, 0);
		Maze::textures_[Maze::Type::WALL] = SDL_CreateTextureFromSurface(renderer_, surface);
	}
	else
	{
		Maze::textures_[Maze::Type::GROUND] = IMG_LoadTexture(renderer_, "./images/ground.png");
		Maze::textures_[Maze::Type::WALL] = IMG_LoadTexture(renderer_, "./images/wall.png");
	}

	// Allocating grid
	grid_ = std::vector<std::vector<int>>(Maze::HEIGHT, std::vector<int>(Maze::WIDTH, Type::WALL));

	// Setting up the current cell
	int x, y;
	do
		x = (rand() % Maze::WIDTH - 2) + 2;
	while (x % 2 == 0);
	do
		y = (rand() % Maze::HEIGHT - 2) + 2;
	while (y % 2 == 0);
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
	// Starting point
	auto startPoint = std::make_pair(16,16);// std::make_pair(int(currCellPosition_.x * Maze::SIZE), int(currCellPosition_.y * Maze::SIZE));

	// Generate the maze
	if (algorithm_ == Algorithm::BFS)
		generateBFS();
	else if (algorithm_ == Algorithm::RandomizedPrim)
		generateRandomizedPrim();

	// End point
	std::pair<int, int> endPoint = std::make_pair(2* Maze::SIZE,2 * Maze::SIZE);
	while(true)
	{
		auto i = (rand() % Maze::WIDTH - 2) + 2;
		auto j = (rand() % Maze::HEIGHT - 2) + 2;
		if (grid_[i][j] == Type::GROUND)
		{
			endPoint = std::make_pair(i * Maze::SIZE, j * Maze::SIZE);
			break;
		}
	}

	// Creating a runner
	Runner runner(Runner::Color::RED, startPoint, grid_, renderer_, true);
	
	// Running runner in the maze
	while (!runner.isArrived(endPoint))
	{
		// Updating
		update(false);

		// Rendering startPoint and endPoint
		renderPoints(startPoint, endPoint);

		// Move the runner
		runner.move();

		// Render all objects
		SDL_RenderPresent(renderer_);
		SDL_Delay(1000);
	}

	SDL_Delay(5000);
}

void Maze::update(const bool &drawCurrentCell)
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

	if(drawCurrentCell)
	{
		// Rendering the current position cell
		SDL_SetRenderDrawColor(renderer_, 0, 0, 255, 255);
		SDL_RenderFillRect(renderer_, &currCellPosition_);
	}
}

void Maze::generateBFS(const bool& trailOn)
{
	// The queue to execute
	std::stack<std::pair<int, int>> q;

	// Adding the first point
	q.emplace(std::make_pair(currCellPosition_.x, currCellPosition_.y));

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
		auto adjCells = getNeighborsOfCell(pt.first, pt.second);

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

		// Render all objects
		SDL_RenderPresent(renderer_);
		//SDL_Delay(50);
	}
}

void Maze::generateRandomizedPrim()
{
	// Getting a random cell as current cell
	auto currentCell = currCellPosition_;

	currentCell.x = 1;
	currentCell.y = 1;

	// Updating that cell to be ground
	grid_[currentCell.x][currentCell.y] = Type::GROUND;

	// List of all neighbor
	std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> neighbors;

	// If it's the first iteration
	bool firstRun = true;

	// Looping until there is no more neighbor to choose from
	while (firstRun || neighbors.size() > 0)
	{
		// If first iteration
		if (firstRun)
			firstRun = false;

		// Getting all adjacent valid cells of chosen cell
		auto adjCells = getNeighborsOfCell(currentCell.x, currentCell.y);

		// Appending them to neighbors list
		for (auto& cell : adjCells)
			neighbors.emplace_back(cell);

		//Choosing random cell from neighbors list
		auto index = rand() % (neighbors.size());
		auto randomCell = neighbors[index];

		// Removing the chosen cell from neighbors list
		neighbors.erase(neighbors.begin() + index);

		// If the chosen rando cell is ground, pass to next iteration
		if (grid_[randomCell.first.first][randomCell.first.second] == Type::GROUND)
			continue;

		// Setting the chosen cell and the path to it as ground
		grid_[randomCell.second.first][randomCell.second.second] = Type::GROUND;
		grid_[randomCell.first.first][randomCell.first.second] = Type::GROUND;

		// Updating current cell position
		currentCell.x = randomCell.first.first;
		currentCell.y = randomCell.first.second;

		// Updating the current cell marker position
		currCellPosition_.y = randomCell.first.first * Maze::SIZE;
		currCellPosition_.x = randomCell.first.second * Maze::SIZE;

		// Updating maze
		update();

		// Render all objects
		SDL_RenderPresent(renderer_);
		//SDL_Delay(50);
	}
}

std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> Maze::getNeighborsOfCell(int i, int j)
{
	std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> output;
	int direction = rand() % 4;
	if ((i - 2) > 0 && (i - 2) < Maze::WIDTH && grid_[i - 2][j] != Maze::Type::GROUND && (i - 2) > 0 && (i - 2) < Maze::HEIGHT && j > 0 && j < Maze::WIDTH)
		output.emplace_back(std::make_pair(std::make_pair(i - 2, j), std::make_pair(i - 1, j)));
	if ((i + 2) > 0 && (i + 2) < Maze::WIDTH && grid_[i + 2][j] != Maze::Type::GROUND && (i + 2) > 0 && (i + 2) < Maze::HEIGHT && j > 0 && j < Maze::WIDTH)
		output.emplace_back(std::make_pair(std::make_pair(i + 2, j), std::make_pair(i + 1, j)));
	if ((j - 2) > 0 && (j - 2) < Maze::WIDTH && grid_[i][j - 2] != Maze::Type::GROUND && (j - 2) > 0 && (j - 2) < Maze::HEIGHT && i > 0 && i < Maze::WIDTH)
		output.emplace_back(std::make_pair(std::make_pair(i, j - 2), std::make_pair(i, j - 1)));
	if ((j + 2) > 0 && (j + 2) < Maze::WIDTH && grid_[i][j + 2] != Maze::Type::GROUND && (j + 2) > 0 && (j + 2) < Maze::HEIGHT && i > 0 && i < Maze::WIDTH)
		output.emplace_back(std::make_pair(std::make_pair(i, j + 2), std::make_pair(i, j + 1)));

	return output;

};

void Maze::renderPoints(const std::pair<int, int>& startPoint, const std::pair<int, int>& endPoint)
{
	// Rendering endPoint ans startPoint
	SDL_FRect rect = { float(startPoint.first), float(startPoint.second), Maze::SIZE, Maze::SIZE };
	/*
	SDL_SetRenderDrawColor(renderer_, 255, 0, 0, 255);
	SDL_RenderFillRect(renderer_, &rect);
	*/
	rect = { float(endPoint.first), float(endPoint.second), Maze::SIZE, Maze::SIZE };
	SDL_SetRenderDrawColor(renderer_, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer_, &rect);
}