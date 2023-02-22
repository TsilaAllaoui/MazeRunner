#include "ghost.h"

Ghost::Ghost(vector < vector < int >>tab)
{
	finished = false;
	for (int i = 0; i < LONG; i++)
		tmp.push_back(vector < int >(LARG));
	for (int i = 0; i < LONG; i++)
		for (int j = 0; j < LARG; j++)
			tmp[i][j] = tab[i][j];
	position.x = 16;
	position.y = 16;
}

vector < Point > Ghost::get_chemin()
{
	return chemin;
}

bool Ghost::check_finished()
{
	if (tmp[LONG - 2][LARG - 2] == 2)
		return true;
	else
		return false;
}

void Ghost::go_back(SDL_Surface * ecran, SDL_Rect * pos)
{
	int j = pos->x / 16, i = pos->y / 16;
	SDL_BlitSurface(sol, NULL, ecran, pos);
	chemin.pop_back();
	if (tmp[i - 1][j] == 2)
	{
		pos->y -= 16;
		tmp[i][j] = 1;
		return;
	}
    if (tmp[i + 1][j] == 2)
	{
		pos->y += 16;
		tmp[i][j] = 1;
		return;
	}
	if (tmp[i][j - 1] == 2)
	{
		pos->x -= 16;
		tmp[i][j] = 1;
		return;
	}
	if (tmp[i][j + 1] == 2)
	{
		pos->x += 16;
		tmp[i][j] = 1;
		return;
	}
	SDL_BlitSurface(pac_back, NULL, ecran, pos);
}

Red::Red(vector < vector < int >>tab):Ghost(tab)
{
	way = IMG_Load("./images/way_red.png");
	pac_haut = IMG_Load("./images/red_haut.png");
	pac_bas = IMG_Load("./images/red_bas.png");
	pac_gauche = IMG_Load("./images/red_gauche.png");
	pac_droite = IMG_Load("./images/red_droite.png");
	pac_back = IMG_Load("./images/red_back.png");
	sol = IMG_Load("./images/sol.png");
}

Pink::Pink(vector < vector < int >>tab):Ghost(tab)
{
	way = IMG_Load("./images/way_pink.png");
	pac_haut = IMG_Load("./images/pink_haut.png");
	pac_bas = IMG_Load("./images/pink_bas.png");
	pac_gauche = IMG_Load("./images/pink_gauche.png");
	pac_droite = IMG_Load("./images/pink_droite.png");
	pac_back = IMG_Load("./images/pink_back.png");
	sol = IMG_Load("./images/sol.png");
}

Yellow::Yellow(vector < vector < int >>tab):Ghost(tab)
{
	way = IMG_Load("./images/way_yellow.png");
	pac_haut = IMG_Load("./images/yellow_haut.png");
	pac_bas = IMG_Load("./images/yellow_bas.png");
	pac_gauche = IMG_Load("./images/yellow_gauche.png");
	pac_droite = IMG_Load("./images/yellow_droite.png");
	pac_back = IMG_Load("./images/yellow_back.png");
	sol = IMG_Load("./images/sol.png");
}

Blue::Blue(vector < vector < int >>tab):Ghost(tab)
{
	way = IMG_Load("./images/way_blue.png");
	pac_haut = IMG_Load("./images/blue_haut.png");
	pac_bas = IMG_Load("./images/blue_bas.png");
	pac_gauche = IMG_Load("./images/blue_gauche.png");
	pac_droite = IMG_Load("./images/blue_droite.png");
	pac_back = IMG_Load("./images/blue_back.png");
	sol = IMG_Load("./images/sol.png");
}

Green::Green(vector < vector < int >>tab):Ghost(tab)
{
	way = IMG_Load("./images/way_green.png");
	pac_haut = IMG_Load("./images/green_haut.png");
	pac_bas = IMG_Load("./images/green_bas.png");
	pac_gauche = IMG_Load("./images/green_gauche.png");
	pac_droite = IMG_Load("./images/green_droite.png");
	pac_back = IMG_Load("./images/green_back.png");
	sol = IMG_Load("./images/sol.png");
}

