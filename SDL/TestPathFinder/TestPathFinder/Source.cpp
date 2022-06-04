#include <iostream>

int px = 3;
int py = 1;

int map[10][10] = {
	{1,1,1,1,1,1,1,1,1,1},
	{1,0,1,0,0,0,0,0,0,1},
	{1,0,1,0,0,0,1,0,0,1},
	{1,0,1,0,1,1,1,0,0,1},
	{1,0,1,1,1,0,1,0,1,1},
	{1,0,0,0,1,0,1,0,0,1},
	{1,0,1,1,1,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1}
};

void PathFinder(int startx, int starty, int endx, int endy)
{
	int w[10][10];
	for (size_t i = 0; i < 10; i++)
		for (size_t j = 0; j < 10; j++)
			if (map[i][j] == 1)
				w[i][j] = -1;
			else if (i == startx && j == starty)
				w[i][j] = 1;
			else
				w[i][j] = 0;

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

		void Connect(int branchId, int w[10][10])
		{
			Point branch = branchPoints[branchId];

			w[branch.x][branch.y] = w[point.x][point.y] + 1;
		}
	};

	bool end = false;
	while (!end)
	{
		Root roots[100];
		int rootCount = 0;

		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
			{

				if (w[i][j] > 0)
				{
					if (i == endx && j == endy)
					{
						end = true;
						break;
					}
					int weights[4] = { w[i + 1][j],w[i - 1][j],w[i][j + 1],w[i][j - 1] };
					bool canConnect = false;
					if ((weights[0] != -1 && weights[0] >= w[i][j] + 1 || weights[0] == 0) && i < 9)
					{
						roots[rootCount].addBranch({ i + 1,j });
						canConnect = true;
					}
					if ((weights[1] != -1 && weights[1] >= w[i][j] + 1 || weights[1] == 0) && i > 0)
					{
						roots[rootCount].addBranch({ i - 1,j });
						canConnect = true;
					}
					if ((weights[2] != -1 && weights[2] >= w[i][j] + 1 || weights[2] == 0) && j < 9)
					{
						roots[rootCount].addBranch({ i,j + 1 });
						canConnect = true;
					}
					if ((weights[3] != -1 && weights[3] >= w[i][j] + 1 || weights[3] == 0) && j > 0)
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

			roots[rootId].Connect(branchId, w);
		}
		else
		{
			break;
		}
	}

	system("cls");
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			if (startx == i && starty == j)
				printf("  X");
			else if (endx == i && endy == j)
				printf("  Z");
			else
				printf("%3d", map[i][j]);
		}
		printf("\n");
	}

	printf("\n\n\n\n");
	for (size_t i = 0; i < 10; i++)
	{
		for (size_t j = 0; j < 10; j++)
		{
			printf("%3d", w[i][j]);
		}
		printf("\n");
	}
}

int main()
{
	PathFinder(py, px, 1, 1);

	return 0;
}