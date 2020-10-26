#ifndef FONCTION_H
#define FONCTION_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <vector>
#include "defs.h"
#include "ghost.h"

using namespace std;

void move(vector < vector <int> > &tab);
int fin_jeu(vector < vector <int> > tab);
int check_end(vector < Point > chemin, vector < Point > chemin1, int i, int j);
void affiche_solution(SDL_Surface *ecran,Red red,Pink pink,Yellow yellow,Blue blue,Green green,Black black,White white);

#endif
