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
bool fpsShow = false;

int winWdt = 960;
int winHgt = 960;

float scrollx = 480, scrolly = 480;
float scale = 1;

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

struct Queue
{
	int count;
	bool shot[3];
	int maxs[3];
	int counter[3];
};

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

	float damage;

	Bullet(Position posC, int sizeWC, int sizeHC, float rotateAngleC, float motionAngleC, int textureId, int destroyTime, int team, float damage) :textureId(textureId), destroyTime(destroyTime), team(team), damage(damage) {
		pos = posC;
		sizeW = sizeWC;
		sizeH = sizeHC;
		rotateAngle = rotateAngleC;
		motionAngle = motionAngleC;
		CalculateSides();
	}

	void Move()
	{
		pos.x += cos(motionAngle) * 14;
		pos.y += sin(motionAngle) * 14;
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

struct Turret : Object
{
	int textureId;
	int targetId = -1;
	int type;
	int rotating;
	float damage;
	int lastShot;
	int shotInterval;
	int shotRange;
	Position offset;
	int queueType;
	int queue;
};

struct SpaceShip : Object
{
	float hp;
	float maxHp;

	float speed;
	float maxSpeed;
	float acceleration;
	int detectRange;

	float rotateSpeed;

	int team;
	int type;

	int targetId;

	Queue queue;

	Turret* turrets;
	int turretsCount;

	int GetTurretTarget(Turret turret)
	{
		if (turret.targetId > -1)
		{
			if (ships[targetId].team == team || shipsCount >= turret.targetId)
				return -1;
			if (Distance(turret.pos, ships[targetId].pos) > turret.shotRange)
				return -1;
		}
		else
			for (int i = 0; i < shipsCount; i++)
			{
				if (Distance(turret.pos, ships[i].pos) <= turret.shotRange && ships[i].team != team)
					return i;
			}
		return -1;
	}

	void GetTarget()
	{
		if (targetId > -1)
		{
			if (ships[targetId].team == team || shipsCount >= targetId)
				targetId = -1;
			if (Distance(pos, ships[targetId].pos) > detectRange)
				targetId = -1;
		}
		else
			for (int i = 0; i < shipsCount; i++)
			{
				if (Distance(pos, ships[i].pos) <= detectRange && ships[i].team != team)
					targetId = i;
			}

		for (int i = 0; i < turretsCount; i++)
		{
			turrets[i].targetId = -1;
			if (!turrets[i].rotating)
				turrets[i].targetId = targetId;
			else
				turrets[i].targetId = GetTurretTarget(turrets[i]);
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


		if (speed < maxSpeed)
			speed += acceleration;
		pos.x += cos(motionAngle) * speed;
		pos.y += sin(motionAngle) * speed;


		for (int i = 0; i < turretsCount; i++)
		{
			turrets[i].pos = GetPosRotated(turrets[i].offset.x, turrets[i].offset.y);
			if (turrets[i].targetId > -1)
			{
				if (turrets[i].rotating)
				{
					Position targetPos = ships[turrets[i].targetId].pos;
					targetPos.x += ships[turrets[i].targetId].sizeW / 2;
					targetPos.y += ships[turrets[i].targetId].sizeH / 2;
					Position firePos = GetPosRotated(turrets[i].offset.x, turrets[i].offset.y);
					firePos.x += turrets[i].sizeW / 2;
					firePos.y += turrets[i].sizeH / 2;
					turrets[i].rotateAngle = GetAngle(targetPos, firePos) * GRAD;

				}
				if (newTime >= turrets[i].lastShot + 150)
				{
					turrets[i].lastShot = newTime;
					if (turrets[i].type == 0)
					{
						if (turrets[i].queue == queue.counter[turrets[i].queueType])
						{
							queue.shot[turrets[i].queueType] = true;
							if (!turrets[i].rotating && Distance(turrets[i].pos, ships[i].pos) <= turrets[i].shotRange)
							{
								Bullet bullet(GetPosRotated(turrets[i].offset.x, turrets[i].offset.y), 8, 2, rotateAngle, rotateAngle * RAD, 20 + team, newTime + 1000, team, turrets[i].damage);
								AddBullet(bullet);
							}
							else
							{
								Bullet bullet(GetPosRotated(turrets[i].offset.x, turrets[i].offset.y), 8, 2, turrets[i].rotateAngle, turrets[i].rotateAngle * RAD, 20 + team, newTime + 1000, team, turrets[i].damage);
								AddBullet(bullet);
							}
						}
					}
				}
			}
		}

		for (int i = 0; i < queue.count; i++)
		{
			if (queue.shot[i])
			{
				queue.counter[i] += 1;
				queue.counter[i] %= queue.maxs[i];
				queue.shot[i] = false;
			}
		}

		float rtA = motionAngle * GRAD;
		AngularLerp(rtA, rotateAngle, 0.5);
		motionAngle = rtA * RAD;
		CalculateSides();

		if (targetId != -1)
		{
			Position targetPos = ships[targetId].pos;
			targetPos.x += ships[targetId].sizeW / 2;
			targetPos.y += ships[targetId].sizeH / 2;
			Position firePos = pos;
			firePos.x += sizeW / 2;
			firePos.y += sizeH / 2;
			AngularLerp(rotateAngle, GetAngle(targetPos, firePos) * GRAD, rotateSpeed);
		}
		else
		{
			for (int i = 0; i < turretsCount; i++)
			{
				turrets[i].rotateAngle = rotateAngle;
			}
			rotateAngle += rand() % 3 - 1;
		}
		for (int i = 0; i < turretsCount; i++)
			turrets[i].pos = GetPosRotated(turrets[i].offset.x, turrets[i].offset.y);
	}
};

SpaceShip* spaceShipTypes;
int spaceShipTypesCount;

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
}

void SpawnShips()
{
	shipsCount = 50;

	ships = (SpaceShip*)realloc(ships, sizeof(SpaceShip) * shipsCount);

	for (int i = 0; i < shipsCount; i++)
	{
		int type = 0;
		if (i % 10 == 0)
			type = 2;

		ships[i] = spaceShipTypes[type];
		ships[i].type = type;
		ships[i].hp = ships[i].maxHp;
		if (i % 10 == 0)
		{
			ships[i].pos.x = 750;
			ships[i].pos.y = 750;
			ships[i].team = 1;
		}
		else
		{
			ships[i].pos.x = 500 + rand() % 250;
			ships[i].pos.y = 500 + rand() % 250;
			ships[i].team = 0;
		}

		ships[i].speed = 0;
		ships[i].motionAngle = 0 + rand() % 1000;
		ships[i].rotateAngle = 0 + rand() % 1000;

		ships[i].targetId = 0;

		ships[i].turrets = (Turret*)malloc(sizeof(Turret) * ships[i].turretsCount);
		for (int j = 0; j < ships[i].turretsCount; j++)
		{
			ships[i].turrets[j] = spaceShipTypes[type].turrets[j];
		}

		for (int j = 0; j < ships[i].queue.count; j++)
		{
			ships[i].queue.maxs[j] = spaceShipTypes[type].queue.maxs[j];
			ships[i].queue.counter[j] = 0;
		}
	}
}

void InitShips()
{
	FILE* ft;
	if (fopen_s(&ft, "Params\\Ships.txt", "rt") != 0)
	{
		exit(1);
	}
	fscanf_s(ft, "%d", &spaceShipTypesCount);

	spaceShipTypes = (SpaceShip*)malloc(sizeof(SpaceShip) * spaceShipTypesCount);

	for (int i = 0; i < spaceShipTypesCount; i++)
	{
		fscanf_s(ft, "%d %d %f %f %f %f %d %d %d", &spaceShipTypes[i].sizeW, &spaceShipTypes[i].sizeH, &spaceShipTypes[i].maxHp, &spaceShipTypes[i].maxSpeed, &spaceShipTypes[i].acceleration, &spaceShipTypes[i].rotateSpeed, &spaceShipTypes[i].turretsCount, &spaceShipTypes[i].detectRange, &spaceShipTypes[i].queue.count);

		for (int j = 0; j < spaceShipTypes[i].queue.count; j++)
		{
			fscanf_s(ft, "%d", &spaceShipTypes[i].queue.maxs[j]);
		}

		spaceShipTypes[i].turrets = (Turret*)malloc(sizeof(Turret) * spaceShipTypes[i].turretsCount);
		for (int j = 0; j < spaceShipTypes[i].turretsCount; j++)
			fscanf_s(ft, "%d %d %d %d %d %f %d %f %f %d %d %d", &spaceShipTypes[i].turrets[j].sizeW, &spaceShipTypes[i].turrets[j].sizeH, &spaceShipTypes[i].turrets[j].textureId, &spaceShipTypes[i].turrets[j].type, &spaceShipTypes[i].turrets[j].rotating, &spaceShipTypes[i].turrets[j].damage, &spaceShipTypes[i].turrets[j].shotInterval, &spaceShipTypes[i].turrets[j].offset.x, &spaceShipTypes[i].turrets[j].offset.y, &spaceShipTypes[i].turrets[j].shotRange, &spaceShipTypes[i].turrets[j].queueType, &spaceShipTypes[i].turrets[j].queue);
	}

	SpawnShips();
}

void LoadTextures()
{
	textures[0] = IMG_LoadTexture(ren, "GFX\\BlueSpaceShip0.png");
	textures[1] = IMG_LoadTexture(ren, "GFX\\BlueSpaceShip1.png");
	textures[2] = IMG_LoadTexture(ren, "GFX\\BlueSpaceShip2.png");
	textures[10] = IMG_LoadTexture(ren, "GFX\\RedSpaceShip0.png");
	textures[11] = IMG_LoadTexture(ren, "GFX\\RedSpaceShip1.png");
	textures[12] = IMG_LoadTexture(ren, "GFX\\RedSpaceShip2.png");
	textures[20] = IMG_LoadTexture(ren, "GFX\\BlueShot.png");
	textures[21] = IMG_LoadTexture(ren, "GFX\\RedShot.png");
	textures[50] = IMG_LoadTexture(ren, "GFX\\Turret0.png");
	textures[51] = IMG_LoadTexture(ren, "GFX\\Turret1.png");
	textures[52] = IMG_LoadTexture(ren, "GFX\\Turret2.png");
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

void SetCam()
{
	Position minPos{ 100000000,100000000 };
	Position maxPos{ -100000000 ,-100000000 };
	for (int i = 0; i < shipsCount; i++)
	{
		minPos.x = min(ships[i].pos.x, minPos.x);
		minPos.y = min(ships[i].pos.y, minPos.y);
		maxPos.x = max(ships[i].pos.x, maxPos.x);
		maxPos.y = max(ships[i].pos.y, maxPos.y);
	}

	scale = min(960 / (maxPos.x - minPos.x), 960 / (maxPos.y - minPos.y))/1.5;
	Lerp(scrollx, minPos.x + (maxPos.x - minPos.x) / 2, 2.5);
	Lerp(scrolly, minPos.y + (maxPos.y - minPos.y) / 2, 2.5);
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

	for (int i = 0; i < shipsCount; i++)
	{
		if (abs(ships[i].pos.x - scrollx) < 500 / scale && abs(ships[i].pos.y - scrolly) < 500 / scale)
		{
			if (devUI)
				PrintText(ships[i].hp, { ships[i].pos.x,ships[i].pos.y + 34 }, 16, 255, 0);

			RenderAngleImage(ships[i].type + ships[i].team * 10, ships[i].pos, ships[i].sizeW, ships[i].sizeH, 255, ships[i].rotateAngle);
			for (int j = 0; j < ships[i].turretsCount; j++)
				if (ships[i].turrets[j].textureId != 0)
				{
					Position pos = ships[i].turrets[j].pos;
					pos.x -= ships[i].turrets[j].sizeW / 2;
					pos.y -= ships[i].turrets[j].sizeH / 2;
					RenderAngleImage(ships[i].turrets[j].textureId, pos, ships[i].turrets[j].sizeW, ships[i].turrets[j].sizeH, 255, ships[i].turrets[j].rotateAngle);

				}

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
					if (Distance(bullets[i].pos, ships[j].pos) <= ships[j].sizeH + ships[j].sizeW)
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
	Init();

	srand(time(NULL));

	font = TTF_OpenFont("Fonts\\MainFont.ttf", 20);

	while (true)
	{
		newTime = SDL_GetTicks();
		delta = newTime - lastTime;
		lastTime = newTime;

		SetCam();
		Draw();
		MoveShips();

		if (delta < 16)
		{
			SDL_Delay(16 - delta);
		}
	}

	DeInit(0);

	return 0;
}