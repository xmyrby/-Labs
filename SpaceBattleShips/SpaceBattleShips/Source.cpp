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

bool devUI = false;
bool fpsShow = true;

int winWdt = 960;
int winHgt = 960;

float scrollx = 480, scrolly = 480;
float scale = 1;
int scrollship = 2;

int lastTime = SDL_GetTicks(), newTime, delta = 0;

const float RAD = M_PI / 180;
const float GRAD = 180 / M_PI;

void Swap(float& a, float& b)
{
	float c = a;
	a = b;
	b = c;
}

struct Position
{
	float x, y;
};

inline int Area(Position a, Position b, Position c)
{
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

inline bool Intersect_1(float a, float b, float c, float d)
{
	if (a > b)  Swap(a, b);
	if (c > d)  Swap(c, d);
	return max(a, c) <= min(b, d);
}

bool Intersect(Position a, Position b, Position c, Position d)
{
	return Intersect_1(a.x, b.x, c.x, d.x)
		&& Intersect_1(a.y, b.y, c.y, d.y)
		&& Area(a, b, c) * Area(a, b, d) <= 0
		&& Area(c, d, a) * Area(c, d, b) <= 0;
}

struct BoundingBox
{
	struct Side
	{
		Position pos1;
		Position pos2;
	};

	Side sides[4];
};

bool CheckCollision(BoundingBox collider1, BoundingBox collider2)
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (Intersect(collider1.sides[i].pos1, collider1.sides[i].pos2, collider2.sides[j].pos1, collider2.sides[j].pos2))
				return true;
		}
	}
	return false;
}

struct Object
{
	Position pos;
	BoundingBox collider;
	int sizeW, sizeH;

	float motionAngle;
	float rotateAngle;

	Position GetPosRotated(float offsetX, float offsetY)
	{
		if (rotateAngle == NULL)
			return { (pos.x + sizeW / 2) + (offsetX)*cos(motionAngle) - (offsetY)*sin(motionAngle), (pos.y + sizeH / 2) + (offsetX)*sin(motionAngle) + (offsetY)*cos(motionAngle) };
		return { (pos.x + sizeW / 2) + (offsetX)*cos(rotateAngle * RAD) - (offsetY)*sin(rotateAngle * RAD), (pos.y + sizeH / 2) + (offsetX)*sin(rotateAngle * RAD) + (offsetY)*cos(rotateAngle * RAD) };
	}

	void CalculateSides()
	{
		Position pos1, pos2;

		int dW = sizeW / 2, dH = sizeH / 2;

		pos1 = GetPosRotated(-dW, -dH);
		pos2 = GetPosRotated(+dW, -dH);

		collider.sides[0] = { pos1,pos2 };

		pos1 = GetPosRotated(+dW, +dH);
		collider.sides[1] = { pos2,pos1 };

		pos2 = GetPosRotated(-dW, +dH);
		collider.sides[2] = { pos1,pos2 };

		pos1 = GetPosRotated(-dW, -dH);
		collider.sides[3] = { pos2,pos1 };
	}
};

struct Bullet : Object
{
	int team;

	int textureId;

	int destroyTime;

	int damage;

	Bullet(Position posC, int sizeWC, int sizeHC, float rotateAngleC, float motionAngleC, int textureId, int destroyTime, int team, int damage) :textureId(textureId), destroyTime(destroyTime), team(team), damage(damage) {
		pos = posC;
		sizeW = sizeWC;
		sizeH = sizeHC;
		rotateAngle = rotateAngleC;
		motionAngle = motionAngleC;
		CalculateSides();
	}

	void Move()
	{
		pos.x += cos(motionAngle) * 7;
		pos.y += sin(motionAngle) * 7;
		CalculateSides();
	}

