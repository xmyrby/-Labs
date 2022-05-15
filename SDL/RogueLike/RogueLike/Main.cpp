#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;
SDL_Surface* win_surf = NULL;

int winWdt = 960;
int winHgt = 960;


struct Player
{
	int x, y;
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

void Draw(int map[mapSize][mapSize])
{
	SDL_Texture* textures[20];
	textures[0] = SDL_CreateTextureFromSurface(ren, IMG_Load("GFX\\Tile0.png"));
	textures[1] = SDL_CreateTextureFromSurface(ren, IMG_Load("GFX\\Tile1.png"));
	textures[2] = SDL_CreateTextureFromSurface(ren, IMG_Load("GFX\\Tile2.png"));
	textures[3] = SDL_CreateTextureFromSurface(ren, IMG_Load("GFX\\Tile3.png"));
	textures[4] = SDL_CreateTextureFromSurface(ren, IMG_Load("GFX\\Tile4.png"));
	textures[5] = SDL_CreateTextureFromSurface(ren, IMG_Load("GFX\\Tile5.png"));
	textures[6] = SDL_CreateTextureFromSurface(ren, IMG_Load("GFX\\Tile6.png"));
	textures[7] = SDL_CreateTextureFromSurface(ren, IMG_Load("GFX\\Tile7.png"));
	textures[8] = SDL_CreateTextureFromSurface(ren, IMG_Load("GFX\\Tile8.png"));
	textures[9] = SDL_CreateTextureFromSurface(ren, IMG_Load("GFX\\Tile9.png"));
	textures[10] = SDL_CreateTextureFromSurface(ren, IMG_Load("GFX\\Tile10.png"));
	textures[11] = SDL_CreateTextureFromSurface(ren, IMG_Load("GFX\\Tile11.png"));
	textures[12] = SDL_CreateTextureFromSurface(ren, IMG_Load("GFX\\Tile12.png"));
	textures[13] = SDL_CreateTextureFromSurface(ren, IMG_Load("GFX\\Tile13.png"));
	textures[14] = SDL_CreateTextureFromSurface(ren, IMG_Load("GFX\\Tile14.png"));
	textures[15] = SDL_CreateTextureFromSurface(ren, IMG_Load("GFX\\Tile15.png"));
	textures[16] = SDL_CreateTextureFromSurface(ren, IMG_Load("GFX\\Tile16.png"));

	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderClear(ren);

	for (int i = player.x - 15; i < player.x + 16; i++)
		for (int j = player.y - 15; j < player.y + 16; j++)
		{
			SDL_Rect rect = { (i + 15 - player.x) * 32 - 16,(j + 15 - player.y) * 32 - 16,32,32 };
			if (map[i][j] == 1)
			{
				//SDL_RenderCopy(ren, textures[GetTile(map, i, j)], NULL, &rect);
				SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
				SDL_RenderFillRect(ren, &rect);
			}
			else
			{
				SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
				SDL_RenderFillRect(ren, &rect);
			}
		}

	SDL_Rect rect = { 464, 464,32,32 };
	SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
	SDL_RenderFillRect(ren, &rect);

	SDL_RenderPresent(ren);
}

void SpawnPlayer(int map[mapSize][mapSize])
{
	do
	{
		player.x = rand() % mapSize;
		player.y = rand() % mapSize;
	} while (map[player.x][player.y] != 0);
}

#undef main;
int main()
{
	srand(time(NULL));
	int map[mapSize][mapSize];
	Init();
	SDL_Event event;
	TTF_Font* font = TTF_OpenFont("Chava.ttf", 20);
	printf("%s\n", TTF_GetError());
	if (!font) {
		printf("Unable to open font"); exit(1);
	}

	char str[10] = "Great";
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, str, { 255, 0, 0, 255 });

	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(ren, textSurface);

	SDL_FreeSurface(textSurface);

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
				if (map[player.x][player.y - 1] == 0)
					player.y--;
			}
			else if (state[SDL_SCANCODE_DOWN])
			{
				if (map[player.x][player.y + 1] == 0)
					player.y++;
			}
			else if (state[SDL_SCANCODE_LEFT])
			{
				if (map[player.x - 1][player.y] == 0)
					player.x--;
			}
			else if (state[SDL_SCANCODE_RIGHT])
			{
				if (map[player.x + 1][player.y] == 0)
					player.x++;
			}

			Draw(map);
			SDL_Rect rect = { 10,10,200,20 };
			SDL_RenderCopy(ren, textTexture, NULL, &rect);
		}
	}
	TTF_CloseFont(font);

	DeInit(0);
	return 0;
}