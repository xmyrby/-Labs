#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;

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

	if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == 0)
	{
		printf("SDL Image couldn't init! SDL_Error: %s\n", SDL_GetError());
		DeInit(1);
	}

	win = SDL_CreateWindow(u8"Прудников", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 700, 800, SDL_WINDOW_SHOWN
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

	SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
}

#undef main

int main()
{
	Init();
	SDL_Texture* texture = IMG_LoadTexture(ren, "Image.png");
	SDL_Rect rect = { 350,400 ,350,400 };
	SDL_RenderCopy(ren, texture, NULL, &rect);
	SDL_RenderPresent(ren);

	SDL_Delay(10000);

	DeInit(0);
	return 0;
}