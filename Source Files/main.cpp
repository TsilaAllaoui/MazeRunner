#include <SDL3/SDL_image.h>
#include <SDL3/SDL.h>
#include <string>

#include "maze.h"

int main(int argc, char *argv[])
{
	/* The algorithm that will be used to generate the maze
	 The algorithm that can be used:
		- BFS
		- Randomized Prim's Algorithm

	0 : For BFS
	1 : For RPA
	*/
	Maze::Algorithm algorithm = Maze::Algorithm::RandomizedPrim;

	if (argc == 2)
	{
		if (argv[1] == "0")
			algorithm = Maze::Algorithm::BFS;
	} 

	// Running the maze generation and solve it
	Maze(algorithm, true).run();
    return 0;
}