Black::Black(vector < vector < int >>tab):Ghost(tab)
{
	way = IMG_Load("./images/way_black.png");
	pac_haut = IMG_Load("./images/black_haut.png");
	pac_bas = IMG_Load("./images/black_bas.png");
	pac_gauche = IMG_Load("./images/black_gauche.png");
	pac_droite = IMG_Load("./images/black_droite.png");
	pac_back = IMG_Load("./images/black_back.png");
	sol = IMG_Load("./images/sol.png");
}

White::White(vector < vector < int >>tab):Ghost(tab)
{
	way = IMG_Load("./images/way_white.png");
	pac_haut = IMG_Load("./images/white_haut.png");
	pac_bas = IMG_Load("./images/white_bas.png");
	pac_gauche = IMG_Load("./images/white_gauche.png");
	pac_droite = IMG_Load("./images/white_droite.png");
	pac_back = IMG_Load("./images/white_back.png");
	sol = IMG_Load("./images/sol.png");
}

void Red::move(SDL_Surface * ecran)
{
	SDL_Rect *pos = &position;
	int i = pos->y / 16;
	int j = pos->x / 16;
	if (tmp[i - 1][j] != 0 && tmp[i + 1][j] != 0 && tmp[i][j - 1] != 0 && tmp[i][j + 1] != 0)
		go_back(ecran, pos);
	else
	{
		if (tmp[i + 1][j] == 0)
		{
			Point a;
			a.x = pos->x;
			a.y = pos->y;
			pos->y += 16;
			tmp[i + 1][j] = 2;
			tmp[i][j] = 2;
			chemin.push_back(a);
			SDL_BlitSurface(pac_bas, NULL, ecran, pos);
		}
		else if (tmp[i][j + 1] == 0)
		{
			Point a;
			a.x = pos->x;
			a.y = pos->y;
			pos->x += 16;
			tmp[i][j + 1] = 2;
			tmp[i][j] = 2;
			chemin.push_back(a);
			SDL_BlitSurface(pac_droite, NULL, ecran, pos);
		}
		else if (tmp[i][j - 1] == 0)
		{
			Point a;
			a.x = pos->x;
			a.y = pos->y;
			pos->x -= 16;
			tmp[i][j - 1] = 2;
			tmp[i][j] = 2;
			chemin.push_back(a);
			SDL_BlitSurface(pac_gauche, NULL, ecran, pos);
		}
		else if (tmp[i - 1][j] == 0)
		{
			Point a;
			a.x = pos->x;
			a.y = pos->y;
			pos->y -= 16;
			tmp[i - 1][j] = 2;
			tmp[i][j] = 2;
			chemin.push_back(a);
			SDL_BlitSurface(pac_bas, NULL, ecran, pos);
		}
		SDL_Rect position;
		for (int i = 0; i < chemin.size(); i++)
		{
			position.x = chemin[i].x;
			position.y = chemin[i].y;
			SDL_BlitSurface(way, NULL, ecran, &position);
		}
	}
	SDL_Flip(ecran);
}

