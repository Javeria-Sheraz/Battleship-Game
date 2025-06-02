/*====================================================================================================
 | Filename: battleShip.c
 | Written by: Javeria Sheraz
 | Project title: The Battle Ship Game
 | Date: May 14, 2025
 | Lines of code: 632
 ========================================================================================================*/

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

void rules();
void displayboard(char board[8][8], int isOpponent);
void initializeBoard(char board[8][8]);
void loadingAnimation();
void start_game();
void playerShipPlacement(char board[8][8]);
int isValidPlacement(char board[8][8], int row, int col, int length, int vertical);
void placeShip(char board[8][8], int row, int col, int length, int vertical, char symbol);
int computerShipPlacement(char board[8][8], const char *filename);
void playGame(char playerBoard[8][8], char computerBoard[8][8]);
int playerAttack(char computerBoard[8][8]);
void computerAttack(char playerBoard[8][8]);
int checkGameOver(char board[8][8]);

// DECLARING STRUCTURES
typedef struct
{
    char symbol;
    int length;
    char name[30];
    char shipColour[20];
} GameShips;

typedef struct
{
    char symbol;
    const char *colour;
} DisplaySymbol;

// DEFINING STRUCTURES
DisplaySymbol hitSymbol = {'X', "\033[1;31m"};
DisplaySymbol missSymbol = {' ', ""};
DisplaySymbol waterSymbol = {'~', "\033[0;36m"};

// Structure to define array of ship details
GameShips ships[7] = {
    {'C', 5, "Carrier", "\033[1;32m"},
    {'T', 4, "Tank", "\033[1;33m"},
    {'B', 4, "Battleship", "\033[1;34m"},
    {'R', 3, "Cruiser", "\033[1;35m"},
    {'S', 3, "Submarine", "\033[1;33m"},
    {'D', 2, "Destroyer", "\033[1;37m"},
    {'A', 2, "Boat", "\033[1;32m"}};

// MAIN FUNCTION
int main()
{
    char initialBoard[8][8];
    system("cls");

    printf("--------------------------  WELCOME TO THE  ------------------------\n");
    system("color 03");
    printf("#####   ####  ###### ###### ##     ######     ##### ##  ##  ##  ####\n");
    printf("##  ## ##  ##   ##     ##   ##     ##        ##     ##  ##  ##  ##  ##\n");
    printf("#####  ##  ##   ##     ##   ##     ####       ####  ######  ##  ####\n");
    printf("##  ## ######   ##     ##   ##     ##            ## ##  ##  ##  ##\n");
    printf("#####  ##  ##   ##     ##   ###### ######    #####  ##  ##  ##  ##\n\n");

    Sleep(2000);
    system("cls");

    int num;
    while (1)
    {
        system("color 04");
        printf("Please choose from the following\n");
        printf("1) Play Battleship\n");
        printf("2) Print Game Rules\n");
        printf("3) Exit The Game\n\n");
        printf("Enter your choice: ");
        scanf("%d", &num);

        switch (num)
        {
        case 1:
            printf("\nStarting the game...\n\n");
            loadingAnimation();
            start_game();
            return 0;
        case 2:
            system("cls");
            rules();

            int nextChoice;
            while (1)
            {
                printf("Enter 1 to PLAY or 3 to EXIT: ");
                scanf("%d", &nextChoice);
                if (nextChoice == 1)
                {
                    printf("\nStarting the game...\n\n");
                    loadingAnimation();
                    system("cls");
                    system("color 07");
                    start_game();
                    return 0;
                }
                else if (nextChoice == 3)
                {
                    printf("\nExiting the game!\n");
                    exit(0);
                }
                else
                {
                    printf("Choose valid option:\n");
                }
            }
            break;
        case 3:
            printf("\nExiting the game!\n");
            exit(0);

        default:
            printf("Choose valid option!");
        }
    }

    initializeBoard(initialBoard);
    return 0;
}

// FUNCTIONS
//  FUNCTION THAT DISPLAYS RULES OF THE GAME WHEN CASE 2 IS SELECTED IN MAIN
void rules()
{
    char rules[500] = {" 1. This is a two player game.\n 2. Player 1 is you and Player 2 is the computer.\n 3. You and the computer will position ships on separate 8x8 grids.\n 4. Ship types (placed from longest to shortest):\n    [C] Carrier has 5 cells, [B] Battleship has 4 cells, [T] Tank has 4 cells,\n    [R] Cruiser has 3 cells, [S] Submarine has 3 cells,\n    [D] Destroyer has 2 cells, [A] Boat has 2 cells\n 5. Take turns guessing ship locations on the enemy grid.\n    [X] = Hit, [ ] = Miss.\n\n"};
    char instructions[500] = {" 1. Place your ships on your grid.\n 2. Attack the enemy grid by entering row and column coordinates.\n 3. The game will tell you if it was a hit or miss.\n 4. Destroy all enemy ships to win!\n\n"};
    Sleep(1000);
    system("color 06");
    printf("\nRULES OF THE GAME:\n");
    Sleep(400);
    for (int i = 0; rules[i] != '\0'; i++)
    {
        printf("%c", rules[i]);
        Sleep(20);
    }
    printf("\nHOW TO PLAY:\n");
    Sleep(400);
    for (int i = 0; instructions[i] != '\0'; i++)
    {
        printf("%c", instructions[i]);
        Sleep(20);
    }
}

