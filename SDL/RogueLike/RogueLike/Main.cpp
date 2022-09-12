#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <math.h>

SDL_Window* win = NULL;
SDL_Renderer* ren = NULL;
SDL_Surface* win_surf = NULL;
TTF_Font* font = NULL;
SDL_Texture* textures[51];
SDL_Texture* lastRender;

int winWdt = 960;
int winHgt = 960;

int moves = 0;
const int MAP_SIZE = 300;
const int CELLS_DENSITY = 7;
const int CELLS_FILL = 10000;
const int ANTS_COUNT = 6;
const int LAMPS_COUNT = 15;

int enemiesCount = 200;
int enemiesTypesCount = 0;
int lastBtnId = -1;
int playerMenu = 0;
int itemsCount = 0;
int dropCount = 0;
int itemMenuType = 0;
int itemMenu = 0;

bool saveMap = true;

bool showMap = false;

int Random(int a, int b)
{
	if (a >= b)
		return 0;
	return rand() % (b - a + 1) + a;
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

struct Position
{
	int x, y;
};

struct OverlayNum
{
	Position pos;
	Position offset;
	int num;
	int color;
	int alpha;
};

struct Lamp
{
	int textureId;
	Position position;
	int bright;
};

struct OverlayParticle
{
	Position pos;
	float offX;
	float offY;
	int size;
	int color;
	int alpha;
	float angleOfMove;
	float moveSpeed;
};

Position PrintText(int var, Position position, int size, Uint8 alpha, int colorId);
Position PrintText(const char* var, Position position, int siz, Uint8 alpha, int colorId);
void RenderImage(int textureId, Position position, int w, int h, int alpha);
bool CheckEntity(Position pos);

struct ItemParam
{
	int type;
	int value;
};

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
	char name[100];
	int iconTextureId;
	int type;
	int bonusesCount;
	int level = 1;
	int requirementsCount;

	ItemParam* bonuses;
	ItemParam* requirements;
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
	int level = 1;
	int protection;
	int agility;
	int blinding = 0;

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

	int xp = 0;
	int next = 100;
	int points = 3;
	int gold;
	int mana;
	int maxMana;

	int equipment[5][2]{ {-1,0},{-1,0},{-1, 0},{-1, 0},{-1,0} };

	int params[5]{ 1,1,1,1,1 };
};

struct Enemy : Entity
{
	int type = 0;
	Path path;
	char name[100];
	int iconTextureId;
	int xpReward;
	int goldReward;
	int dropChance;

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
	OverlayParticle* overlayParticles;
	int numsCount = 0;
	int particlesCount = 0;

	void Init()
	{
		overlayNums = (OverlayNum*)malloc(sizeof(OverlayNum));
		overlayParticles = (OverlayParticle*)malloc(sizeof(OverlayParticle));
	}

	void ClearNum(int id)
	{
		for (int i = id; i < numsCount - 1; i++)
		{
			overlayNums[i] = overlayNums[i + 1];
		}
		numsCount--;

		overlayNums = (OverlayNum*)realloc(overlayNums, sizeof(OverlayNum) * numsCount);
	}

	void ClearParticle(int id)
	{
		for (int i = id; i < particlesCount - 1; i++)
		{
			overlayParticles[i] = overlayParticles[i + 1];
		}
		particlesCount--;

		overlayParticles = (OverlayParticle*)realloc(overlayParticles, sizeof(OverlayParticle) * particlesCount);
	}

	void AddNum(Position pos, int num, int color)
	{
		overlayNums = (OverlayNum*)realloc(overlayNums, sizeof(OverlayNum) * (numsCount + 1));
		Position posOff;
		posOff.x = rand() % 16 + 4;
		posOff.y = rand() % 16 + 6;
		overlayNums[numsCount] = { pos,posOff,num, color, 255 };
		numsCount++;
	}

	void AddParticle(Position pos, int size, int color, int count)
	{

		overlayParticles = (OverlayParticle*)realloc(overlayParticles, sizeof(OverlayParticle) * (particlesCount + count));
		float angle = 6.28319 / count;
		for (int i = 0; i < count; i++)
		{
			overlayParticles[particlesCount + i] = { pos,16,16,size + Random(size - 1,size + 1), color, Random(155,255),angle * i,(float)Random(5,8) };
		}
		particlesCount += count;
	}
};

struct Drop
{
	int id;
	Position position;
	int level;
};

Player player;

Enemy* enemies;
Enemy* enemiesTypes;

Button* buttons;

Item* items;

Overlay overlay;

SDL_Color colors[10];

Lamp lamps[LAMPS_COUNT];

int map[MAP_SIZE][MAP_SIZE];
int mapOverview[MAP_SIZE][MAP_SIZE];
Drop* drop;

