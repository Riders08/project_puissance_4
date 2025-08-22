#include "game_puissance_4.h"
#include <assert.h>

// FONCTIONS CHECKS
void check_taille(pos_t test){
	if(test.x<DEFAULT_SIZE_HEIGTH || test.y<DEFAULT_SIZE_WIDTH){
		fprintf(stderr,"error argument coordinates!\n");
		exit(EXIT_FAILURE);
	}
}

void check_color(color_t c){
	if(c!=RED && c!=YELLOW && c!=EMPTY){
		fprintf(stderr,"error argument color!\n");
		exit(EXIT_FAILURE);
	}
}
void check_same_color(color_t c, color_t c2){
	if(c == c2){
		fprintf(stderr,"error 2 color are used same moment!\n");
		exit(EXIT_FAILURE);
	}
}

void check_color_play(color_t c){
	if(c!=RED && c!=YELLOW){
		fprintf(stderr,"error color for play!\n");
		exit(EXIT_FAILURE);
	}
}

void check_game(game_t game){
	if(!game){
		fprintf(stderr,"error create game!\n");
		exit(EXIT_FAILURE);
	}
}

void check_player(player_t player){
	if(!player){
		fprintf(stderr,"error create player!\n");
		exit(EXIT_FAILURE);
	}
}

bool check_player_won(player_t joueur){
	check_player(joueur);
	if(joueur->win == WINNER){
		return true;
	}
	fprintf(stderr, "the player %s has not again win\n", joueur->nick);
	return false;
}

// FIN FONCTIONS CHECKS

// FONCTIONS PARTY
game_t game_default(void){
	pos_t position_default = {DEFAULT_SIZE_HEIGTH,DEFAULT_SIZE_WIDTH};
	player_t J1 = default_player_Red();
	player_t J2 = default_player_Yellow();
	game_t game = create_new_party(	position_default,J1,J2);
	return game;
}

game_t game_default_solution_winH(void){
	game_t game = game_default();
	assert(game);
	game->color[0][6] = RED;
	game->color[1][6] = RED;
	game->color[2][6] = RED;
	game->color[3][6] = RED;
	game->status[0][6] = SATIFIED;
	game->status[1][6] = SATIFIED;
	game->status[2][6] = SATIFIED;
	game->status[3][6] = SATIFIED;
	game->color[0][5] = YELLOW;
	game->color[1][5] = YELLOW;
	game->color[2][5] = YELLOW;
	game->status[0][5] = SATIFIED;
	game->status[1][5] = SATIFIED;
	game->status[2][5] = SATIFIED;
	return game;
}

game_t game_default_solution_winV(void){
	game_t game = game_default();
	assert(game);
	game->color[3][6] = RED;
	game->color[3][5] = RED;
	game->color[3][4] = RED;
	game->color[3][3] = RED;
	game->status[3][6] = SATIFIED;
	game->status[3][5] = SATIFIED;
	game->status[3][4] = SATIFIED;
	game->status[3][3] = SATIFIED;
	game->color[0][6] = YELLOW;
	game->color[1][6] = YELLOW;
	game->color[2][6] = YELLOW;
	game->status[0][6] = SATIFIED;
	game->status[1][6] = SATIFIED;
	game->status[2][6] = SATIFIED;
	return game;
}

game_t game_default_solution_winD(void){
	game_t game = game_default();
	assert(game);
	game->color[5][6] = RED;
	game->color[4][5] = RED;
	game->color[3][4] = RED;
	game->color[2][3] = RED;
	game->status[5][6] = SATIFIED;
	game->status[4][5] = SATIFIED;
	game->status[3][4] = SATIFIED;
	game->status[2][3] = SATIFIED;
	game->color[4][6] = YELLOW;
	game->color[3][5] = YELLOW;
	game->color[2][4] = YELLOW;
	game->status[4][6] = SATIFIED;
	game->status[3][5] = SATIFIED;
	game->status[2][4] = SATIFIED;
	game->color[3][6] = YELLOW;
	game->color[2][6] = YELLOW;
	game->color[2][5] = YELLOW;
	game->status[2][6] = SATIFIED;
	game->status[3][6] = SATIFIED;
	game->status[2][5] = SATIFIED;
	game->color[0][6] = RED;
	game->color[0][5] = RED;
	game->color[0][4] = RED;
	game->status[0][6] = SATIFIED;
	game->status[0][5] = SATIFIED;
	game->status[0][4] = SATIFIED;
	return game;
}

game_t game_default_solution_win_and_full(void){
	game_t game = game_default();
	assert(game);
	for(int i = game->pos.x -1;i>=0;i--){
		for(int j =game->pos.y-1;j >=0 ;j--){
			pos_t position = {i,j};
			play_move(game,position);
		}
	}
	return game;
}

