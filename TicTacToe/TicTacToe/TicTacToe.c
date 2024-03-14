#include <stdio.h>
#include <stdbool.h>

typedef struct
{
	char name[13];
	char side;
} player;

void EnterPlayerData(player* p1, player* p2)
{
	printf("\nHello, Player 1! Please enter your data.\n");
	printf("\nName: ");
	scanf("%s", p1->name);
	while (true)
	{
		printf("Side (x OR o): ");
		scanf(" %c", &p1->side);
		if (p1->side == 'x' || p1->side == 'o')
			break;
		printf("Invalid side! Please choose again!\n");
	}

	printf("\nHello, Player 2! Please enter your data.\n");
	printf("\nName: ");
	scanf("%s", p2->name);
	p2->side = (p1->side == 'x') ? 'o' : 'x';
}

void ShowGrid(char grid[3][3])
{
	printf(" %c | %c | %c ", grid[0][0], grid[0][1], grid[0][2]);
	printf("\n---|---|---\n");
	printf(" %c | %c | %c ", grid[1][0], grid[1][1], grid[1][2]);
	printf("\n---|---|---\n");
	printf(" %c | %c | %c ", grid[2][0], grid[2][1], grid[2][2]);
	printf("\n");
}

bool Win(char grid[3][3], char side)
{
	for (int i = 0; i < 3; i++)
	{
		if ((grid[i][0] == grid[i][1] && grid[i][0] == grid[i][2] && grid[i][0] == side) ||  //rows
			(grid[0][i] == grid[1][i] && grid[0][i] == grid[2][i] && grid[0][i] == side))    //columns
		{
			return true;
		}
	}
	//diagonals
	if ((grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2] && grid[1][1] == side) ||
		(grid[0][2] == grid[1][1] && grid[2][0] == grid[1][1] && grid[1][1] == side))
	{
		return true;
	}
	return false;
}

int FullGrid(char grid[3][3])
{
	int full = 9;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (grid[i][j] != ' ')
			{
				full--;
			}
		}
	}
	return full;
}

void Game(player p1, player p2)
{
	char grid[3][3] = { {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '} };
	int moves = 9;

	while (moves != 0)
	{
		ShowGrid(grid);
		printf("%s's turn. Choose a position (row column): ", (moves % 2 == 1) ? p1.name : p2.name);
		int choiceR, choiceC;
		if (scanf("%d %d", &choiceR, &choiceC) != 2 || choiceR < 0 || choiceR > 2 || choiceC < 0 || choiceC > 2 || grid[choiceR][choiceC] != ' ')
		{
			printf("Invalid input or spot already taken! Please choose again.\n");
			while (getchar() != '\n');
			continue;
		}
		grid[choiceR][choiceC] = (moves % 2 == 1) ? p1.side : p2.side;
		if (Win(grid, (moves % 2 == 1) ? p1.side : p2.side))
		{
			ShowGrid(grid);
			printf("%s WON! CONGRATULATIONS!!! :D\n", (moves % 2 == 1) ? p1.name : p2.name);
			return;
		}
		else if (FullGrid(grid) == 0)
		{
			ShowGrid(grid);
			printf("IT'S A DRAW! Please restart the game to try again!\n");
			return;
		}
		moves--;
	}
}

int main()
{
	printf("\n --- Welcome to TIC-TAC-TOE! --- \n\n");
	player p1, p2;
	EnterPlayerData(&p1, &p2);
	printf("\n\nThis is your board:\n\n");
	printf(" %s | %s | %s ", "0 0", "0 1", "0 2");
	printf("\n-----|-----|-----\n");
	printf(" %s | %s | %s ", "1 0", "1 1", "1 2");
	printf("\n-----|-----|-----\n");
	printf(" %s | %s | %s ", "2 0", "2 1", "2 2");
	printf("\n\n");

	Game(p1, p2);
	printf("Thank you for playing Tic-Tac-Toe!\n");
	return 0;
}
