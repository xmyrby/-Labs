#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;
SDL_Surface* win_surf = NULL;
TTF_Font* font = NULL;
SDL_Texture* textures[5];

int winWdt = 960;
int winHgt = 960;

int moves = 0;

const int MAP_SIZE = 300;
const int CELLS_DENSITY = 7;
const int CELLS_FILL = 6000;
const int ANTS_COUNT = 6;
const int ENEMIES_COUNT = 20;

struct Position
{
	int x, y;
};

struct Entity
{
	Position position;
	int health;
	int moves = 1;
	int attacks = 1;
	int damage = 1;
	int attackrange = 1;

	int x()
	{
		return position.x;
	}

	void x(int x)
	{
		position.x = x;
	}

	int y()
	{
		return position.y;
	}

	void y(int y)
	{
		position.y = y;
	}
};

struct Player : Entity
{
	int selectedEnemy = -1;
	int level = 1;
};

struct Enemy : Entity
{
	int type = 0;
};

Player player;

Enemy enemies[ENEMIES_COUNT];

int map[MAP_SIZE][MAP_SIZE];

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
	textures[2] = IMG_LoadTexture(ren, "GFX\\PlayerPawn.png");
	textures[3] = IMG_LoadTexture(ren, "GFX\\TigerPawn.png");
	textures[4] = IMG_LoadTexture(ren, "GFX\\Selection.png");
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

bool CheckCell(int x, int y)
{
	int weight = 0;
	for (int i = x; i < x + 5; i++)
		for (int j = y; j < y + 5; j++)
			if (map[i][j] != 0)
				weight++;

	if (weight < CELLS_DENSITY)
		return false;
	return true;
}

void Generate()
{
	struct Ant
	{
		Position position;
	};

	for (int i = 0; i < MAP_SIZE; i++)
		for (int j = 0; j < MAP_SIZE; j++)
			map[i][j] = 1;

	Ant ants[ANTS_COUNT];
	int cells = 0;

	for (int i = 0; i < ANTS_COUNT; i++)
	{
		ants[i] = { rand() % (MAP_SIZE / 2) + (MAP_SIZE / 4), rand() % (MAP_SIZE / 2) + (MAP_SIZE / 4) };
		map[ants[i].position.x][ants[i].position.y] = 0;
		cells++;
	}

	while (cells < CELLS_DENSITY)
		for (int j = 0; j < ANTS_COUNT; j++)
		{
			Ant ant = ants[j];

			for (int i = 0; i < 1000; i++)
			{
				int dir = rand() % 4;

				switch (dir)
				{
				case 0:
					if (ant.position.x > 1)
						ant.position.x--;
					break;
				case 1:
					if (ant.position.x < MAP_SIZE - 2)
						ant.position.x++;
					break;
				case 2:
					if (ant.position.y > 1)
						ant.position.y--;
					break;
				case 3:
					if (ant.position.y < MAP_SIZE - 2)
						ant.position.y++;
					break;
				default:
					break;
				}
				if (map[ant.position.x][ant.position.y] != 0 && CheckCell(ant.position.x - 2, ant.position.y - 2))
				{
					map[ant.position.x][ant.position.y] = 0;
					cells++;
				}
			}
		}
}

/*int GetTile(int i, int j)
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
}*/