game_t create_new_party(pos_t taille,player_t J1, player_t J2){
	if(!taille.x || !taille.y){
		fprintf(stderr,"error argument!\n");
		exit(EXIT_FAILURE);
	}
	check_taille(taille);
	game_t new_game=(game_t)malloc(sizeof(struct game_plat));
	check_game(new_game);
	new_game->pos=taille;
	new_game->J1 = J1;
	full_pion(new_game,new_game->J1);
	new_game->J2 = J2;
	full_pion(new_game,new_game->J2);
	new_game->nb_players=DEFAULT_NB_PLAYERS;
	new_game->status=malloc(new_game->pos.x*sizeof(status*));
	new_game->color=malloc(new_game->pos.x*sizeof(color_t*));
	if(!new_game->color || !new_game->color){
		fprintf(stderr,"error allocation memory of argument\n");
		free(new_game->color);
		free(new_game->status);
		free(new_game);
		exit(EXIT_FAILURE);
	}
	for(uint i=0;i<new_game->pos.x;i++){
		new_game->status[i]=malloc(new_game->pos.y*sizeof(status));
		new_game->color[i]=malloc(new_game->pos.y*sizeof(color_t));
		if(!new_game->color[i]||!new_game->status[i]){
			fprintf(stderr,"error allocation again!!!\n");
			free(new_game->color[i]);
			free(new_game->status[i]);
			free(new_game->color);
			free(new_game->status);
			free(new_game);
			exit(EXIT_FAILURE);
		}
		for(uint j=0;j<new_game->pos.y;j++){
			new_game->status[i][j]=UNSATISFIED;
			new_game->color[i][j]=EMPTY;
		}
	}
	return new_game;
}

game_t copy_party(game_t g){
	check_game(g);
	check_taille(g->pos);
	game_t copy_game =create_new_party(g->pos, g->J1, g->J2);
	check_game(copy_game);
	for(uint i=0;i<copy_game->pos.x;i++){
		for(uint j=0;j<copy_game->pos.y;j++){
			copy_game->color[i][j]=g->color[i][j];
			copy_game->status[i][j]=g->status[i][j];
		}
	}
	return copy_game;
}

bool egal_party(game_t g1 , game_t g2){
	check_game(g1);
	check_game(g2);
	if(g1->pos.x!=g2->pos.x || g1->pos.y!=g2->pos.y){
		fprintf(stderr,"error cohesion taille!\n");
		return false;
	}
	for(uint i=0;i<g1->pos.x;i++){
		for(uint j=0;j<g1->pos.y;j++){
			if(g1->color[i][j]!=g2->color[i][j] 
			|| g1->status[i][j]!=g2->status[i][j]){
				return false;
			}
		}
	}
	return true;
}

game_t reset_party(game_t g){
	check_game(g);
	check_taille(g->pos);
	for(int i =0;i < g->pos.x;i++){
		for(int j =0;j < g->pos.y;j++){
			g->color[i][j]=EMPTY;
			g->status[i][j]=UNSATISFIED;
		}
	}
	return g;
}

void delete_game(game_t g){
	check_game(g);
	check_taille(g->pos);
	if(g){
		if(g->color){
			for(uint i=0;i<g->pos.x;i++){
				if(g->color[i]){
					free(g->color[i]);
				}
			}
			free(g->color);
		}
		if(g->status){
			for(uint i=0;i<g->pos.x;i++){
				if(g->status[i]){
					free(g->status[i]);
				}
			}
			free(g->status);
		}
		free(g);
	}
}

// FIN FONCTIONS PARTY

// FONCTIONS PLAYER
player_t default_player(){
	player_t player = create_player(YELLOW,"IA");
	return player;
}
player_t default_player_Red(){
	player_t player = create_player(RED,"IA_red");
	return player;
}
player_t default_player_Yellow(){
	player_t player = create_player(YELLOW,"IA_yellow");
	return player;
}

player_t create_player(color_t c,const char* surnom){
	check_color_play(c);
	if(!surnom){
		fprintf(stderr,"error argument surnom!\n");
		exit(EXIT_FAILURE);
	}
	if(strlen(surnom)>DEFAULT_SIZE_NICK){
		fprintf(stderr,"attention ton surnom est trop long!\n");
		exit(EXIT_FAILURE);
	}
	player_t player=malloc(sizeof(struct player));
	check_player(player);
	player->win=EGALITY;
	player->nb_pion_play=0;
	player->is_turn = true;
	player->color_player=c;
	strncpy(player->nick, surnom, DEFAULT_SIZE_NICK);
	player->nick[DEFAULT_SIZE_NICK - 1] = '\0';
	return player;
}

