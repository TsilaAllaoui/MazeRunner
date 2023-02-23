#include <SDL3/SDL_image.h>
#include <stack>

#include "runner.h"

const int Runner::SIZE = 16;

Runner::Runner(const Color& color, const std::pair<int, int>& pos, const std::vector<std::vector<int>>& grid, SDL_Renderer* renderer, const bool& useMonochrome)
{
	// Assigning the renderer
	renderer_ = renderer;

	// Loading texture if is monochrome
	if (useMonochrome)
	{
		SDL_Surface *surface = SDL_CreateSurface(Runner::SIZE, Runner::SIZE, SDL_PixelFormatEnum::SDL_PIXELFORMAT_RGBA8888);
		SDL_FillSurfaceRect(surface, NULL, 0xFF0000FF);
		texture_ = SDL_CreateTextureFromSurface(renderer_, surface);
	}

	else texture_ = IMG_LoadTexture(renderer_, "./images/runner.png");

	// Setting up position
	pos_ = { float(pos.first), float(pos.second), Runner::SIZE, Runner::SIZE };

	// Assigning the grid
	grid_ = grid;
}

Runner::~Runner()
{
	// Freeing memory
	SDL_DestroyTexture(texture_);
}

void Runner::move()
{
	auto neighbors = getNeighbors();

	if (neighbors.size() == 0)
	{
		stack_.pop();
		render();
		return;
	}

	auto index = rand() % (neighbors.size());

	/*for (auto& cell : neighbors)
		stack_.emplace(std::make_pair(cell.first / Runner::SIZE, cell.second / Runner::SIZE));*/
	stack_.emplace(std::make_pair( pos_.x / Runner::SIZE, pos_.y / Runner::SIZE));
	
 	pos_.x = neighbors[index].first * Runner::SIZE;
	pos_.y = neighbors[index].second * Runner::SIZE;


	// Render the runner
	render();
}

void Runner::render()
{
	SDL_RenderTexture(renderer_, texture_, NULL, &pos_);
}

bool Runner::isArrived(const std::pair<int, int>& endPoint)
{
	return (pos_.x == endPoint.first && pos_.y == endPoint.second);
}

std::vector<std::pair<int, int>> Runner::getNeighbors()
{
	std::vector<std::pair<int, int>> neighbors;

	auto x = pos_.x / Runner::SIZE;
	auto y = pos_.y / Runner::SIZE;

	if ( (x + 1) > 0 && ((x + 1) < grid_.size() - 1) && grid_[x + 1][y] == Runner::Type::GROUND)
		neighbors.emplace_back(std::make_pair(x + 1, y));
	if ((x - 1) > 0 && ((x - 1) < grid_.size() - 1) && grid_[x - 1][y] == Runner::Type::GROUND)
		neighbors.emplace_back(std::make_pair(x - 1, y));
	if ((y + 1) > 0 && ((y + 1) < grid_[0].size() - 1) && grid_[x][y + 1] == Runner::Type::GROUND)
		neighbors.emplace_back(std::make_pair(x, y + 1));
	if ((y - 1) > 0 && ((y - 1) < grid_.size() - 1) && grid_[x][y - 1] == Runner::Type::GROUND)
		neighbors.emplace_back(std::make_pair(x, y - 1));

	auto s = stack_;
	for (int i = 0; i < neighbors.size(); i++)
	{
		while (!s.empty())
		{
			if (s.top() == neighbors[i])
				neighbors.erase(neighbors.begin() + i);
			s.pop();
		}
	}

	/*auto s = stack_;
	while (!s.empty())
	{
		for (int i = 0; i < neighbors.size(); i++)
		{
			if (s.top() == neighbors[i])
				neighbors.erase(neighbors.begin() + i);
		}
		s.pop();
	}*/
	return neighbors;
}