// FUNCTION TO DISPLAY DOTS ANIMATION IN THE CODE
void loadingAnimation()
{
    printf("Loading game");
    for (int i = 0; i < 3; i++)
    {
        Sleep(600);
        printf(".");
    }
    printf("\n");
    Sleep(600);
    system("cls");
}

// FUNCTION THAT DISPLAYS BOARD OF BOTH PLAYERS
//  1 is passed for opponent's board and 0 for the players board
void displayBoard(char board[8][8], int isOpponent)
{
    int row, col;
    printf("     ");
    for (col = 0; col < 8; col++)
    {
        printf(" %d  ", col);
    }
    printf("\n");

    for (row = 0; row < 8; row++)
    {
        printf(" %2d   ", row);
        for (col = 0; col < 8; col++)
        {
            // if it is opponents board, function shows only water, hits amd misses
            if (isOpponent == 1)
            {
                if (board[row][col] == hitSymbol.symbol)
                {
                    printf("%s%c   \033[0m", hitSymbol.colour, hitSymbol.symbol);
                }
                else if (board[row][col] == missSymbol.symbol)
                {
                    printf(" %c  ", missSymbol.symbol);
                }
                else
                {
                    printf("%s%c   \033[0m", waterSymbol.colour, waterSymbol.symbol);
                }
            }
            else
            {
                // Check if cell matches any ship symbol to print a character there
                int matchFound = 0;
                for (int i = 0; i < 7; i++)
                {
                    if (board[row][col] == ships[i].symbol)
                    {
                        printf("%s%c   \033[0m", ships[i].shipColour, board[row][col]);
                        matchFound = 1;
                        break;
                    }
                    if (board[row][col] == hitSymbol.symbol)
                    {
                        printf("%s%c   \033[0m", hitSymbol.colour, board[row][col]);
                        matchFound = 1;
                        break;
                    }
                }
                if (matchFound == 0)
                {
                    printf("%s%c   \033[0m", waterSymbol.colour, board[row][col]);
                }
            }
        }
        printf("\n");
    }
}

// FUNCTION TO INTIALIZE PLAYER BOARDS WITH WATER
void initializeBoard(char board[8][8])
{
    // initializing the board here (with water symbols)
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
            board[r][c] = waterSymbol.symbol;
}

// FUNCTION THAT STARTS THE GAME WHEN USER ENTERS 1 IN THE MAIN
void start_game()
{
    char playerBoard[8][8], computerBoard[8][8];
    initializeBoard(playerBoard);

    system("color 03");

    printf("\nTotal ships to place: 7\n\n");
    for (int i = 0; i < 7; i++)
    {
        printf("Ship %d: %s [%c]\n", i + 1, ships[i].name, ships[i].symbol);
    }

    Sleep(2000);
    system("cls");
    system("color 07");

    displayBoard(playerBoard, 0); // displaying empty board
    printf("\nPlease place your ships...\n");
    playerShipPlacement(playerBoard);

    initializeBoard(computerBoard);
    printf("\n=====================================================\n");
    printf("Computer is placing its ships");
    for (int i = 0; i < 3; i++)
    {
        Sleep(500);
        printf(".");
    }
    Sleep(600);
    printf("\n");
    if (computerShipPlacement(computerBoard, "comp_placements.txt"))
    {
        printf("Computer has placed its ships!\n");
    }
    printf("======================================================\n");
    Sleep(1500);

    system("cls");
    system("color 03");
    printf("\n\t______       _   _   _           _     _       \n");
    printf("\t| ___ \\     | | | | | |         | |   (_)      \n");
    printf("\t| |_/ / __ _| |_| |_| | ___  ___| |__  _ _ __  \n");
    printf("\t| ___ \\/ _` | __| __| |/ _ \\/ __| '_ \\| | '_ \\ \n");
    printf("\t| |_/ / (_| | |_| |_| |  __/\\__ \\ | | | | |_) |\n");
    printf("\t\\____/ \\__,_|\\__|\\__|_|\\___||___/_| |_|_| .__/ \n");
    printf("\t                                        | |    \n");
    printf("\t                                        |_|    \n");
    Sleep(1500);
    printf("\t\t\t           BEGINS\n");
    Sleep(1550);
    printf("\t\t\t\t           NOW");
    for (int i = 0; i < 3; i++)
    {
        Sleep(600);
        printf(".");
    }
    printf("\n");
    Sleep(1000);
    printf("\t\t\t\n    BEST OF LUCK!!! \n");
    Sleep(1100);
    system("cls");
    system("color 07");

    playGame(playerBoard, computerBoard);
}

