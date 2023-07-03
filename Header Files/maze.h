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

		
		// Textures of Wall and Ground
		static SDL_Texture* textures_[2];

		// The current position of the current cell
		SDL_FRect currCellPosition_;

		// If we need to see trail of the current cell when backtracking
		bool useTrail_;


    public:
		// Useful enumeration
		//enum Type { WALL, GROUND };

		// Useful enumration for the algorithm type that will be used in the generation of the maze
		enum Algorithm { BFS, RandomizedPrim };

		// For the direction
		enum Direction{ UP, DOWN, LEFT, RIGTH };

		// The algorithm that will be used to generate the maze
		Algorithm algorithm_;

		//  and destructor
		/**
		* \brief Constructor
		* \param algorithm The algorithm that will be used to generate the maze 
		* \param isMonochrome To set true if we want a monochrome version of the maze insated of using sprites
		* \return
		*/
		Maze(const Algorithm &algorithm, const bool &isMonochrome = false);

		// Destructor
		~Maze();

		/**
		* \brief Run the generation of the maze and the solver
		* \return
		*/
        void run();

		/**
		* \brief Update the visual of the maze
		* \param srawCurrentCell If we want to draw current cell
		* \return
		*/
        void update(const bool &drawCurrentCell = true);

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

		/**
		* \brief Get all neighbors of a cell at given position
		* \param i The x coordinate
		* \param j The y coordinate
		* \return 
		*/
		std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> getNeighborsOfCell(int i, int j);
		
		/**
		* \brief Render start and end point on the maze
		* \param startPoint The start point
		* \param endPoint The end Point
		* \return
		*/
		void renderPoints(const std::pair<int, int>& startPoint, const std::pair<int, int>& endPoint);
};
