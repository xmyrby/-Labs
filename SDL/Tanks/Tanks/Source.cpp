#include <SDL_image.h>
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
	float x;
	float y;
};

struct Dot
{
	float angle;
	float length;
};

struct Object
{
	int _dotsCount;
	Dot _dots[10];

	void Init(Dot* dots, int dotsCount)
	{
		_dotsCount = dotsCount;
		for (int i = 0; i < _dotsCount; i++)
			_dots[i] = dots[i];
	}
};

Dot* GetDots(int& dotsCount, const char* file)
{
	FILE* ft;
	if (fopen_s(&ft, file, "rt") != 0)
	{
		printf("error");
		exit(1);
		return 0;
	}
	else
	{
		fscanf_s(ft, "%d", &dotsCount);

		Dot* dots = new Dot[dotsCount];

		for (int i = 0; i < dotsCount; i++)
			fscanf_s(ft, "%f %f", &dots[i].angle, &dots[i].length);

		fclose(ft);
		return dots;
	}
}

struct Tank
{
	Point position;
	float angle;
	int health;
	Object turret, stem, base;

	void Init(Point inPosition, float inAngle, int inHealth)
	{
		position = inPosition;
		angle = inAngle;
		health = inHealth;
		int count = 0;
		turret.Init(GetDots(count, "turret.dots"), count);
		stem.Init(GetDots(count, "stem.dots"), count);
		base.Init(GetDots(count, "base.dots"), count);
	}
};


void Renderer(Object object, Point position, float angle)
{
	SDL_SetRenderDrawColor(ren, 125, 100, 105, 0);
	int dotsCount = object._dotsCount;
	Point* points = new Point[dotsCount];
	for (int i = 0; i < dotsCount; i++)
	{
		Dot dot = object._dots[i];
		points[i] = { position.x + dot.length * cos((dot.angle + angle) * RAD),position.y + dot.length * sin((dot.angle + angle) * RAD) };
	}

	for (int i = 0; i < dotsCount; i++)
	{
		SDL_RenderDrawLine(ren, points[i].x, points[i].y, points[(i + 1) % dotsCount].x, points[(i + 1) % dotsCount].y);
	}
}

void RenderTank(Tank tank)
{
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 0);
	SDL_RenderClear(ren);
	SDL_SetRenderDrawColor(ren, 225, 200, 205, 0);
	Renderer(tank.turret, tank.position, tank.angle);
	Renderer(tank.stem, tank.position, tank.angle);
	Renderer(tank.base, tank.position, tank.angle);
	SDL_RenderPresent(ren);
}

#undef main
int main()
{
	SDL_Event event;
	Init();
	Tank tank;

	bool buttons[SDL_NUM_SCANCODES]{};

	int count = 0;
	tank.Init({ 420,420 }, 0, 100);

	bool w = false, a = false, s = false, d = false;

	while (true)
	{
		RenderTank(tank);

		const Uint8* keyboard_state_array = SDL_GetKeyboardState(NULL);

		SDL_PollEvent(&event);

		if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
		{
			if (keyboard_state_array[SDL_SCANCODE_A])
			{
				a = true;
			}
			else if (!keyboard_state_array[SDL_SCANCODE_A])
			{
				a = false;
			}
			if (keyboard_state_array[SDL_SCANCODE_D])
			{
				d = true;
			}
			else if (!keyboard_state_array[SDL_SCANCODE_D])
			{
				d = false;
			}

			if (keyboard_state_array[SDL_SCANCODE_W] && !keyboard_state_array[SDL_SCANCODE_S])
			{
				w = true;
			}
			if (!keyboard_state_array[SDL_SCANCODE_W] || keyboard_state_array[SDL_SCANCODE_S])
			{
				w = false;
			}

			if (keyboard_state_array[SDL_SCANCODE_S] && !keyboard_state_array[SDL_SCANCODE_W])
			{
				s = true;
			}
			else if (!keyboard_state_array[SDL_SCANCODE_S] || keyboard_state_array[SDL_SCANCODE_W])
			{
				s = false;
			}
		}

		if (a)
		{
			tank.angle -= 0.75;
		}
		else if (d)
		{
			tank.angle += 0.75;
		}

		if (w)
		{
			tank.position.x += 1.25 * cos(tank.angle * RAD);
			tank.position.y += 1.25 * sin(tank.angle * RAD);
		}
		else if (s)
		{
			tank.position.x -= 0.5 * cos(tank.angle * RAD);
			tank.position.y -= 0.5 * sin(tank.angle * RAD);
		}

		SDL_Delay(10);
	}

	DeInit(0);

	return 0;
}