#include "SDL.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <string.h>
#include <ctime>


struct Player
{
	int x, y;
};
struct Werb
{
	int jek = 0, jek1 = 1, jek2 = 100, jek3 = 100;
};

void DrawPlayer(Player player, SDL_Window* window,
	SDL_Renderer* renderer)
{
	SDL_SetRenderDrawColor(renderer, 80, 50, 50, 0);


	SDL_SetRenderDrawColor(renderer, 50, 50, 100, 0);
	SDL_Rect rect2 = { player.x * 35, player.y * 35, 35, 35 };
	SDL_RenderFillRect(renderer, &rect2);
}




// OneStadia(int a, int b, int TWOmass[20][20], SDL_Renderer* renderer, SDL_Rect rec, SDL_Surface* myImage, SDL_Surface* myImage2, int qw, int wq)
void Output_To_Screen(Player player, Werb werb, SDL_Window* window,
	SDL_Renderer* renderer, int TWOmass[100][100])
{
	SDL_SetRenderDrawColor(renderer, 250, 0, 0, 0);
	SDL_RenderClear(renderer);

	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			if (TWOmass[i][j] == 1)
			{
				SDL_SetRenderDrawColor(renderer, 250, 0, 0, 0);
				SDL_Rect rect2 = { i * 35,j * 35,35,35 };
				SDL_RenderFillRect(renderer, &rect2);

			}


			if (TWOmass[i][j] == 0)
			{
				SDL_SetRenderDrawColor(renderer, 0, 250, 0, 0);
				SDL_Rect rect2 = { i * 35,j * 35,35,35 };
				SDL_RenderFillRect(renderer, &rect2);

			}
		}

	}

	DrawPlayer(player, window, renderer);
	SDL_RenderPresent(renderer);
}



void Rand(int TWOmass[100][100], int A, int B)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			TWOmass[i][j] = rand() % (B - A + 1) + A;
		}
	}
}




int main(int arcg, char** argv) {
	setlocale(LC_ALL, "Russian");
	const int m = 100;
	const int s = 100;
	//int TWOmass[m][m];
	int razmass[2];
	int A = 0, B = 1;

	Player r = { 17,0 };
	Werb e;

	int map[m][m] = {
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,},
	{1,0,1,0,0,1,0,1,0,0,0,1,1,1,1,0,0,0,0,1,},
	{1,0,1,1,0,1,0,1,0,1,0,0,0,0,1,0,1,1,0,1,},
	{1,0,0,0,0,0,0,1,0,1,1,1,1,0,1,0,0,1,0,1,},
	{1,1,1,1,1,1,0,1,0,1,0,0,1,0,1,1,0,1,0,1,},
	{1,0,0,1,0,0,0,0,0,1,1,0,0,0,0,0,0,1,0,1,},
	{1,0,1,1,0,1,1,1,1,1,0,0,1,0,1,1,1,1,0,1,},
	{1,0,0,0,0,0,0,0,0,1,1,1,1,0,1,0,0,0,0,1,},
	{1,1,1,1,1,1,0,1,1,1,0,0,0,0,1,0,1,1,1,1,},
	{1,1,0,0,0,1,0,1,1,1,0,1,1,1,1,0,0,0,0,1,},
	{1,0,0,1,0,0,0,0,0,1,0,0,0,0,1,1,1,1,0,1,},
	{1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,1,1,},
	{1,0,1,1,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,},
	{1,0,1,0,0,0,1,0,0,0,1,0,0,0,0,0,1,1,1,1,},
	{1,0,1,1,1,1,1,0,1,0,1,1,1,0,1,1,1,0,0,1,},
	{1,0,1,0,0,0,1,0,1,0,0,0,1,0,1,1,1,1,1,1,},
	{1,0,1,0,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,1,},
	{1,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,} };

	SDL_Init(SDL_INIT_EVERYTHING);
	SDL_Window* window = SDL_CreateWindow("HI", 100, 100, 700, 700, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
	Output_To_Screen(r, e, window, renderer, map);

	SDL_Event event;
	bool quit = false;
	while (!quit)
	{
		SDL_PollEvent(&event);
		if (event.type == SDL_QUIT)
			quit = true;
		if (event.type == SDL_KEYDOWN)
		{
			if (event.key.keysym.sym == SDLK_UP)
				if (r.y >= 0 && map[r.x][r.y - 1] == 0) r.y -= 1;
			if (event.key.keysym.sym == SDLK_DOWN)
				if (r.y < 19 && map[r.x][r.y + 1] == 0) r.y += 1;
			if (event.key.keysym.sym == SDLK_LEFT)
				if (r.x >= 0 && map[r.x - 1][r.y] == 0) r.x -= 1;
			if (event.key.keysym.sym == SDLK_RIGHT)
				if (r.x < 19 && map[r.x + 1][r.y] == 0) r.x += 1;
			Output_To_Screen(r, e, window, renderer, map);
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}