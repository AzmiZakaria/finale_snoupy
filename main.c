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
    int choix;
    do {
        Menu();
        printf("Choisissez une option (1-4): ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                displayRules();
                break;
            case 2:
                // Lancer le niveau
                playGame(gameBoard, MAX_TIME);
                break;
            case 3:
                // Charger une partie
                // Ajoutez ici le code pour charger une partie
                loadGame(gameBoard);
                break;
            case 4:
                // Quitter
                printf("Merci d'avoir joué! Au revoir.\n");
                break;
            default:
                printf("Option invalide. Veuillez choisir une option valide.\n");
        }

    }while (choix != 4);

    return 0;
}