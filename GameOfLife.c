/*Initially, there is a grid with some cells which may be alive or dead. Our task is to generate the next generation of cells based on the following rules:

Any live cell with fewer than two live neighbors dies as if caused by underpopulation.
Any live cell with two or three live neighbors lives on to the next generation.
Any live cell with more than three live neighbors dies, as if by overpopulation.
Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int **matrix(int n)
{
	int **res = (int **)malloc(n * sizeof(int *));
	for (int i = 0; i < n; i++)
	{
		res[i] = (int *)malloc(n * sizeof(int));
	}
	return res;
}

void randMat(int **mat, int p, int n)
{
	srand(time(NULL));
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			int rd = rand() % p;
			if (rd == 0)
			{
				mat[i][j] = 1;
			}
			else
			{
				mat[i][j] = 0;
			}
		}
	}
}

int printMat(int **mat, int n)
{
	int cells = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (mat[i][j] == 0)
				printf("  ");
			else
			{
				printf("O ");
				cells++;
			}
		}
		printf("\n");
	}
	return cells;
}

int life(int **mat, int i, int j, int n)
{
	int spell = 0;

	if (i > 0)
	{
		if (mat[i - 1][j] == 1)
			spell++;
	}

	if (j > 0)
	{
		if (mat[i][j - 1] == 1)
			spell++;
	}

	if (i < n - 1)
	{
		if (mat[i + 1][j] == 1)
			spell++;
	}

	if (j < n - 1)
	{
		if (mat[i][j + 1] == 1)
			spell++;
	}

	if (i > 0 && j > 0)
	{
		if (mat[i - 1][j - 1] == 1)
			spell++;
	}

	if (i > 0 && j < n - 1)
	{
		if (mat[i - 1][j + 1] == 1)
			spell++;
	}

	if (i < n - 1 && j > 0)
	{
		if (mat[i + 1][j - 1] == 1)
			spell++;
	}

	if (i < n - 1 && j < n - 1)
	{
		if (mat[i + 1][j + 1] == 1)
			spell++;
	}

	return spell;
}

int matReader(int **mat, int n)
{
	int born = 0;
	int m;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			m = mat[i][j];
			int lf = life(mat, i, j, n);
			if (lf == 3)
			{
				if (m == 0)
				{
					mat[i][j] = 1;
					born++;
				}
			}
			else if (lf < 2)
			{
				if (m == 1)
					mat[i][j] = 0;
			}
			else if (lf > 3)
			{
				if (m == 1)
					mat[i][j] = 0;
			}
		}
	}
	return born;
}

int main()
{
	int n;
	int p;
	int g;
	printf("select the dimension of the matrix: ");
	scanf("%d", &n);
	printf("select the level of population (1 max 10 min): ");
	scanf("%d", &p);
	printf("select number of generations (1 min 1000 max): ");
	scanf("%d", &g);
	int **mat = matrix(n);
	randMat(mat, p, n);
	printMat(mat, n);
	printf("starting process...\n");
	sleep(2);
	for (int i = 0; i < g; i++)
	{
		system("CLS");
		printf("%d new borns\n", matReader(mat, n));
		printf("%d live cells\n", printMat(mat, n));
	}
}