player_t reset_player(player_t p,const char* surnom, bool choice){
	check_player(p);
	player_t reset_player=malloc(sizeof(struct player));
	check_player(reset_player);
	if(choice){
		reset_player->win=p->win;
		reset_player->nb_pion_play=p->nb_pion_play;
	}
	else{
		reset_player->win=EGALITY;
		reset_player->nb_pion_play=0;
	}
	strncpy(reset_player->nick, surnom, DEFAULT_SIZE_NICK);
	reset_player->nick[DEFAULT_SIZE_NICK - 1] = '\0';
	reset_player->color_player=p->color_player;
	return reset_player;
}

bool check_name_player(player_t joueur1,player_t joueur2){
	check_player(joueur1);
	check_player(joueur2);
	if(strcmp(joueur1->nick,joueur2->nick)==0 || joueur1->color_player == joueur2->color_player){
		return false;
	}
	return true;
}

void delete_player(player_t joueur){
	check_player(joueur);
	if(joueur){
		free(joueur);
	}
}

// FIN FONCTIONS PLAYER

// FONCTIONS DE FIN

bool full_game(game_t g){
	check_game(g);
	for(uint i=0;i<g->pos.x;i++){
		for(uint j=0;j<g->pos.y;j++){
			if(g->color[i][j]==EMPTY){
				return false;
			}
			else if(g->status[i][j]==UNSATISFIED){
				return false;
			}
		}
	}
	return true;
}

bool finish_game(game_t g){
	check_game(g);
	check_player(g->J1);
	check_player(g->J2);
	if(full_game(g) || check_player_won(g->J1) || check_player_won(g->J2)){
		return true;
	}
	return false;
}


bool game_won(game_t g){
	check_game(g);
	for(int i = 0;i< g->pos.x;i++){
		for(int j = 0;j< g->pos.y;j++){
			color_t c = g->color[i][j];
			if (g->color[i][j] == EMPTY){
				continue;
			}
			else if (j + 3 < g->pos.y && g->color[i][j+1] == c && g->color[i][j+2] == c && g->color[i][j+3] == c){
				return true;
			}
			else if (j - 3 >= 0 && g->color[i][j-1] == c && g->color[i][j-2] == c && g->color[i][j-3] == c){
				return true;
			}
			else if (i + 3 < g->pos.x && g->color[i+1][j] == c && g->color[i+2][j] == c && g->color[i+3][j] == c){
				return true;
			}
			else if (i - 3 >= 0 && g->color[i-1][j] == c && g->color[i-2][j] == c && g->color[i-3][j] == c){
				return true;
			}
			else if (i + 3 < g->pos.x && j + 3 < g->pos.y && g->color[i+1][j+1] == c && g->color[i+2][j+2] == c && g->color[i+3][j+3] == c){
                return true;
			}
			else if (i - 3 >= 0 && j + 3 < g->pos.y && g->color[i-1][j+1] == c && g->color[i-2][j+2] == c && g->color[i-3][j+3] == c){
                return true;
			}
			else if (i + 3 < g->pos.x && j - 3 >= 0 && g->color[i+1][j-1] == c && g->color[i+2][j-2] == c && g->color[i+3][j-3] == c){
                return true;
			}
			else if (i - 3 >= 0 && j - 3 >= 0 && g->color[i-1][j-1] == c && g->color[i-2][j-2] == c && g->color[i-3][j-3] == c){
                return true;
			}
		}
	}
	return false;
}

void player_won(player_t joueur){
	check_player(joueur);
	if(joueur->win==WINNER){
		printf("CONGRATULATION: THE VICTORY IS FOR %s !!!\n",joueur->nick);
	}else{
		printf("SORRY: YOU LOSE, TRY AGAIN, YOU CAN DO IT\n");
	}
}

// FIN FONCTIONS DE FIN

// FONCTIONS D'AFFICHAGES

void print_option_of_game(game_t g,player_t J1,player_t J2){
	check_game(g);
	check_taille(g->pos);
	fprintf(stdout," Nous avons un jeu de taille %d*%d.\n "
	,g->pos.x,g->pos.y);
	fprintf(stdout," equipe ROUGE %s = %d 		vs		equipe JAUNE %s = %d  \n",
	J1->nick,J1->nb_pion_play,J2->nick,J2->nb_pion_play);
}

