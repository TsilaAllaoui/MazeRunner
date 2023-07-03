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
	// Get possible neighbor
	auto neighbors = getNeighbors();

	// If no valid neighbor
	if (neighbors.size() == 0)
	{
		stack_.pop_back();
		pos_.y = stack_.back().first * Runner::SIZE;
		pos_.x = stack_.back().second * Runner::SIZE;
	}

	else
	{
		// Select a random cell in neighbor
		auto index = rand() % (neighbors.size());
		stack_.push_back(std::make_pair(pos_.y / Runner::SIZE, pos_.x / Runner::SIZE));
		visited_.emplace_back(std::make_pair(pos_.y / Runner::SIZE, pos_.x / Runner::SIZE));

		pos_.y = neighbors[index].first * Runner::SIZE;
		pos_.x = neighbors[index].second * Runner::SIZE;
	}
	
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

	auto j = pos_.x / Runner::SIZE;
	auto i = pos_.y / Runner::SIZE;

	if ( (i + 1) > 0 && ((i + 1) < grid_[0].size() - 1))
		if (grid_[i + 1][j] == Runner::Type::GROUND)
			neighbors.emplace_back(std::make_pair(i + 1, j));
	if ((i - 1) > 0 && ((i - 1) < grid_[0].size() - 1))
		if (grid_[i - 1][j] == Runner::Type::GROUND)
			neighbors.emplace_back(std::make_pair(i - 1, j));
	if ((j + 1) > 0 && ((j + 1) < grid_.size() - 1))
		if (grid_[i][j + 1] == Runner::Type::GROUND)
			neighbors.emplace_back(std::make_pair(i, j + 1));
	if ((j - 1) > 0 && ((j - 1) < grid_.size() - 1))
		if (grid_[i][j - 1] == Runner::Type::GROUND)
			neighbors.emplace_back(std::make_pair(i, j - 1));

	// Temporary list to stock valid neighbor
	std::vector<std::pair<int, int>> tmp;

	// Stocking only valid neighbor that are not in the visisted cells list
	for (int i = 0; i < neighbors.size(); i++)
	{
		std::pair<int, int> n = neighbors[i];
		auto res = std::find(visited_.begin(), visited_.end(), n);
		if (res == visited_.end())
			tmp.emplace_back(n);
	}

	return tmp;
}
