//сделать интерфейс с выбором сложности. В зависимости от сложности будет меняться дальность видимости.

#include <SDL_image.h>
#include <SDL.h>
#include <iostream>

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;

int winWdt = 840;
int winHgt = 840;

struct Rgb
{
	int red;
	int green;
	int blue;
};

Rgb rgbBack, rgbFace;

struct Player
{
	int x;
	int y;
};

struct Cell
{
	bool left;
	bool right;
	bool top;
	bool bottom;
};

void Open(Cell map[20][20], int direction, int x, int y)
{

	switch (direction)
	{
	case 0:
	{
		map[x][y].left = true;
		map[x - 1][y].right = true;
		break;
	}
	case 1:
	{
		map[x][y].right = true;
		map[x + 1][y].left = true;
		break;
	}
	case 2:
	{
		map[x][y].top = true;
		map[x][y - 1].bottom = true;
		break;
	}
	case 3:
	{
		map[x][y].bottom = true;
		map[x][y + 1].top = true;
		break;
	}
	default:
		break;
	}

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


int Rnd(int start, int end)
{
	return rand() % (end - start + 1) + start;
}

void RandColor()
{
	int mainColor = Rnd(0, 2);
	switch (mainColor)
	{
	case 0:
	{
		rgbBack.blue = Rnd(160, 185);
		rgbBack.green = Rnd(30, 100);
		rgbBack.red = Rnd(30, 100);

		rgbFace.blue = rgbBack.blue + 70;
		rgbFace.green = rgbBack.green + 15;
		rgbFace.red = rgbBack.red + 15;
		break;
	}
	case 1:
	{
		rgbBack.blue = Rnd(30, 100);
		rgbBack.green = Rnd(160, 185);
		rgbBack.red = Rnd(30, 100);

		rgbFace.blue = rgbBack.blue + 15;
		rgbFace.green = rgbBack.green + 70;
		rgbFace.red = rgbBack.red + 15;
		break;
	}
	case 2:
	{
		rgbBack.blue = Rnd(30, 100);
		rgbBack.green = Rnd(30, 100);
		rgbBack.red = Rnd(160, 185);

		rgbFace.blue = rgbBack.blue + 15;
		rgbFace.green = rgbBack.green + 15;
		rgbFace.red = rgbBack.red + 70;
		break;
	}
	default:
		break;
	}
}

int GetCellWeight(Cell cell)
{
	return int(!cell.left) + int(!cell.right) + int(!cell.top) + int(!cell.bottom);
}

int Max(int a, int b)
{
	if (a > b)
		return a;
	return b;
}

int Min(int a, int b)
{
	if (a < b)
		return a;
	return b;
}

void DrawRect(Cell cell, int x, int y, int offset)
{
	SDL_Rect rect;

	if (cell.left == false)
	{
		rect = { 10 + x * 40,10 - offset + y * 40,20,60 };
		SDL_RenderFillRect(ren, &rect);
	}
	if (cell.right == false)
	{
		rect = { 50 + x * 40,10 - offset + y * 40,20,60 };
		SDL_RenderFillRect(ren, &rect);
	}
	if (cell.top == false)
	{
		rect = { 10 + x * 40,10 - offset + y * 40,60,20 };
		SDL_RenderFillRect(ren, &rect);
	}
	if (cell.bottom == false)
	{
		rect = { 10 + x * 40,50 - offset + y * 40,60,20 };
		SDL_RenderFillRect(ren, &rect);
	}
}

void DrawMap(Cell map[20][20], Player player, float dist, bool lerp)
{
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			int distance = Min(Max((pow(pow((player.x - i), 2) + pow((player.y - j), 2), 0.5)) - 1, 0) * 75, Max((pow(pow(19 - i, 2) + pow(-j, 2), 0.5)) - 1, 0) * 100);
			distance *= dist;

			SDL_SetRenderDrawColor(ren, Max(rgbBack.red - distance, 35), Max(rgbBack.green - distance, 35), Max(rgbBack.blue - distance, 35), 0);
			DrawRect(map[i][j], i, j, 0);

			SDL_SetRenderDrawColor(ren, Max(rgbFace.red - distance, 35), Max(rgbFace.green - distance, 35), Max(rgbFace.blue - distance, 35), 0);
			DrawRect(map[i][j], i, j, 5);
		}
	}
}

