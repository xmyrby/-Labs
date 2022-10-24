#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <math.h>
#include <Windows.h>

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;
SDL_Surface* win_surf = NULL;
TTF_Font* font = NULL;
SDL_Texture* textures[100];

int winWdt = 960;
int winHgt = 960;

int lastTime = SDL_GetTicks(), newTime, delta = 0;

struct Position
{
	double x, y;
};

struct Bullet
{
	Position pos;
	int textureId;
	int w, h;

	float angle;

	void Move()
	{
		pos.x += cos(angle) * 5;
		pos.y += sin(angle) * 5;
	}
};

int bulletsCount = 0;

int shipsCount;

float Distance(Position a, Position b)
{
	return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

float GetAngle(Position a, Position b)
{
	return atan2(a.y - b.y, a.x - b.x);
}

void Lerp(float& a, float b, float k)
{
	if (a > b)
		a -= k;
	else
		a += k;
}

void AngularLerp(float& a, float b, float k)
{
	if (b > 360)
		b -= 360;
	else if (b < 0)
		b += 360;

	if (a > 360)
		a -= 360;
	else if (a < 0)
		a += 360;

	if (a > b && a - b > 180)
		a += k;
	else if (a > b && a - b < 180)
		a -= k;
	else if (a < b && b - a > 180)
		a -= k;
	else if (a < b && b - a < 180)
		a += k;
}

struct SpaceShip;

SpaceShip* ships;

Bullet* bullets;

void AddBullet(Bullet bullet)
{
	bullets = (Bullet*)realloc(bullets, sizeof(Bullet) * (bulletsCount + 1));
	bullets[bulletsCount] = bullet;
	bulletsCount++;
}

struct SpaceShip
{
	Position pos;

	float hp;
	float maxHp;

	float speed;
	float angleOfMotion;

	float rotateAngle;

	int team;
	int type;

	int targetId;

	int damage;
	int lastShot;

	void GetTarget()
	{
		if (targetId != -1)
		{
			if (Distance(pos, ships[targetId].pos) > 350)
				targetId = -1;
		}
		if (targetId == -1)
			for (int i = 0; i < shipsCount; i++)
			{
				if (Distance(pos, ships[i].pos) <= 350 && ships[i].team != team)
					targetId = i;
			}
	}

	void Move()
	{
		if (rotateAngle >= 360)
		{
			rotateAngle -= 360;
		}
		else if (rotateAngle < 0)
		{
			rotateAngle += 360;
		}


		if (speed < 0.5)
			speed += 0.01;
		pos.x += cos(angleOfMotion) * speed;
		pos.y += sin(angleOfMotion) * speed;

		if (targetId != -1)
		{
			AngularLerp(rotateAngle, GetAngle(ships[targetId].pos, pos) * 180 / M_PI, 2);
			if (GetTickCount() >= lastShot + 500)
			{
				lastShot = GetTickCount();
				Position poss = { pos.x + cos(rotateAngle * M_PI / 180) * 22,pos.y + sin(rotateAngle * M_PI / 180) * 7 };
				Bullet bullet = { pos,20 + team,8,2,rotateAngle * M_PI / 180 };
				AddBullet(bullet);
			}
		}

		float rtA = angleOfMotion * 180 / M_PI;
		AngularLerp(rtA, rotateAngle, 0.5);
		angleOfMotion = rtA * M_PI / 180;
	}
};

void InitShips()
{
	shipsCount = 4;

	ships = (SpaceShip*)realloc(ships, sizeof(SpaceShip) * shipsCount);

	for (int i = 0; i < shipsCount; i++)
	{
		Position pos = { 50 + i / 2 * 300 + i * 150,70 + (i + 1) % 2 * 820 };
		ships[i] = { pos,100,100,0,0,float(i % 2 * 180 - 90),i % 2,0,-1, 1 };
		ships[i].angleOfMotion = ships[i].rotateAngle * M_PI / 180;
		ships[i].lastShot = SDL_GetTicks();
	}
}

void LoadTextures()
{
	textures[0] = IMG_LoadTexture(ren, "GFX\\BlueSpaceShip0.png");
	textures[10] = IMG_LoadTexture(ren, "GFX\\RedSpaceShip0.png");
	textures[20] = IMG_LoadTexture(ren, "GFX\\BlueShot.png");
	textures[21] = IMG_LoadTexture(ren, "GFX\\RedShot.png");
}

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

	if (TTF_Init())
	{
		printf("SDL TTF couldn't init! SDL_Error: %s\n", SDL_GetError());
		DeInit(1);
	}

	win = SDL_CreateWindow(u8"Game", SDL_WINDOWPOS_CENTERED,
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

	win_surf = SDL_GetWindowSurface(win);

	LoadTextures();
	InitShips();

	SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);

	HWND hide_console;
	AllocConsole();
	hide_console = FindWindowA("ConsoleWindowClass", NULL);
	ShowWindow(hide_console, true);
}

