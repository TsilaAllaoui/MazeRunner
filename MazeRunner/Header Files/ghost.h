#ifndef GHOST_H
#define GHOST_H

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "defs.h"
#include <vector>

using namespace std;

class Ghost
{
protected:
    bool finished;
    SDL_Surface *pac_haut, *pac_bas, *pac_droite, *pac_gauche, *pac_back,*pac_actu, *way, *sol;
    vector < vector < int > >tmp;
    vector < Point > chemin;
    SDL_Rect position;
public:
    Ghost(vector < vector <int> >tab);
    bool check_finished();
    vector < Point > get_chemin();
    void go_back(SDL_Surface *ecran,SDL_Rect *pos);
};

class Red : public Ghost
{
public:
    Red(vector < vector <int> >tab);
    void move(SDL_Surface *ecran);
};

class Blue : public Ghost
{
public:
    Blue(vector < vector <int> >tab);
    void move(SDL_Surface *ecran);
};

class Yellow : public Ghost
{
public:
    Yellow(vector < vector <int> >tab);
    void move(SDL_Surface *ecran);
};

class Pink : public Ghost
{
public:
    Pink(vector < vector <int> >tab);
    void move(SDL_Surface *ecran);
};

class Black : public Ghost
{
public:
    Black(vector < vector <int> >tab);
    void move(SDL_Surface *ecran);
};

class White : public Ghost
{
public:
    White(vector < vector <int> >tab);
    void move(SDL_Surface *ecran);
};

class Green : public Ghost
{
public:
    Green(vector < vector <int> >tab);
    void move(SDL_Surface *ecran);
};

#endif // GHOST_H
