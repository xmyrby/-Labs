#include <SDL.h>
#include <iostream>

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;

int winWdt = 840;
int winHgt = 840;

const float RAD = M_PI / 180;

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

	win = SDL_CreateWindow(u8"PARAGON MAZE", SDL_WINDOWPOS_CENTERED,
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

struct Point
{
	float x, y;
};

struct Planet
{
	Point position;
	Point rotatePosition;

	float angle;
	float distance;

	int size;
};

struct BigPlanet : Planet
{
	bool fixed;
	Planet planets[4];
};

int Randomize(int start, int end)
{
	return rand() % (end - start + 1) + start;
}

Planet GenBig(BigPlanet planet, int sizeStart, bool genCords)
{
	if (genCords)
	{
		planet.position.x = Randomize(300, 600);
		planet.position.y = Randomize(300, 600);
	}
	planet.size = Randomize(sizeStart, sizeStart * 1.75);
}

void Generate(BigPlanet* planets)
{
	planets[0].fixed = true;
	GenBig(planets[0], 100, true);

	int planetsCount = Randomize(1, 4);

	for (size_t i = 0; i < planetsCount; i++)
	{

	}
}

#undef main
int main()
{
	srand(time(NULL));
	BigPlanet planets[10];

	Generate(planets);

	return 0;
}