#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#include "game_puissance_4.h"

// Fonction utile à l'affichage
void usage(char * command){
	fprintf(stderr,"There is an error argument %s", command);
	exit(EXIT_FAILURE);
}

void passed(game_t g){
	fprintf(stdout,"[ " "%s" RESET " ] \n", BOLDGREEN "success");
	delete_game(g);
}

void failed(game_t g){
	fprintf(stdout,"[ " "%s" RESET " ] \n", BOLDRED "fail");
	delete_game(g);
}

void passed_p(player_t p){
	fprintf(stdout,"[ " "%s" RESET " ] \n", BOLDGREEN "success");
	delete_player(p);
}

void failed_p(player_t p){
	fprintf(stdout,"[ " "%s" RESET " ] \n", BOLDRED "fail");
	delete_player(p);
}

void test_create_new_party(){
	game_t game_create_default = game_default();
	pos_t position_default = game_create_default->pos;
	assert(game_create_default);
	for(int i =0 ;i < game_create_default->pos.x; i++){
		for(int j = 0;j < game_create_default->pos.y;j++){
			if (game_create_default->color[i][j] != EMPTY ||
				game_create_default->status[i][j] != UNSATISFIED){
					failed(game_create_default);
			}
		}
	}
	if (game_create_default->pos.x != position_default.x || game_create_default->pos.y != position_default.y || game_create_default->nb_players != DEFAULT_NB_PLAYERS ) {
		failed(game_create_default);
	}else{
		passed(game_create_default);
	}
}

void test_copy_party(){
	game_t game = game_default();
	assert(game);
	game_t game_copy = copy_party(game);
	if(egal_party(game,game_copy)){
		delete_game(game_copy);
		passed(game);
	} else{
		delete_game(game_copy);
		failed(game);
	}
}

void test_equal_party(){
	game_t game = game_default();
	assert(game);
	game_t game_copy = copy_party(game);
	for(int i =0 ;i < game->pos.x; i++){
		for(int j = 0;j < game->pos.y;j++){
			if (game->color[i][j] != game_copy->color[i][j] ||
				game->status[i][j] != game_copy->status[i][j]){
					delete_game(game);
					failed(game);
			}
		}
	}
	if(game->pos.x != game_copy->pos.x || game->pos.y != game_copy->pos.y || game->nb_players != game_copy->nb_players ){
		delete_game(game_copy);
		failed(game);
	}else{
		delete_game(game_copy);
		passed(game);
	}
}

void test_reset_party(){
	game_t game = game_default();
	assert(game);
	if(game->color[0][0] == EMPTY){
		game->color[0][0] = RED;
		if(game->color[0][0] == RED){
			reset_party(game);
			if(game->color[0][0]== RED){
				failed(game);
			}
			else{
				passed(game);
			}
		}
	}
}

void test_delete_game(){
	game_t game = game_default();
	assert(game);
	game_t game_copy = copy_party(game);
	delete_game(game_copy);
	passed(game);
}

void test_create_player(){
	player_t player = create_player(RED, "test");
	assert(player);
	if (player->win != EGALITY || player->nb_pion_play != 0 || player->color_player != RED || strcmp(player->nick,"test") != 0){
		failed_p(player);
	}
	else{
		passed_p(player);
	}
}

void test_reset_player(){
	player_t player = default_player();
	assert(player);
	uint nb_pion = player->nb_pion_play;
	stat win = player->win;
	char* old_name = player->nick;
	player_t player_reset = reset_player(player,"test",true);
	if (nb_pion != player_reset->nb_pion_play || win != player_reset->win){
		delete_player(player_reset);
		failed_p(player);
	}
	else if (strcmp(player_reset->nick,old_name)==0){
		delete_player(player_reset);
		failed_p(player);
	}
	else if(strcmp(player_reset->nick,"test")==0){
		delete_player(player_reset);
		passed_p(player);
	}
}

void test_check_name_player(){
	player_t j1 = create_player(RED,"J1");
	player_t j2 = create_player(YELLOW,"J2");
	assert(j1);
	assert(j2);
	if(check_name_player(j1,j2)){
		delete_player(j2);
		passed_p(j1);
	}
	else{
		delete_player(j2);
		failed_p(j1);
	}
}

void test_delete_player(){
	player_t player = default_player();
	assert(player);
	passed_p(player);
}

void test_full_game(){
	game_t game = game_default();
	if(full_game(game)){
		failed(game);
	}
	else{
		for(int i = 0;i< game->pos.x;i++){
			for(int j = 0 ;j< game->pos.y;j++){
				if (game->status[i][j] == UNSATISFIED){
					game->status[i][j] = SATIFIED;
				}
				if (game->color[i][j] == EMPTY){
					game->color[i][j] = RED;
				}
			}
		}
		if (full_game(game)){
			passed(game);
		}else{
			failed(game);
		}
	}
}


void test_finish_game(){
	game_t game = game_default_solution_winD();
	player_t j1 = create_player(RED,"riders");
	player_t j2 = default_player();
	assert(j1);
	assert(j2);
	game->J1 = j1;
	game->J1->win = WINNER;
	game->J2 = j2;
	game->J2->win = LOSER;
	assert(game);
	if(finish_game(game)){
		if(game_won(game)){
			if(j1->win == j2->win){
				delete_game(game);
				delete_player(j2);
				failed_p(j1);
			}else{
				delete_game(game);
				delete_player(j2);
				passed_p(j1);
			}
		}
		else if (full_game(game)){
			for(int i =0;i< game->pos.x;i++){
				for(int j =0;j < game->pos.y;j++){
					if (game->status[i][j] == UNSATISFIED || game->color[i][j] == EMPTY){
						delete_game(game);
						delete_player(j2);
						failed_p(j1);
					}
				}
			}
			delete_game(game);
			delete_player(j2);
			passed_p(j1);
		}
	}
	else{
		if (full_game(game)|| game_won(game)){
			delete_game(game);
			delete_player(j2);
			failed_p(j1);
		} else{
			delete_game(game);
			delete_player(j2);
			passed_p(j1);
		}
	}
}

void test_game_won(){
	game_t game = game_default_solution_winD();
	player_t j1 = create_player(RED,"riders");
	player_t j2 = default_player();
	assert(j1);
	assert(j2);
	if (game_won(game)){
		delete_player(j1);
		delete_player(j2);
		passed(game);
	}else{
		delete_player(j1);
		delete_player(j2);
		failed(game);
	}
}

void test_player_won(){
	player_t j1 = default_player();
	j1->win = WINNER;
	if (j1->win == WINNER){
		passed_p(j1);
	} else{
		failed_p(j1);
	}
}

int main(int argc, char* argv[]){
	if (argc != 1){
		usage(argv[0]);
	}
	else{
		printf("DEMARRAGE DES TESTS\n");
		printf("Create new party : ");
		test_create_new_party();
		printf("Copy party : ");
		test_copy_party();
		printf("Equal party : ");
		test_equal_party();
		printf("Reset party : ");
		test_reset_party();
		printf("Delete game : ");
		test_delete_game();
		printf("Create player : ");
		test_create_player();
		printf("Reset player : ");
		test_reset_player();
		printf("Check player : ");
		test_check_name_player();
		printf("Delete player : ");
		test_delete_player();
		printf("Full game : ");
		test_full_game();
		printf("Finish game : ");
		test_finish_game();
		printf("Game WON : ");
		test_game_won();
		printf("Player WON : ");
		test_player_won();
	}
}