int GetItemsBonus(int bonusId)
{
	int bonus = 0;
	for (int i = 0; i < 5; i++)
	{
		if (player.equipment[i][0] != -1)
		{
			Item item = items[player.equipment[i][0]];
			item.level = player.equipment[i][1];

			for (int j = 0; j < item.bonusesCount; j++)
			{
				if (item.bonuses[j].type == 0 && bonusId == 0)
					bonus += (item.bonuses[j].value + item.level - 1);
				else if (item.bonuses[j].type == 1 && bonusId == 1)
					bonus += (item.bonuses[j].value + item.level - 1);
				else if (item.bonuses[j].type == 2 && bonusId == 2)
					bonus += (item.bonuses[j].value + item.level - 1);
				else if (item.bonuses[j].type == 3 && bonusId == 3)
					bonus += item.bonuses[j].value;
				else if (item.bonuses[j].type == 4 && bonusId == 4)
					bonus += item.bonuses[j].value;
				else if (item.bonuses[j].type == 5 && bonusId == 5)
					bonus += (item.bonuses[j].value + item.level - 1);
			}
		}
	}
	return bonus;
}

int GetCellBonus(int cellId, int bonusType)
{
	if (player.equipment[cellId][0] != -1)
	{
		Item item = items[player.equipment[cellId][0]];
		item.level = player.equipment[cellId][1];

		for (int j = 0; j < item.bonusesCount; j++)
		{
			if (item.bonuses[j].type == bonusType)
				if (item.bonuses[j].type != 3 && item.bonuses[j].type != 4)
					return item.bonuses[j].value + (item.level - 1);
				else
					return item.bonuses[j].value;
		}
	}
}

void AddDrop(int itemId, Position position, int level)
{
	dropCount++;
	drop = (Drop*)realloc(drop, sizeof(Drop) * dropCount);

	drop[dropCount - 1] = { itemId, position, level };
}

void DeleteDrop(int id)
{
	for (int i = id; i < dropCount - 1; i++)
	{
		drop[i] = drop[i + 1];
	}
	dropCount--;

	drop = (Drop*)realloc(drop, sizeof(Drop) * dropCount);
}

void InitItems()
{
	FILE* ft;
	if (fopen_s(&ft, "PARAMS\\Items.txt", "rt") != 0)
	{
		exit(1);
	}
	fscanf_s(ft, "%d", &itemsCount);

	items = (Item*)malloc(sizeof(Item) * itemsCount);

	for (int i = 0; i < itemsCount; i++)
	{
		fgets(items[i].name, 126, ft);

		items[i].name[strlen(items[i].name) - 1] = '\0';
		fscanf_s(ft, "%d %d %d %d", &items[i].iconTextureId, &items[i].type, &items[i].bonusesCount, &items[i].requirementsCount);
		items[i].bonuses = (ItemParam*)malloc(sizeof(ItemParam) * items[i].bonusesCount);
		items[i].requirements = (ItemParam*)malloc(sizeof(ItemParam) * items[i].requirementsCount);
		for (int j = 0; j < items[i].bonusesCount; j++)
			fscanf_s(ft, "%d %d", &items[i].bonuses[j].type, &items[i].bonuses[j].value);
		for (int j = 0; j < items[i].requirementsCount; j++)
			fscanf_s(ft, "%d %d", &items[i].requirements[j].type, &items[i].requirements[j].value);
	}

	fclose(ft);
}

void RecalculatePlayer()
{
	player.maxHealth = 10 + (player.level - 1) * 2 + player.params[1] - 1 + GetItemsBonus(1);
	player.damage = player.params[0] + GetItemsBonus(0);
	player.protection = player.params[2] + GetItemsBonus(2);
	player.agility = player.params[3] + GetItemsBonus(5);

	player.health = Min(player.maxHealth, player.health);
}

