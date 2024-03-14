#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

typedef struct
{
    char name[13];
    char side;
} Player;

void EnterPlayerData(Player* p1)
{
    printf("\nHello, Player! Please enter your data.\n");
    printf("\nName: ");
    scanf("%s", p1->name);
    while (true)
    {
        printf("Side (x or o): ");
        scanf(" %c", &p1->side);
        if (p1->side == 'x' || p1->side == 'o')
            break;
        printf("Invalid side! Please choose again!\n");
    }
}

void ShowGrid(char grid[3][3])
{
    printf("\n");
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
        if ((grid[i][0] == grid[i][1] && grid[i][0] == grid[i][2] && grid[i][0] == side) || // Rows
            (grid[0][i] == grid[1][i] && grid[0][i] == grid[2][i] && grid[0][i] == side))   // Columns
        {
            return true;
        }
    }
    // Diagonals
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

void MakeMove(char grid[3][3], char side)
{
    srand(time(NULL));
    int row, col;
    do
    {
        row = rand() % 3;
        col = rand() % 3;
    } while (grid[row][col] != ' ');
    grid[row][col] = side;
}

void GameAgainstComputer(Player p1)
{
    char grid[3][3] = { {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '} };
    int moves = 9;

    Player computer;
    strcpy(computer.name, "Computer");
    computer.side = (p1.side == 'x') ? 'o' : 'x';

    while (moves != 0)
    {
        ShowGrid(grid);
        printf("%s's turn. Choose a position (row column): ", (moves % 2 == 1) ? p1.name : "Computer");
        int choiceR, choiceC;
        if (moves % 2 == 1)
        {
            scanf("%d %d", &choiceR, &choiceC);
            if (choiceR < 0 || choiceR >= 3 || choiceC < 0 || choiceC >= 3 || grid[choiceR][choiceC] != ' ')
            {
                printf("Invalid input or spot already taken! Please choose again.\n");
                continue;
            }
            grid[choiceR][choiceC] = p1.side;
        }
        else
        {
            MakeMove(grid, computer.side);
        }

        if (Win(grid, (moves % 2 == 1) ? p1.side : computer.side))
        {
            ShowGrid(grid);
            printf("%s WON! CONGRATULATIONS!!! :D\n", (moves % 2 == 1) ? p1.name : "Computer");
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

void GameAgainstPlayer(Player p1, Player p2)
{
    char grid[3][3] = { {' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '} };
    int moves = 9;

    while (moves != 0)
    {
        ShowGrid(grid);
        printf("%s's turn. Choose a position (row column): ", (moves % 2 == 1) ? p1.name : p2.name);
        printf("\n");
        int choiceR, choiceC;
        scanf("%d %d", &choiceR, &choiceC);
        if (choiceR < 0 || choiceR >= 3 || choiceC < 0 || choiceC >= 3 || grid[choiceR][choiceC] != ' ')
        {
            printf("Invalid input or spot already taken! Please choose again.\n");
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

void ShowPositionsOnBoard()
{
    printf("\n\nThis is your board:\n\n");
    printf(" %s | %s | %s ", "0 0", "0 1", "0 2");
    printf("\n-----|-----|-----\n");
    printf(" %s | %s | %s ", "1 0", "1 1", "1 2");
    printf("\n-----|-----|-----\n");
    printf(" %s | %s | %s ", "2 0", "2 1", "2 2");
    printf("\n\n");
}

int main()
{
    printf("\n --- Welcome to TIC-TAC-TOE! --- \n\n");

    int choice;
    printf("Choose game mode:\n");
    printf("1. Single Player\n");
    printf("2. Two Players\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1)
    {
        Player p1;
        EnterPlayerData(&p1);
        ShowPositionsOnBoard();
        GameAgainstComputer(p1);
    }
    else if (choice == 2)
    {
        Player p1, p2;
        EnterPlayerData(&p1);
        ShowPositionsOnBoard();
        EnterPlayerData(&p2);
        GameAgainstPlayer(p1, p2);
    }
    else
    {
        printf("Invalid choice!\n");
    }

    printf("Thank you for playing Tic-Tac-Toe!\n");
    return 0;
}
