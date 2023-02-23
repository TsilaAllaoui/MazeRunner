#include <SDL3/SDL_image.h>
#include <SDL3/SDL.h>

#include "maze.h"

int main(int argc, char *argv[])
{
	Maze(Maze::Algorithm::RandomizedPrim, true).run();
	Maze(Maze::Algorithm::BFS).run();
    return 0;
}
