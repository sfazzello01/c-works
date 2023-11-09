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
				mat[i][j] = 0;
			}
			else
			{
				mat[i][j] = 1;
			}
		}
	}
}

int newRound(int **mat, int x, int y)
{
	if (mat[x][y] == -1)
	{
		printf("select an active box\n\n");
		return (-1);
	}
	else if (mat[x][y] == 1)
	{
		printf("you are safe for now!\n\n");
		mat[x][y] = -1;
		return (1);
	}
	else if (mat[x][y] == 0)
	{
		printf("BOOOOOM!!\n ***GAME OVER***\n");
		return (0);
	}
}

void printMat(int **mat, int n, int control)
{
	if (control == 0)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (mat[i][j] == 0)
					printf("! ");
				if (mat[i][j] == -1)
					printf("  ");
				if (mat[i][j] == 1)
					printf("O ");
			}
			printf("\n");
		}
	}
	else
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (mat[i][j] == -1)
					printf("  ");
				else
					printf("O ");
			}
			printf("\n");
		}
	}
	
}

int main()
{
	int dim;
	int diff;
	int x;
	int y;
	printf("select size of the map: ");
	scanf("%d", &dim);
	printf("select difficulty: ");
	scanf("%d", &diff);
	int** mat = matrix(dim);
	randMat(mat, diff, dim);
	printMat(mat, dim, 1);
	printf("coordinates: ");
	scanf("%d %d", &x, &y);
	system("CLS");
	if (x >= dim || y >= dim)
	{
		printf("select an eligible box\n");
	}
	else
		printMat(mat, dim, newRound(mat, x, y));
	while(mat[x][y])
	{
		printf("coordinates: "); 
		scanf("%d %d", &x, &y);
		if (x >= dim || y >= dim)
			{
				printf("select an eligible box\n");
				continue;
			}
		system("CLS");
		printMat(mat, dim, newRound(mat, x, y));
		
	}
}