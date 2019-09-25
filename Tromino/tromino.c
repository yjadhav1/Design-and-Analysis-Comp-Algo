#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
int **tilesStructure;

void tromino(int x_board, int y_board, int x_missing,int y_missing, int board_size, int **tilesStructure)
{
	int half_size=board_size/2;
	int x_center,y_center, x_upper_left,y_upper_left, x_lower_right,y_lower_right, x_lower_left,y_lower_left, x_upper_right,y_upper_right;
	if(board_size == 2)
	{
		int i,j;
		for ( i = x_board; i < (x_board+board_size); ++i)
		{
			for ( j = y_board; j< (y_board+board_size); ++j)
			{
				if(!(i==x_missing && j==y_missing))
				{
					if(x_missing == x_board && y_missing == (y_board + 1))
					{
						tilesStructure[i][j]= 1; //LR
					}
					else if(x_missing == (x_board + 1) && y_missing == (y_board + 1))
					{
						tilesStructure[i][j]= 2; //LL
					}
					else if(x_missing == (x_board + 1) && y_missing == y_board)
					{
						tilesStructure[i][j]=3; //UL
					}
					else if(x_missing == x_board && y_missing == y_board)
					{
						tilesStructure[i][j]=4; //UR
					}
				}
			}
		}
		return;
	}

	x_center=x_board+half_size;
	y_center=y_board+half_size;

	if(x_missing<x_center && y_missing< y_center)
	{
		tilesStructure[x_center-1][y_center]=tilesStructure[x_center][y_center]=tilesStructure[x_center][y_center-1]=4;

		x_upper_left=x_missing;y_upper_left=y_missing;

		x_upper_right=x_center-1; y_upper_right=y_center;

		x_lower_left=x_center; y_lower_left=y_center-1;

		x_lower_right=x_center; y_lower_right=y_center;

	}
	else if(x_missing<x_center && y_missing>=y_center)
	{
		tilesStructure[x_center-1][y_center-1] = tilesStructure[x_center][y_center] = tilesStructure[x_center][y_center-1]=1;

		x_upper_left=x_center-1; y_upper_left=y_center-1;

		x_upper_right=x_missing; y_upper_right=y_missing;

		x_lower_left=x_center; y_lower_left= y_center-1;

		x_lower_right = x_center ; y_lower_right = y_center;


	}
	else if(x_missing>=x_center && y_missing<y_center)
	{
		tilesStructure[x_center-1][y_center-1]=tilesStructure[x_center-1][y_center]=tilesStructure[x_center][y_center]=3;

		x_upper_left=x_center-1;y_upper_left=y_center-1;

		x_upper_right=x_center-1; y_upper_right=y_center;

		x_lower_left=x_missing; y_lower_left=y_missing;

		x_lower_right=x_center; y_lower_right=y_center;

	}
	else if(x_missing>=x_center && y_missing>=y_center)
	{
		tilesStructure[x_center-1][y_center-1]=tilesStructure[x_center-1][y_center]=tilesStructure[x_center][y_center-1]=2;

		x_upper_left=x_center-1;y_upper_left=y_center-1;

		x_upper_right=x_center-1; y_upper_right=y_center;

		x_lower_left=x_center; y_lower_left=y_center-1;

		x_lower_right=x_missing; y_lower_right=y_missing;

	}
	tromino(x_board,y_board, x_upper_left, y_upper_left, half_size,tilesStructure );
	tromino(x_board,y_board+half_size, x_upper_right, y_upper_right, half_size,tilesStructure);
	tromino(x_board+half_size,y_board, x_lower_left, y_lower_left, half_size, tilesStructure);
	tromino(x_board+half_size,y_board+half_size, x_lower_right, y_lower_right, half_size, tilesStructure);

}
void printTiles(int size, int **ptr_arr)
{
	int i,j;

	for (j = (size - 1); j >= 0; --j)
	{
		for ( i = 0; i < size; ++i)
			{
				if(ptr_arr[i][j]==(-1))
				{
					printf("MS\t");
				}
				else if(ptr_arr[i][j]==1)
				{
					printf("LR\t");
				}
				else if(ptr_arr[i][j]==2)
				{
					printf("LL\t");
				}
				else if(ptr_arr[i][j]==3)
				{
					printf("UL\t");
				}
				else if(ptr_arr[i][j]==4)
				{
					printf("UR\t");
				}

			}
		printf("\n");
	}
}
int main(int argc, char *args[])
{
	char *n;
	char *x_y;
	char *token;

	n = (char *) malloc(10);
	x_y = (char *) malloc(10);
	token = (char *) malloc(10);

	printf("Please enter size of board (0 to quit):");
	fgets(n, 10, stdin);
	printf("Please enter coordinates of missing square (separate by a space):");
	fgets(x_y, 10, stdin);
	if(atoi(n)<1)
	{
		printf("Size must be greater than or equal to 2 \n");
		return 0;
	}
		int board_size;
		board_size=atoi(n);

		int i,j,x_missing,y_missing;
		token = strtok(x_y, " ");
	  x_missing = atoi(token);
		token = strtok(NULL, " ");
	  y_missing = atoi(token);

		tilesStructure = (int**)malloc(sizeof(int*) * board_size);
			for (i=0; i<board_size; i++)
			{
				tilesStructure[i] = malloc(board_size * sizeof *tilesStructure[i]);
			}

		for ( i = 0; i < board_size; ++i){

			for ( j = 0; j < board_size; ++j){
				tilesStructure[i][j]=0;
			}
		}
		tilesStructure[x_missing][y_missing]=-1;
		tromino(0,0, x_missing,y_missing,board_size, tilesStructure);

		printTiles(board_size,tilesStructure);

		for (i=0; i<board_size; i++)
		{
			free(tilesStructure[i]);
		}
		free(tilesStructure);
		free(n);
		free(x_y);
		//free(token);

	return 0;
}