	bool CheckActivity()
	{
		if (newTime >= destroyTime)
			return true;
		return false;
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
		a -= min(a - b, k);
	else
		a += min(b - a, k);
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
		a += min(a - b, k);
	else if (a > b && a - b < 180)
		a -= min(a - b, k);
	else if (a < b && b - a > 180)
		a -= min(b - a, k);
	else if (a < b && b - a < 180)
		a += min(b - a, k);
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

void DestroyBullet(int index)
{
	for (int i = index; i < bulletsCount - 1; i++)
	{
		bullets[i] = bullets[i + 1];
	}
	bullets = (Bullet*)realloc(bullets, sizeof(Bullet) * (bulletsCount - 1));
	bulletsCount--;
}

struct SpaceShip : Object
{
	float hp;
	float maxHp;

	float speed;

	int team;
	int type;

	int damage;

	int turret;
	int targetId;
	int lastShot;

	SpaceShip(Position posC, int sizeWC, int sizeHC, float rotateAngleC, float motionAngleC, float hp, float maxHp, float speed, int team, int type, int damage) :hp(hp), maxHp(maxHp), speed(speed), team(team), type(type), damage(damage) {
		pos = posC;
		sizeW = sizeWC;
		sizeH = sizeHC;
		rotateAngle = rotateAngleC;
		motionAngle = motionAngleC;
		turret = 0;
		targetId = -1;
		lastShot = newTime;
		CalculateSides();
	}

	void GetTarget()
	{
		if (targetId != -1)
		{
			if (ships[targetId].team == team || shipsCount >= targetId)
				targetId = -1;
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


		if (speed < 0.75)
			speed += 0.02;
		pos.x += cos(motionAngle) * speed;
		pos.y += sin(motionAngle) * speed;

		if (targetId != -1)
		{
			AngularLerp(rotateAngle, GetAngle(ships[targetId].pos, pos) * GRAD, 2);
			if (newTime >= lastShot + 150)
			{
				lastShot = newTime;

				if (turret == 0)
				{
					Bullet bullet(GetPosRotated(6, -9), 8, 2, rotateAngle, rotateAngle * RAD, 20 + team, newTime + 1000, team, damage);
					AddBullet(bullet);
				}
				else if (turret == 1)
				{
					Bullet bullet(GetPosRotated(6, 7), 8, 2, rotateAngle, rotateAngle * RAD, 20 + team, newTime + 1000, team, damage);
					AddBullet(bullet);
				}
				turret = (turret + 1) % 2;
			}
		}
		else
		{
			rotateAngle += rand() % 7 - 3;
		}

		float rtA = motionAngle * GRAD;
		AngularLerp(rtA, rotateAngle, 0.5);
		motionAngle = rtA * RAD;
		CalculateSides();
	}
};

void DestroyShip(int index)
{
	for (int i = 0; i < shipsCount; i++)
	{
		if (ships[i].targetId == index)
			ships[i].targetId = -1;
	}

	for (int i = index; i < shipsCount - 1; i++)
	{
		ships[i] = ships[i + 1];
	}
	ships = (SpaceShip*)realloc(ships, sizeof(SpaceShip) * (shipsCount - 1));
	shipsCount--;

	if (scrollship == index)
		scrollship = -1;
}

void InitShips()
{
	shipsCount = 20;

	ships = (SpaceShip*)realloc(ships, sizeof(SpaceShip) * shipsCount);

	for (int i = 0; i < shipsCount; i++)
	{
		Position pos = { rand() % 980,rand() % 980 };
		float angle = rand() % 360;
		SpaceShip ship(pos, 32, 32, angle, angle * RAD, 100, 100, 0, i % 2, 0, 0.75);
		ships[i] = ship;
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
	position.x += (480 / scale - scrollx);
	position.y += (480 / scale - scrolly);
	position.x *= scale;
	position.y *= scale;
	size *= scale;
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
	position.x += (480 / scale - scrollx);
	position.y += (480 / scale - scrolly);
	position.x *= scale;
	position.y *= scale;
	SDL_Rect rect = { position.x,position.y,w * scale,h * scale };
	SDL_SetTextureAlphaMod(textures[textureId], alpha);
	SDL_RenderCopy(ren, textures[textureId], NULL, &rect);
}

void RenderAngleImage(int textureId, Position position, int w, int h, int alpha, int angle)
{
	position.x += (480 / scale - scrollx);
	position.y += (480 / scale - scrolly);
	position.x *= scale;
	position.y *= scale;
	SDL_Rect rect = { position.x,position.y,w * scale,h * scale };
	SDL_SetTextureAlphaMod(textures[textureId], alpha);
	SDL_RenderCopyEx(ren, textures[textureId], NULL, &rect, angle, NULL, SDL_FLIP_NONE);
}

void Draw()
{
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderClear(ren);

	if (devUI)
	{
		SDL_SetRenderDrawColor(ren, 25, 25, 25, 255);
		for (int i = -50; i < 50; i++)
		{
			for (int j = -50; j < 50; j++)
			{
				SDL_Rect rect = { (i * 128 + (480 / scale - scrollx)) * scale,(j * 128 + (480 / scale - scrolly)) * scale,128 * scale,128 * scale };
				SDL_RenderDrawRect(ren, &rect);
			}
		}
	}

	if (fpsShow && delta > 0)
		PrintText(1000 / max(16, delta), { (900 - (480 / scale - scrollx)) * scale,(90 - (480 / scale - scrolly)) * scale }, 16 * scale, 255, 0);

	if (devUI)
		PrintText(scrollship, { (90 - (480 / scale - scrollx)) * scale,(90 - (480 / scale - scrolly)) * scale }, 16 * scale, 255, 0);

	for (int i = 0; i < shipsCount; i++)
	{
		if (abs(ships[i].pos.x - scrollx) < 500 / scale && abs(ships[i].pos.y - scrolly) < 500 / scale)
		{
			if (devUI)
				PrintText(ships[i].hp, { ships[i].pos.x,ships[i].pos.y + 34 }, 16, 255, 0);

			RenderAngleImage(ships[i].type + ships[i].team * 10, ships[i].pos, 32, 32, 255, ships[i].rotateAngle);

			if (devUI)
			{
				SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
				for (int j = 0; j < 4; j++)
				{
					SDL_RenderDrawLineF(ren, (ships[i].collider.sides[j].pos1.x + (480 / scale - scrollx)) * scale, (ships[i].collider.sides[j].pos1.y + (480 / scale - scrolly)) * scale, (ships[i].collider.sides[j].pos2.x + (480 / scale - scrollx)) * scale, (ships[i].collider.sides[j].pos2.y + (480 / scale - scrolly)) * scale);
				}

				SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
				if (ships[i].targetId != -1)
				{
					SDL_RenderDrawLineF(ren, (ships[i].pos.x + ships[i].sizeW / 2 + (480 / scale - scrollx)) * scale, (ships[i].pos.y + ships[i].sizeH / 2 + (480 / scale - scrolly)) * scale, (ships[ships[i].targetId].pos.x + ships[ships[i].targetId].sizeW / 2 + (480 / scale - scrollx)) * scale, (ships[ships[i].targetId].pos.y + ships[ships[i].targetId].sizeH / 2 + (480 / scale - scrolly)) * scale);
				}
			}
		}

		if (ships[i].hp <= 0)
		{
			DestroyShip(i);
			i--;
		}
	}

	for (int i = 0; i < bulletsCount; i++)
	{
		if (abs(bullets[i].pos.x - scrollx) < 500 / scale && abs(bullets[i].pos.y - scrolly) < 500 / scale)
		{
			RenderAngleImage(bullets[i].textureId, bullets[i].pos, 8, 2, 255, bullets[i].rotateAngle);
		}

		if (devUI)
		{
			SDL_SetRenderDrawColor(ren, 0, 0, 255, 255);
			for (int j = 0; j < 4; j++)
			{
				SDL_RenderDrawLineF(ren, (bullets[i].collider.sides[j].pos1.x + (480 / scale - scrollx)) * scale, (bullets[i].collider.sides[j].pos1.y + (480 / scale - scrolly)) * scale, (bullets[i].collider.sides[j].pos2.x + (480 / scale - scrollx)) * scale, (bullets[i].collider.sides[j].pos2.y + (480 / scale - scrolly)) * scale);
			}
		}

		if (bullets[i].CheckActivity())
		{
			DestroyBullet(i);
			i--;
		}
		else
		{
			bool hit = false;
			for (int j = 0; j < shipsCount; j++)
			{
				if (ships[j].team != bullets[i].team)
				{
					if (CheckCollision(bullets[i].collider, ships[j].collider))
					{
						ships[j].hp -= bullets[i].damage;
						DestroyBullet(i);
						i--;
						hit = true;
						break;
					}
				}
			}
			if (!hit)
				bullets[i].Move();
		}
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
	int nextCamSwap = 3000;
	Init();

	srand(time(NULL));

	font = TTF_OpenFont("Fonts\\MainFont.ttf", 20);

	while (true)
	{
		newTime = SDL_GetTicks();
		delta = newTime - lastTime;
		lastTime = newTime;

		if (scrollship != -1)
		{
			scrollship = min(scrollship, shipsCount - 1);
			Lerp(scrollx, ships[scrollship].pos.x + ships[scrollship].sizeW / 2 * scale, 2.5);
			Lerp(scrolly, ships[scrollship].pos.y + ships[scrollship].sizeH / 2 * scale, 2.5);
		}
		Draw();
		MoveShips();

		if (newTime >= nextCamSwap)
		{
			nextCamSwap = newTime + 3500;
			scrollship = rand() % shipsCount;
		}

		if (delta < 16)
		{
			SDL_Delay(16 - delta);
		}
	}

	DeInit(0);

	return 0;
}