void hideCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void showCursor() {
    CONSOLE_CURSOR_INFO cursorInfo;
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    GetConsoleCursorInfo(consoleHandle, &cursorInfo);
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

int isPositionValid(char gameBoard[ROWS][COLS], Position pos, Obstacle obstacle) {
    return (pos.x >= 0 && pos.x < ROWS && pos.y >= 0 && pos.y < COLS && gameBoard[pos.x][pos.y] != obstacle.symbol);
}

void initializeGameBoard(char gameBoard[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            gameBoard[i][j] = ' ';
        }
    }
}

void placeElementOnBoard(char gameBoard[ROWS][COLS], Position pos, char symbol) {
    gameBoard[pos.x][pos.y] = symbol;
}

// void displayGameBoard(char gameBoard[ROWS][COLS]) {
//     hideCursor();
//     COORD cursorPos;  // Structure pour stocker la position du curseur
//     cursorPos.X = 0;
//     cursorPos.Y = 0;
//     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPos);
//     printf("|------------------------------------------------------------------------------|\n");
//     for (int i = 0; i < ROWS; i++) {
//         for (int j = 0; j < COLS; j++) {
//             printf("| %c ", gameBoard[i][j]);
//         }
//         printf("|\n");
//     }
//     printf("|------------------------------------------------------------------------------|\n");
//     // showCursor();
// }

void displayGameBoard(char gameBoard[ROWS][COLS], double elapsedTime) {
    hideCursor();
    COORD cursorPos;  // Structure pour stocker la position du curseur
    cursorPos.X = 0;
    cursorPos.Y = 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPos);
    printf("|-------------------------------------------------------------------------------|\n");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            printf("| %c ", gameBoard[i][j]);
        }
        printf("|");
        // Ajouter l'affichage du temps à côté de la matrice
        if (i == ROWS / 2) {
            printf(" Temps: %.1f secondes", elapsedTime);
        }
        printf("\n");
    }
    printf("|-------------------------------------------------------------------------------|\n");
    // showCursor();
}

// void moveSnopy(Snopy *snoopy, char direction) {
//     switch (direction) {
//         case 72:  // Haut
//             snoopy->pos.x = (snoopy->pos.x > 0) ? snoopy->pos.x - 1 : snoopy->pos.x;
//             break;
//         case 80:  // Bas
//             snoopy->pos.x = (snoopy->pos.x < ROWS - 1) ? snoopy->pos.x + 1 : snoopy->pos.x;
//             break;
//         case 75:  // Gauche
//             snoopy->pos.y = (snoopy->pos.y > 0) ? snoopy->pos.y - 1 : snoopy->pos.y;
//             break;
//         case 77:  // Droite
//             snoopy->pos.y = (snoopy->pos.y < COLS - 1) ? snoopy->pos.y + 1 : snoopy->pos.y;
//             break;
//         default:
//             printf("\n");
//     }
    
// }
void moveSnopy(Snopy *snoopy, char direction, char gameBoard[ROWS][COLS], Obstacle obstacle) {
    Position newPos = snoopy->pos;

    switch (direction) {
        case 72:  // Haut
            newPos.x = (snoopy->pos.x > 0) ? snoopy->pos.x - 1 : snoopy->pos.x;
            break;
        case 80:  // Bas
            newPos.x = (snoopy->pos.x < ROWS - 1) ? snoopy->pos.x + 1 : snoopy->pos.x;
            break;
        case 75:  // Gauche
            newPos.y = (snoopy->pos.y > 0) ? snoopy->pos.y - 1 : snoopy->pos.y;
            break;
        case 77:  // Droite
            newPos.y = (snoopy->pos.y < COLS - 1) ? snoopy->pos.y + 1 : snoopy->pos.y;
            break;
        default:
            printf("\n");
    }

    if (isPositionValid(gameBoard, newPos,obstacle)) {
    snoopy->pos = newPos;
}
}

