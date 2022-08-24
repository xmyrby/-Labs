#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <math.h>

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;
SDL_Surface* win_surf = NULL;
TTF_Font* font = NULL;
SDL_Texture* textures[50];

int winWdt = 960;
int winHgt = 960;

int moves = 0;
const int MAP_SIZE = 300;
const int CELLS_DENSITY = 7;
const int CELLS_FILL = 10000;
const int ANTS_COUNT = 6;

int enemiesCount = 100;
int enemiesTypesCount = 0;
int lastBtnId = -1;
int playerMenu = 0;

bool showMap = false;

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

struct Position
{
	int x, y;
};

struct OverlayNum
{
	Position pos;
	int num;
	int color;
};

Position PrintText(int var, Position position, int size, Uint8 alpha, int colorId);
Position PrintText(const char* var, Position position, int siz, Uint8 alpha, int colorId);
void RenderImage(int textureId, Position position, int w, int h, int alpha);
bool CheckEntity(Position pos);

struct Button
{
	Position position;
	int width, height;
	char* text;
	bool active;
	int offset;
	int textureId;
	bool border;

	void DrawButton()
	{
		int alpha = 0;
		if (!active)
			alpha = 125;
		if (border)
		{
			SDL_Rect rect = { position.x,position.y,width,height };
			SDL_SetRenderDrawColor(ren, 55, 55, 55, 150 - alpha);
			SDL_RenderFillRect(ren, &rect);
			SDL_SetRenderDrawColor(ren, 255, 255, 255, 255 - alpha);
			SDL_RenderDrawRect(ren, &rect);
		}
		PrintText(text, { position.x + offset,position.y + 6 }, height / 2, 255 - alpha, 0);
		if (textureId != NULL)
			RenderImage(textureId, position, height, height, 255 - alpha);
	}

	Button(Position pos, char* txt, unsigned int wd, unsigned int ht, bool act, int off, int texture, bool bord) : position(pos), text(txt), width(wd), height(ht), active(act), offset(off), textureId(texture), border(bord) {
	}
};

struct Path
{
	int len;
	Position* path;
	int next;
};

struct Item
{
	int type;
	int iconTexture;
	char name[100];
};

struct Entity
{
	Position position;
	int health;
	int maxHealth;
	int moves = 1;
	int attacks = 1;
	int damage = 1;
	int attackrange = 1;
	int regeneration = 1;

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

	int xp = 0;
	int next = 100;
	int points = 3;
	int gold;

	int equipment[4]{ 0,-1,-1,-1 };

	int params[3]{ 1,1,1 };
};

struct Enemy : Entity
{
	int type = 0;
	Path path;
	char name[100];
	int iconTextureId;
	int xpReward;
	int goldReward;
	int protection;

	void NewPath(Path nPath)
	{
		path = nPath;
		path.next = 0;
	}

	void Move()
	{
		if (path.len > 0 && moves > 0)
		{
			if (CheckEntity(path.path[path.next]))
			{
				position = path.path[path.next];
				moves--;
				path.next++;
				if (path.next >= path.len - 1)
					path.len = 0;
				health = Min(health + regeneration, maxHealth);
			}
		}
	}
};

struct Overlay
{
	OverlayNum* overlayNums;
	int numsCount = 0;

	void Init()
	{
		overlayNums = (OverlayNum*)malloc(sizeof(OverlayNum));
	}

	void Clear()
	{
		numsCount = 0;
		overlayNums = (OverlayNum*)realloc(overlayNums, 0);
	}

	void AddNum(Position pos, int num, int color)
	{
		overlayNums = (OverlayNum*)realloc(overlayNums, sizeof(OverlayNum) * (numsCount + 1));
		overlayNums[numsCount] = { pos,num, color };
		numsCount++;
	}
};

Player player;

Enemy* enemies;
Enemy* enemiesTypes;

Button* buttons;

Item items[1];

Overlay overlay;

SDL_Color colors[5];

int map[MAP_SIZE][MAP_SIZE];
int mapOverview[MAP_SIZE][MAP_SIZE];