void Pink::move(SDL_Surface * ecran)
{
	SDL_Rect *pos = &position;
	int i = pos->y / 16;
	int j = pos->x / 16;
	if (tmp[i - 1][j] != 0 && tmp[i + 1][j] != 0 && tmp[i][j - 1] != 0 && tmp[i][j + 1] != 0)
		go_back(ecran, pos);
	else
	{
		if (tmp[i][j + 1] == 0)
		{
			Point a;
			a.x = pos->x;
			a.y = pos->y;
			pos->x += 16;
			tmp[i][j + 1] = 2;
			tmp[i][j] = 2;
			chemin.push_back(a);
			SDL_BlitSurface(pac_droite, NULL, ecran, pos);
		}
		else if (tmp[i + 1][j] == 0)
		{
			Point a;
			a.x = pos->x;
			a.y = pos->y;
			pos->y += 16;
			tmp[i + 1][j] = 2;
			tmp[i][j] = 2;
			chemin.push_back(a);
			SDL_BlitSurface(pac_bas, NULL, ecran, pos);
		}
		else if (tmp[i][j - 1] == 0)
		{
			Point a;
			a.x = pos->x;
			a.y = pos->y;
			pos->x -= 16;
			tmp[i][j - 1] = 2;
			tmp[i][j] = 2;
			chemin.push_back(a);
			SDL_BlitSurface(pac_gauche, NULL, ecran, pos);
		}
		else if (tmp[i - 1][j] == 0)
		{
			Point a;
			a.x = pos->x;
			a.y = pos->y;
			pos->y -= 16;
			tmp[i - 1][j] = 2;
			tmp[i][j] = 2;
			chemin.push_back(a);
			SDL_BlitSurface(pac_bas, NULL, ecran, pos);
		}
		SDL_Rect position;
		for (int i = 0; i < chemin.size(); i++)
		{
			position.x = chemin[i].x;
			position.y = chemin[i].y;
			SDL_BlitSurface(way, NULL, ecran, &position);
		}
	}
	SDL_Flip(ecran);
}

void Yellow::move (SDL_Surface * ecran)
{
	SDL_Rect *pos = &position;
	int i = pos->y / 16;
	int j = pos->x / 16;
	if (tmp[i - 1][j] != 0 && tmp[i + 1][j] != 0 && tmp[i][j - 1] != 0 && tmp[i][j + 1] != 0)
		go_back(ecran, pos);
	else
	{
		if (tmp[i][j + 1] == 0)
		{
			Point a;
			a.x = pos->x;
			a.y = pos->y;
			pos->x += 16;
			tmp[i][j + 1] = 2;
			tmp[i][j] = 2;
			chemin.push_back(a);
			SDL_BlitSurface(pac_droite, NULL, ecran, pos);
		}
		else if (tmp[i - 1][j] == 0)
		{
			Point a;
			a.x = pos->x;
			a.y = pos->y;
			pos->y -= 16;
			tmp[i - 1][j] = 2;
			tmp[i][j] = 2;
			chemin.push_back(a);
			SDL_BlitSurface(pac_bas, NULL, ecran, pos);
		}
		else if (tmp[i][j - 1] == 0)
		{
			Point a;
			a.x = pos->x;
			a.y = pos->y;
			pos->x -= 16;
			tmp[i][j - 1] = 2;
			tmp[i][j] = 2;
			chemin.push_back(a);
			SDL_BlitSurface(pac_gauche, NULL, ecran, pos);
		}
		else if (tmp[i + 1][j] == 0)
		{
			Point a;
			a.x = pos->x;
			a.y = pos->y;
			pos->y += 16;
			tmp[i + 1][j] = 2;
			tmp[i][j] = 2;
			chemin.push_back(a);
			SDL_BlitSurface(pac_bas, NULL, ecran, pos);
		}
		SDL_Rect position;
		for (int i = 0; i < chemin.size(); i++)
		{
			position.x = chemin[i].x;
			position.y = chemin[i].y;
			SDL_BlitSurface(way, NULL, ecran, &position);
		}
	}
	SDL_Flip(ecran);
}

