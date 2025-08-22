#include <stdio.h>
#include <stdlib.h>
#include "game_puissance_4.c"
#include <time.h>
#include <stdlib.h>
#include <assert.h>

//Fichier main qui doit lancer le jeu en question

int main(void){
    game_t game = game_default();
    //game_t game = game_default_solution_win_and_full();
    assert(game);
    assert(game->J1);
    assert(game->J2);
    srand(time(NULL));
    if (rand() % 2 == 0) {
        game->J1->is_turn = true;
        game->J2->is_turn = false;
    } else {
        game->J1->is_turn = false;
        game->J2->is_turn = true;
    }
    print_game(game,game->J1,game->J2);
    if (game_won(game)){
        printf("it's good\n");
    }
	return EXIT_SUCCESS;
}