void Drawer(Cell map[20][20], Player player, float dist, SDL_Rect rects[2], bool lerp)
{
	if (!lerp)
	{
		SDL_SetRenderDrawColor(ren, 35, 35, 35, 0);
		SDL_RenderClear(ren);
		SDL_SetRenderDrawColor(ren, 255 - rgbFace.red, 255 - rgbFace.green, 255 - rgbFace.blue, 0);
		SDL_RenderFillRect(ren, &rects[0]);
	}


	DrawMap(map, player, dist, lerp);

	if (!lerp)
	{
		SDL_SetRenderDrawColor(ren, 255 - rgbBack.red, 255 - rgbBack.green, 255 - rgbBack.blue, 0);
		SDL_RenderFillRect(ren, &rects[1]);
	}

	SDL_RenderPresent(ren);
}

void DrawFullMap3D(Cell map[20][20], Player player, float dist, int direction, bool lerp)
{
	SDL_SetRenderDrawColor(ren, 35, 35, 35, 0);
	SDL_RenderClear(ren);

	SDL_Rect rects[2];

	switch (direction)
	{
	case -1:
	{
		rects[0] = { 30 + player.x * 40,25 + player.y * 40,20,25 };
		rects[1] = { 30 + player.x * 40,25 + player.y * 40,20,20 };
		Drawer(map, player, dist, rects, lerp);
		break;
	}
	default:
	{
		for (int i = 0; i <= 40; i += 4)
		{
			switch (direction)
			{
			case 0:
			{
				rects[0] = { 30 + (player.x + 1) * 40 - i,25 + player.y * 40,20 + i,25 };
				rects[1] = { 30 + (player.x + 1) * 40 - i,25 + player.y * 40,20 + i,20 };
				Drawer(map, player, dist, rects, lerp);
				SDL_Delay(1);
				break;
			}
			case 1:
			{
				rects[0] = { 30 + (player.x - 1) * 40,25 + player.y * 40,20 + i,25 };
				rects[1] = { 30 + (player.x - 1) * 40,25 + player.y * 40,20 + i,20 };
				Drawer(map, player, dist, rects, lerp);
				SDL_Delay(1);
				break;
			}
			case 2:
			{
				rects[0] = { 30 + player.x * 40,25 + (player.y + 1) * 40 - i,20,25 + i };
				rects[1] = { 30 + player.x * 40,25 + (player.y + 1) * 40 - i,20,20 + i };
				Drawer(map, player,
					dist, rects, lerp);
				SDL_Delay(1);
				break;
			}
			case 3:
			{
				rects[0] = { 30 + player.x * 40,25 + (player.y - 1) * 40,20,25 + i };
				rects[1] = { 30 + player.x * 40,25 + (player.y - 1) * 40,20,20 + i };
				Drawer(map, player, dist, rects, lerp);
				SDL_Delay(1);
				break;
			}
			default:
				break;
			}
		}
		for (int i = 0; i <= 40; i += 8)
		{
			switch (direction)
			{
			case 0:
			{
				rects[0] = { 30 + player.x * 40,25 + player.y * 40,60 - i,25 };
				rects[1] = { 30 + player.x * 40,25 + player.y * 40,60 - i,20 };
				Drawer(map, player, dist, rects, lerp);
				SDL_Delay(1);
				break;
			}
			case 1:
			{
				rects[0] = { 30 + (player.x - 1) * 40 + i,25 + player.y * 40,60 - i,25 };
				rects[1] = { 30 + (player.x - 1) * 40 + i,25 + player.y * 40,60 - i,20 };
				Drawer(map, player, dist, rects, lerp);
				SDL_Delay(1);
				break;
			}
			case 2:
			{
				rects[0] = { 30 + player.x * 40,25 + player.y * 40,20,65 - i };
				rects[1] = { 30 + player.x * 40,25 + player.y * 40,20,60 - i };
				Drawer(map, player, dist, rects, lerp);
				SDL_Delay(1);
				break;
			}
			case 3:
			{
				rects[0] = { 30 + player.x * 40,25 + (player.y - 1) * 40 + i,20,65 - i };
				rects[1] = { 30 + player.x * 40,25 + (player.y - 1) * 40 + i,20,60 - i };
				Drawer(map, player, dist, rects, lerp);
				SDL_Delay(1);
				break;
			}
			default:
				break;
			}
		}
		break;
	}
	}
}

