#define ROWS 10
#define COLS 20
#define NUM_OISEAUX 4
#define MAX_TIME 15
extern clock_t lastMoveTime; // Déclaration de lastMoveTime en tant que variable externe
//head.h
#include "../fonctions/caracter.c"
#include "../fonctions/function.c"

void moveBall(Ball *ball);

void updateGameState(char gameBoard[ROWS][COLS], Snopy *snoopy, Ball *ball, Obstacle *obstacle, Oiseau oiseaux[NUM_OISEAUX],double elapsedTime);

void moveSnopy(Snopy *snoopy, char direction, char gameBoard[ROWS][COLS], Obstacle obstacle);
void displayGameBoard(char gameBoard[ROWS][COLS], double elapsedTime);
void placeElementOnBoard(char gameBoard[ROWS][COLS], Position pos, char symbol);

void initializeGameBoard(char gameBoard[ROWS][COLS]);

void showCursor();

void hideCursor();
void playGame(char gameBoard[ROWS][COLS],int x) ;
int isPositionValid(char gameBoard[ROWS][COLS], Position pos, Obstacle obstacle);