void playerShipPlacement(char board[8][8])
{
    int row, col, vertical;
    char dir;

    for (int s = 0; s < 7; s++)
    {
        while (1)
        {
            Sleep(2000);
            printf("\nPress enter key after each input!\n");
            printf("\nPlace your %s [%c] (length: %d):\n", ships[s].name, ships[s].symbol, ships[s].length);

            printf("Enter starting row (0-7): ");
            scanf("%d", &row);
            if (row < 0 || row > 7)
            {
                printf("Invalid row. Choose between 0-7.\n");
                continue;
            }
            printf("Enter starting column (0-7): ");
            scanf("%d", &col);
            if (col < 0 || col > 7)
            {
                printf("Invalid column. Choose between 0-7.\n");
                continue;
            }
            printf("Enter direction (H for horizontal, V for vertical placement): ");
            scanf(" %c", &dir);
            if (dir == 'v' || dir == 'V')
            {
                vertical = 1;
            }
            else if (dir == 'h' || dir == 'H')
            {
                vertical = 0;
            }
            else
            {
                printf("Invalid direction. Use 'H' or 'V'.\n");
                continue;
            }

            if (isValidPlacement(board, row, col, ships[s].length, vertical))
            {
                placeShip(board, row, col, ships[s].length, vertical, ships[s].symbol);
                system("cls");
                displayBoard(board, 0); // after each ship is placed
                break;
            }
            else
            {
                printf("Invalid placement. Try again.\n");
            }
        }
    }
}

// FUNCTION THAT VERIFIES IF A CERTAIN SHIP PLACEMENT STAYS WITHIN THE BOARD'S BOUNDARIES
int isValidPlacement(char board[8][8], int row, int col, int ShipLength, int vertical)
{
    // if ship is vertical, checks make sure it doesnt go the bottom of board
    if (vertical == 1)
    {
        if (row + ShipLength > 8)
            return 0;
        for (int i = 0; i < ShipLength; i++)
        {
            if (board[row + i][col] != waterSymbol.symbol) // if any cell is not water, return 0
                return 0;                                  // col remains same, row changes
        }
    }
    else
    { // if ship is horizontal, checks to make sure it doesnt exceed the right boundary
        if (col + ShipLength > 8)
            return 0;
        for (int i = 0; i < ShipLength; i++)
        {
            if (board[row][col + i] != waterSymbol.symbol)
                return 0;
        }
    }
    return 1;
}

// FUNCTION THAT PLACES THE SHIP ON THE BOARD AFTER VALIDATING ITS PLACEMENT
void placeShip(char board[8][8], int row, int col, int ShipLength, int vertical, char symbol)
{
    for (int i = 0; i < ShipLength; i++)
    {
        if (vertical == 1)
        {
            board[row + i][col] = symbol;
        }
        else
        {
            board[row][col + i] = symbol;
        }
    }
}

// FUNCTION THAT READS A THE TEXT FILE AND PLACES SHIPS ON THE COMPUTER'S BOARD
int computerShipPlacement(char board[8][8], const char *filename)
{
    FILE *fp;
    char buff[100];

    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return 0;
    }

    // Intializing to available number options for computer ship placement in the file
    // Each option is available in a block of five line seperated by an empty line
    int blocksInFile = 6;
    int currentBlock = 0, chosenBlock;

    srand(time(NULL));
    chosenBlock = rand() % blocksInFile;

    while (currentBlock < chosenBlock)
    {
        // fgets reads each line from the file and increases block count if it finds an empty line
        // loop runs till it reaches theclea
        if (fgets(buff, sizeof(buff), (FILE *)fp) && buff[0] == '\n')
            currentBlock++;
    }
    // file pointer fp is moved to the required block of code using this while loop

    // Make sure all four inputs are read from each line of the chosen block
    char symbol, dir;
    int row, column, vertical;
    for (int i = 0; i < 7; i++)
    {
        if (fscanf(fp, " %c %d %d %c\n", &symbol, &row, &column, &dir) != 4)
        {
            printf("Invalid format in file\n");
            fclose(fp);
            return 0;
        }

        if (dir == 'V' || dir == 'v')
        {
            vertical = 1;
        }
        else
        {
            vertical = 0;
        }

        // Extract ship length from symbol read from file using the 'ships' array
        int length = 0;
        for (int t = 0; t < 7; t++)
        {
            if (ships[t].symbol == symbol)
            {
                length = ships[t].length;
                break;
            }
        }

        // Now check validplacement for each ship and place it
        if (!isValidPlacement(board, row, column, length, vertical))
        {
            printf("Invalid placement for ship %c.\nExiting.\n", symbol);
            printf("Start the game again.\n ");
            printf("=====================================================\n");
            fclose(fp);
            exit(0);
        }
        else
        {
            placeShip(board, row, column, length, vertical, symbol);
        }
    }
    fclose(fp);
    return 1;
}

