#include <SDL3/SDL_image.h>
#include <SDL3/SDL.h>

#include "maze.h"

int main(int argc, char *argv[])
{
	Maze(Maze::Algorithm::BFS, true).run();
    return 0;
}