int RayTracing(Position position)
{
	float ax = position.x, ay = position.y;
	float kx = player.x() - position.x, ky = player.y() - position.y;
	int lastx = position.x, lasty = position.y;
	int blocks = 0;
	if (abs(kx) == abs(ky))
		blocks++;
	while (position.x != player.x() || position.y != player.y())
	{
		ax += kx / 40;
		ay += ky / 40;
		position.x = round(ax);
		position.y = round(ay);
		if (lastx != position.x || lasty != position.y)
		{
			if (map[position.x][position.y] == 1)
				blocks += 5;
			blocks += 1;
			lastx = position.x;
			lasty = position.y;
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

int GetSize(const char* text)
{
	int count = 0;
	while (text[count] != '\0')
		count++;
	return count;
}

void PrintText(int var, Position position, int size)
{
	char text[10];

	_itoa_s(var, (char*)text, 10, 10);

	SDL_Surface* textSurface = TTF_RenderText_Blended(font, text, { 255, 255, 255, 255 });

	SDL_Rect rect = { position.x,position.y, 0.75 * GetSize(text) * size,size };

	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(ren, textSurface);
	SDL_RenderCopy(ren, textTexture, NULL, &rect);

	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
}

void PrintText(const char* text, Position position, int size)
{
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, text, { 255, 255, 255, 255 });

	SDL_Rect rect = { position.x,position.y, 0.75 * GetSize(text) * size,size };

	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(ren, textSurface);
	SDL_RenderCopy(ren, textTexture, NULL, &rect);

	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);
}

void RenderImage(int textureId, Position position, int w, int h, int alpha)
{
	SDL_Rect rect = { position.x,position.y,w,h };
	SDL_SetTextureAlphaMod(textures[textureId], alpha);
	SDL_RenderCopy(ren, textures[textureId], NULL, &rect);
}

bool CheckEntity(int posx, int posy)
{
	if (player.x() == posx && player.y() == posy)
		return false;
	for (int i = 0; i < ENEMIES_COUNT; i++)
		if (enemies[i].x() == posx && enemies[i].y() == posy)
			return false;
	return true;
}

int GetAlpha(int value, int b)
{
	int k = ceil((value - 15) / 7.6875);
	return Max(15, value - b * k);
}

void DrawUI()
{
	PrintText("Move: #", { 10,18 }, 16);
	PrintText(moves + 1, { 96, 18 }, 16);
	RenderImage(0, { 10, 52 }, 32, 32, 255);
	PrintText(player.attacks, { 52, 60 }, 16);
	RenderImage(1, { 10, 94 }, 32, 32, 255);
	PrintText(player.moves, { 52, 104 }, 16);
	PrintText("Health: ", { 10, 926 }, 16);
	PrintText(player.health, { 102, 926 }, 16);

	if (player.selectedEnemy >= 0)
		if (RayTracing(enemies[player.selectedEnemy].position) > 5)
			player.selectedEnemy = -1;
		else
		{
			Position position;
			position.x = (enemies[player.selectedEnemy].x() + 15 - player.x()) * 32 - 16;
			position.y = (enemies[player.selectedEnemy].y() + 15 - player.y()) * 32 - 16;
			RenderImage(4, position, 32, 32, 255);
		}

}

void Draw()
{
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderClear(ren);

	for (int i = player.x() - 15; i < player.x() + 16; i++)
		for (int j = player.y() - 15; j < player.y() + 16; j++)
		{
			SDL_Rect rect = { (i + 15 - player.x()) * 32 - 16,(j + 15 - player.y()) * 32 - 16,32,32 };
			int blocks = RayTracing({ i, j });
			if (map[i][j] == 1)
			{
				SDL_SetRenderDrawColor(ren, GetAlpha(138, blocks), GetAlpha(22, blocks), GetAlpha(31, blocks), 255);
				SDL_RenderFillRect(ren, &rect);
			}
			else
			{
				SDL_SetRenderDrawColor(ren, GetAlpha(30, blocks), GetAlpha(30, blocks), GetAlpha(30, blocks), 255);
				SDL_RenderFillRect(ren, &rect);
			}
		}

	SDL_Rect rect = { 464, 464,32,32 };
	SDL_SetRenderDrawColor(ren, 114, 230, 221, 255);
	SDL_RenderFillRect(ren, &rect);
	RenderImage(2, { 464, 464 }, 32, 32, 255);

	SDL_SetRenderDrawColor(ren, 114, 230, 221, 255);
	for (int i = 0; i < ENEMIES_COUNT; i++)
	{
		int blocks = RayTracing(enemies[i].position);
		rect = { (enemies[i].x() + 15 - player.x()) * 32 - 16, (enemies[i].y() + 15 - player.y()) * 32 - 16,32,32 };
		SDL_SetRenderDrawColor(ren, GetAlpha(198, blocks), GetAlpha(101, blocks), GetAlpha(202, blocks), 255);
		SDL_RenderFillRect(ren, &rect);
		if (blocks <= 5)
		{
			RenderImage(3, { rect.x, rect.y }, 32, 32, 255 - blocks * 33);
		}
	}

	DrawUI();
}

void SpawnPlayer()
{
	do
	{
		player.x(rand() % MAP_SIZE);
		player.y(rand() % MAP_SIZE);
	} while (map[player.x()][player.y()] != 0);
	player.health = 10;
}

void SpawnEnemies()
{
	for (int i = 0; i < ENEMIES_COUNT; i++)
	{
		Enemy enemy;
		do
		{
			enemy.x(rand() % MAP_SIZE);
			enemy.y(rand() % MAP_SIZE);
		} while (map[enemy.x()][enemy.y()] != 0);
		enemies[i] = enemy;
	}
}

int MinWd(int a, int b)
{
	if (a < b && a > 0)
		return a;
	return b;
}

bool Comp(Position position1, Position position2)
{
	if (position1.x == position2.x && position1.y == position2.y)
		return true;
	return false;
}

void SetWd(Position pos, Position end, int weights[MAP_SIZE][MAP_SIZE], int dir, int tes)
{
	if (map[pos.x][pos.y] == 0 && !Comp(pos, end) && tes < 20)
	{
		weights[pos.x][pos.y] = MinWd(weights[pos.x - 1][pos.y], MinWd(weights[pos.x + 1][pos.y], MinWd(weights[pos.x][pos.y - 1], weights[pos.x][pos.y + 1]))) + 1;

		int d = weights[pos.x - 1][pos.y];
		if (dir != 0)
			SetWd({ pos.x - 1,pos.y }, end, weights, 0, tes + 1);
		d = weights[pos.x + 1][pos.y];
		if (dir != 1)
			SetWd({ pos.x + 1,pos.y }, end, weights, 1, tes + 1);
		d = weights[pos.x][pos.y - 1];
		if (dir != 2)
			SetWd({ pos.x,pos.y - 1 }, end, weights, 2, tes + 1);
		d = weights[pos.x][pos.y + 1];
		if (dir != 3)
			SetWd({ pos.x,pos.y + 1 }, end, weights, 3, tes + 1);
	}
}

void FindPath(Position start, Position end)
{
	SDL_Rect rect = { (end.x + 15 - player.x()) * 32 - 16, (end.y + 15 - player.y()) * 32 - 16,32,32 };
	SDL_SetRenderDrawColor(ren, 0, 255, 0, 255);
	SDL_RenderFillRect(ren, &rect);
	SDL_RenderPresent(ren);

	int weights[MAP_SIZE][MAP_SIZE];
	for (int i = 0; i < MAP_SIZE; i++)
		for (int j = 0; j < MAP_SIZE; j++)
			weights[i][j] = 0;

	SetWd({ start.x - 1,start.y }, end, weights, 0, 0);
	SetWd({ start.x + 1,start.y }, end, weights, 1, 0);
	SetWd({ start.x,start.y - 1 }, end, weights, 2, 0);
	SetWd({ start.x,start.y + 1 }, end, weights, 3, 0);

	Position cur = start;

	while (!Comp(cur, end))
	{
		int md = MinWd(weights[cur.x - 1][cur.y], MinWd(weights[cur.x + 1][cur.y], MinWd(weights[cur.x][cur.y - 1], weights[cur.x][cur.y + 1]))) + 1;
		SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
		if (md == weights[cur.x - 1][cur.y])
		{
			SDL_RenderDrawLine(ren, cur.x, cur.y, cur.x - 1, cur.y);
			SDL_RenderPresent(ren);
			cur.x -= 1;
		}
		else if (md == weights[cur.x + 1][cur.y])
		{
			SDL_RenderDrawLine(ren, cur.x, cur.y, cur.x + 1, cur.y);
			SDL_RenderPresent(ren);
			cur.x += 1;
		}
		else if (md == weights[cur.x][cur.y - 1])
		{
			SDL_RenderDrawLine(ren, cur.x, cur.y, cur.x, cur.y - 1);
			SDL_RenderPresent(ren);
			cur.y -= 1;
		}
		else if (md == weights[cur.x][cur.y + 1])
		{
			SDL_RenderDrawLine(ren, cur.x, cur.y, cur.x, cur.y + 1);
			SDL_RenderPresent(ren);
			cur.y += 1;
		}
	}
}

void MakeEnemyMove(Enemy& enemy)
{
	if (RayTracing(enemy.position) <= 5)
	{
		if (enemy.x() < player.x() && map[enemy.x() + 1][enemy.y()] == 0 && CheckEntity(enemy.x() + 1, enemy.y()))
		{
			enemy.position.x++;
		}
		else if (enemy.x() > player.x() && map[enemy.x() - 1][enemy.y()] == 0 && CheckEntity(enemy.x() - 1, enemy.y()))
		{
			enemy.position.x--;
		}
		else if (enemy.y() < player.y() && map[enemy.x()][enemy.y() + 1] == 0 && CheckEntity(enemy.x(), enemy.y() + 1))
		{
			enemy.position.y++;
		}
		else if (enemy.y() > player.y() && map[enemy.x()][enemy.y() - 1] == 0 && CheckEntity(enemy.x(), enemy.y() - 1))
		{
			enemy.position.y--;
		}
	}
}

void CheckMove()
{
	if (player.moves == 0 && player.attacks == 0)
	{
		moves++;
		player.moves++;
		player.attacks++;

		for (int i = 0; i < ENEMIES_COUNT; i++)
		{
			MakeEnemyMove(enemies[i]);
		}
	}
}

int CheckSelection(Position position)
{
	position.x = round(position.x + 16) / 32 + player.x() - 15;
	position.y = round(position.y + 16) / 32 + player.y() - 15;
	for (int i = 0; i < ENEMIES_COUNT; i++)
	{
		if (position.x == enemies[i].x() && position.y == enemies[i].y())
			if (RayTracing(position) <= 5)
				return i;
	}
	return -1;
}

#undef main;
int main()
{
	srand(time(NULL));
	Init();
	Position _mouse{ 0,0 };

	bool _down = false;
	font = TTF_OpenFont("Fonts\\MainFont.ttf", 20);
	SDL_Event event;

	Generate();
	SpawnPlayer();
	SpawnEnemies();

	Draw();

	while (true)
	{
		const Uint8* state = SDL_GetKeyboardState(NULL);

		SDL_PumpEvents();
		Uint32 events = SDL_GetMouseState(&_mouse.x, &_mouse.y);

		if ((events & SDL_BUTTON_LMASK) != 0 && !_down)
		{
			_down = true;
			player.selectedEnemy = CheckSelection(_mouse);
			Draw();
			if (player.selectedEnemy == -1)
				FindPath(player.position, { (_mouse.x + 16) / 32 + player.x() - 15,(_mouse.y + 16) / 32 + player.y() - 15 });
		}
		if ((events & SDL_BUTTON_LMASK) == 0)
			_down = false;

		SDL_PollEvent(&event);

		if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
		{
			if (state[SDL_SCANCODE_W])
			{
				if (map[player.x()][player.y() - 1] == 0 && player.moves > 0 && CheckEntity(player.x(), player.y() - 1))
				{
					player.position.y--;
					player.moves--;
				}
			}
			else if (state[SDL_SCANCODE_S])
			{
				if (map[player.x()][player.y() + 1] == 0 && player.moves > 0 && CheckEntity(player.x(), player.y() + 1))
				{
					player.position.y++;
					player.moves--;
				}
			}
			else if (state[SDL_SCANCODE_A])
			{
				if (map[player.x() - 1][player.y()] == 0 && player.moves > 0 && CheckEntity(player.x() - 1, player.y()))
				{
					player.position.x--;
					player.moves--;
				}
			}
			else if (state[SDL_SCANCODE_D])
			{
				if (map[player.x() + 1][player.y()] == 0 && player.moves > 0 && CheckEntity(player.x() + 1, player.y()))
				{
					player.position.x++;
					player.moves--;
				}
			}
			else if (state[SDL_SCANCODE_SPACE])
			{
				player.moves = 0;
				player.attacks = 0;
			}

			CheckMove();
			Draw();
		}

		SDL_RenderPresent(ren);
	}
	TTF_CloseFont(font);

	DeInit(0);
	return 0;
}