void MovePlayer(Cell map[20][20], Player& player, int direction)
{
	int dir = -1;
	switch (direction)
	{
	case 0:
	{
		if (map[player.x][player.y].left == true && player.x > 0)
		{
			player.x--;
			dir = direction;
		}
		break;
	}
	case 1:
	{
		if (map[player.x][player.y].right == true && player.x < 19)
		{
			player.x++;
			dir = direction;
		}
		break;
	}
	case 2:
	{
		if (map[player.x][player.y].top == true && player.y > 0)
		{
			player.y--;
			dir = direction;
		}
		break;
	}
	case 3:
	{
		if (map[player.x][player.y].bottom == true && player.y < 19)
		{
			player.y++;
			dir = direction;
		}
		break;
	}
	default:
		break;
	}

	DrawFullMap3D(map, player, 1, dir, 0);
}

void GenerateMap(Cell map[20][20], bool startScreen)
{
	struct Point
	{
		int x;
		int y;
	};

	struct Root
	{
		Point point;
		int branchCount = 0;
		Point branchPoints[100];

		void addBranch(Point branch)
		{
			branchPoints[branchCount] = branch;
			branchCount++;
		}

		void Connect(int branchId, Cell map[20][20])
		{
			Point branch = branchPoints[branchId];

			int xDif = branch.x - point.x;
			int yDif = branch.y - point.y;

			if (xDif == -1)
			{
				Open(map, 0, point.x, point.y);
			}
			else if (xDif == 1)
			{
				Open(map, 1, point.x, point.y);
			}
			else if (yDif == -1)
			{
				Open(map, 2, point.x, point.y);
			}
			else if (yDif == 1)
			{
				Open(map, 3, point.x, point.y);
			}
		}
	};

	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
		{
			map[i][j].left = false;

			map[i][j].right = false;

			map[i][j].top = false;

			if (j == 19 && i == 0)
				map[i][j].bottom = true;
			else
				map[i][j].bottom = false;
		}

	if (startScreen)
	{
		Open(map, 3, 2, 6);
		Open(map, 3, 2, 7);
		Open(map, 1, 2, 9);
		Open(map, 1, 3, 6);
		Open(map, 3, 3, 8);
		Open(map, 1, 3, 8);
		Open(map, 3, 4, 6);
		Open(map, 1, 4, 6);
		Open(map, 1, 4, 9);
		Open(map, 1, 5, 6);
		Open(map, 3, 5, 8);
		Open(map, 1, 5, 9);
		Open(map, 1, 5, 9);
		Open(map, 1, 6, 6);
		Open(map, 3, 6, 6);
		Open(map, 3, 6, 8);
		Open(map, 3, 6, 9);
		Open(map, 3, 6, 10);
		Open(map, 3, 6, 11);
		Open(map, 1, 6, 12);
		Open(map, 1, 7, 6);
		Open(map, 1, 7, 8);
		Open(map, 3, 7, 8);
		Open(map, 1, 7, 9);
		Open(map, 3, 7, 10);
		Open(map, 3, 7, 11);
		Open(map, 1, 7, 12);
		Open(map, 1, 8, 6);
		Open(map, 3, 8, 6);
		Open(map, 3, 8, 7);
		Open(map, 1, 8, 9);
		Open(map, 3, 8, 9);
		Open(map, 3, 8, 11);
		Open(map, 3, 9, 8);
		Open(map, 1, 9, 9);
		Open(map, 3, 9, 11);
		Open(map, 1, 9, 12);
		Open(map, 1, 10, 6);
		Open(map, 3, 10, 7);
		Open(map, 3, 10, 8);
		Open(map, 3, 10, 10);
		Open(map, 1, 10, 10);
		Open(map, 3, 10, 11);
		Open(map, 1, 10, 12);
		Open(map, 1, 11, 6);
		Open(map, 1, 11, 7);
		Open(map, 3, 11, 7);
		Open(map, 1, 11, 9);
		Open(map, 1, 11, 11);
		Open(map, 1, 12, 6);
		Open(map, 3, 12, 7);
		Open(map, 3, 12, 8);
		Open(map, 3, 12, 9);
		Open(map, 3, 12, 11);
		Open(map, 1, 12, 12);
		Open(map, 1, 13, 6);
		Open(map, 3, 13, 7);
		Open(map, 1, 13, 9);
		Open(map, 1, 13, 10);
		Open(map, 1, 13, 11);
		Open(map, 1, 13, 12);
		Open(map, 1, 14, 6);
		Open(map, 3, 14, 6);
		Open(map, 3, 14, 7);
		Open(map, 3, 14, 9);
		Open(map, 3, 14, 10);
		Open(map, 3, 15, 6);
		Open(map, 3, 15, 8);
		Open(map, 1, 15, 9);
		Open(map, 3, 16, 6);
		Open(map, 3, 16, 7);

		for (int i = 1; i < 17; i++)
			Open(map, 1, i, 5);

		for (int i = 5; i < 10; i++)
			Open(map, 3, 1, i);

		for (int i = 1; i < 5; i++)
			Open(map, 1, i, 10);

		for (int i = 10; i < 13; i++)
			Open(map, 3, 5, i);

		for (int i = 5; i < 15; i++)
			Open(map, 1, i, 13);

		for (int i = 10; i < 13; i++)
			Open(map, 3, 15, i);

		for (int i = 15; i < 17; i++)
			Open(map, 1, i, 10);

		for (int i = 5; i < 10; i++)
			Open(map, 3, 17, i);
	}

	while (true)
	{
		Root roots[100];
		int rootCount = 0;

		for (int i = 0; i < 20; i++)
			for (int j = 0; j < 20; j++)
			{
				int weight = GetCellWeight(map[i][j]);
				if (weight < 4)
				{
					int weights[4] = { GetCellWeight(map[i + 1][j]),GetCellWeight(map[i - 1][j]),GetCellWeight(map[i][j + 1]),GetCellWeight(map[i][j - 1]) };
					bool canConnect = false;
					if (weights[0] == 4 && i < 19)
					{
						roots[rootCount].addBranch({ i + 1,j });
						canConnect = true;
					}
					if (weights[1] == 4 && i > 0)
					{
						roots[rootCount].addBranch({ i - 1,j });
						canConnect = true;
					}
					if (weights[2] == 4 && j < 19)
					{
						roots[rootCount].addBranch({ i,j + 1 });
						canConnect = true;
					}
					if (weights[3] == 4 && j > 0)
					{
						roots[rootCount].addBranch({ i,j - 1 });
						canConnect = true;
					}

					if (canConnect)
					{
						roots[rootCount].point.x = i;
						roots[rootCount].point.y = j;
						rootCount++;
					}
				}
			}

		if (rootCount)
		{
			int rootId = rand() % rootCount;

			int branchId = rand() % roots[rootId].branchCount;

			roots[rootId].Connect(branchId, map);
		}
		else
		{
			break;
		}
	}
	map[19][0].top = true;
}