void print_game(game_t g,player_t J1,player_t J2){
	check_game(g);
	check_taille(g->pos);
	print_option_of_game(g,J1,J2);
	const char* yellow="🟡";
	const char* red="🔴";
	fprintf(stdout, "  ");
    for (uint i=0; i < g->pos.x; i++){
		fprintf(stdout, " %d", i);
	}
    fprintf(stdout, "\n   ");
	for (uint i = 0; i < g->pos.x; i++){
		fprintf(stdout, "--");
	}
    fprintf(stdout, "\n");

	for (uint i = 0; i < g->pos.y; i++){
        fprintf(stdout, "%d |", i);
        for (uint j = 0; j < g->pos.x; j++){
            if (g->color[j][i] == RED && g->status[j][i] == SATIFIED) {
                fprintf(stdout, "%s",red);
            }
			else if (g->color[j][i] == YELLOW && g->status[j][i] == SATIFIED) {
                fprintf(stdout, "%s",yellow);
            }else{
				fprintf(stdout, "  ");
			}
        }
        fprintf(stdout, "|\n");
    }

	fprintf(stdout, "  ");
    for (uint i = 0; i < g->pos.x; i++){
		fprintf(stdout, "--");
	}
    fprintf(stdout, "\n");
}
// FIN FONCTIONS D'AFFICHAGES

// Fonctions Nécessaires au bon fonctionnement du jeu

void play_move(game_t g, pos_t p){
	assert(g);
	player_t player_to_play = check_turn(g,g->J1,g->J2);
	if ( p.x > g->pos.x || p.x < 0 || p.y > g->pos.y || p.y < 0){
		fprintf(stderr,"error, the position argument is out of game (%d,%d)\n",p.x,p.y);
		return;
	}
	if(p.x < g->pos.x && (p.y)+1 < g->pos.y && g->status[p.x][(p.y)+1] == UNSATISFIED){
		fprintf(stderr,"Is not possible play here because this position isn't full => (%d,%d)\n",p.x, p.y+1);
		return;
	}
	if (g->status[p.x][p.y] == SATIFIED) {
		fprintf(stderr, "This position is already taken.\n");
        return;
    }
	g->status[p.x][p.y] = SATIFIED;
	g->color[p.x][p.y] = player_to_play->color_player;
	player_to_play->nb_pion_play--;
	/*if (game_won(g,joueur1,joueur2)){
		player_won(joueur1);
		player_won(joueur2);
	}else{
		printf("IT'S FINISH, EGALITY. FINALLY, WHO IS THE STRONGER ?\n");
	}
	if(finish_game(g,joueur1,joueur2) || full_game(g)){
		if (game_won(g,joueur1,joueur2)){
			player_won(joueur1);
			player_won(joueur2);
		}else{
			printf("IT'S FINISH, EGALITY. FINALLY, WHO IS THE STRONGER ?\n");
		}
		return;
	}*/
	switch_turn(g->J1,g->J2);
}

player_t check_turn(game_t game, player_t J1, player_t J2){
	assert(game);
	if(is_empty(J1) && is_empty(J2)){
		fprintf(stderr,"Any player can play again, so the game is finish\n");
		return NULL;
	}
	if( J1->is_turn){
		return J1;
	}
	if( J2->is_turn){
		return J2;
	}
	fprintf(stderr,"Error: Any player is her turn. Cheating?\n");
	exit(EXIT_FAILURE);
}

void switch_turn(player_t J1, player_t J2){
    if (J1->is_turn) {
        J1->is_turn = false;
        J2->is_turn = true;
    } else {
        J1->is_turn = true;
        J2->is_turn = false;
    }
}

bool is_empty(player_t J1){
	assert(J1);
	if (J1->nb_pion_play == 0){
		return true;
	}else{
		return false;
	}
}

void full_pion(game_t game, player_t player){
	assert(game);
	uint number_cases = game->pos.x * game->pos.y;
	if( number_cases %2 == 0) {
		player->nb_pion_play = number_cases / 2;
	}
	else{
		player->nb_pion_play = (number_cases+1)/2;
	}
}

// FONCTIONS GETTER

color_t get_color_player(player_t player){
	return player->color_player;
}

char* get_nickname(player_t player){
	return player->nick;
}

uint get_nb_pion_of_player(player_t player){
	return player->nb_pion_play;
}

bool get_turn_player(player_t player){
	return player->is_turn;
}

stat get_win_player(player_t player){
	return player->win;
}

status get_status(game_t game,pos_t pos){
	return game->status[pos.x][pos.y];
}

uint get_nb_players(game_t game){
	return game->nb_players;
}

color_t get_color(game_t game,pos_t pos){
	return game->color[pos.x][pos.y];
}

pos_t get_pos(game_t g){
	if(g){
		return g->pos;
	}else{
		fprintf(stderr,"error game argument\n");
		exit(EXIT_FAILURE);
	}
}