#include <SDL3/SDL_image.h>

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
}

Runner::~Runner()
{
	// Freeing memory
	SDL_DestroyTexture(texture_);
}

void Runner::move()
{

}

void Runner::render()
{
	SDL_RenderTexture(renderer_, texture_, NULL, &pos_);
}

bool Runner::isArrived(const std::pair<int, int>& endPoint)
{
	return (pos_.x == endPoint.first && pos_.y == endPoint.second);
}