// FUNCTION THAT SWITCHES TURNS BETWEEN THE PLAYER AND COMPUTER DURING THE GAME
void playGame(char playerBoard[8][8], char computerBoard[8][8])
{
    int playerTurn = 1; // 1 for player's turn, 0 for computer's turn
    int gameOver = 0;   // used to stop the loop if someone wins
    int result;

    while (!gameOver)
    {
        if (playerTurn)
        {
            Sleep(1650);
            printf("\nYOUR TURN:\n");
            printf("\t\tComputer's Board:\n");
            displayBoard(computerBoard, 1); // Displays opponent's board (all water except hits/misses)

            if (playerAttack(computerBoard))
            {
                result = 1;
            }
            else
            {
                result = 0;
            }

            // Check if player one won or the turn goes to the computer
            if (checkGameOver(computerBoard))
            {
                printf("Congratulations! You sunk all the opponent's ships!\n");
                gameOver = 1;
            }
            else
            {
                playerTurn = 0; // switching turns
            }
        }
        else
        {
            Sleep(1650);
            system("cls");
            printf("\nCOMPUTER'S TURN:\n");

            computerAttack(playerBoard);

            if (checkGameOver(playerBoard))
            {
                printf("Oh no! The computer sunk all your ships!\n");
                gameOver = 1;
            }
            else
            {
                playerTurn = 1; // Switch to player's turn
            }
        }
    }
}

// FUNCTION THAT HANDLES THE ATTACK OF PLAYER ON COMPUTER'S BOARD
int playerAttack(char computerBoard[8][8])
{
    int row, col;
    while (1)
    {
        printf("Enter attack coordinates (row column): ");
        scanf("%d %d", &row, &col);

        if (row < 0 || row > 7 || col < 0 || col > 7)
        {
            printf("Invalid coordinates. Try again.\n");
            continue;
        }
        if (computerBoard[row][col] == hitSymbol.symbol || computerBoard[row][col] == missSymbol.symbol)
        {
            printf("You've already attacked this location. Try again.\n");
            continue;
        }
        break;
    }

    // returns 1 when player hits and 0 when he misses
    if (computerBoard[row][col] != waterSymbol.symbol)
    {
        printf("You hit a ship!\n");
        computerBoard[row][col] = hitSymbol.symbol;
        return 1;
    }
    else
    {
        printf("You missed!\n");
        computerBoard[row][col] = missSymbol.symbol;
        return 0;
    }
}

// FUNCTION THAT HANDLES THE ATTACK OF COMPUTER'S ON PLAYERS BOARD
void computerAttack(char playerBoard[8][8])
{
    int row, col;
    // Computer picks random coordinates until it finds a spot not already attacked
    do
    {
        row = rand() % 8;
        col = rand() % 8;
    } while (playerBoard[row][col] == hitSymbol.symbol || playerBoard[row][col] == missSymbol.symbol);

    printf("\n***************************************\n");
    printf("Computer attacks at (%d, %d)\n", row, col);
    Sleep(1500);
    if (playerBoard[row][col] != waterSymbol.symbol)
    {
        printf("Computer hit your ship!\n");
        playerBoard[row][col] = hitSymbol.symbol;
    }
    else
    {
        printf("Computer missed!\n");
        playerBoard[row][col] = missSymbol.symbol;
    }
    printf("***************************************\n\n");
    Sleep(1330);
    printf("\tYour Board (after computer's attack):\n");
    displayBoard(playerBoard, 0); // Show player's board with hits and misses
}

// FUNCTION THAT CHECK OF GAME OVER WHEN ALL THE SHIPS ARE SUNK
int checkGameOver(char board[8][8])
{
    for (int s = 0; s < 7; s++)
    {
        // checks every cell for the ship present
        for (int r = 0; r < 8; r++)
            for (int c = 0; c < 8; c++)
                if (board[c][r] == ships[s].symbol)
                {
                    return 0; // exit it ship is found
                }
    }
    // when no ship is found on the board
    return 1;
}
