#pragma once

#include <SDL3/SDL.h>
#include <vector>
#include <deque>

// Maze Runner class
class Runner
{
	private:
		// The renderer
		SDL_Renderer* renderer_;

		// The texture of the runner
		SDL_Texture* texture_;

		// The position of the runner
		SDL_FRect pos_;

		// The maze grid to search solution for
		std::vector<std::vector<int>> grid_;

		// The stack to backtrack
		std::deque<std::pair<int, int>> stack_;

		// For retaining visited cells
		std::vector<std::pair<int, int>> visited_;

	public:

		// Useful enumeration
		enum Type { WALL, GROUND };

		// Useful enumeration
		enum Color {RED, GREEN, BLUE};

		// For the direction
		enum Direction { UP, DOWN, LEFT, RIGTH };

		// The size of the runner
		static const int SIZE;
		
		/**
		* \brief Constructor
		* \param color The color to be assigned to the runner
		* \param pos The starting position where to place the runner
		* \param grid The grid to search solution for
		* \param isMonochrome If we want to use simple color instead of sprite
		* \param renderer The renderer
		* \return
		*/
		Runner(const Color& color, const std::pair<int,int>& pos,const std::vector<std::vector<int>>& grid, SDL_Renderer* renderer, const bool& useMonochrome = true);

		/**
		* \brief Destructor
		* \return
		*/
		~Runner();

		/**
		* \brief Move the runner in the maze
		* \return
		*/
		void move();

		/**
		* \brief Render the runner in the maze
		* \return
		*/
		void render();

		/**
		* \brief Return true if the runner has arrived at destination
		* \param endPoint The final destination of the runner
		* \return
		*/
		bool isArrived(const std::pair<int, int>& endPoint);


		/**
		* \brief Get all neighbors of the runner
		* \return
		*/
		std::vector<std::pair<int, int>> getNeighbors();
};