void InitItems()
{
	items[0] = { 0, 25, NULL };
}

void RecalculatePlayer()
{
	player.maxHealth = 10 + (player.level - 1) * 2 + player.params[1] * player.level / 4;
	player.damage = 1 + player.params[0] * player.level / 2;
	player.health = Min(player.maxHealth, player.health);
}

void InitColors()
{
	colors[0] = { 255,255,255 };
	colors[1] = { 255,200,200 };
	colors[2] = { 0,0,0 };
	colors[3] = { 100,255,100 };
	colors[4] = { 232,211,68 };
}

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
	textures[5] = IMG_LoadTexture(ren, "GFX\\TigerIcon.png");
	textures[6] = IMG_LoadTexture(ren, "GFX\\AttackIcon.png");
	textures[7] = IMG_LoadTexture(ren, "GFX\\PlayerMenuButton.png");
	textures[8] = IMG_LoadTexture(ren, "GFX\\UpgradeMenuButton.png");
	textures[9] = IMG_LoadTexture(ren, "GFX\\EquipmentMenuButton.png");
	textures[10] = IMG_LoadTexture(ren, "GFX\\HelmetMenuCell.png");
	textures[11] = IMG_LoadTexture(ren, "GFX\\PlateMenuCell.png");
	textures[12] = IMG_LoadTexture(ren, "GFX\\PantsMenuCell.png");
	textures[13] = IMG_LoadTexture(ren, "GFX\\BootsMenuCell.png");
	textures[14] = IMG_LoadTexture(ren, "GFX\\MenuCell.png");
	textures[19] = IMG_LoadTexture(ren, "GFX\\GoldMenu.png");
	textures[25] = IMG_LoadTexture(ren, "GFX\\EQP\\Item0.png");
}

void InitEnemies()
{
	FILE* ft;
	if (fopen_s(&ft, "PARAMS\\EnemiesTypes.txt", "rt") != 0)
	{
		exit(1);
	}
	fscanf_s(ft, "%d", &enemiesTypesCount);

	enemiesTypes = (Enemy*)malloc(sizeof(Enemy) * enemiesTypesCount);

	for (int i = 0; i < enemiesTypesCount; i++)
	{
		fscanf_s(ft, "%s %d %d %d %d %d %d %d %d %d %d", &enemiesTypes[i].name, sizeof(enemiesTypes[i].name), &enemiesTypes[i].iconTextureId, &enemiesTypes[i].maxHealth, &enemiesTypes[i].attacks, &enemiesTypes[i].moves, &enemiesTypes[i].damage, &enemiesTypes[i].attackrange, &enemiesTypes[i].regeneration, &enemiesTypes[i].xpReward, &enemiesTypes[i].protection, &enemiesTypes[i].goldReward);
		enemiesTypes[i].health = enemiesTypes[i].maxHealth;
		enemiesTypes[i].type = i;
	}

	fclose(ft);

	enemies = (Enemy*)malloc(sizeof(Enemy) * enemiesCount);
	for (int i = 0; i < enemiesCount; i++)
		enemies[i].type = rand() % enemiesTypesCount;
}

void KillEnemy(int id)
{
	player.xp += enemies[id].xpReward;
	int gold = enemies[id].goldReward;
	gold = rand() % (gold / 2) + gold / 2;
	player.gold += gold;
	for (int i = id; i < enemiesCount - 1; i++)
	{
		enemies[i] = enemies[i + 1];
	}
	enemiesCount--;
	player.selectedEnemy = -1;

	enemies = (Enemy*)realloc(enemies, sizeof(Enemy) * enemiesCount);
}

