#include <SDL.h>
#include <iostream>

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;

int winWdt = 1920;
int winHgt = 1080;

const float K = M_PI / 180;

const float G = 0.0007;

const float scalex = 10;
const float scaley = 5;
const float scalesize = 3;

struct Planet
{
	float x, y, vx, vy, mas;
	int radius;
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

	win = SDL_CreateWindow(u8"Симуляция", SDL_WINDOWPOS_CENTERED,
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

float max(float a, float b)
{
	if (a > b)
		return a;
	return b;
}

void DrawPlanet(Planet planet)
{
	SDL_SetRenderDrawColor(ren, 255, 0, 0, 0);
	for (int w = -planet.radius * scalesize; w < planet.radius * scalesize; w++)
	{
		for (int h = -planet.radius * scalesize; h < planet.radius * scalesize; h++)
		{
			int dx = w;
			int dy = h;
			if ((dx * dx + dy * dy) <= max((planet.radius * planet.radius) * scalesize, 1))
			{
				SDL_RenderDrawPoint(ren, planet.x * scalex + dx, planet.y * scaley + dy);
			}
		}
	}
}

void GenPlanets(Planet* planets, int planetsCount)
{
	planets[0].x = 100;
	planets[0].y = 100;
	planets[0].vx = 0.0;
	planets[0].vy = 0.0;
	planets[0].radius = 10;
	planets[0].mas = 1000;

	int minDist = 19;

	for (int i = 1; i < planetsCount; i++)
	{
		int dist = rand() % 10 + minDist + 3;
		minDist = dist;

		float angle = rand() % 360 * K;

		planets[i].x = planets[0].x + dist * cos(angle);
		planets[i].y = planets[0].y + dist * sin(angle);
		planets[i].mas = dist / 10 + 1;
		planets[i].radius = planets[i].mas;
		planets[i].vx = 0.1 * sin(angle);
		planets[i].vy = 0.1 * cos(angle);
	}

	/*planets[1].x = 130;
	planets[1].y = 100;
	planets[1].vx = 0;
	planets[1].vy = -0.1;
	planets[1].radius = 3;
	planets[1].mas = 7;

	planets[2].x = 30;
	planets[2].y = 100;
	planets[2].vx = 0;
	planets[2].vy = 0.1;
	planets[2].radius = 5;
	planets[2].mas = 10;

	planets[3].x = 25;
	planets[3].y = 100;
	planets[3].vx = 0;
	planets[3].vy = 0.11;
	planets[3].radius = 1;
	planets[3].mas = 0.1;*/
}

void Calculate(Planet* planets, int planetsCount)
{
	for (int i = 0; i < planetsCount; i++)
	{
		Planet& p0 = planets[i];
		for (int j = 0; j < planetsCount; j++)
		{
			if (i != j)
			{
				const Planet& p = planets[j];
				float r = sqrt(pow((p0.x - p.x), 2) + pow((p0.y - p.y), 2));

				if (r > 3)
				{
					p0.vx += G * p.mas / r / r * (p.x - p0.x) / r;
					p0.vy += G * p.mas / r / r * (p.y - p0.y) / r;
				}
			}
		}
		p0.x += p0.vx;
		p0.y += p0.vy;
	}
}

#undef main
int main()
{
	const int count = 6;

	srand(time(NULL));

	Planet planets[count];

	GenPlanets(planets, count);

	Init();

	while (true)
	{
		SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
		SDL_RenderClear(ren);

		Calculate(planets, count);

		for (int i = 0; i < count; i++)
			DrawPlanet(planets[i]);

		SDL_RenderPresent(ren);

		SDL_Delay(2);
	}

	DeInit(0);

	return 0;
}