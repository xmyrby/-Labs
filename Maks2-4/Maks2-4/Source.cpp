#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <math.h>

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;

int winWdt = 700;
int winHgt = 800;

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
}

void ShowWindow()
{
	win = SDL_CreateWindow(u8"Прудников", SDL_WINDOWPOS_CENTERED,
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

void DrawPc()
{
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	SDL_RenderClear(ren);

	SDL_Texture* texture = IMG_LoadTexture(ren, "Image.png");

	SDL_Rect rect = { winWdt - 250,winHgt - 250,250,250 };

	SDL_RenderCopy(ren, texture, NULL, &rect);

	SDL_DestroyTexture(texture);
}

void DrawParallel()
{
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
	SDL_Rect rect = { winWdt / 4 - winWdt / 8,winHgt / 4 + winWdt / 8,winWdt / 2,winHgt / 2 };
	SDL_RenderDrawRect(ren, &rect);
	rect = { winWdt / 4 + winWdt / 8,winHgt / 4 - winWdt / 8,winWdt / 2,winHgt / 2 };
	SDL_RenderDrawRect(ren, &rect);
	SDL_RenderDrawLine(ren, winWdt / 4 - winWdt / 8, winHgt / 4 + winWdt / 8, winWdt / 4 + winWdt / 8, winHgt / 4 - winWdt / 8);
	SDL_RenderDrawLine(ren, winWdt / 4 - winWdt / 8 + winWdt / 2, winHgt / 4 + winWdt / 8 + winHgt / 2, winWdt / 4 + winWdt / 8 + winWdt / 2, winHgt / 4 - winWdt / 8 + winHgt / 2);
	SDL_RenderDrawLine(ren, winWdt / 4 - winWdt / 8 + winWdt / 2, winHgt / 4 + winWdt / 8, winWdt / 4 + winWdt / 8 + winWdt / 2, winHgt / 4 - winWdt / 8);
	SDL_RenderDrawLine(ren, winWdt / 4 - winWdt / 8, winHgt / 4 + winWdt / 8 + winHgt / 2, winWdt / 4 + winWdt / 8, winHgt / 4 - winWdt / 8 + winHgt / 2);
}

void DrawCircle(float x, float y, float radius, bool full)
{
	for (int w = 0; w < radius * 2; w++)
	{
		for (int h = 0; h < radius * 2; h++)
		{
			int dx = radius - w;
			int dy = radius - h;
			int d = (dx * dx + dy * dy);
			if (d <= (radius * radius) && (d >= (radius * radius) / 6 * 5 || full))
			{
				SDL_RenderDrawPoint(ren, x + dx, y + dy);
			}
		}
	}
}

void DrawOlimpic()
{
	SDL_SetRenderDrawColor(ren, 200, 200, 200, 255);
	SDL_RenderClear(ren);

	int sW = winWdt / 8;
	int sH = winHgt / 8;

	SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
	DrawCircle(sW * 2, sH * 3, 120, false);
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	DrawCircle(sW * 4, sH * 3, 120, false);
	SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
	DrawCircle(sW * 6, sH * 3, 120, false);
	SDL_SetRenderDrawColor(ren, 255, 255, 0, 255);
	DrawCircle(sW * 3, sH * 4, 120, false);
	SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
	DrawCircle(sW * 5, sH * 4, 120, false);
}

void DrawGraph(float A, float B, float C)
{
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderClear(ren);

	SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);

	SDL_RenderDrawLine(ren, winWdt / 2, 0, winWdt / 2, winHgt);
	SDL_RenderDrawLine(ren, 0, winHgt / 2, winWdt, winHgt / 2);
	for (int x = -winWdt / 2; x < winHgt * 1.5; x++)
	{
		int y = A * log(x * x + B) + C;
		y *= -1;

		SDL_RenderDrawPoint(ren, x + winWdt / 2, y + winWdt / 2);
	}
}

int Min(int a, int b)
{
	if (a < b)
		return a;
	return b;
}

void DrawDomino()
{
	struct Domino
	{
		float x1, y1, x2, y2;
	};
	Domino dominos[10];
	int step = winWdt / 10;
	int height = winHgt / 1.5 - winHgt / 2;
	for (int j = 0; j < 10; j++)
	{
		dominos[j].x1 = step * (j + 1);
		dominos[j].y1 = winHgt / 2;
		dominos[j].x2 = step * (j + 1);
		dominos[j].y2 = winHgt / 1.5;
	}
	int dominoId = 0;
	for (int i = 0; i < 1000; i++)
	{
		SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
		SDL_RenderClear(ren);
		SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
		if (dominos[dominoId].x1 >= dominos[dominoId + 1].x1 && dominoId < 9)
			dominoId++;
		for (int j = 0; j < 10; j++)
		{
			if (j <= dominoId && dominos[j].y1 < dominos[j].y2)
			{
				dominos[j].x1 += step / 50.0;
				dominos[j].y1 += height / 100.0;
			}

			SDL_RenderDrawLine(ren, dominos[j].x1, dominos[j].y1, dominos[j].x2, dominos[j].y2);
		}
		SDL_Delay(8);
		SDL_RenderPresent(ren);
	}
}

float GetAngle(int x1, int y1, int x2, int y2)
{
	return atan2(y1 - y2, x1 - x2);
}

void CircGame()
{
	int x, y;
	struct Circle
	{
		float x, y;
		int rad;
		float angle;
		SDL_Color color;
		bool flight;
	};

	Circle circle = { winWdt / 2,winHgt / 2,15,0.0,{
255,255,255,255
}, false };

	bool _down = false;

	SDL_Event event;

	while (true)
	{
		SDL_PollEvent(&event);

		SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
		SDL_RenderClear(ren);
		Uint32 events = SDL_GetMouseState(&x, &y);

		if ((events & SDL_BUTTON_LMASK) != 0 && !_down)
		{
			_down = true;
			if (x <= winWdt / 10 || y <= winHgt / 10 || x >= winWdt / 10 * 9 || y >= winHgt / 10 * 9)
			{
				circle.x = winWdt / 2;
				circle.y = winHgt / 2;
				circle.color.r = rand() % 205 + 51;
				circle.color.g = rand() % 205 + 51;
				circle.color.b = rand() % 205 + 51;
				circle.flight = false;
			}
			else
			{
				circle.angle = GetAngle(x, y, circle.x, circle.y);
				circle.flight = true;
			}
		}
		if ((events & SDL_BUTTON_RMASK) != 0 && !_down)
		{
			_down = true;
			circle.angle = GetAngle(circle.x, circle.y, x, y);
			circle.flight = true;
		}
		if ((events & SDL_BUTTON_LMASK && SDL_BUTTON_RMASK) == 0)
			_down = false;

		if (circle.flight)
		{
			if (circle.x <= 0 + circle.rad || circle.x >= winWdt - circle.rad || circle.y <= 0 + circle.rad || circle.y >= winHgt - circle.rad)
				circle.angle += 3.14159;
			circle.x += cos(circle.angle) * 2;
			circle.y += sin(circle.angle) * 2;
		}
		SDL_SetRenderDrawColor(ren, circle.color.r, circle.color.g, circle.color.b, 255);

		DrawCircle(circle.x, circle.y, circle.rad, true);
		SDL_RenderPresent(ren);

		SDL_Delay(10);
	}
}

void Switcher()
{
	int type = 0;

	do
	{
		printf("0 - Вывод компуктера\n1 - Параллелепипед\n2 - Олимпийская эмблема\n3 - Формула Y-A*ln(x^2+B)+C [1:10]\n4 - Домино\n5 - Игра с кругом\nВыбор: ");
		scanf_s("%d", &type);
	} while (type < 0 || type > 5);
	if (type != 3)
		ShowWindow();

	switch (type)
	{
	case 0:
		DrawPc();
		break;
	case 1:
		DrawParallel();
		break;
	case 2:
		DrawOlimpic();
		break;
	case 3:
	{
		printf("Введите A B C: ");
		float A, B, C;
		scanf_s("%f %f %f", &A, &B, &C);

		ShowWindow();

		DrawGraph(A, B, C);
		break;
	}
	case 4:
		DrawDomino();
		break;
	case 5:
		CircGame();
		break;
	default:
		break;
	}
}

#undef main;
int main()
{
	srand(time(NULL));

	system("chcp 1251 > nul");
	Init();

	Switcher();

	SDL_RenderPresent(ren);

	SDL_Delay(1000);

	DeInit(0);
	return 0;
}