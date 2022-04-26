#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;
SDL_Surface* win_surf = NULL;

int winWdt = 960;
int winHgt = 960;

int x = 150, y = 150;

const int mapSize = 300;

const int cellsDensity = 6;
const int cellsFill = 6000;
const int antsCount = 6;

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

int GetTile(int map[mapSize][mapSize],int i, int j)
{
	if (map[i + 1][j] == 0 && map[i - 1][j] != 0 && map[i][j - 1] == 0 && map[i][j + 1] != 0)
		return 2;
	if (map[i + 1][j] == 0 && map[i][j - 1] != 0 && map[i][j + 1] != 0)
		return 3;
	return 8;
}

void Draw(int map[mapSize][mapSize])
{
	SDL_Texture* textures[9];
	textures[0] = SDL_CreateTextureFromSurface(ren, IMG_Load("GFX\\Tile0.png"));
	textures[1] = SDL_CreateTextureFromSurface(ren, IMG_Load("GFX\\Tile1.png"));
	textures[2] = SDL_CreateTextureFromSurface(ren, IMG_Load("GFX\\Tile2.png"));
	textures[3] = SDL_CreateTextureFromSurface(ren, IMG_Load("GFX\\Tile3.png"));
	textures[4] = SDL_CreateTextureFromSurface(ren, IMG_Load("GFX\\Tile4.png"));
	textures[5] = SDL_CreateTextureFromSurface(ren, IMG_Load("GFX\\Tile5.png"));
	textures[6] = SDL_CreateTextureFromSurface(ren, IMG_Load("GFX\\Tile6.png"));
	textures[7] = SDL_CreateTextureFromSurface(ren, IMG_Load("GFX\\Tile7.png"));
	textures[8] = SDL_CreateTextureFromSurface(ren, IMG_Load("GFX\\Tile8.png"));

	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderClear(ren);

	for (int i = 0; i < mapSize; i++)
		for (int j = 0; j < mapSize; j++)
		{
			SDL_Rect rect = { (i + 15 - x) * 32,(j + 15 - y) * 32,32,32 };
			if (map[i][j] == 1)
			{
				SDL_RenderCopy(ren, textures[GetTile(map,i,j)], NULL, &rect);
				//SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
				//SDL_RenderFillRect(ren, &rect);
			}
			else
			{
				SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
				SDL_RenderFillRect(ren, &rect);
			}
		}
	SDL_RenderPresent(ren);
}

#undef main;
int main()
{
	srand(time(NULL));
	int map[mapSize][mapSize];
	Init();

	Generate(map);

	Draw(map);

	SDL_Delay(10000);

	DeInit(0);
	return 0;
}