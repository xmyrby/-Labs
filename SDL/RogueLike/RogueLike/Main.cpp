#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;
SDL_Surface* win_surf = NULL;
TTF_Font* font = NULL;
SDL_Texture* textures[2];

int winWdt = 960;
int winHgt = 960;

int moves = 0;

struct Player
{
	int x, y;
	int moves = 1;
	int attacks = 1;
};

Player player = { 150,150 };

const int mapSize = 300;
const int cellsDensity = 12;
const int cellsFill = 6000;
const int antsCount = 6;

void DeInit(char error)
{
	SDL_DestroyRenderer(ren);
	SDL_DestroyWindow(win);
	SDL_Quit();
	exit(error);
}

void LoadTextures()
{
	textures[0] = IMG_LoadTexture(ren, "GFX\\AttackMoves.png");
	textures[1] = IMG_LoadTexture(ren, "GFX\\MoveMoves.png");
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
}

bool CheckCell(int map[mapSize][mapSize], int x, int y)
{
	int weight = 0;
	for (int i = x; i < x + 5; i++)
		for (int j = y; j < y + 5; j++)
			if (map[i][j] != 0)
				weight++;

	if (weight < cellsDensity)
		return false;
	return true;
}

void Generate(int map[mapSize][mapSize])
{
	struct Ant
	{
		int x, y;
	};

	for (int i = 0; i < mapSize; i++)
		for (int j = 0; j < mapSize; j++)
			map[i][j] = 1;

	Ant ants[antsCount];
	int cells = 0;

	for (int i = 0; i < antsCount; i++)
	{
		ants[i] = { rand() % (mapSize / 2) + (mapSize / 4), rand() % (mapSize / 2) + (mapSize / 4) };
		map[ants[i].x][ants[i].y] = 0;
		cells++;
	}

	while (cells < cellsFill)
		for (int j = 0; j < antsCount; j++)
		{
			Ant ant = ants[j];

			for (int i = 0; i < 1000; i++)
			{
				int dir = rand() % 4;

				switch (dir)
				{
				case 0:
					if (ant.x > 1)
						ant.x--;
					break;
				case 1:
					if (ant.x < mapSize - 2)
						ant.x++;
					break;
				case 2:
					if (ant.y > 1)
						ant.y--;
					break;
				case 3:
					if (ant.y < mapSize - 2)
						ant.y++;
					break;
				default:
					break;
				}
				if (map[ant.x][ant.y] != 0 && CheckCell(map, ant.x - 2, ant.y - 2))
				{
					map[ant.x][ant.y] = 0;
					cells++;
				}
			}
		}
}

int GetTile(int map[mapSize][mapSize], int i, int j)
{
	if (map[i - 1][j] == 0 && map[i + 1][j] != 0 && map[i][j - 1] == 0 && map[i][j + 1] != 0 && map[i + 1][j + 1] != 0)
		return 0;
	if (map[i + 1][j] != 0 && map[i][j - 1] == 0 && map[i][j + 1] != 0 && map[i - 1][j] != 0)
		return 1;
	if (map[i + 1][j] == 0 && map[i - 1][j] != 0 && map[i][j - 1] == 0 && map[i][j + 1] != 0 && map[i - 1][j + 1] != 0)
		return 2;
	if (map[i + 1][j] == 0 && map[i][j - 1] != 0 && map[i][j + 1] != 0 && map[i - 1][j] != 0)
		return 3;
	if (map[i + 1][j] == 0 && map[i - 1][j] != 0 && map[i][j + 1] == 0 && map[i][j - 1] != 0 && map[i - 1][j - 1] != 0)
		return 4;
	if (map[i - 1][j] != 0 && map[i][j + 1] == 0 && map[i][j - 1] != 0 && map[i + 1][j] != 0)
		return 5;
	if (map[i - 1][j] == 0 && map[i + 1][j] != 0 && map[i][j + 1] == 0 && map[i][j - 1] != 0 && map[i + 1][j - 1] != 0)
		return 6;
	if (map[i - 1][j] == 0 && map[i][j - 1] != 0 && map[i][j + 1] != 0 && map[i + 1][j] != 0)
		return 7;
	if (map[i - 1][j] == 0 && map[i][j - 1] == 0 && map[i][j + 1] != 0 && map[i + 1][j] == 0)
		return 9;
	if (map[i - 1][j] != 0 && map[i][j - 1] == 0 && map[i][j + 1] == 0 && map[i + 1][j] == 0)
		return 10;
	if (map[i - 1][j] == 0 && map[i][j + 1] == 0 && map[i][j - 1] != 0 && map[i + 1][j] == 0)
		return 11;
	if (map[i - 1][j] == 0 && map[i][j - 1] == 0 && map[i][j + 1] == 0 && map[i + 1][j] != 0)
		return 12;
	if (map[i - 1][j] == 0 && map[i + 1][j] != 0 && map[i][j - 1] == 0 && map[i][j + 1] != 0 && map[i + 1][j + 1] == 0)
		return 13;
	if (map[i + 1][j] == 0 && map[i - 1][j] != 0 && map[i][j - 1] == 0 && map[i][j + 1] != 0 && map[i - 1][j + 1] == 0)
		return 14;
	if (map[i + 1][j] == 0 && map[i - 1][j] != 0 && map[i][j + 1] == 0 && map[i][j - 1] != 0 && map[i - 1][j - 1] == 0)
		return 15;
	if (map[i - 1][j] == 0 && map[i + 1][j] != 0 && map[i][j + 1] == 0 && map[i][j - 1] != 0 && map[i + 1][j - 1] == 0)
		return 16;
	return 8;
}

