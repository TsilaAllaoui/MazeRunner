#pragma once

#include <SDL3/SDL.h>
#include <vector>

// Point class
typedef struct Point
{
	int x, y;
} Point;

#define LONG 109
#define LARG 109

//void move();
//int fin_jeu();
//int check_end(vector < Point > chemin, vector < Point > chemin1, int i, int j);

// Maze class
class Maze
{
    private:
		// The main window
        SDL_Window* window_;

		// The window renderer
		SDL_Renderer* renderer_;

		// The grid representing the board of the maze
        std::vector<std::vector<int>> grid_;

		// Dimensions of the maze
		static const int WIDTH, HEIGHT, SIZE;

		// Useful enumeration
		enum Type { WALL, GROUND };

		// Useful enumration for the algorithm type that will be used in the generation of the maze
		enum Algorithm { BFS };
		
		// Textures of Wall and Ground
		static SDL_Texture* textures[2];
    public:

		// Constructor and destructor
		Maze();
		~Maze();

		/**
		* \brief Run the generation of the maze and the solver
		* \return
		*/
        void run();

		/**
		* \brief Update the visual of the maze
		* \return
		*/
        void update();

		/**
		* \brief Generate the maze using a given algorithm
		* \param algorithm The algorithm type that will be used in the generation of the maze
		* \return
		*/
		void generate(const Algorithm &algorithm);
};
