#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

int	is_valid(int board[4][4])
{
	int	shown[4] = {0,0,0,0};
	int	i;
	int	j;

	//おかしい行があればFALSE
	for(i = 0; i < 4; i++)
	{
		for(j = 0; j < 4; j++)
			shown[j] = 0;

		for(j = 0; j < 4; j++)
		{
			if(board[i][j] != 0)
				shown[board[i][j] - 1]++;
		}
		for(j = 0; j < 4; j++)
		{
			if(shown[j] >= 2)
				return (FALSE);
		}
	}

	//おかしい列があればFALSE
	for(j = 0; j < 4; j++)
	{
		for(i = 0; i < 4; i++)
			shown[i] = 0;

		for(i = 0; i < 4; i++)
		{
			if(board[i][j] != 0)
				shown[board[i][j] - 1]++;
		}
		for(i = 0; i < 4; i++)
		{
			if(shown[i] >= 2)
				return (FALSE);
		}
	}
	return (TRUE);
}

int	count_buildings(int board[4][4], int mode, int num)
{
	int	count;
	int	biggest;

	count = 0;
	biggest = 0;
	if(mode == UP)
	{
		for(int i = 0; i < 4; i++)
		{
			if(board[i][num] > biggest)
			{
				biggest = board[i][num];
				count++;
			}
		}
	}
	if(mode == DOWN)
	{
		for(int i = 3; i >= 0; i--)
		{
			if(board[i][num] > biggest)
			{
				biggest = board[i][num];
				count++;
			}
		}
	}
	if(mode == LEFT)
	{
		for(int i = 0; i < 4; i++)
		{
			if(board[num][i] > biggest)
			{
				biggest = board[num][i];
				count++;
			}
		}
	}
	if(mode == RIGHT)
	{
		for(int i = 3; i >= 0; i--)
		{
			if(board[num][i] > biggest)
			{
				biggest = board[num][i];
				count++;
			}
		}
	}
	return (count);
}

int	check_hint(int board[4][4], int *hint)
{
	int	i;

	for(i = 0; i < 4; i++)
	{
		if(count_buildings(board, UP, i) != hint[i])
			return(FALSE);
	}
	for(i = 0; i < 4; i++)
	{
		if(count_buildings(board, DOWN, i) != hint[i + 4])
			return(FALSE);
	}
	for(i = 0; i < 4; i++)
	{
		if(count_buildings(board, LEFT, i) != hint[i + 8])
			return(FALSE);
	}
	for(i = 0; i < 4; i++)
	{
		if(count_buildings(board, RIGHT, i) != hint[i + 12])
			return(FALSE);
	}
	return (TRUE);
}

void	show_board(int board[4][4])
{
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			printf("%d", board[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void	mk_board(int board[4][4], int *hint, int x, int y)
{
	if(y == 4)
	{
		if(check_hint(board, hint) == TRUE)
		{
			show_board(board);
		}
		return;
	}

	for(int num = 1; num <= 4; num++)
	{
		board[x][y] = num;
		if(is_valid(board) == TRUE)
		{
			if(x == 3)
				mk_board(board, hint, 0, y + 1);
			else
				mk_board(board, hint, x + 1, y);
		}
		board[x][y] = 0;
	}
}

int	main(int argc, char *argv[])
{
	int	board[4][4];
	int	*hint;
	int	count;
	int	hint_i;

	count = 0;
	hint_i = 0;
	if (argc != 2)
	{
		printf("ERROR\n");
		return (1);
	}
	for(int i = 0; argv[1][i] != '\0'; i++)
	{
		if(argv[1][i] >= '0' && argv[1][i] <= '9')
			count++;
	}
	hint = malloc(sizeof(int) * count);
	if(hint == NULL)
	{
		printf("ERROR\n");
		return (1);
	}
	for(int i = 0; argv[1][i] != '\0'; i++)
	{
		if(argv[1][i] >= '0' && argv[1][i] <= '9')
		{
			hint[hint_i] = argv[1][i] - '0';
			hint_i++;
		}
	}

	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
			board[i][j] = 0;
	}

	mk_board(board, hint, 0, 0);
	free(hint);
	return (0);
}
