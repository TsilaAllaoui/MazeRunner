#include "maze.h"
#include "fonctions.h"

Maze::Maze()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	ecran = SDL_SetVideoMode(LONG * 16, LARG * 16, 32, SDL_SWSURFACE);
	srand(time(0));
}

void Maze::run()
{
	vector < vector < int >>tmp, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6;
	for (int i = 0; i < LONG; i++)
	{
		tab.push_back(vector < int >(LARG));
		tmp.push_back(vector < int >(LARG));
		tmp1.push_back(vector < int >(LARG));
		tmp2.push_back(vector < int >(LARG));
		tmp3.push_back(vector < int >(LARG));
		tmp4.push_back(vector < int >(LARG));
		tmp5.push_back(vector < int >(LARG));
		tmp6.push_back(vector < int >(LARG));
	}

	for (int i = 0; i < LONG; i++)
	{
		for (int j = 0; j < LARG; j++)
			if (i % 2 == 0 || i == 0 || i == LONG - 1 || j % 2 == 0 || j == 0 || j == LARG)
				tab[i][j] = 1;
			else
				tab[i][j] = 2;
	}
	int x, y;
	do
		x = (rand() % LONG - 2) + 2;
	while (x % 2 == 0);
	do
		y = (rand() % LARG - 2) + 2;
	while (y % 2 == 0);
	tab[x][y] = 0;
	int fin = 1;
	while (fin)
	{
		move(tab);
		if (fin_jeu(tab) == 1)
			fin = 0;
		update();
		SDL_Flip(ecran);
	}
	Red red(tab);
	Pink pink(tab);
	Yellow yellow(tab);
	Blue blue(tab);
	Green green(tab);
	White white(tab);
	Black black(tab);
	while (!red.check_finished() && !pink.check_finished() && !yellow.check_finished()
		   && !blue.check_finished() && !green.check_finished() && !white.check_finished()
		   && !black.check_finished())
	{
		red.move(ecran);
		/*pink.move(ecran);
		yellow.move(ecran);
		blue.move(ecran);
		green.move(ecran);
		white.move(ecran);
		black.move(ecran);*/
	}
	update();
	affiche_solution(ecran, red, pink, yellow, blue, green, black, white);
	SDL_Delay(100000);
}

void Maze::update()
{
	SDL_Surface *mur, *sol;
	mur = IMG_Load("./images/mur.png");	// ("/sdcard/Prim'sAlgorithm/prims/images/mur.png");
	sol = IMG_Load("./images/sol.png");	// ("/sdcard/Prim'sAlgorithm/prims/images/sol.png");
	for (int i = 0; i < LONG; i++)
	{
		for (int j = 0; j < LARG; j++)
		{
			SDL_Rect pos;
			pos.x = j * 16;
			pos.y = i * 16;
			if (tab[i][j] == 1)
				SDL_BlitSurface(mur, NULL, ecran, &pos);
			if (tab[i][j] == 0)	// || tab[i][j] == 3)
				SDL_BlitSurface(sol, NULL, ecran, &pos);
		}
	}
}

SDL_Surface *Maze::get_screen()
{
	return ecran;
}

vector < vector < int >>Maze::get_tab()
{
	return tab;
}