void Blue::move(SDL_Surface * ecran)
{
	SDL_Rect *pos = &position;
	int i = pos->y / 16;
	int j = pos->x / 16;
	if (tmp[i - 1][j] != 0 && tmp[i + 1][j] != 0 && tmp[i][j - 1] != 0 && tmp[i][j + 1] != 0)
		go_back(ecran, pos);
	else
	{
		if (tmp[i][j + 1] == 0)
		{
			Point a;
			a.x = pos->x;
			a.y = pos->y;
			pos->x += 16;
			tmp[i][j + 1] = 2;
			tmp[i][j] = 2;
			chemin.push_back(a);
			SDL_BlitSurface(pac_droite, NULL, ecran, pos);
		}
		else if (tmp[i + 1][j] == 0)
		{
			Point a;
			a.x = pos->x;
			a.y = pos->y;
			pos->y += 16;
			tmp[i + 1][j] = 2;
			tmp[i][j] = 2;
			chemin.push_back(a);
			SDL_BlitSurface(pac_bas, NULL, ecran, pos);
		}
		else if (tmp[i - 1][j] == 0)
		{
			Point a;
			a.x = pos->x;
			a.y = pos->y;
			pos->y -= 16;
			tmp[i - 1][j] = 2;
			tmp[i][j] = 2;
			chemin.push_back(a);
			SDL_BlitSurface(pac_bas, NULL, ecran, pos);
		}
		else if (tmp[i][j - 1] == 0)
		{
			Point a;
			a.x = pos->x;
			a.y = pos->y;
			pos->x -= 16;
			tmp[i][j - 1] = 2;
			tmp[i][j] = 2;
			chemin.push_back(a);
			SDL_BlitSurface(pac_gauche, NULL, ecran, pos);
		}
		SDL_Rect position;
		for (int i = 0; i < chemin.size(); i++)
		{
			position.x = chemin[i].x;
			position.y = chemin[i].y;
			SDL_BlitSurface(way, NULL, ecran, &position);
		}
	}
	SDL_Flip(ecran);
}

void Green::move(SDL_Surface * ecran)
{
	SDL_Rect *pos = &position;
	int i = pos->y / 16;
	int j = pos->x / 16;
	if (tmp[i - 1][j] != 0 && tmp[i + 1][j] != 0 && tmp[i][j - 1] != 0 && tmp[i][j + 1] != 0)
		go_back(ecran, pos);
	else
	{
		if (tmp[i + 1][j] == 0)
		{
			Point a;
			a.x = pos->x;
			a.y = pos->y;
			pos->y += 16;
			tmp[i + 1][j] = 2;
			tmp[i][j] = 2;
			chemin.push_back(a);
			SDL_BlitSurface(pac_bas, NULL, ecran, pos);
		}
		else if (tmp[i][j + 1] == 0)
		{
			Point a;
			a.x = pos->x;
			a.y = pos->y;
			pos->x += 16;
			tmp[i][j + 1] = 2;
			tmp[i][j] = 2;
			chemin.push_back(a);
			SDL_BlitSurface(pac_droite, NULL, ecran, pos);
		}
		else if (tmp[i - 1][j] == 0)
		{
			Point a;
			a.x = pos->x;
			a.y = pos->y;
			pos->y -= 16;
			tmp[i - 1][j] = 2;
			tmp[i][j] = 2;
			chemin.push_back(a);
			SDL_BlitSurface(pac_bas, NULL, ecran, pos);
		}
		else if (tmp[i][j - 1] == 0)
		{
			Point a;
			a.x = pos->x;
			a.y = pos->y;
			pos->x -= 16;
			tmp[i][j - 1] = 2;
			tmp[i][j] = 2;
			chemin.push_back(a);
			SDL_BlitSurface(pac_gauche, NULL, ecran, pos);
		}
		SDL_Rect position;
		for (int i = 0; i < chemin.size(); i++)
		{
			position.x = chemin[i].x;
			position.y = chemin[i].y;
			SDL_BlitSurface(way, NULL, ecran, &position);
		}
	}
	SDL_Flip(ecran);
}

