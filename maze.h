#ifndef MAZE_H
#define MAZE_H


#include "defs.h"
#include "ghost.h"
#include <vector>
#include <ctime>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <cstdlib>

using namespace std;

void move();
int fin_jeu();
int check_end(vector < Point > chemin, vector < Point > chemin1, int i, int j);

class Maze
{
    private:
        SDL_Surface *ecran;
        vector < vector < int > >tab;
    public:
        Maze();
        void run();
        void update();
        SDL_Surface * get_screen();
        vector < vector < int > > get_tab();
};

#endif