void InitButtons()
{
	buttons = (Button*)malloc(sizeof(Button) * 6);
	buttons[0] = *(new Button({ 652,80 }, new char[7]{ "Attack" }, 296, 24, false, 30, 6, true));
	buttons[1] = *(new Button({ 928,480 }, new char[2]{ "\0" }, 32, 32, false, NULL, 7, false));
	buttons[2] = *(new Button({ 928,512 }, new char[2]{ "\0" }, 32, 32, false, NULL, 9, false));
	buttons[3] = *(new Button({ 928,558 }, new char[2]{ "\0" }, 24, 24, false, NULL, 8, false));
	buttons[4] = *(new Button({ 928,590 }, new char[2]{ "\0" }, 24, 24, false, NULL, 8, false));
	buttons[5] = *(new Button({ 928,622 }, new char[2]{ "\0" }, 24, 24, false, NULL, 8, false));
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

	InitButtons();

	InitEnemies();

	InitColors();

	InitItems();

	overlay.Init();

	SDL_SetRenderDrawBlendMode(ren, SDL_BLENDMODE_BLEND);
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

int ConvBig(int a, int b)
{
	return (a + 15 - b) * 32 - 16;
}

int ConvSmall(int a, int b)
{
	return round(a + 16) / 32 + b - 15;
}

void Generate()
{
	struct Ant
	{
		Position position;
	};

	for (int i = 0; i < MAP_SIZE; i++)
		for (int j = 0; j < MAP_SIZE; j++)
		{
			map[i][j] = 1;
			mapOverview[i][j] = 0;
		}

	Ant ants[ANTS_COUNT];
	int cells = 0;

	for (int i = 0; i < ANTS_COUNT; i++)
	{
		ants[i] = { rand() % (MAP_SIZE / 2) + (MAP_SIZE / 4), rand() % (MAP_SIZE / 2) + (MAP_SIZE / 4) };
		map[ants[i].position.x][ants[i].position.y] = 0;
		cells++;
	}

	while (cells < CELLS_FILL)
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

float GetAngle(Position a, Position b)
{
	return atan2(a.y - b.y, a.x - b.x);
}

int RayTracing(Position position, Position mainPos)
{
	float ax = position.x, ay = position.y;
	float angle = GetAngle(mainPos, position);
	int blocks = 0;
	while (position.x != mainPos.x || position.y != mainPos.y)
	{
		if (position.x != mainPos.x)
			ax += cos(angle);
		if (position.y != mainPos.y)
			ay += sin(angle);
		position.x = round(ax);
		position.y = round(ay);
		if (map[position.x][position.y] == 1)
			blocks += 5;

		blocks += 1;
	}

	return blocks;
}

int GetSize(const char* text)
{
	int count = 0;
	while (text[count] != '\0')
		count++;
	return count;
}

Position PrintText(int var, Position position, int size, Uint8 alpha, int colorId)
{
	char text[10];

	_itoa_s(var, (char*)text, 10, 10);

	SDL_Color color = colors[colorId];
	color.a = alpha;
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, text, color);

	int width = 0.75 * GetSize(text) * size;
	SDL_Rect rect = { position.x,position.y, width,size };

	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(ren, textSurface);
	SDL_RenderCopy(ren, textTexture, NULL, &rect);

	SDL_FreeSurface(textSurface);
	SDL_DestroyTexture(textTexture);

	return (Position{ position.x + width, position.y + size });
}

Position PrintText(const char* text, Position position, int size, Uint8 alpha, int colorId)
{
	SDL_Color color = colors[colorId];
	color.a = alpha;

	SDL_Surface* textSurface = TTF_RenderText_Blended(font, text, color);

	int width = 0.75 * GetSize(text) * size;
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

bool CheckEntity(Position pos)
{
	if (player.x() == pos.x && player.y() == pos.y)
		return false;
	for (int i = 0; i < enemiesCount; i++)
		if (enemies[i].x() == pos.x && enemies[i].y() == pos.y)
			return false;
	return true;
}

int GetAlpha(int value, int b)
{
	int k = ceil((value - 15) / 7.6875);
	return Max(15, value - b * k);
}

float Distance(Position a, Position b)
{
	return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

bool CheckAttackDist(Entity a, Entity b)
{
	if (a.attackrange >= int(round(sqrt((a.x() - b.x()) * (a.x() - b.x()) + (a.y() - b.y()) * (a.y() - b.y())))))
		return true;
	return false;
}

void DrawOverlay()
{
	for (int i = 0; i < overlay.numsCount; i++)
	{
		OverlayNum oNum = overlay.overlayNums[i];
		Position pos = oNum.pos;
		pos.x = ConvBig(pos.x, player.x()) + rand() % 16 + 4;
		pos.y = ConvBig(pos.y, player.y()) + rand() % 16 + 6;
		PrintText(oNum.num, pos, 16, 255, 2);
		pos.y--;
		PrintText(oNum.num, pos, 16, 255, oNum.color);
	}
}

void DrawUI()
{
	Position offset;
	offset = PrintText("Moves: ", { 10,18 }, 16, 255, 0);
	PrintText(moves + 1, { offset.x + 4, 18 }, 16, 255, 0);
	RenderImage(0, { 10, 52 }, 32, 32, 255);
	PrintText(player.attacks, { 52, 60 }, 16, 255, 0);
	RenderImage(1, { 10, 94 }, 32, 32, 255);
	PrintText(player.moves, { 52, 104 }, 16, 255, 0);
	PrintText("Health: ", { 10, 926 }, 16, 255, 0);
	offset = PrintText(player.health, { 102, 926 }, 16, 255, 0);
	offset = PrintText("/", { offset.x + 4, 926 }, 16, 255, 0);
	PrintText(player.maxHealth, { offset.x + 4, 926 }, 16, 255, 0);

	if (player.selectedEnemy >= 0)
		if (RayTracing(enemies[player.selectedEnemy].position, player.position) > 5)
			player.selectedEnemy = -1;
		else
		{
			Position position;
			position.x = ConvBig(enemies[player.selectedEnemy].x(), player.x());
			position.y = ConvBig(enemies[player.selectedEnemy].y(), player.y());
			RenderImage(4, position, 32, 32, 255);
		}

	if (showMap)
	{
		SDL_Rect rect = { 240 + (30) * 8 - 4,540 + (30) * 8 - 4,8,8 };
		SDL_SetRenderDrawColor(ren, 255, 100, 100, 100);
		SDL_RenderFillRect(ren, &rect);
		for (int i = player.x() - 30; i < player.x() + 31; i++)
			for (int j = player.y() - 30; j < player.y() + 31; j++)
			{
				SDL_Rect rect = { 240 + (i + 30 - player.x()) * 8 - 4,540 + (j + 30 - player.y()) * 8 - 4,8,8 };
				if (mapOverview[i][j] == 1)
				{
					SDL_SetRenderDrawColor(ren, 255, 255, 255, 75 - Min(int(round(Distance({ i,j }, player.position))) * 4, 75));
					SDL_RenderFillRect(ren, &rect);
				}
			}
	}

	if (player.selectedEnemy != -1)
	{
		SDL_Rect rect = { 640,0,320,480 };
		SDL_SetRenderDrawColor(ren, 0, 0, 0, 55);
		SDL_RenderFillRect(ren, &rect);
		RenderImage(5, { 652, 16 }, 48, 48, 255);
		PrintText(enemies[player.selectedEnemy].name, { 716, 20 }, 16, 255, 0);
		PrintText("Health: ", { 716, 44 }, 16, 255, 0);
		offset = PrintText(enemies[player.selectedEnemy].health, { 808, 44 }, 16, 255, 0);
		offset = PrintText("/", { offset.x + 4, 44 }, 16, 255, 0);
		PrintText(enemies[player.selectedEnemy].maxHealth, { offset.x + 4, 44 }, 16, 255, 0);

		bool active = false;
		if (CheckAttackDist(player, enemies[player.selectedEnemy]) && player.attacks)
			active = true;
		buttons[0].active = active;
		buttons[0].DrawButton();
	}
	else
	{
		buttons[0].active = false;
	}

	if (playerMenu == 0)
	{
		buttons[1].position.x = 928;
		buttons[1].active = true;
		buttons[1].DrawButton();
		buttons[2].position.x = 928;
		buttons[2].position.y = 512;
		buttons[2].active = true;
		buttons[2].DrawButton();
	}
	else if (playerMenu == 1)
	{
		buttons[1].position.x = 608;
		buttons[1].active = true;
		buttons[1].DrawButton();
		buttons[2].active = false;
		SDL_Rect rect = { 640,480,320,480 };
		SDL_SetRenderDrawColor(ren, 0, 0, 0, 55);
		SDL_RenderFillRect(ren, &rect);
		offset = PrintText("Level ", { 656, 496 }, 16, 255, 0);
		PrintText(player.level, { offset.x, 496 }, 16, 255, 0);
		offset = PrintText("Exp: ", { 760, 496 }, 16, 255, 0);
		offset = PrintText(player.xp, { offset.x, 496 }, 16, 255, 0);
		offset = PrintText("/", { offset.x + 4, 496 }, 16, 255, 0);
		offset = PrintText(player.next, { offset.x + 4, 496 }, 16, 255, 0);
		offset = PrintText("Points ", { 656, 520 }, 16, 255, 0);
		PrintText(player.points, { offset.x, 520 }, 16, 255, 0);

		offset = PrintText("Strength ", { 656, 560 }, 16, 255, 0);
		offset = PrintText(player.params[0], { offset.x, 560 }, 16, 255, 0);
		if (player.points > 0)
		{
			offset = PrintText("Cost: ", { offset.x + 36, 564 }, 12, 255, 0);
			PrintText(floor(1 + player.params[0] * 0.4), { offset.x, 562 }, 12, 255, 0);
		}

		offset = PrintText("Vitality ", { 656, 592 }, 16, 255, 0);
		offset = PrintText(player.params[1], { offset.x, 592 }, 16, 255, 0);
		if (player.points > 0)
		{
			offset = PrintText("Cost: ", { offset.x + 36, 594 }, 12, 255, 0);
			PrintText(floor(1 + player.params[1] * 0.4), { offset.x, 592 }, 12, 255, 0);
		}

		offset = PrintText("Protection ", { 656, 624 }, 16, 255, 0);
		offset = PrintText(player.params[2], { offset.x, 624 }, 16, 255, 0);
		if (player.points > 0)
		{
			offset = PrintText("Cost: ", { offset.x + 36, 626 }, 12, 255, 0);
			PrintText(floor(1 + player.params[2] * 0.4), { offset.x, 626 }, 12, 255, 0);
		}

		for (int i = 0; i < 3; i++)
		{
			if (player.points >= floor(1 + player.params[i] * 0.4))
				buttons[3 + i].active = true;
			else
				buttons[3 + i].active = false;
			if (player.points > 0)
				buttons[3 + i].DrawButton();
		}
	}
	else if (playerMenu == 2)
	{
		buttons[2].position.x = 608;
		buttons[2].position.y = 480;
		buttons[2].active = true;
		buttons[2].DrawButton();
		buttons[1].active = false;
		SDL_Rect rect = { 640,480,320,480 };
		SDL_SetRenderDrawColor(ren, 0, 0, 0, 55);
		SDL_RenderFillRect(ren, &rect);

		RenderImage(11, { 768,592 }, 64, 64, 255);
		RenderImage(12, { 768,672 }, 64, 64, 255);
		RenderImage(13, { 768,752 }, 64, 64, 255);
		RenderImage(19, { 640,480 }, 32, 32, 255);
		PrintText(player.gold, { 676, 488 }, 16, 255, 4);

		if (player.equipment[0] != -1)
		{
			RenderImage(14, { 768,512 }, 64, 64, 255);
			RenderImage(items[player.equipment[0]].iconTexture, { 768,512 }, 64, 64, 255);
			Item item = items[player.equipment[0]];
			printf("%d %d\n", item.iconTexture, item.type);
		}
		else
		{
			RenderImage(10, { 768,512 }, 64, 64, 255);
		}
	}
}

void Draw()
{
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderClear(ren);
	for (int i = player.x() - 15; i < player.x() + 16; i++)
		for (int j = player.y() - 15; j < player.y() + 16; j++)
		{
			SDL_Rect rect = { ConvBig(i, player.x()),ConvBig(j, player.y()),32,32 };

			int blocks = RayTracing({ i, j }, player.position);
			if (blocks <= 5 && map[i][j] == 1)
				mapOverview[i][j] = 1;
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
	for (int i = 0; i < enemiesCount; i++)
	{
		int blocks = RayTracing(enemies[i].position, player.position);
		rect = { ConvBig(enemies[i].x(), player.x()) ,ConvBig(enemies[i].y(), player.y()),32,32 };
		SDL_SetRenderDrawColor(ren, GetAlpha(198, blocks), GetAlpha(101, blocks), GetAlpha(202, blocks), 255);
		SDL_RenderFillRect(ren, &rect);
		if (blocks <= 5)
		{
			RenderImage(3, { rect.x, rect.y }, 32, 32, GetAlpha(255, blocks));
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

	player.maxHealth = 10;
	player.health = 10;
}

void SpawnEnemies()
{
	for (int i = 0; i < enemiesCount; i++)
	{
		Enemy enemy;
		do
		{
			enemy.x(rand() % MAP_SIZE);
			enemy.y(rand() % MAP_SIZE);
		} while (map[enemy.x()][enemy.y()] != 0);
		enemies[i] = enemiesTypes[enemies[i].type];
		enemies[i].position = enemy.position;
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

bool CheckWd(int weight, int* weights)
{
	if (weight <= 0)
		return false;
	for (int i = 0; i < 4; i++)
	{
		int wd = weights[i];
		if (wd != -1 && (wd > weight + 1 || wd == 0))
			return true;
	}
	return false;
}

Path FindPath(Position start, Position end)
{
	int w[MAP_SIZE][MAP_SIZE];
	for (int i = 0; i < MAP_SIZE; i++)
		for (int j = 0; j < MAP_SIZE; j++)
			if (map[i][j] == 1 || !CheckEntity({ i,j }) && !Comp(end, { i,j }) && !Comp(start, { i,j }))
				w[i][j] = -1;
			else if (i == start.x && j == start.y)
				w[i][j] = 1;
			else
				w[i][j] = 0;
	if (w[end.x][end.y] == -1)
		return { 0,NULL };

	struct Root
	{
		Position point;
		int branchCount = 0;
		Position branchPoints[100];

		bool addBranch(Position branch)
		{
			if (branchCount < 0)
				return false;
			branchPoints[branchCount] = branch;
			branchCount++;
		}

		void Connect(int branchId, int w[MAP_SIZE][MAP_SIZE])
		{
			Position branch = branchPoints[branchId];
			int wb = w[branch.x][branch.y];
			int wp = w[point.x][point.y];
			if (wb != -1 && wb > wp + 1 || wb == 0)
				w[branch.x][branch.y] = wp + 1;
		}
	};

	bool find = false;
	while (!find)
	{
		Root roots[100];
		int rootCount = 0;

		for (int i = 0; i < MAP_SIZE; i++)
			for (int j = 0; j < MAP_SIZE; j++)
			{
				int wd = w[i][j];
				int weights[4] = { w[i + 1][j],w[i - 1][j],w[i][j + 1],w[i][j - 1] };
				if (CheckWd(wd, weights))
				{
					if (Comp({ i,j }, end))
					{
						find = true;
						break;
					}
					bool canConnect = false;
					bool resulter = false;
					if ((weights[0] != -1 && weights[0] > wd + 1 || weights[0] == 0) && i < MAP_SIZE - 1)
					{
						resulter = roots[rootCount].addBranch({ i + 1,j });
						canConnect = true;
					}
					if ((weights[1] != -1 && weights[1] > wd + 1 || weights[1] == 0) && i > 0)
					{
						resulter = roots[rootCount].addBranch({ i - 1,j });
						canConnect = true;
					}
					if ((weights[2] != -1 && weights[2] > wd + 1 || weights[2] == 0) && j < MAP_SIZE - 1)
					{
						resulter = roots[rootCount].addBranch({ i,j + 1 });
						canConnect = true;
					}
					if ((weights[3] != -1 && weights[3] > wd + 1 || weights[3] == 0) && j > 0)
					{
						resulter = roots[rootCount].addBranch({ i,j - 1 });
						canConnect = true;
					}

					if (!resulter)
						return { 0,NULL };

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
			for (int i = 0; i < rootCount; i++)
				for (int j = 0; j < roots[i].branchCount; j++)
					roots[i].Connect(j, w);
		}
		else
		{
			find = true;
		}
	}

	int len = w[end.x][end.y] - 1;
	if (len < 0)
		return { 0,NULL };
	Position* path = new Position[len];

	path[len - 1] = end;

	for (int i = len - 2; i >= 0; i--)
	{
		Position last = path[i + 1];
		int weights[4] = { w[last.x + 1][last.y],w[last.x - 1][last.y],w[last.x][last.y + 1],w[last.x][last.y - 1] };
		int id = 0, min = w[last.x][last.y];

		for (int j = 0; j < 4; j++)
		{
			if (w[last.x][last.y] > weights[j] && weights[j] > 0)
			{
				id = j;
				min = weights[j];
			}
		}

		switch (id)
		{
		case 0:
			path[i] = { last.x + 1,last.y };
			break;
		case 1:
			path[i] = { last.x - 1,last.y };
			break;
		case 2:
			path[i] = { last.x,last.y + 1 };
			break;
		case 3:
			path[i] = { last.x,last.y - 1 };
			break;
		default:
			break;
		}
	}

	return { len,path };
}

void MakeEnemyMove(Enemy& enemy)
{
	if (RayTracing(enemy.position, player.position) <= 5)
	{
		while (enemy.moves > 0 && !CheckAttackDist(enemy, player))
		{
			enemy.NewPath(FindPath(enemy.position, player.position));

			enemy.Move();
		}

		for (int i = 0; i < enemy.attacks; i++)
		{
			if (CheckAttackDist(enemy, player))
			{
				int damage = round(enemy.damage / floor(1 + player.params[2] / 3));
				player.health -= damage;
				enemy.moves--;
				overlay.AddNum(player.position, -damage, 1);
			}
		}
	}
	else
	{
		enemy.Move();
	}
	enemy.moves = enemiesTypes[enemy.type].moves;
	enemy.attacks = enemiesTypes[enemy.type].attacks;
}

void CheckMove()
{
	bool canMove = true;
	if (!player.moves && !player.attacks)
	{
		canMove = false;
	}
	else if (player.attacks && !player.moves)
	{
		canMove = false;
		for (int i = 0; i < enemiesCount; i++)
		{
			if (CheckAttackDist(player, enemies[i]) && RayTracing(player.position, enemies[i].position) <= 5)
			{
				canMove = true;
				break;
			}
		}
	}

	if (!canMove)
	{
		player.moves = 0;
		player.attacks = 0;
		moves++;
		player.moves++;
		player.attacks++;

		for (int i = 0; i < enemiesCount; i++)
		{
			MakeEnemyMove(enemies[i]);
		}
	}

	if (player.xp >= player.next)
	{
		RecalculatePlayer();
		player.health = player.maxHealth;
		player.points++;
		player.xp -= player.next;
		player.next *= 1.25;
		player.level++;
	}

	RecalculatePlayer();
}

int CheckSelection(Position position)
{
	position.x = ConvSmall(position.x, player.x());
	position.y = ConvSmall(position.y, player.y());
	for (int i = 0; i < enemiesCount; i++)
	{
		if (position.x == enemies[i].x() && position.y == enemies[i].y())
			if (RayTracing(position, player.position) <= 5)
				return i;
	}
	if (lastBtnId == 0 || lastBtnId == 1 || lastBtnId == 2)
		return player.selectedEnemy;
	return -1;
}

void ButtonAction(int buttonId)
{
	if (buttonId == 0 && player.attacks)
	{
		int damage = round(player.damage / floor(1 + enemies[player.selectedEnemy].protection / 3));

		enemies[player.selectedEnemy].health -= damage;
		player.attacks -= 1;
		overlay.AddNum(enemies[player.selectedEnemy].position, -damage, 1);
		player.moves = Max(0, player.moves - 1);
		if (enemies[player.selectedEnemy].health <= 0)
			KillEnemy(player.selectedEnemy);
		CheckMove();
	}
	else if (buttonId == 1)
	{
		if (playerMenu == 0)
		{
			playerMenu = 1;
		}
		else
		{
			playerMenu = 0;
		}
	}
	else if (buttonId == 2)
	{
		if (playerMenu == 0)
		{
			playerMenu = 2;
		}
		else
		{
			playerMenu = 0;
		}
	}
	else if (buttonId >= 3 && buttonId <= 5)
	{
		int reqPoints = floor(1 + player.params[buttonId - 3] * 0.4);

		if (player.points >= (int)reqPoints)
		{
			player.points -= reqPoints;
			player.params[buttonId - 3]++;
			RecalculatePlayer();
		}
	}
	Draw();
}

int CheckButtonClick(Position mPos)
{
	for (int i = 0; i < 6; i++)
	{
		Button button = buttons[i];
		if (mPos.x >= button.position.x && mPos.y >= button.position.y && mPos.x <= button.position.x + button.width && mPos.y <= button.position.y + button.height && button.active)
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
	int lDraw = 0;
	font = TTF_OpenFont("Fonts\\MainFont.ttf", 20);
	SDL_Event event;

	Generate();
	SpawnPlayer();
	SpawnEnemies();
	RecalculatePlayer();
	Draw();

	while (true)
	{
		const Uint8* state = SDL_GetKeyboardState(NULL);

		SDL_PumpEvents();
		Uint32 events = SDL_GetMouseState(&_mouse.x, &_mouse.y);

		if ((events & SDL_BUTTON_LMASK) != 0 && !_down)
		{
			_down = true;
			lastBtnId = CheckButtonClick(_mouse);
			ButtonAction(lastBtnId);
			player.selectedEnemy = CheckSelection(_mouse);
			Draw();
		}
		if ((events & SDL_BUTTON_LMASK) == 0)
			_down = false;

		SDL_PollEvent(&event);

		if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
		{
			bool moved = false;
			if (state[SDL_SCANCODE_W])
			{
				if (map[player.x()][player.y() - 1] == 0 && player.moves > 0 && CheckEntity({ player.x(), player.y() - 1 }))
				{
					player.position.y--;
					moved = true;
				}
			}
			else if (state[SDL_SCANCODE_S])
			{
				if (map[player.x()][player.y() + 1] == 0 && player.moves > 0 && CheckEntity({ player.x(), player.y() + 1 }))
				{
					player.position.y++;
					moved = true;
				}
			}
			else if (state[SDL_SCANCODE_A])
			{
				if (map[player.x() - 1][player.y()] == 0 && player.moves > 0 && CheckEntity({ player.x() - 1, player.y() }))
				{
					player.position.x--;
					moved = true;
				}
			}
			else if (state[SDL_SCANCODE_D])
			{
				if (map[player.x() + 1][player.y()] == 0 && player.moves > 0 && CheckEntity({ player.x() + 1, player.y() }))
				{
					player.position.x++;
					moved = true;
				}
			}
			else if (state[SDL_SCANCODE_SPACE])
			{
				player.moves = 0;
				player.attacks = 0;
			}
			else if (state[SDL_SCANCODE_M])
			{
				if (showMap)
					showMap = false;
				else
					showMap = true;
			}

			if (moved)
			{
				player.moves--;
				if (player.health < player.maxHealth)
				{
					player.health = Min(player.health + player.regeneration, player.maxHealth);
					overlay.AddNum(player.position, player.regeneration, 3);
				}
			}

			CheckMove();
			Draw();
		}


		if (moves != lDraw)
		{
			DrawOverlay();
			overlay.Clear();
			lDraw = moves;
		}
		SDL_RenderPresent(ren);
	}
	TTF_CloseFont(font);

	DeInit(0);
	return 0;
}