void moveBall(Ball *ball) {
    // Mesurer le temps actuel
    clock_t currentTime = clock();

    // Vérifier si le délai minimum (en millisecondes) s'est écoulé depuis le dernier déplacement
    if ((currentTime - lastMoveTime) > 1000) {  // 100 millisecondes, ajustez selon votre préférence
        // Logique de déplacement de la balle (diagonale vers le bas et vers la droite)
        ball->pos.x = (ball->pos.x < ROWS - 1) ? ball->pos.x + 1 : 0;
        ball->pos.y = (ball->pos.y < COLS - 1) ? ball->pos.y + 1 : 0;

        // Mettre à jour le dernier temps de déplacement
        lastMoveTime = currentTime;
    }
}

void updateGameState(char gameBoard[ROWS][COLS], Snopy *snoopy, Ball *ball, Obstacle *obstacle, Oiseau oiseaux[NUM_OISEAUX],double elapsedTime) {
    // Effacer les anciennes positions
    placeElementOnBoard(gameBoard, snoopy->pos, ' ');
    placeElementOnBoard(gameBoard, ball->pos, ' ');
    placeElementOnBoard(gameBoard, obstacle->pos, ' ');
    // for (int i = 0; i < NUM_OISEAUX; ++i) {
    //     placeElementOnBoard(gameBoard, oiseaux[i].pos, ' ');
    // }
    // Mettre à jour les positions
    moveBall(ball);
    // moveObstacle(obstacle);
    // moveOiseau(oiseau);

    // Gérer les collisions
    if (snoopy->pos.x == ball->pos.x && snoopy->pos.y == ball->pos.y) {
        placeElementOnBoard(gameBoard, ball->pos, ball->symbol);
        displayGameBoard(gameBoard,elapsedTime);
        printf("\nSnoopy a touché la balle! Le jeu est terminé.\n");
        exit(0); // ou utilisez un autre moyen pour quitter le jeu
    }
    // Afficher les nouvelles positions
    placeElementOnBoard(gameBoard, snoopy->pos, snoopy->symbol);
    placeElementOnBoard(gameBoard, ball->pos, ball->symbol);
    placeElementOnBoard(gameBoard, obstacle->pos, obstacle->symbol);
    for (int i = 0; i < NUM_OISEAUX; ++i) {
        if (oiseaux[i].pos.x != -1 && oiseaux[i].pos.y != -1) {
            placeElementOnBoard(gameBoard, oiseaux[i].pos, oiseaux[i].symbol);
        }
    }
    displayGameBoard(gameBoard,elapsedTime);
    
}

void saveGame(char gameBoard[ROWS][COLS]) {
    FILE *file = fopen("saved_game.bin", "wb");

    if (file != NULL) {
        fwrite(gameBoard, sizeof(char), ROWS * COLS, file);
        fclose(file);
        printf("La partie a été sauvegardée avec succès.\n");
    } else {
        printf("Erreur lors de l'ouverture du fichier pour sauvegarde.\n");
    }
}

void loadGame(char gameBoard[ROWS][COLS]) {
    FILE *file = fopen("saved_game.bin", "rb");

    if (file != NULL) {
        fread(gameBoard, sizeof(char), ROWS * COLS, file);
        fclose(file);
        printf("La partie a été chargée avec succès.\n");
    } else {
        printf("Erreur lors de l'ouverture du fichier pour chargement.\n");
    }
}