void InitColors()
{
	colors[0] = { 255,255,255 };
	colors[1] = { 255,200,200 };
	colors[2] = { 0,0,0 };
	colors[3] = { 100,255,100 };
	colors[4] = { 232,211,68 };
	colors[5] = { 200,200,255 };
	colors[6] = { 190,162,88 };
	colors[7] = { 255,142,68 };
	colors[8] = { 142,255,68 };
	colors[9] = { 255,35,15 };
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
	textures[14] = IMG_LoadTexture(ren, "GFX\\WeaponMenuCell.png");
	textures[17] = IMG_LoadTexture(ren, "GFX\\MenuCell.png");
	textures[19] = IMG_LoadTexture(ren, "GFX\\GoldMenu.png");
	textures[25] = IMG_LoadTexture(ren, "GFX\\EQP\\Item0.png");
	textures[26] = IMG_LoadTexture(ren, "GFX\\EQP\\Item1.png");
	textures[27] = IMG_LoadTexture(ren, "GFX\\EQP\\Item2.png");
	textures[28] = IMG_LoadTexture(ren, "GFX\\EQP\\Item3.png");
	textures[29] = IMG_LoadTexture(ren, "GFX\\EQP\\Item4.png");
	textures[30] = IMG_LoadTexture(ren, "GFX\\EQP\\Item5.png");
	textures[31] = IMG_LoadTexture(ren, "GFX\\EQP\\Item6.png");
	textures[32] = IMG_LoadTexture(ren, "GFX\\EQP\\Item7.png");
	textures[33] = IMG_LoadTexture(ren, "GFX\\EQP\\Item8.png");
	textures[50] = IMG_LoadTexture(ren, "GFX\\Lamp.png");
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
		fscanf_s(ft, "%s %d %d %d %d %d %d %d %d %d %d %d", &enemiesTypes[i].name, sizeof(enemiesTypes[i].name), &enemiesTypes[i].iconTextureId, &enemiesTypes[i].maxHealth, &enemiesTypes[i].attacks, &enemiesTypes[i].moves, &enemiesTypes[i].damage, &enemiesTypes[i].attackrange, &enemiesTypes[i].regeneration, &enemiesTypes[i].xpReward, &enemiesTypes[i].protection, &enemiesTypes[i].goldReward, &enemiesTypes[i].dropChance);
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
	player.xp += enemies[id].xpReward + enemies[id].xpReward * enemies[id].level / 4;
	int gold = enemies[id].goldReward;
	gold = Random(gold / 2, gold);
	player.gold += gold;

	overlay.AddParticle(enemies[id].position, 3, 9, 20);

	if (Random(0, 100) <= enemies[id].dropChance)
	{
		AddDrop(Random(0, itemsCount - 1), enemies[id].position, enemies[id].level);
	}

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
	buttons = (Button*)malloc(sizeof(Button) * 16);
	buttons[0] = *(new Button({ 652,100 }, new char[7]{ "Attack" }, 296, 24, false, 30, 6, true));
	buttons[1] = *(new Button({ 928,480 }, new char[2]{ "\0" }, 32, 32, false, NULL, 7, false));
	buttons[2] = *(new Button({ 928,512 }, new char[2]{ "\0" }, 32, 32, false, NULL, 9, false));
	buttons[3] = *(new Button({ 928,558 }, new char[2]{ "\0" }, 24, 24, false, NULL, 8, false));
	buttons[4] = *(new Button({ 928,590 }, new char[2]{ "\0" }, 24, 24, false, NULL, 8, false));
	buttons[5] = *(new Button({ 928,622 }, new char[2]{ "\0" }, 24, 24, false, NULL, 8, false));
	buttons[6] = *(new Button({ 928,654 }, new char[2]{ "\0" }, 24, 24, false, NULL, 8, false));
	buttons[15] = *(new Button({ 400,674 }, new char[5]{ "Robe" }, 160, 24, false, 64, NULL, true));
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
		ants[i] = { Random(MAP_SIZE / 4,MAP_SIZE / 4 * 3), Random(MAP_SIZE / 4,MAP_SIZE / 4 * 3) };
		map[ants[i].position.x][ants[i].position.y] = 0;
		cells++;
	}

	while (cells < CELLS_FILL)
		for (int j = 0; j < ANTS_COUNT; j++)
		{
			Ant ant = ants[j];

			for (int i = 0; i < 1000; i++)
			{
				int dir = Random(0, 3);

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

	for (int i = 0; i < LAMPS_COUNT; i++)
	{
		do
		{
			lamps[i].position.x = Random(0, MAP_SIZE - 1);
			lamps[i].position.y = Random(0, MAP_SIZE - 1);
		} while (map[lamps[i].position.x][lamps[i].position.y] != 0);
		lamps[i].textureId = 50;
		lamps[i].bright = Random(-2, 2);
		map[lamps[i].position.x][lamps[i].position.y] = 2;
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
		pos.x = ConvBig(pos.x, player.x()) + oNum.offset.x;
		pos.y = ConvBig(pos.y, player.y()) + oNum.offset.y;
		PrintText(oNum.num, pos, 16, overlay.overlayNums[i].alpha, 2);
		pos.y--;
		PrintText(oNum.num, pos, 16, overlay.overlayNums[i].alpha, oNum.color);
		overlay.overlayNums[i].offset.y -= 1;
		overlay.overlayNums[i].alpha = Max(overlay.overlayNums[i].alpha - 3, 0);
		if (overlay.overlayNums[i].alpha <= 0)
			overlay.ClearNum(i);
	}

	for (int i = 0; i < overlay.particlesCount; i++)
	{
		OverlayParticle oPart = overlay.overlayParticles[i];
		Position pos = oPart.pos;
		pos.x = ConvBig(pos.x, player.x()) + (int)oPart.offX;
		pos.y = ConvBig(pos.y, player.y()) + (int)oPart.offY;

		SDL_Rect rect = { pos.x ,pos.y,oPart.size,oPart.size };
		SDL_Color cl = colors[oPart.color];
		SDL_SetRenderDrawColor(ren, cl.r, cl.g, cl.b, oPart.alpha);
		SDL_RenderFillRect(ren, &rect);

		overlay.overlayParticles[i].offX += cos(oPart.angleOfMove) * oPart.moveSpeed;
		overlay.overlayParticles[i].offY += sin(oPart.angleOfMove) * oPart.moveSpeed;
		overlay.overlayParticles[i].moveSpeed = Max(overlay.overlayParticles[i].moveSpeed - 0.01, 0);
		overlay.overlayParticles[i].alpha -= 2;

		if (overlay.overlayParticles[i].alpha <= 0)
			overlay.ClearParticle(i);
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
	PrintText("Health: ", { 10, 896 }, 16, 255, 0);
	offset = PrintText(player.health, { 102, 896 }, 16, 255, 0);
	offset = PrintText("/", { offset.x + 4, 896 }, 16, 255, 0);
	PrintText(player.maxHealth, { offset.x + 4, 896 }, 16, 255, 0);
	PrintText("Mana: ", { 10, 926 }, 16, 255, 0);
	offset = PrintText(player.mana, { 102, 926 }, 16, 255, 0);
	offset = PrintText("/", { offset.x + 4, 926 }, 16, 255, 0);
	PrintText(player.maxMana, { offset.x + 4, 926 }, 16, 255, 0);

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
	buttons[15].active = false;

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
		offset = PrintText("Level: ", { 652, 68 }, 16, 255, 0);
		PrintText(enemies[player.selectedEnemy].level, { offset.x + 4, 68 }, 16, 255, 0);

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
		for (int i = 0; i < 3; i++)
			buttons[3 + i].active = false;
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

		int bn = GetItemsBonus(0);

		offset = PrintText("Strength ", { 656, 560 }, 12, 255, 0);
		offset = PrintText(player.params[0], { offset.x, 560 }, 12, 255, 0);
		if (bn)
		{
			offset = PrintText(" + ", { offset.x, 560 }, 12, 255, 5);
			offset = PrintText(bn, { offset.x, 560 }, 12, 255, 5);
		}
		if (player.points > 0)
		{
			offset = PrintText("Cost: ", { offset.x + 16, 560 }, 12, 255, 0);
			PrintText(floor(1 + player.params[0] * 0.4), { offset.x, 560 }, 12, 255, 0);
		}

		bn = GetItemsBonus(1);

		offset = PrintText("Vitality ", { 656, 592 }, 12, 255, 0);
		offset = PrintText(player.params[1], { offset.x, 592 }, 12, 255, 0);
		if (bn)
		{
			offset = PrintText(" + ", { offset.x, 592 }, 12, 255, 5);
			offset = PrintText(bn, { offset.x, 592 }, 12, 255, 5);
		}
		if (player.points > 0)
		{
			offset = PrintText("Cost: ", { offset.x + 16, 592 }, 12, 255, 0);
			PrintText(floor(1 + player.params[1] * 0.4), { offset.x, 592 }, 12, 255, 0);
		}

		bn = GetItemsBonus(2);

		offset = PrintText("Protection ", { 656, 624 }, 12, 255, 0);
		offset = PrintText(player.params[2], { offset.x, 624 }, 12, 255, 0);
		if (bn)
		{
			offset = PrintText(" + ", { offset.x, 624 }, 12, 255, 5);
			offset = PrintText(bn, { offset.x, 624 }, 12, 255, 5);
		}
		if (player.points > 0)
		{
			offset = PrintText("Cost: ", { offset.x + 16, 624 }, 12, 255, 0);
			PrintText(floor(1 + player.params[2] * 0.4), { offset.x, 624 }, 12, 255, 0);
		}

		bn = GetItemsBonus(5);

		offset = PrintText("Agility ", { 656, 656 }, 12, 255, 0);
		offset = PrintText(player.params[3], { offset.x, 656 }, 12, 255, 0);
		if (bn)
		{
			offset = PrintText(" + ", { offset.x, 656 }, 12, 255, 5);
			offset = PrintText(bn, { offset.x, 656 }, 12, 255, 5);
		}
		if (player.points > 0)
		{
			offset = PrintText("Cost: ", { offset.x + 16, 656 }, 12, 255, 0);
			PrintText(floor(1 + player.params[3] * 0.4), { offset.x, 656 }, 12, 255, 0);
		}

		for (int i = 0; i < 4; i++)
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

		RenderImage(19, { 640,480 }, 32, 32, 255);
		PrintText(player.gold, { 676, 488 }, 16, 255, 4);

		if (player.equipment[0][0] != -1)
		{
			RenderImage(17, { 768,512 }, 64, 64, 255);
			RenderImage(items[player.equipment[0][0]].iconTextureId, { 768,512 }, 64, 64, 255);
			Item item = items[player.equipment[0][0]];
		}
		else
		{
			RenderImage(10, { 768,512 }, 64, 64, 255);
		}

		if (player.equipment[1][0] != -1)
		{
			RenderImage(17, { 768,576 }, 64, 64, 255);
			RenderImage(items[player.equipment[1][0]].iconTextureId, { 768,576 }, 64, 64, 255);
			Item item = items[player.equipment[1][0]];
		}
		else
		{
			RenderImage(11, { 768,576 }, 64, 64, 255);
		}

		if (player.equipment[2][0] != -1)
		{
			RenderImage(17, { 768,640 }, 64, 64, 255);
			RenderImage(items[player.equipment[2][0]].iconTextureId, { 768,640 }, 64, 64, 255);
			Item item = items[player.equipment[2][0]];
		}
		else
		{
			RenderImage(12, { 768,640 }, 64, 64, 255);
		}

		if (player.equipment[3][0] != -1)
		{
			RenderImage(17, { 768,704 }, 64, 64, 255);
			RenderImage(items[player.equipment[3][0]].iconTextureId, { 768,704 }, 64, 64, 255);
			Item item = items[player.equipment[3][0]];
		}
		else
		{
			RenderImage(13, { 768,704 }, 64, 64, 255);
		}

		if (player.equipment[4][0] != -1)
		{
			RenderImage(17, { 688,576 }, 64, 64, 255);
			RenderImage(items[player.equipment[4][0]].iconTextureId, { 688,576 }, 64, 64, 255);
			Item item = items[player.equipment[4][0]];
		}
		else
		{
			RenderImage(14, { 688,576 }, 64, 64, 255);
		}
	}
	else if (playerMenu == 3)
	{
		buttons[2].active = false;
		buttons[1].active = false;

		SDL_Rect rect = { 320,240,320,480 };
		SDL_SetRenderDrawColor(ren, 0, 0, 0, 155);
		SDL_RenderFillRect(ren, &rect);

		if (itemMenuType == 0)
		{
			Drop droped = drop[itemMenu];
			Item item = items[droped.id];
			item.level = droped.level;
			RenderImage(17, { 336,256 }, 64, 64, 255);
			RenderImage(item.iconTextureId, { 336,256 }, 64, 64, 255);
			PrintText(item.name, { 416,264 }, 16, 255, 0);
			switch (item.type)
			{
			case 0:
				PrintText("On Head", { 416,300 }, 16, 255, 0);
				break;
			case 1:
				PrintText("On Body", { 416,300 }, 16, 255, 0);
				break;
			case 2:
				PrintText("On Legs", { 416,300 }, 16, 255, 0);
				break;
			case 3:
				PrintText("On Feet", { 416,300 }, 16, 255, 0);
				break;
			case 4:
				PrintText("One-Arm Weapon", { 416,300 }, 16, 255, 0);
				break;
			default:
				break;
			}

			offset = PrintText("Level: ", { 336,336 }, 16, 255, 0);
			PrintText(item.level, { offset.x,336 }, 16, 255, 0);

			PrintText("Bonuses:", { 336,384 }, 16, 255, 6);

			for (int i = 0; i < item.bonusesCount; i++)
			{
				switch (item.bonuses[i].type)
				{
				case 0:
					offset = PrintText("Strength ", { 336,408 + i * 24 }, 16, 255, 0);
					break;
				case 1:
					offset = PrintText("Vitality ", { 336,408 + i * 24 }, 16, 255, 0);
					break;
				case 2:
					offset = PrintText("Protection ", { 336,408 + i * 24 }, 16, 255, 0);
					break;
				case 3:
					offset = PrintText("Moves +", { 336,408 + i * 24 }, 16, 255, 0);
					break;
				case 4:
					offset = PrintText("Attacks +", { 336,408 + i * 24 }, 16, 255, 0);
					break;
				case 5:
					offset = PrintText("Agility ", { 336,408 + i * 24 }, 16, 255, 0);
					break;
				default:
					break;
				}

				int itemBonus;
				if (item.bonuses[i].type != 3 && item.bonuses[i].type != 4)
					itemBonus = item.bonuses[i].value + (item.level - 1);
				else
					itemBonus = item.bonuses[i].value;

				offset = PrintText(itemBonus, { offset.x,408 + i * 24 }, 16, 255, 0);

				if (player.equipment[item.type][0] != -1)
				{
					int cellBonus = GetCellBonus(item.type, item.bonuses[i].type);

					if (cellBonus > itemBonus)
					{
						offset = PrintText(" -", { offset.x,408 + i * 24 }, 16, 255, 7);
						offset = PrintText(cellBonus - itemBonus, { offset.x,408 + i * 24 }, 16, 255, 7);
					}
					else if (cellBonus < itemBonus)
					{
						offset = PrintText(" +", { offset.x,408 + i * 24 }, 16, 255, 8);
						offset = PrintText(itemBonus - cellBonus, { offset.x,408 + i * 24 }, 16, 255, 8);
					}
				}

			}

			int bnDown = 432 + item.bonusesCount * 24;

			PrintText("Requirements:", { 336,bnDown }, 16, 255, 6);

			bnDown += 24;

			for (int i = 0; i < item.requirementsCount; i++)
			{
				int color;
				switch (item.requirements[i].type)
				{
				case 0:
				{
					color = player.level >= item.requirements[i].value + (item.level - 1) ? 0 : 7;
					offset = PrintText("Level ", { 336,bnDown + i * 24 }, 16, 255, color);
					break;
				}
				case 1:
				{
					color = player.params[0] >= item.requirements[i].value + (item.level - 1) ? 0 : 7;
					offset = PrintText("Strength ", { 336,bnDown + i * 24 }, 16, 255, color);
					break;
				}
				case 2:
				{
					color = player.params[1] >= item.requirements[i].value + (item.level - 1) ? 0 : 7;
					offset = PrintText("Vitality ", { 336,bnDown + i * 24 }, 16, 255, color);
					break;
				}
				case 3:
				{
					color = player.params[2] >= item.requirements[i].value + (item.level - 1) ? 0 : 7;
					offset = PrintText("Protection ", { 336,bnDown + i * 24 }, 16, 255, color);
					break;
				}
				case 4:
				{
					color = player.params[3] >= item.requirements[i].value + (item.level - 1) ? 0 : 7;
					offset = PrintText("Agility ", { 336,bnDown + i * 24 }, 16, 255, color);
					break;
				}
				default:
					break;
				}

				PrintText(item.requirements[i].value + (item.level - 1), { offset.x,bnDown + i * 24 }, 16, 255, color);
			}

			bool robe = true;
			for (int i = 0; i < item.requirementsCount; i++)
			{
				switch (item.requirements[i].type)
				{
				case 0:
					if (item.requirements[i].value + (item.level - 1) > player.level)
						robe = false;
					break;
				case 1:
					if (item.requirements[i].value + (item.level - 1) > player.params[0])
						robe = false;
					break;
				case 2:
					if (item.requirements[i].value + (item.level - 1) > player.params[1])
						robe = false;
					break;
				case 3:
					if (item.requirements[i].value + (item.level - 1) > player.params[2])
						robe = false;
					break;
				case 4:
					if (item.requirements[i].value + (item.level - 1) > player.params[3])
						robe = false;
					break;
				default:
					break;
				}
			}

			if (robe)
				buttons[15].active = true;

			buttons[15].DrawButton();
		}
	}
}

void Draw()
{
	SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
	SDL_RenderClear(ren);
	if (saveMap)
	{
		for (int i = player.x() - 15; i < player.x() + 16; i++)
			for (int j = player.y() - 15; j < player.y() + 16; j++)
			{
				SDL_Rect rect = { ConvBig(i, player.x()),ConvBig(j, player.y()),32,32 };

				int blocks = RayTracing({ i, j }, player.position);
				SDL_SetRenderDrawColor(ren, GetAlpha(30, blocks), GetAlpha(30, blocks), GetAlpha(30, blocks), 255);
				SDL_RenderFillRect(ren, &rect);
				for (int l = 0; l < LAMPS_COUNT; l++)
					if (Distance(player.position, lamps[l].position) <= 15 && RayTracing(lamps[l].position, player.position) <= 6)
					{
						blocks = Min(blocks, Max(RayTracing({ i, j }, lamps[l].position) + lamps[l].bright, 0));
						SDL_SetRenderDrawColor(ren, GetAlpha(30, blocks), GetAlpha(30, blocks), GetAlpha(30, blocks), 255);
						SDL_RenderFillRect(ren, &rect);
						RenderImage(lamps[l].textureId, { ConvBig(lamps[l].position.x, player.x()),ConvBig(lamps[l].position.y, player.y()) }, 32, 32, 255);
					}

				if (blocks <= 5 && map[i][j] == 1)
					mapOverview[i][j] = 1;
				if (map[i][j] == 1)
				{
					SDL_SetRenderDrawColor(ren, GetAlpha(138, blocks), GetAlpha(22, blocks), GetAlpha(31, blocks), 255);
					SDL_RenderFillRect(ren, &rect);
				}
				else if (map[i][j] == 0)
				{
					SDL_SetRenderDrawColor(ren, GetAlpha(30, blocks), GetAlpha(30, blocks), GetAlpha(30, blocks), 255);
					SDL_RenderFillRect(ren, &rect);
				}
			}

		SDL_Surface* lastRenderSur = SDL_CreateRGBSurface(0, winWdt, winHgt, 32, 0x00ff0000, 0x0000ff00, 0x000000ff, 0xff000000);
		SDL_RenderReadPixels(ren, NULL, SDL_GetWindowPixelFormat(win), lastRenderSur->pixels, lastRenderSur->pitch);
		SDL_DestroyTexture(lastRender);
		lastRender = SDL_CreateTextureFromSurface(ren, lastRenderSur);
		SDL_FreeSurface(lastRenderSur);

		saveMap = false;
	}
	else
	{
		SDL_Rect rect = { 0,0,winWdt,winHgt };
		SDL_RenderCopy(ren, lastRender, NULL, &rect);
	}


	for (int i = 0; i < dropCount; i++)
	{
		int blocks = RayTracing(drop[i].position, player.position);
		if (blocks < 5)
			RenderImage(items[drop[i].id].iconTextureId, { ConvBig(drop[i].position.x,player.x()), ConvBig(drop[i].position.y,player.y()) }, 32, 32, GetAlpha(255, blocks));
	}

	SDL_Rect rect = { 464, 464,32,32 };
	SDL_SetRenderDrawColor(ren, 114, 230, 221, 255);
	SDL_RenderFillRect(ren, &rect);
	RenderImage(2, { 464, 464 }, 32, 32, 255);

	SDL_SetRenderDrawColor(ren, 114, 230, 221, 255);
	for (int i = 0; i < enemiesCount; i++)
	{
		if (Distance(player.position, enemies[i].position) <= 20)
		{
			int blocks = RayTracing(enemies[i].position, player.position);
			for (int l = 0; l < LAMPS_COUNT; l++)
				if (Distance(player.position, lamps[l].position) <= 15 && RayTracing(lamps[l].position, player.position) <= 5)
					blocks = Min(blocks, Max(RayTracing(enemies[i].position, lamps[l].position) + lamps[l].bright, 0));
			rect = { ConvBig(enemies[i].x(), player.x()) ,ConvBig(enemies[i].y(), player.y()),32,32 };
			SDL_SetRenderDrawColor(ren, GetAlpha(198, blocks), GetAlpha(101, blocks), GetAlpha(202, blocks), 255);
			SDL_RenderFillRect(ren, &rect);
			if (blocks <= 5)
				RenderImage(3, { rect.x, rect.y }, 32, 32, GetAlpha(255, blocks));
		}
	}

	DrawOverlay();
	DrawUI();
}

void SpawnPlayer()
{
	do
	{
		player.x(Random(0, MAP_SIZE - 1));
		player.y(Random(0, MAP_SIZE - 1));
	} while (map[player.x()][player.y()] != 0);

	player.maxHealth = 10;
	player.health = 10;

	//AddDrop(2, player.position, 1);
}

void SpawnEnemies()
{
	for (int i = 0; i < enemiesCount; i++)
	{
		Enemy enemy;
		do
		{
			enemy.x(Random(0, MAP_SIZE - 1));
			enemy.y(Random(0, MAP_SIZE - 1));
		} while (map[enemy.x()][enemy.y()] != 0);
		enemies[i] = enemiesTypes[enemies[i].type];
		enemies[i].position = enemy.position;
		enemies[i].level = Random(1, 3);
		enemies[i].maxHealth += enemies[i].maxHealth / 5 * (enemies[i].level - 1);
		enemies[i].health = enemies[i].maxHealth;
		enemies[i].damage += enemies[i].level - 1;
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
	for (int i = Max(Min(start.x, end.x) - 5, 0); i < Min(Max(start.x, end.x) + 5, 299); i++)
		for (int j = Max(Min(start.y, end.y) - 5, 0); j < Min(Max(start.y, end.y) + 5, 299); j++)
			if (map[i][j] == 1 || map[i][j] == 2 || !CheckEntity({ i,j }) && !Comp(end, { i,j }) && !Comp(start, { i,j }))
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
			if (enemy.path.len <= 0)
				break;
		}

		for (int i = 0; i < enemy.attacks; i++)
		{
			if (CheckAttackDist(enemy, player))
			{
				int damage = round(enemy.damage / floor(1 + player.protection / 3));
				player.health -= damage;
				enemy.moves--;
				overlay.AddNum(player.position, -damage, 1);
				overlay.AddParticle(player.position, 2, 9, 15);
			}
		}
	}
	else if (Distance(player.position, enemy.position) <= 15)
	{
		if (enemy.path.len > 0)
			enemy.Move();
		else if (Random(0, 15) <= 3)
			enemy.NewPath(FindPath(enemy.position, { enemy.position.x + Random(-2,2),enemy.position.y + Random(-2,2) }));
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
		player.moves = 1;
		player.attacks = 1;
		moves++;
		player.moves += GetItemsBonus(3);
		player.attacks += GetItemsBonus(4);

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
	if (buttonId == 0 && player.attacks && playerMenu != 3)
	{
		int damage = round(player.damage / floor(1 + enemies[player.selectedEnemy].protection / 3));

		enemies[player.selectedEnemy].health -= damage;
		player.attacks -= 1;
		overlay.AddNum(enemies[player.selectedEnemy].position, -damage, 1);
		overlay.AddParticle(enemies[player.selectedEnemy].position, 2, 9, 15);
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
	else if (buttonId >= 3 && buttonId <= 6)
	{
		int reqPoints = floor(1 + player.params[buttonId - 3] * 0.4);

		if (player.points >= (int)reqPoints)
		{
			player.points -= reqPoints;
			player.params[buttonId - 3]++;
			RecalculatePlayer();
		}
	}
	else if (buttonId == 15)
	{
		Drop droped = drop[itemMenu];
		int type = items[droped.id].type;

		if (player.equipment[type][0] != -1)
		{
			drop[itemMenu].id = player.equipment[type][0];
			drop[itemMenu].level = player.equipment[type][1];
		}
		else
		{
			DeleteDrop(itemMenu);
		}

		player.equipment[type][0] = droped.id;
		player.equipment[type][1] = droped.level;

		itemMenu = -1;
		itemMenuType = -1;
		buttonId = -1;
		playerMenu = 0;

		RecalculatePlayer();
	}
	else if (buttonId >= 100)
	{
		if (playerMenu != 3)
		{
			playerMenu = 3;
			itemMenuType = 0;
			itemMenu = buttonId % 100;
			player.selectedEnemy = -1;
		}
		else
		{
			playerMenu = 0;
		}
	}
}

int CheckButtonClick(Position mPos)
{
	if (playerMenu != 3)
	{
		for (int i = 0; i < dropCount; i++)
		{
			Position pos = { ConvBig(drop[i].position.x,player.x()), ConvBig(drop[i].position.y,player.y()) };
			if (mPos.x >= pos.x && mPos.y >= pos.y && mPos.x <= pos.x + 32 && mPos.y <= pos.y + 32 && RayTracing(player.position, drop[i].position) <= 5 && Distance(player.position, drop[i].position) <= 2)
			{
				return 100 + i;
			}
		}
	}
	else if ((mPos.x < 320 || mPos.x>640 || mPos.y < 240 || mPos.y>720))
		playerMenu = 0;
	for (int i = 0; i < 16; i++)
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
	int lastTime = SDL_GetTicks(), newTime, delta = 0;

	font = TTF_OpenFont("Fonts\\MainFont.ttf", 20);
	SDL_Event event;

	Generate();
	SpawnPlayer();
	SpawnEnemies();
	RecalculatePlayer();

	while (true)
	{
		const Uint8* state = SDL_GetKeyboardState(NULL);

		SDL_PumpEvents();
		Uint32 events = SDL_GetMouseState(&_mouse.x, &_mouse.y);

		if ((events & SDL_BUTTON_LMASK) != 0 && !_down)
		{
			_down = true;
			lastBtnId = CheckButtonClick(_mouse);
			if (lastBtnId < 100)
			{
				ButtonAction(lastBtnId);
				if (playerMenu != 3)
					player.selectedEnemy = CheckSelection(_mouse);
			}
			else
			{
				player.selectedEnemy = CheckSelection(_mouse);
				if (player.selectedEnemy == -1)
					ButtonAction(lastBtnId);
			}
		}
		if ((events & SDL_BUTTON_LMASK) == 0)
			_down = false;

		SDL_PollEvent(&event);

		if ((event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) && playerMenu != 3)
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

			if (moved)
			{
				saveMap = true;
			}
		}
		Draw();
		SDL_RenderPresent(ren);

		newTime = SDL_GetTicks();
		delta = newTime - lastTime;
		lastTime = newTime;

		if (delta < 16)
		{
			SDL_Delay(16 - delta);
		}
	}
	TTF_CloseFont(font);

	DeInit(0);
	return 0;
}