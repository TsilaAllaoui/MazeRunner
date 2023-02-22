#include "fonctions.h"
#include "defs.h"
#include "ghost.h"

void move(vector < vector <int> > &tab)
{
    for (int i = 1; i < LONG - 1; i += 2)
    {
        for (int j = 1; j < LARG - 1; j += 2)
        {
            int direction;
            if (tab[i][j] == 0)
            {
                direction = rand() % 4;
                if (direction == 0)
                {
                    if (i - 2 > 0)
                        if (tab[i - 2][j] == 2)
                        {
                            tab[i - 2][j] = 0;
                            tab[i - 1][j] = 0;
                        }
                }
                else if (direction == 1)
                {
                    if (i + 2 < LONG)
                        if (tab[i + 2][j] == 2)
                        {
                            tab[i + 2][j] = 0;
                            tab[i + 1][j] = 0;
                        }
                }
                else if (direction == 2)
                {
                    if (j - 2 > 0)
                        if (tab[i][j - 2] == 2)
                        {
                            tab[i][j - 2] = 0;
                            tab[i][j - 1] = 0;
                        }
                }
                else if (direction == 3)
                {
                    if (j + 2 < LARG)
                        if (tab[i][j + 2] == 2)
                        {

                            tab[i][j + 2] = 0;
                            tab[i][j + 1] = 0;
                        }
                }
            }
        }
    }
}

int fin_jeu(vector < vector <int> > tab)
{
    for (int i = 0; i < LONG; i++)
    {
        for (int j = 0; j < LARG; j++)
            if (tab[i][j] == 2)
                return 0;
    }
    return 1;
}

int check_end(vector < Point > chemin, vector < Point > chemin1, int i, int j)
{
    for (int k = 0; k < chemin.size(); k++)
    {
        if (chemin[k].x == i && chemin[k].y == j)
            return 1;
    }
    return 0;
}

void affiche_solution(SDL_Surface *ecran,Red red,Pink pink,Yellow yellow,Blue blue,Green green,Black black,White white)
{
    SDL_Surface *way, *way1,*way2,*way3,*way4,*way5,*way6,*arrow, *pac_fin;
    arrow = IMG_Load("./images/arrow.bmp");
    way = IMG_Load("./images/way_red.png");
    way1 = IMG_Load("./images/way_pink.png");
    way2 = IMG_Load("./images/way_yellow.png");
    way3 = IMG_Load("./images/way_blue.png");
    way4 = IMG_Load("./images/way_green.png");
    way5 = IMG_Load("./images/way_black.png");
    way6 = IMG_Load("./images/way_white.png");
    SDL_SetColorKey(arrow, SDL_SRCCOLORKEY, SDL_MapRGB(arrow->format, 255, 255, 255));
    SDL_Rect position;
    position.x = 0;
    position.y = 16;
    SDL_BlitSurface(arrow, NULL, ecran, &position);
    if (red.check_finished())
    {
        vector <Point> chemin = red.get_chemin();
        for (int i = 0; i < chemin.size(); i++)
        {
            position.x = chemin[i].x;
            position.y = chemin[i].y;
            SDL_BlitSurface(way, NULL, ecran, &position);
            position.x = (LONG - 2) * 16;
            position.y = (LARG - 2) * 16;
            SDL_BlitSurface(IMG_Load("./images/red_back.png"), NULL, ecran, &position);
        }
    }
    else if (pink.check_finished())
    {
        vector <Point> chemin = pink.get_chemin();
        for (int i = 0; i < chemin.size(); i++)
        {
            position.x = chemin[i].x;
            position.y = chemin[i].y;
            SDL_BlitSurface(way1, NULL, ecran, &position);
            position.x = (LONG - 2) * 16;
            position.y = (LARG - 2) * 16;
            SDL_BlitSurface(IMG_Load("./images/pink_back.png"), NULL, ecran, &position);
        }
    }
    else if (yellow.check_finished())
    {
        vector <Point> chemin = yellow.get_chemin();
        for (int i = 0; i < chemin.size(); i++)
        {
            position.x = chemin[i].x;
            position.y = chemin[i].y;
            SDL_BlitSurface(way2, NULL, ecran, &position);
            position.x = (LONG - 2) * 16;
            position.y = (LARG - 2) * 16;
            SDL_BlitSurface(IMG_Load("./images/yellow_back.png"), NULL, ecran, &position);
        }
    }
    else if (blue.check_finished())
    {
        vector <Point> chemin = blue.get_chemin();
        for (int i = 0; i < chemin.size(); i++)
        {
            position.x = chemin[i].x;
            position.y = chemin[i].y;
            SDL_BlitSurface(way3, NULL, ecran, &position);
            position.x = (LONG - 2) * 16;
            position.y = (LARG - 2) * 16;
            SDL_BlitSurface(IMG_Load("./images/blue_back.png"), NULL, ecran, &position);
        }
    }
    else if (green.check_finished())
    {
        vector <Point> chemin = green.get_chemin();
        for (int i = 0; i < chemin.size(); i++)
        {
            position.x = chemin[i].x;
            position.y = chemin[i].y;
            SDL_BlitSurface(way4, NULL, ecran, &position);
            position.x = (LONG - 2) * 16;
            position.y = (LARG - 2) * 16;
            SDL_BlitSurface(IMG_Load("./images/green_back.png"), NULL, ecran, &position);
        }
    }
    else if (black.check_finished())
    {
        vector <Point> chemin = black.get_chemin();
        for (int i = 0; i < chemin.size(); i++)
        {
            position.x = chemin[i].x;
            position.y = chemin[i].y;
            SDL_BlitSurface(way5, NULL, ecran, &position);
            position.x = (LONG - 2) * 16;
            position.y = (LARG - 2) * 16;
            SDL_BlitSurface(IMG_Load("./images/black_back.png"), NULL, ecran, &position);
        }
    }
    else if (white.check_finished())
    {
        vector <Point> chemin = white.get_chemin();
        for (int i = 0; i < chemin.size(); i++)
        {
            position.x = chemin[i].x;
            position.y = chemin[i].y;
            SDL_BlitSurface(way6, NULL, ecran, &position);
            position.x = (LONG - 2) * 16;
            position.y = (LARG - 2) * 16;
            SDL_BlitSurface(IMG_Load("./images/white_back.png"), NULL, ecran, &position);
        }
    }
    position.x = 16 * (LONG - 1);
    position.y = 16 * (LARG - 2);
    SDL_BlitSurface(arrow, NULL, ecran, &position);
    SDL_Flip(ecran);
}

