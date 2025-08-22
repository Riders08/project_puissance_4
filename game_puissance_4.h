/**
* @copyright Réalisé par Riders. Si une autre personne utilise ce code, sache le... Je vais te retrouver!!!
**/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#ifndef PUISSANCE_4
#define PUISSANCE_4

/* Text colors*/
//It's beautiful!!!
#define BOLDGREEN "\033[1m\033[32m" /* Bold Green */
#define BOLDRED   "\033[1m\033[31m" /* Bold Red */
#define BOLDMAGENTA "\033[1m\033[35m" /* Bold Magenta */
#define BOLDBLACK "\033[1m\033[30m" /* Bold Black */
#define RESET     "\033[0m"


//Longueur et largeur de la plateforme
#define DEFAULT_SIZE_WIDTH 7 //y
#define DEFAULT_SIZE_HEIGTH 6 //x

//Nombre de joueurs(à revoir)
#define DEFAULT_NB_PLAYERS 2

//Limite longueur noms autorisées
#define DEFAULT_SIZE_NICK 25

//Définition des valeurs de pion
#define CONSTRAINT_YELLOW 0
#define CONSTRAINT_RED 1
#define CONSTRAINT_EMPTY 2

typedef unsigned int uint;

// Création de la liste des structures nécessaires
//Structure de couleur
typedef enum{
	YELLOW,
	RED,
	EMPTY,
}color_t;

typedef enum{
	UNSATISFIED,
	SATIFIED,
}status;

typedef enum{
	EGALITY,
	LOSER,
	WINNER,
}stat;

typedef enum{
	LEFT,
	RIGHT
}direction;

typedef struct position {
	uint x;
	uint y;
} pos_t;

//Structure joueur
struct player{
	color_t color_player;
	char nick[DEFAULT_SIZE_NICK];
	uint nb_pion_play;
	bool is_turn;
	stat win;
};

typedef struct game_plat *game_t;

typedef struct player *player_t;

//Structure plateforme du jeu
struct game_plat{
	status ** status;
	color_t ** color;
	uint nb_players;
	player_t J1;
	player_t J2;
	pos_t pos;
};

//Liste des fonctions nécessaire
//PARTIE PLATEAU
game_t game_default();
game_t game_default_solution_win_and_full(void);
game_t game_default_solution_winD(void);
game_t game_default_solution_winH(void);
game_t game_default_solution_winV(void);
game_t create_new_party(pos_t taille, player_t J1, player_t J2);
game_t reset_party(game_t g);
game_t copy_party(game_t g);
bool egal_party(game_t g1 , game_t g2);
void delete_game(game_t g);

//PARTIE JOUEUR
player_t default_player();
player_t default_player_Red();
player_t default_player_Yellow();
player_t create_player(color_t c,const char* surnom);
player_t reset_player(player_t p,const char* surnom,bool choice);
bool check_name_player(player_t joueur1,player_t joueur2);
void delete_player(player_t joueur);


//FONCTIONS Nécessaire au bon fonctionnement du jeu
void play_move(game_t g, pos_t p);
player_t check_turn(game_t g,player_t joueur1,player_t joueur2);
void switch_turn(player_t J1, player_t J2);

//FONCTIONS qui gère les fins de games
bool full_game(game_t g);
bool finish_game(game_t g);
bool game_won(game_t g);
void player_won(player_t joueur);

//LA FONTION QUI AFFICHE LE JEU !

void print_option_of_game(game_t g,player_t J1,player_t J2);
void print_game(game_t g,player_t J1,player_t J2);

// PARTIE PION
bool is_empty(player_t joueur);
void full_pion(game_t game, player_t joueur);

// FONCTIONS GETTEURS
color_t get_color_player(player_t player);
char* get_nickname(player_t player);
uint get_nb_pion_of_player(player_t player);
bool get_turn_player(player_t player);
stat get_win_player(player_t player);

status get_status(game_t game, pos_t pos);
color_t get_color(game_t game, pos_t pos);
uint get_nb_players(game_t game);
pos_t get_pos(game_t g);


#endif /* PUISSANCE_4 */