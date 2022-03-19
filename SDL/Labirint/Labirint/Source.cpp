#include <iostream>
#include <SDL.h>
#include <stdio.h>

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;

int winWdt = 1920;
int winHgt = 1080;
float fallangle = 1.39626;
const int countBlobs = 1500;

struct Rgb
{
	int red;
	int green;
	int blue;
};

struct Blob
{
	Rgb color;
	float x;
	float y;
	float speed;
};

void DeInit(char error)
{
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
	exit(error);
}

void Init()
{

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL couldn't init! SDL_Error: %s\n", SDL_GetError());
		DeInit(1);
	}

	win = SDL_CreateWindow(u8"Дождек", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, winWdt, winHgt, SDL_WINDOW_SHOWN
	);
	if (win == NULL)
	{
		printf("SDL couldn't init! SDL_Error: %s\n", SDL_GetError());
		DeInit(1);
	}

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (ren == NULL)
	{
		printf("SDL couldn't create renderer! SDL_Error: %s\n", SDL_GetError());
		DeInit(1);
	}
}

void drawLine(float x, float y, float angle, float length, Rgb color)
{
	SDL_SetRenderDrawColor(ren, color.red, color.green, color.blue, 0);
	SDL_RenderDrawLine(ren, x, y, x - cos(angle) * length, y - sin(angle) * length);
}

void drawBLobs(Blob* blobs)
{
	for (int i = 0; i < countBlobs; i++)
	{
		drawLine(blobs[i].x, blobs[i].y, fallangle, blobs[i].y / 3.0 + 20, blobs[i].color);
		blobs[i].x += cos(fallangle) * blobs[i].speed;
		blobs[i].y += sin(fallangle) * blobs[i].speed;
		if (blobs[i].x > winWdt * 1.35)
			blobs[i].x = 0;
		if (blobs[i].x < -winWdt * 0.35)
			blobs[i].x = winWdt;
		if (blobs[i].y > winHgt * 1.35)
			blobs[i].y = 0;
		if (blobs[i].y < -winHgt * 0.35)
			blobs[i].y = winHgt;
	}
}

void CreateBlobs(Blob* blobs)
{
	for (int i = 0; i < countBlobs; i++)
	{
		blobs[i].color.red = 50;
		blobs[i].color.green = 0;
		blobs[i].color.blue = (rand() % 229 - 144 + 1) - 74;
		blobs[i].x = rand() % winWdt;
		blobs[i].y = rand() % winHgt;
		blobs[i].speed = (rand() % 56) / 10.0 + 4.5;
	}
}

#undef main
int main()
{
	srand(time(NULL));
	Init();

	Blob blobs[countBlobs];

	CreateBlobs(blobs);

	while (true)
	{
		fallangle += 0.001;
		drawBLobs(blobs);

		SDL_RenderPresent(ren);

		SDL_Delay(1);
		SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
		SDL_RenderClear(ren);
	}

	DeInit(0);
	return 0;
}