int RayTracing(int map[mapSize][mapSize], int x, int y)
{
	float ax = x, ay = y;
	float kx = player.x - x, ky = player.y - y;
	int lastx = x, lasty = y;
	int blocks = 0;
	while (x != player.x || y != player.y)
	{
		ax += kx / 40;
		ay += ky / 40;
		x = round(ax);
		y = round(ay);
		if (lastx != x || lasty != y)
		{
			if (map[x][y] == 1)
				blocks += 5;
			blocks += 1;
			lastx = x;
			lasty = y;
		}

	}
	return blocks;
}

int Max(int a, int b)
{
	if (a > b)
		return a;
	return b;
}

void Draw(int map[mapSize][mapSize])
{
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderClear(ren);

	for (int i = player.x - 15; i < player.x + 16; i++)
		for (int j = player.y - 15; j < player.y + 16; j++)
		{
			SDL_Rect rect = { (i + 15 - player.x) * 32 - 16,(j + 15 - player.y) * 32 - 16,32,32 };
			int blocks = RayTracing(map, i, j);
			if (map[i][j] == 1)
			{
				SDL_SetRenderDrawColor(ren, Max(15, 138 - blocks * 16), Max(15, 22 - blocks), Max(15, 31 - blocks * 2), 255);
				SDL_RenderFillRect(ren, &rect);
			}
			else
			{
				SDL_SetRenderDrawColor(ren, Max(15, 30 - blocks * 2), Max(15, 30 - blocks * 2), Max(15, 30 - blocks * 2), 255);
				SDL_RenderFillRect(ren, &rect);
			}
		}

	SDL_Rect rect = { 464, 464,32,32 };
	SDL_SetRenderDrawColor(ren, 114, 230, 221, 255);
	SDL_RenderFillRect(ren, &rect);
}

void SpawnPlayer(int map[mapSize][mapSize])
{
	do
	{
		player.x = rand() % mapSize;
		player.y = rand() % mapSize;
	} while (map[player.x][player.y] != 0);
}

int GetSize(const char* text)
{
	int count = 0;
	while (text[count] != '\0')
		count++;
	return count;
}

const char* CC(int var)
{
	char buff[10];

	_itoa_s(var, (char*)buff, 10, 10);
	return buff;
}

void PrintText(const char* text, int posx, int posy, int size)
{
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, text, { 255, 255, 255, 255 });

	SDL_Rect rect = { posx,posy, 0.75 * GetSize(text) * size,size };

	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(ren, textSurface);
	SDL_RenderCopy(ren, textTexture, NULL, &rect);

	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
}

void PrintText(int var, int posx, int posy, int size)
{
	char text[10];

	_itoa_s(var, (char*)text, 10, 10);

	SDL_Surface* textSurface = TTF_RenderText_Blended(font, text, { 255, 255, 255, 255 });

	SDL_Rect rect = { posx,posy, 0.75 * GetSize(text) * size,size };

	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(ren, textSurface);
	SDL_RenderCopy(ren, textTexture, NULL, &rect);

	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
}

void RenderImage(int textureId, int x, int y, int w, int h)
{
	SDL_Rect rect = { x,y,w,h };
	SDL_RenderCopy(ren, textures[textureId], NULL, &rect);
}

void DrawUI()
{
	PrintText("Move: #", 10, 18, 16);
	PrintText(moves+1, 96, 18, 16);
	RenderImage(0, 10, 52, 32, 32);
	PrintText(player.attacks, 52, 60, 16);
	RenderImage(1, 10, 94, 32, 32);
	PrintText(player.moves, 52, 104, 16);
}

void CheckMove()
{
	if (player.moves == 0 && player.attacks == 0)
	{
		moves++;
		player.moves++;
		player.attacks++;
	}
}

#undef main;
int main()
{
	srand(time(NULL));
	int map[mapSize][mapSize];
	Init();
	font = TTF_OpenFont("Fonts\\MainFont.ttf", 20);
	SDL_Event event;

	Generate(map);
	SpawnPlayer(map);

	Draw(map);

	while (true)
	{
		const Uint8* state = SDL_GetKeyboardState(NULL);
		SDL_PollEvent(&event);

		if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
		{
			if (state[SDL_SCANCODE_UP])
			{
				if (map[player.x][player.y - 1] == 0 && player.moves > 0)
				{
					player.y--;
					player.moves--;
				}
			}
			else if (state[SDL_SCANCODE_DOWN])
			{
				if (map[player.x][player.y + 1] == 0 && player.moves > 0)
				{
					player.y++;
					player.moves--;
				}
			}
			else if (state[SDL_SCANCODE_LEFT])
			{
				if (map[player.x - 1][player.y] == 0 && player.moves > 0)
				{
					player.x--;
					player.moves--;
				}
			}
			else if (state[SDL_SCANCODE_RIGHT])
			{
				if (map[player.x + 1][player.y] == 0 && player.moves > 0)
				{
					player.x++;
					player.moves--;
				}
			}
			else if (state[SDL_SCANCODE_SPACE])
			{
				player.moves = 0;
				player.attacks = 0;
			}

			CheckMove();

			Draw(map);
		}
		DrawUI();

		SDL_RenderPresent(ren);
	}
	TTF_CloseFont(font);

	DeInit(0);
	return 0;
}