void Black::move(SDL_Surface * ecran)
{
	SDL_Rect *pos = &position;
	int i = pos->y / 16;
	int j = pos->x / 16;
	if (tmp[i - 1][j] != 0 && tmp[i + 1][j] != 0 && tmp[i][j - 1] != 0 && tmp[i][j + 1] != 0)
		go_back(ecran, pos);
	else
	{
		if (tmp[i][j + 1] == 0)
		{
			Point a;
			a.x = pos->x;
			a.y = pos->y;
			pos->x += 16;
			tmp[i][j + 1] = 2;
			tmp[i][j] = 2;
			chemin.push_back(a);
			SDL_BlitSurface(pac_droite, NULL, ecran, pos);
		}
		else if (tmp[i - 1][j] == 0)
		{
			Point a;
			a.x = pos->x;
			a.y = pos->y;
			pos->y -= 16;
			tmp[i - 1][j] = 2;
			tmp[i][j] = 2;
			chemin.push_back(a);
			SDL_BlitSurface(pac_bas, NULL, ecran, pos);
		}
		else if (tmp[i + 1][j] == 0)
		{
			Point a;
			a.x = pos->x;
			a.y = pos->y;
			pos->y += 16;
			tmp[i + 1][j] = 2;
			tmp[i][j] = 2;
			chemin.push_back(a);
			SDL_BlitSurface(pac_bas, NULL, ecran, pos);
		}
		else if (tmp[i][j - 1] == 0)
		{
			Point a;
			a.x = pos->x;
			a.y = pos->y;
			pos->x -= 16;
			tmp[i][j - 1] = 2;
			tmp[i][j] = 2;
			chemin.push_back(a);
			SDL_BlitSurface(pac_gauche, NULL, ecran, pos);
		}
		SDL_Rect position;
		for (int i = 0; i < chemin.size(); i++)
		{
			position.x = chemin[i].x;
			position.y = chemin[i].y;
			SDL_BlitSurface(way, NULL, ecran, &position);
		}
	}
	SDL_Flip(ecran);
}

void White::move(SDL_Surface * ecran)
{
	SDL_Rect *pos = &position;
	int i = pos->y / 16;
	int j = pos->x / 16;
	if (tmp[i - 1][j] != 0 && tmp[i + 1][j] != 0 && tmp[i][j - 1] != 0 && tmp[i][j + 1] != 0)
		go_back(ecran, pos);
	else
	{
		if (tmp[i + 1][j] == 0)
		{
			Point a;
			a.x = pos->x;
			a.y = pos->y;
			pos->y += 16;
			tmp[i + 1][j] = 2;
			tmp[i][j] = 2;
			chemin.push_back(a);
			SDL_BlitSurface(pac_bas, NULL, ecran, pos);
		}
		else if (tmp[i][j - 1] == 0)
		{
			Point a;
			a.x = pos->x;
			a.y = pos->y;
			pos->x -= 16;
			tmp[i][j - 1] = 2;
			tmp[i][j] = 2;
			chemin.push_back(a);
			SDL_BlitSurface(pac_gauche, NULL, ecran, pos);
		}
		else if (tmp[i][j + 1] == 0)
		{
			Point a;
			a.x = pos->x;
			a.y = pos->y;
			pos->x += 16;
			tmp[i][j + 1] = 2;
			tmp[i][j] = 2;
			chemin.push_back(a);
			SDL_BlitSurface(pac_droite, NULL, ecran, pos);
		}
		else if (tmp[i - 1][j] == 0)
		{
			Point a;
			a.x = pos->x;
			a.y = pos->y;
			pos->y -= 16;
			tmp[i - 1][j] = 2;
			tmp[i][j] = 2;
			chemin.push_back(a);
			SDL_BlitSurface(pac_bas, NULL, ecran, pos);
		}
		SDL_Rect position;
		for (int i = 0; i < chemin.size(); i++)
		{
			position.x = chemin[i].x;
			position.y = chemin[i].y;
			SDL_BlitSurface(way, NULL, ecran, &position);
		}
	}
	SDL_Flip(ecran);
}