Position PrintText(int var, Position position, int size, Uint8 alpha, int colorId)
{
	char text[10];

	_itoa_s(var, (char*)text, 10, 10);

	SDL_Color color = { 255,255,255 };
	color.a = alpha;
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, text, color);

	int width = 0.75 * strlen(text) * size;
	SDL_Rect rect = { position.x,position.y, width,size };

	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(ren, textSurface);
	SDL_RenderCopy(ren, textTexture, NULL, &rect);

	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);

	return (Position{ position.x + width, position.y + size });
}

void RenderImage(int textureId, Position position, int w, int h, int alpha)
{
	SDL_Rect rect = { position.x,position.y,w,h };
	SDL_SetTextureAlphaMod(textures[textureId], alpha);
	SDL_RenderCopy(ren, textures[textureId], NULL, &rect);
}

void RenderAngleImage(int textureId, Position position, int w, int h, int alpha, int angle)
{
	SDL_Rect rect = { position.x,position.y,w,h };
	SDL_SetTextureAlphaMod(textures[textureId], alpha);
	SDL_RenderCopyEx(ren, textures[textureId], NULL, &rect, angle, NULL, SDL_FLIP_NONE);
}

void Draw()
{
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderClear(ren);

	for (int i = 0; i < shipsCount; i++)
	{
		RenderAngleImage(ships[i].type + ships[i].team * 10, ships[i].pos, 32, 32, 255, ships[i].rotateAngle);
		/*SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
		SDL_RenderDrawLine(ren, ships[i].pos.x + 16, ships[i].pos.y + 16, ships[i].pos.x + cos(ships[i].angleOfMotion) * ships[i].speed * 30 + 16, ships[i].pos.y + sin(ships[i].angleOfMotion) * ships[i].speed * 30 + 16);
		SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
		SDL_RenderDrawLine(ren, ships[i].pos.x + 16, ships[i].pos.y + 16, ships[i].pos.x + cos(ships[i].rotateAngle * M_PI / 180) * 30 + 16, ships[i].pos.y + sin(ships[i].rotateAngle * M_PI / 180) * 30 + 16);*/

		//PrintText(ships[i].rotateAngle, { ships[i].pos.x,ships[i].pos.y + 32 }, 16, 255, 0);
	}

	for (int i = 0; i < bulletsCount; i++)
	{
		RenderAngleImage(bullets[i].textureId, bullets[i].pos, 8, 2, 255, bullets[i].angle * 180 / M_PI);
		bullets[i].Move();
		SDL_Delay(1000);
	}

	SDL_RenderPresent(ren);
}

void MoveShips()
{
	for (int i = 0; i < shipsCount; i++)
	{
		ships[i].GetTarget();
		ships[i].Move();
	}
}

#undef main;
int main()
{
	Init();

	font = TTF_OpenFont("Fonts\\MainFont.ttf", 20);

	while (true)
	{
		Draw();
		MoveShips();

		newTime = SDL_GetTicks();
		delta = newTime - lastTime;
		lastTime = newTime;

		if (delta < 16)
		{
			SDL_Delay(16 - delta);
		}
	}

	DeInit(0);

	return 0;
}