#undef main
int main()
{
	srand(time(NULL));
	Cell map[20][20];
	Player player{ 0,19 };
	SDL_Event event;
	bool running = false;

	int seconds = time(NULL)-3;

	Init();
	bool prepare = false;
	while (!running)
	{
		if (int(time(NULL)) >= seconds + 3)
		{
			GenerateMap(map, 1);
			RandColor();
			DrawFullMap3D(map, player, 0, -1, 1);

			seconds = time(NULL);
		}
		
		SDL_PollEvent(&event);
		switch(event.type)
		{
		case SDL_KEYDOWN:
		{
			prepare = true;
			break;
		}
		default:
			break;
		}

		if (prepare)
		{
			for (int i = 0; i < 21; i++)
			{
				DrawFullMap3D(map, player, i * 0.05, -1, 1);
				SDL_Delay(75);
			}
			prepare = false;
			running = true;
		}
	}
	GenerateMap(map, 0);
	RandColor();
	DrawFullMap3D(map, player, 1, -1, 0);

	while (running)
	{
		if (player.x == 19 && player.y == 0)
		{
			for (int i = 0; i < 21; i++)
			{
				DrawFullMap3D(map, player, 1.0 - i * 0.05, -1, 0);
				SDL_Delay(75);
			}
			SDL_Delay(1000);
			GenerateMap(map, 0);
			player.x = 0;
			player.y = 19;
			RandColor();
			DrawFullMap3D(map, player, 1, -1, 0);
		}
		else
		{
			SDL_PollEvent(&event);
			switch (event.type)
			{
			case SDL_KEYDOWN:
			{
				switch (event.key.keysym.scancode)
				{
				case SDL_SCANCODE_ESCAPE:
				{
					running = false;
					break;
				}
				case SDL_SCANCODE_LEFT:
				{
					MovePlayer(map, player, 0);
					break;
				}
				case SDL_SCANCODE_RIGHT:
				{
					MovePlayer(map, player, 1);
					break;
				}
				case SDL_SCANCODE_UP:
				{
					MovePlayer(map, player, 2);
					break;
				}
				case SDL_SCANCODE_DOWN:
				{
					MovePlayer(map, player, 3);
					break;
				}
				default:
					break;
				}
			}
			}
		}
	}

	DeInit(0);

	return 0;
}