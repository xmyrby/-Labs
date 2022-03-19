#include <SDL.h>
#include <iostream>

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;

int winWdt = 840;
int winHgt = 840;

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

int GetCellWeight(Cell cell)
{
	return int(!cell.left) + int(!cell.right) + int(!cell.top) + int(!cell.bottom);
}

void DrawFullMap(Cell map[20][20])
{
	SDL_SetRenderDrawColor(ren, 255, 255, 255, 0);
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (map[i][j].left == false)
				SDL_RenderDrawLine(ren, 20 + i * 40, 20 + j * 40, 20 + i * 40, 60 + j * 40);
			if (map[i][j].right == false)
				SDL_RenderDrawLine(ren, 60 + i * 40, 20 + j * 40, 60 + i * 40, 60 + j * 40);
			if (map[i][j].top == false)
				SDL_RenderDrawLine(ren, 20 + i * 40, 20 + j * 40, 60 + i * 40, 20 + j * 40);
			if (map[i][j].bottom == false)
				SDL_RenderDrawLine(ren, 20 + i * 40, 60 + j * 40, 60 + i * 40, 60 + j * 40);
		}
	}
	SDL_RenderPresent(ren);
}

int Max(int a, int b)
{
	if (a > b)
		return a;
	return b;
}

void DrawMap(Cell map[20][20], Player player, float dist)
{
	SDL_Rect rect;
	for (int i = 0; i < 20; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			int distance = Max((pow(pow((player.x - i), 2) + pow((player.y - j), 2), 0.5)) - 1, 0) * 75;
			distance *= dist;

			SDL_SetRenderDrawColor(ren, Max(185 - distance, 35), Max(50 - distance, 35), Max(80 - distance, 35), 0);
			if (map[i][j].left == false)
			{
				rect = { 10 + i * 40,10 + j * 40,20,60 };
				SDL_RenderFillRect(ren, &rect);
			}
			if (map[i][j].right == false)
			{
				rect = { 50 + i * 40,10 + j * 40,20,60 };
				SDL_RenderFillRect(ren, &rect);
			}
			if (map[i][j].top == false)
			{
				rect = { 10 + i * 40,10 + j * 40,60,20 };
				SDL_RenderFillRect(ren, &rect);
			}
			if (map[i][j].bottom == false)
			{
				rect = { 10 + i * 40,50 + j * 40,60,20 };
				SDL_RenderFillRect(ren, &rect);
			}

			SDL_SetRenderDrawColor(ren, Max(255 - distance, 35), Max(50 - distance, 35), Max(80 - distance, 35), 0);
			if (map[i][j].left == false)
			{
				rect = { 10 + i * 40,5 + j * 40,20,60 };
				SDL_RenderFillRect(ren, &rect);
			}
			if (map[i][j].right == false)
			{
				rect = { 50 + i * 40,5 + j * 40,20,60 };
				SDL_RenderFillRect(ren, &rect);
			}
			if (map[i][j].top == false)
			{
				rect = { 10 + i * 40,5 + j * 40,60,20 };
				SDL_RenderFillRect(ren, &rect);
			}
			if (map[i][j].bottom == false)
			{
				rect = { 10 + i * 40,45 + j * 40,60,20 };
				SDL_RenderFillRect(ren, &rect);
			}
		}
	}
}