void playGame(char gameBoard[ROWS][COLS],int maxGameTime) {
    int oiseauxCaptured = 0;
    double score = 0;
    Snopy snoopy = {{1, 1}, 0x2};
    Ball ball = {{3, 3}, 0xB};
    Obstacle obstacle = {{5, 5}, 0xF};
    Oiseau oiseaux[NUM_OISEAUX] = {
        {{0, 0}, 0xE},
        {{0, COLS - 1}, 0xE},
        {{ROWS - 1, 0}, 0xE},
        {{ROWS - 1, COLS - 1}, 0xE}
    };
    clock_t startTime = clock();
    initializeGameBoard(gameBoard);

    while (1) {
        clock_t currentTime = clock();
        double elapsedTime = ((double)(currentTime - startTime)) / CLOCKS_PER_SEC;
        updateGameState(gameBoard, &snoopy, &ball, &obstacle,oiseaux,elapsedTime);
        printf("Déplacez Snoopy (↑ pour haut, ↓ pour bas, ← pour gauche, → pour droite): \n");
        for (int i = 0; i < NUM_OISEAUX; ++i) {
            if (snoopy.pos.x == oiseaux[i].pos.x && snoopy.pos.y == oiseaux[i].pos.y) {
                oiseauxCaptured++;
                oiseaux[i].pos.x = -1;  // Marquer l'oiseau comme capturé
                oiseaux[i].pos.y = -1;             
                break;
            }
        }

        if (oiseauxCaptured == NUM_OISEAUX) {
            placeElementOnBoard(gameBoard, snoopy.pos,snoopy.symbol);
            displayGameBoard(gameBoard,elapsedTime);
            printf("\n\nFélicitations, Snoopy a récupéré tous les oiseaux!\n");
            printf("vous aver teriner le jeux en: %.lf seconds\n",elapsedTime);
            printf("Votre Score est de : %.lf\n",score);
            break;
        }
            if (elapsedTime >= maxGameTime) {
                // system('cls');
                printf("\nTemps écoulé. Le jeu est terminé.\n");
                break;
        }
        score = (maxGameTime - elapsedTime) * 100;
        if (kbhit()) {
            char direction = _getch();
            if (direction == 'q' || direction == 'Q') {
                printf("\nVous avez quitté le jeu.\n");
                break;
            }
            else if (direction == 's' || direction == 'S') {
                // Sauvegarder la partie
                saveGame(gameBoard);
                printf("\nLa partie a été sauvegardée.\n");
                break;
            }
            placeElementOnBoard(gameBoard, snoopy.pos, ' ');
            moveSnopy(&snoopy, direction, gameBoard,obstacle);
        }
        displayGameBoard(gameBoard, elapsedTime);
    }
}

void Menu() {
    hideCursor();
    printf("Bienvenue dans le jeu Snoupy!\n");
    printf("1. Règles du jeu\n");
    printf("2. Lancer niveau\n");
    printf("3. Charger une partie\n");
    printf("4. Quitter\n");
}
void displayRules() {
    system("cls");  // Efface l'écran pour afficher les règles
    printf("=== Règles du Jeu ===\n\n");
    printf("Objectif :\n");
    printf("Le but du jeu est de guider Snoopy pour capturer tous les oiseaux avant que le temps ne s'écoule.\n\n");

    printf("Déplacements :\n");
    printf("Utilisez les touches fléchées pour déplacer Snoopy :\n");
    printf("↑ : Déplacer vers le haut\n");
    printf("↓ : Déplacer vers le bas\n");
    printf("← : Déplacer vers la gauche\n");
    printf("→ : Déplacer vers la droite\n\n");

    printf("Éléments du Jeu :\n");
    printf("1. Snoopy :\n");
    printf("   - Représenté par le symbole 0x2.\n");
    printf("   - Déplacez Snoopy pour capturer les oiseaux.\n\n");

    printf("2. Oiseaux :\n");
    printf("   - Représentés par le symbole 0xE.\n");
    printf("   - Capturez tous les oiseaux pour gagner.\n\n");

    printf("3. Balle :\n");
    printf("   - Représentée par le symbole 0xB.\n");
    printf("   - Évitez la balle, une collision met fin au jeu.\n\n");

    printf("4. Obstacle :\n");
    printf("   - Représenté par le symbole 0xF.\n");
    printf("   - Évitez l'obstacle en le contournant.\n\n");

    printf("Gestion du Temps :\n");
    printf("Le jeu a une limite de temps. Capturez tous les oiseaux avant que le temps ne s'écoule.\n\n");

    printf("Fin du Jeu :\n");
    printf("Le jeu se termine si :\n");
    printf("- Snoopy capture tous les oiseaux avant la fin du temps (victoire).\n");
    printf("- Snoopy entre en collision avec la balle (défaite).\n");
    printf("- Le temps imparti est écoulé (défaite).\n\n");

    printf("Appuyez sur n'importe quelle touche pour retourner au menu...\n");
    getch();  // Attend une touche pour continuer
    system("cls");  // Efface l'écran pour revenir au menu
}
