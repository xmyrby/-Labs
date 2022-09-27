#include<iostream>
#include<SDL.h>

SDL_Window* win;
SDL_Renderer* ren;

int win_width = 1000, win_height = 1000;

struct Point
{
	int x, y;
};

struct Snake
{
	Point body[100];
	int size;

	int direction;
};

void DeInit(int error)
{
	if (ren != NULL) SDL_DestroyRenderer(ren);
	if (win != NULL) SDL_DestroyWindow(win);
	SDL_Quit();
	exit(error);

}

void Init()
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("ploho: %s", SDL_GetError());
		system("pause");
		DeInit(1);
	}

	win = SDL_CreateWindow("Just Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		win_width, win_height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (win == NULL)
	{
		printf("win: %s", SDL_GetError());
		system("pause");
		DeInit(1);
	}


	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
	if (ren == NULL)
	{
		printf("okna ne ma render: %s", SDL_GetError());
		system("pause");
		DeInit(1);
	}
}

void DrawSnake(Snake snake)
{
	SDL_Rect r;
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderClear(ren);
	SDL_SetRenderDrawColor(ren, 250, 100, 125, 255);
	for (int i = 0; i < snake.size; i++)
	{
		r = { snake.body[i].x * 25,snake.body[i].y * 25,25,25 };
		SDL_RenderFillRect(ren, &r);
		SDL_SetRenderDrawColor(ren, 150, 100, 125, 255);
	}
	SDL_RenderPresent(ren);
}

void MoveSnake(Snake& snake)
{
	for (int i = snake.size - 1; i > 0; i--)
	{
		snake.body[i] = snake.body[i - 1];
	}
	if (snake.size > 1)
		snake.body[0] = snake.body[1];

	switch (snake.direction)
	{
	case 0:
	{
		snake.body[0].y--;
		break;
	}
	case 1:
	{
		snake.body[0].x++;
		break;
	}
	case 2:
	{
		snake.body[0].y++;
		break;
	}
	case 3:
	{
		snake.body[0].x--;
		break;
	}
	default:
		break;
	}
}

void DrawApple(Point apple)
{
	SDL_SetRenderDrawColor(ren, 255, 0, 0, 255);
	SDL_Rect r = { apple.x * 25,apple.y * 25,25,25 };
	SDL_RenderFillRect(ren, &r);
	SDL_RenderPresent(ren);
}

bool CheckCollision(Snake& snake, Point apple, bool& spawned)
{
	Point head = snake.body[0];

	if (head.x > 39)
		return true;
	if (head.x < 0)
		return true;
	if (head.y > 39)
		return true;
	if (head.y < 0)
		return true;

	for (int i = 1; i < snake.size; i++)
	{
		if (snake.body[i].x == head.x && snake.body[i].y == head.y)
			return true;
	}
	if (snake.body[0].x == apple.x && snake.body[0].y == apple.y)
	{
		snake.size++;
		for (int i = snake.size - 1; i > 0; i--)
		{
			snake.body[i] = snake.body[i - 1];
		}
		snake.body[0] = apple;
		spawned = false;
	}

	return false;
}

#undef main
int main()
{
	int lastTime = SDL_GetTicks(), newTime, delta = 0;
	srand(time(NULL));
	Init();
	SDL_Event event;
	Snake snake;
	Point apple;
	bool spawned = false;

	snake.size = 1;
	snake.body[0].x = 20;
	snake.body[0].y = 20;
	snake.direction = 0;

	int spawn = 0;
	while (true)
	{
		while (SDL_PollEvent(&event) != 0)
		{
			const Uint8* keys = SDL_GetKeyboardState(NULL);

			if (keys[SDL_SCANCODE_UP])
				snake.direction = 0;
			if (keys[SDL_SCANCODE_RIGHT])
				snake.direction = 1;
			if (keys[SDL_SCANCODE_DOWN])
				snake.direction = 2;
			if (keys[SDL_SCANCODE_LEFT])
				snake.direction = 3;
		}

		DrawSnake(snake);

		if (spawn >= 10)
		{
			spawn = 0;
			spawned = true;
			apple.x = rand() % 40;
			apple.y = rand() % 40;
		}

		MoveSnake(snake);

		if (spawned)
		{
			DrawApple(apple);

			if (CheckCollision(snake, apple, spawned))
			{
				spawn = 0;
				spawned = false;
				snake.size = 1;
				snake.body[0].x = 20;
				snake.body[0].y = 20;
				snake.direction = 0;
			}
		}

		if (!spawned)
			spawn++;

		newTime = SDL_GetTicks();
		delta = newTime - lastTime;
		lastTime = newTime;

		if (delta < 96)
		{
			SDL_Delay(96 - delta);
		}
	}
}