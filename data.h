#ifndef DATA_H
#define DATA_H

/* ########################################## */
/* ### PARAMETRES DE LA FENETRE GRAPHIQUE ### */
/* ########################################## */
#define WINDOW_WIDTH  600			// Largeur fenetre
#define WINDOW_HEIGHT 400			// Hauteur fenetre


/* ######################### */
/* ### PARAMETRES DU JEU ### */
/* ######################### */
#define GAME_LEVEL_NUMBER    5      // Nombre de niveaux
#define INITIAL_LIVES_NUMBER 5     // Nombre de vies

#define HAUTEUR_BANDEAU 30
#define BANDEAU_COLOR_RED 1.0f
#define BANDEAU_COLOR_GREEN 1.0f
#define BANDEAU_COLOR_BLUE 1.0f

#define RAQUETTE_WIDTH 100			// Largeur raquette
#define RAQUETTE_HEIGHT 10			// Hauteur raquette
#define RAQUETTE_RED_COLOR 1.0f		// Couleur rouge
#define RAQUETTE_GREEN_COLOR 1.0f	// Couleur verte
#define RAQUETTE_BLUE_COLOR 1.0f	// Couleur bleu

#define NB_LIGNE_BRIQUE 4
#define NB_COLONNE_BRIQUE 6
#define DISTANCE_VIDE 5
#define BALL_ZONE 150
#define NB_BRIQUES NB_LIGNE_BRIQUE * NB_COLONNE_BRIQUE

#define BRIQUE_WIDTH (WINDOW_WIDTH - (NB_COLONNE_BRIQUE + 1.0) * DISTANCE_VIDE)/NB_COLONNE_BRIQUE								// Largeur brique
#define BRIQUE_HEIGHT (WINDOW_HEIGHT - HAUTEUR_BANDEAU - BALL_ZONE -(NB_LIGNE_BRIQUE + 1.0) * DISTANCE_VIDE)/NB_LIGNE_BRIQUE	// Hauteur brique
#define BRIQUE_RED_COLOR 1.0f		// Couleur rouge
#define BRIQUE_GREEN_COLOR 1.0f		// Couleur verte
#define BRIQUE_BLUE_COLOR 1.0f		// Couleur bleu


#define BALL_RADIUS 10
#define BALL_COLOR_RED 0.0f
#define BALL_COLOR_GREEN 1.0f
#define BALL_COLOR_BLUE 1.0f
#define BALL_SPEED_X 0.0
#define BALL_SPEED_Y 200

#define SCORE_SPEED 3
#define SCORE_TIME 1

#define COTES_BALL 30
#define DEUX_PI 6.283185

#define ANGLE 3.14/6

#define PI 3.141592
#define COURBURE_RAQUETTE 30

#endif