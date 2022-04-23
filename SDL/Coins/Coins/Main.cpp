#include <iostream>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
SDL_Window* win;
SDL_Renderer* ren;

int win_width = 1000, win_height = 1000; // Размеры окна как глобальные переменные

struct Mole
{
	int x, y;
	int size;
	bool spawned;
	int lifetime;
};

void DeInit(int error)
{
	if (ren != NULL) SDL_DestroyRenderer(ren);
	if (win != NULL) SDL_DestroyWindow(win);
	SDL_Quit();
	exit(error);

}

void Init()
{
	//SDL_Init(SDL_INIT_EVERYTHING);

	//Инициализация SDL
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("ploho: %s", SDL_GetError());
		system("pause");
		DeInit(1);
	}

	win = SDL_CreateWindow("Just Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		win_width, win_height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (win == NULL)
	{
		printf("win: %s", SDL_GetError());
		system("pause");
		DeInit(1);
	}


	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (ren == NULL)
	{
		printf("okna ne ma render: %s", SDL_GetError());
		system("pause");
		DeInit(1);
	}
}

Mole GenMole()
{
	return { rand() % 980,rand() % 980, rand() % 21 + 20, 1 ,rand() % 501 + 500 };
}

void DrawMoles(Mole* moles)
{
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderClear(ren);
	for (int i = 0; i < 10; i++)
	{
		Mole mole = moles[i];
		if (mole.spawned)
		{
			SDL_Rect rect = { mole.x,mole.y,mole.size,mole.size };
			SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
			SDL_RenderFillRect(ren, &rect);
		}
	}
	SDL_RenderPresent(ren);
}

void CheckMoles(Mole* moles, int count, int& misses)
{
	for (int i = 0; i < count; i++)
	{
		moles[i].lifetime -= 1;
		Mole mole = moles[i];

		if (mole.lifetime <= 0)
		{
			moles[i] = GenMole();
			misses++;
			DrawMoles(moles);
		}
	}
}

void KillMole(Mole* moles, int x, int y, int count, int& counter)
{
	for (int i = 0; i < count; i++)
	{
		Mole mole = moles[i];

		if (x >= mole.x && x <= mole.x + mole.size && y >= mole.y && y <= mole.y + mole.size)
		{
			counter++;
			moles[i] = GenMole();
			DrawMoles(moles);
		}

	}
}

void output_file(int counter)
{
	FILE* f;

	if (fopen_s(&f, "save.txt", "r+b") != 0)
	{
		printf("Ошибка записи!");
		exit(1);
	}
	fprintf_s(f, "Последняя игра: %d\n", counter);
	fclose(f);
}

int main(int argc, char* argv[])
{
	system("chcp 1251 > nul");
	Init();
	srand(time(NULL));
	int mouse_x = 0, mouse_y = 0, counter = 0, count = 1, spawn = 10000, misses = 0;
	Uint32 events;
	Mole moles[10];

	bool isRunning = true, down = false;

	moles[0] = GenMole();
	DrawMoles(moles);

	while (isRunning)
	{
		SDL_PumpEvents();
		events = SDL_GetMouseState(&mouse_x, &mouse_y);

		if ((events & SDL_BUTTON_LMASK) != 0 && !down)
		{
			down = true;
			KillMole(moles, mouse_x, mouse_y, count, counter);
			system("cls");
			printf("Кротов поймано: %i\nНе поймано: %i", counter, misses);
		}
		if ((events & SDL_BUTTON_LMASK) == 0)
			down = false;

		CheckMoles(moles, count, misses);

		if (count < 3)
		{
			spawn--;
			if (spawn == 0)
			{
				moles[count] = GenMole();
				DrawMoles(moles);
				count++;
				spawn = 10000 / count;
			}
		}

		if (misses >= 10)
		{
			output_file(counter);
			break;
		}

		SDL_Delay(1);
	}
	DeInit(0);
	SDL_Quit();
	return 0;
}