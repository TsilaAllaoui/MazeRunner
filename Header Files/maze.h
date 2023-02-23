#pragma once

#include <SDL3/SDL.h>
#include <vector>

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
		
		// Textures of Wall and Ground
		static SDL_Texture* textures_[2];

		// The current position of the current cell
		SDL_FRect currCellPosition_;

		// If we need to see trail of the current cell when backtracking
		bool useTrail_;


    public:

		// Useful enumration for the algorithm type that will be used in the generation of the maze
		enum Algorithm { BFS, RandomizedPrim };

		// The algorithm that will be used to generate the maze
		Algorithm algorithm_;

		// Constructor and destructor
		Maze(const Algorithm &algorithm);
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
		* \brief Generate the maze using BFS Algorithm
		* \param trailOn if we want ot see the trail of the current cell when backtracking
		* \return
		*/
		void generateBFS(const bool &trailOn = true);

		/**
		* \brief Generate the maze using Randomized Prim's Algorithm
		* \return
		*/
		void generateRandomizedPrim();
};
