#include<iostream>
#include<SDL.h>

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;

int win_width = 1920, win_height = 1080;

void DeInit(int error)
{
	if (ren != NULL) SDL_DestroyRenderer(ren);
	if (win != NULL) SDL_DestroyWindow(win);
	SDL_Quit();
	exit(error);
}

void Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("Couldn't init SDL! Error: %s", SDL_GetError());
		system("pause");
		DeInit(1);
	}

	win = SDL_CreateWindow("BlazBlue", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		win_width, win_height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (win == NULL)
	{
		printf("Couldn't creat window! Error: %s", SDL_GetError());
		system("pause");
		DeInit(1);
	}

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (ren == NULL)
	{
		printf("Couldn't creat renderer! Error: %s", SDL_GetError());
		system("pause");
		DeInit(1);
	}
}
struct rain
{
	int change;
	float x1, y1, x2, y2;
	int len;
	float speed = 5;
	int color_green, color_red, color_blue;
};
void coord(rain* mas, int i)
{
	mas[i].len = rand() % 100;
	mas[i].x1 = rand() % win_width;
	mas[i].change = rand() % 5;
	mas[i].y1 = win_height / 50;
	mas[i].x2 = mas[i].x1 - mas[i].change - 100;
	mas[i].y2 = mas[i].y1 - mas[i].len + 100;

}
void color(rain* mas, int i)
{
	mas[i].color_blue = 255;
	mas[i].color_red = 124;
	mas[i].color_green = 8;

}
void drawline(rain* mas, int i)
{
	SDL_SetRenderDrawColor(ren, mas[i].color_red, mas[i].color_green, mas[i].color_blue, 255);
	SDL_RenderDrawLine(ren, mas[i].x1, mas[i].y1, mas[i].x2, mas[i].y2);
}
void speed_rain(rain* mas, int i)
{
	mas[i].y1 = mas[i].y2;
	mas[i].y2 = mas[i].y2 + mas[i].len * 1.2;
	mas[i].x1 = mas[i].x2;
	mas[i].x2 = mas[i].x1 + mas[i].change;
	if (mas[i].y1 > win_height || mas[i].x1 >= win_width)
		coord(mas, i);
}

int main(int argc, char* args[])
{
	const int quan = 50;
	rain mas[400];

	//додуматься до массива
	srand(time(0));
	Init();
	while (true)
	{
		SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
		SDL_RenderClear(ren);
		for (int i = 0; i < quan; i++)
		{
			color(mas, i);
			coord(mas, i);
			drawline(mas, i);
			SDL_RenderPresent(ren);
		}
		while (true)
		{
			SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
			SDL_RenderClear(ren);
			for (int i = 0; i < quan; i++)
			{
				drawline(mas, i);
				SDL_RenderPresent(ren);
				speed_rain(mas, i);

			}

		}
	}
	SDL_Delay(5000);


	DeInit(0);
	return 0;
}
