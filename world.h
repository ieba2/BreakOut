#ifndef WORLD_H
#define WORLD_H

#include "raquette.h"
#include "brique.h"
#include "ball.h"
#include "data.h"

typedef struct World {

   int currentGameLevel;	// niveau courant
   int currentGameScore;	// score courant
   int restingLives;		// nombre de vies restantes
   int enJeu;				// nombre de balles en jeu
   int briqueCasse;			// nombre de brique casse

   bool GameOver;
   bool pause;

   Raquette raquette;
   Brique brique[NB_LIGNE_BRIQUE][NB_COLONNE_BRIQUE];

   float hauteur_plafond;

   float mur_droit;
   float mur_gauche;

   float hauteur_sol;

   Ball ball[INITIAL_LIVES_NUMBER];

   //A COMPLETER...

} World;

void build_world(World*);
void draw_world(World*);

void game_over(World*);
void next_level(World*);
void score_up(float, float, double);

void draw_bandeau(World*);
void drawBitmapString(char*, void*, Color*, Point*);

void simul_world(World*);

void collision_raquette(Ball*, Raquette*);
void collision_balle_sol(Ball*, World*, float);
void collision_brique(Ball*, Brique*, World*);

#endif