void DrawFullMap3D(Cell map[20][20], Player player, float dist, int direction)
{
	SDL_Rect rect;

	switch (direction)
	{
	case -1:
	{
		SDL_SetRenderDrawColor(ren, 80, 50, 185, 0);
		rect = { 30 + player.x * 40,25 + player.y * 40,20,25 };
		SDL_RenderFillRect(ren, &rect);

		DrawMap(map, player, dist);

		SDL_SetRenderDrawColor(ren, 110, 80, 255, 0);
		rect = { 30 + player.x * 40,25 + player.y * 40,20,20 };
		SDL_RenderFillRect(ren, &rect);

		SDL_RenderPresent(ren);
		break;
	}
	case 0:
	{
		for (int i = 0; i <= 40; i++)
		{
			SDL_SetRenderDrawColor(ren, 80, 50, 185, 0);
			rect = { 30 + (player.x + 1) * 40 - i,25 + player.y * 40,20 + i,25 };
			SDL_RenderFillRect(ren, &rect);

			DrawMap(map, player, dist);

			SDL_SetRenderDrawColor(ren, 110, 80, 255, 0);
			rect = { 30 + (player.x + 1) * 40 - i,25 + player.y * 40,20 + i,20 };
			SDL_RenderFillRect(ren, &rect);

			SDL_RenderPresent(ren);
			SDL_Delay(1);
		}

		for (int i = 0; i <= 40; i += 2)
		{
			SDL_SetRenderDrawColor(ren, 35, 35, 35, 0);
			SDL_RenderClear(ren);

			SDL_SetRenderDrawColor(ren, 80, 50, 185, 0);
			rect = { 30 + player.x * 40,25 + player.y * 40,60 - i,25 };
			SDL_RenderFillRect(ren, &rect);

			DrawMap(map, player, dist);

			SDL_SetRenderDrawColor(ren, 110, 80, 255, 0);
			rect = { 30 + player.x * 40,25 + player.y * 40,60 - i,20 };
			SDL_RenderFillRect(ren, &rect);

			SDL_RenderPresent(ren);
			SDL_Delay(1);
		}
		break;
	}
	case 1:
	{
		for (int i = 0; i <= 40; i++)
		{
			SDL_SetRenderDrawColor(ren, 80, 50, 185, 0);
			rect = { 30 + (player.x - 1) * 40,25 + player.y * 40,20 + i,25 };
			SDL_RenderFillRect(ren, &rect);

			DrawMap(map, player, dist);

			SDL_SetRenderDrawColor(ren, 110, 80, 255, 0);
			rect = { 30 + (player.x - 1) * 40,25 + player.y * 40,20 + i,20 };
			SDL_RenderFillRect(ren, &rect);

			SDL_RenderPresent(ren);
			SDL_Delay(1);
		}

		for (int i = 0; i <= 40; i += 2)
		{
			SDL_SetRenderDrawColor(ren, 35, 35, 35, 0);
			SDL_RenderClear(ren);

			SDL_SetRenderDrawColor(ren, 80, 50, 185, 0);
			rect = { 30 + (player.x - 1) * 40 + i,25 + player.y * 40,60 - i,25 };
			SDL_RenderFillRect(ren, &rect);

			DrawMap(map, player, dist);

			SDL_SetRenderDrawColor(ren, 110, 80, 255, 0);
			rect = { 30 + (player.x - 1) * 40 + i,25 + player.y * 40,60 - i,20 };
			SDL_RenderFillRect(ren, &rect);

			SDL_RenderPresent(ren);
			SDL_Delay(1);
		}
		break;
	}
	case 2:
	{
		for (int i = 0; i <= 40; i++)
		{
			SDL_SetRenderDrawColor(ren, 80, 50, 185, 0);
			rect = { 30 + player.x * 40,25 + (player.y + 1) * 40 - i,20,25 + i };
			SDL_RenderFillRect(ren, &rect);

			DrawMap(map, player, dist);

			SDL_SetRenderDrawColor(ren, 110, 80, 255, 0);
			rect = { 30 + player.x * 40,25 + (player.y + 1) * 40 - i,20,20 + i };
			SDL_RenderFillRect(ren, &rect);

			SDL_RenderPresent(ren);
			SDL_Delay(1);
		}

		for (int i = 0; i <= 40; i += 2)
		{
			SDL_SetRenderDrawColor(ren, 35, 35, 35, 0);
			SDL_RenderClear(ren);

			SDL_SetRenderDrawColor(ren, 80, 50, 185, 0);
			rect = { 30 + player.x * 40,25 + player.y * 40,20,65 - i };
			SDL_RenderFillRect(ren, &rect);

			DrawMap(map, player, dist);

			SDL_SetRenderDrawColor(ren, 110, 80, 255, 0);
			rect = { 30 + player.x * 40,25 + player.y * 40,20,60 - i };
			SDL_RenderFillRect(ren, &rect);

			SDL_RenderPresent(ren);
			SDL_Delay(1);
		}
		break;
	}
	case 3:
	{
		for (int i = 0; i <= 40; i++)
		{
			SDL_SetRenderDrawColor(ren, 80, 50, 185, 0);
			rect = { 30 + player.x * 40,25 + (player.y - 1) * 40,20,25 + i };
			SDL_RenderFillRect(ren, &rect);

			DrawMap(map, player, dist);

			SDL_SetRenderDrawColor(ren, 110, 80, 255, 0);
			rect = { 30 + player.x * 40,25 + (player.y - 1) * 40,20,20 + i };
			SDL_RenderFillRect(ren, &rect);

			SDL_RenderPresent(ren);
			SDL_Delay(1);
		}

		for (int i = 0; i <= 40; i += 2)
		{
			SDL_SetRenderDrawColor(ren, 35, 35, 35, 0);
			SDL_RenderClear(ren);

			SDL_SetRenderDrawColor(ren, 80, 50, 185, 0);
			rect = { 30 + player.x * 40,25 + (player.y - 1) * 40 + i,20,65 - i };
			SDL_RenderFillRect(ren, &rect);

			DrawMap(map, player, dist);

			SDL_SetRenderDrawColor(ren, 110, 80, 255, 0);
			rect = { 30 + player.x * 40,25 + (player.y - 1) * 40 + i,20,60 - i };
			SDL_RenderFillRect(ren, &rect);

			SDL_RenderPresent(ren);
			SDL_Delay(1);
		}
		break;
	}
	default:
		break;
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

	SDL_SetRenderDrawColor(ren, 35, 35, 35, 0);
	SDL_RenderClear(ren);

	DrawFullMap3D(map, player, 1, dir);
}

void GenerateMap(Cell map[20][20])
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

			if (xDif == 1)
			{
				map[point.x][point.y].right = true;
				map[branch.x][branch.y].left = true;
			}
			else if (xDif == -1)
			{
				map[point.x][point.y].left = true;
				map[branch.x][branch.y].right = true;
			}
			else if (yDif == 1)
			{
				map[point.x][point.y].bottom = true;
				map[branch.x][branch.y].top = true;
			}
			else if (yDif == -1)
			{
				map[point.x][point.y].top = true;
				map[branch.x][branch.y].bottom = true;
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
	bool running = true;

	Init();
	GenerateMap(map);

	SDL_SetRenderDrawColor(ren, 35, 35, 35, 0);
	SDL_RenderClear(ren);

	DrawFullMap3D(map, player, 1, -1);

	while (running)
	{
		if (player.x == 19 && player.y == 0)
		{
			for (int i = 0; i < 21; i++)
			{
				DrawFullMap3D(map, player, 1.0 - i * 0.05, -1);
				SDL_Delay(75);
			}
			SDL_Delay(1000);
			GenerateMap(map);
			player.x = 0;
			player.y = 19;
		}

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

	DeInit(0);

	return 0;
}