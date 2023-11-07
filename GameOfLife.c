/*Initially, there is a grid with some cells which may be alive or dead. Our task is to generate the next generation of cells based on the following rules:

Any live cell with fewer than two live neighbors dies as if caused by underpopulation.
Any live cell with two or three live neighbors lives on to the next generation.
Any live cell with more than three live neighbors dies, as if by overpopulation.
Any dead cell with exactly three live neighbors becomes a live cell, as if by reproduction.*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define SIZE 30

int **matrix()
{
	int **res = (int **)malloc(SIZE * sizeof(int *));
	for (int i = 0; i < SIZE; i++)
	{
		res[i] = (int *)malloc(SIZE * sizeof(int));
	}
	return res;
}

void randMat(int **mat)
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			int rd = rand() % 9;
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

int printMat(int **mat)
{
	int cells = 0;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
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

int life(int **mat, int i, int j)
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

	if (i < SIZE - 1)
	{
		if (mat[i + 1][j] == 1)
			spell++;
	}

	if (j < SIZE - 1)
	{
		if (mat[i][j + 1] == 1)
			spell++;
	}

	if (i > 0 && j > 0)
	{
		if (mat[i - 1][j - 1] == 1)
			spell++;
	}

	if (i > 0 && j < SIZE - 1)
	{
		if (mat[i - 1][j + 1] == 1)
			spell++;
	}

	if (i < SIZE - 1 && j > 0)
	{
		if (mat[i + 1][j - 1] == 1)
			spell++;
	}

	if (i < SIZE - 1 && j < SIZE - 1)
	{
		if (mat[i + 1][j + 1] == 1)
			spell++;
	}

	return spell;
}

int matReader(int **mat)
{
	int born = 0;
	int m;
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			m = mat[i][j];
			int lf = life(mat, i, j);
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
	int **mat = matrix();
	randMat(mat);
	printMat(mat);
	printf("\n");
	sleep(2);
	for (int i = 0; i < 600; i++)
	{
		system("CLS");
		printf("\n\n");
		printf("%d new borns\n", matReader(mat));
		printf("%d live cells\n", printMat(mat));
	}
}