#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include "./header/head.h"
#define ROWS 10
#define COLS 20
#define NUM_OISEAUX 4
#define MAX_TIME 15

clock_t lastMoveTime = 0;

int kbhit(void) {
    return _kbhit();
}

int main() {
    char gameBoard[ROWS][COLS];
    playGame(gameBoard,MAX_TIME);
    return 0;
}