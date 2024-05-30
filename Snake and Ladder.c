#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BOARD_SIZE 100
#define MAX_PLAYERS 4

typedef struct {
    char name[50];
    int position;
} Player;

void initializeGame(Player players[], int numPlayers, int snakes[], int ladders[]);
int rollDice();
void movePlayer(Player *player, int diceRoll, int snakes[], int ladders[]);
int checkSnakesAndLadders(int position, int snakes[], int ladders[]);
int checkWin(Player *player);

int main() {
    int numPlayers;
    Player players[MAX_PLAYERS];
    int snakes[BOARD_SIZE + 1] = {0};
    int ladders[BOARD_SIZE + 1] = {0};

    srand(time(0));

    printf("Enter the number of players (2-4): ");
    scanf("%d", &numPlayers);
    getchar(); // Consume newline character

    if(numPlayers < 2 || numPlayers > 4) {
        printf("Invalid number of players. Exiting...\n");
        return 1;
    }

    initializeGame(players, numPlayers, snakes, ladders);

    int currentPlayer = 0;
    while(1) {
        printf("\n%s's turn. Press Enter to roll the dice...", players[currentPlayer].name);
        getchar();
        int diceRoll = rollDice();
        printf("%s rolled a %d\n", players[currentPlayer].name, diceRoll);
        movePlayer(&players[currentPlayer], diceRoll, snakes, ladders);

        if(checkWin(&players[currentPlayer])) {
            printf("%s wins the game!\n", players[currentPlayer].name);
            break;
        }

        currentPlayer = (currentPlayer + 1) % numPlayers;
    }

    return 0;
}

void initializeGame(Player players[], int numPlayers, int snakes[], int ladders[]) {
    // Initialize players
    for(int i = 0; i < numPlayers; i++) {
        printf("Enter name for player %d: ", i + 1);
        fgets(players[i].name, sizeof(players[i].name), stdin);
        players[i].name[strcspn(players[i].name, "\n")] = '\0'; // Remove newline character
        players[i].position = 1;
    }

    // Initialize snakes
    snakes[17] = 7;
    snakes[54] = 34;
    snakes[62] = 19;
    snakes[64] = 60;
    snakes[87] = 36;
    snakes[93] = 73;
    snakes[95] = 75;
    snakes[98] = 79;

    // Initialize ladders
    ladders[1] = 38;
    ladders[4] = 14;
    ladders[9] = 31;
    ladders[21] = 42;
    ladders[28] = 84;
    ladders[51] = 67;
    ladders[72] = 91;
    ladders[80] = 99;
}

int rollDice() {
    return (rand() % 6) + 1;
}

void movePlayer(Player *player, int diceRoll, int snakes[], int ladders[]) {
    player->position += diceRoll;

    if(player->position > BOARD_SIZE) {
        player->position = BOARD_SIZE - (player->position - BOARD_SIZE);
    }

    int newPosition = checkSnakesAndLadders(player->position, snakes, ladders);
    if(newPosition != player->position) {
        printf("%s hit a %s and moved from %d to %d\n",
               player->name,
               newPosition > player->position ? "ladder" : "snake",
               player->position,
               newPosition);
        player->position = newPosition;
    }

    printf("%s is now at position %d\n", player->name, player->position);
}

int checkSnakesAndLadders(int position, int snakes[], int ladders[]) {
    if(snakes[position] != 0) {
        return snakes[position];
    }
    if(ladders[position] != 0) {
        return ladders[position];
    }
    return position;
}

int checkWin(Player *player) {
    return player->position == BOARD_SIZE;
}
