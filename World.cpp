#include "world.h"
#include "data.h"
#include "point.h"

#include <stdio.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#include <iostream>

#include <gl/gl.h>
#include <gl/glut.h>

void drawBitmapString(char* texte, void* police, Color* color, Point* position) {	//Affiche un texte dans la fenêtre
	glColor3d(color->red, color->green, color->blue);
	glRasterPos2d(position->x, position->y);
	for (unsigned int i = 0; i < strlen(texte); i++) {
		glutBitmapCharacter(police, texte[i]);
	}
}

/* ++++++++++++++++++++++++++++ */
/* +++ Fonction build_world +++ */
/* ++++++++++++++++++++++++++++ */
void build_world(World* monde){
/* ======================= */
/* === Initialisations === */
/* ======================= */
   monde->currentGameLevel = 1;
   monde->currentGameScore = 0;
   monde->restingLives = INITIAL_LIVES_NUMBER;
   monde->enJeu = 0;
   monde->briqueCasse = 0;

  
   build_raquette(&(monde->raquette));						//Construction de la raquette
   
   monde->hauteur_plafond = WINDOW_HEIGHT-HAUTEUR_BANDEAU;	//Def la hauteur du plafond
   
   monde->mur_gauche = 0;									//Def la position du mur gauche
   monde->mur_droit = WINDOW_WIDTH;							//Def la position du mur droit
  
   monde->hauteur_sol = 0;									//Def la position du sol

   for (int i=0; i<INITIAL_LIVES_NUMBER; i++){				//Initialisation des balles
	   build_ball(&(monde->ball[i]));
   }
   srand(time(NULL));
   for (int i = 0; i < NB_LIGNE_BRIQUE; i++) {				//Construction des briques
	   for (int j = 0; j < NB_COLONNE_BRIQUE; j++) {
		   double x = DISTANCE_VIDE * (1 + j) + (j + 0.5)* BRIQUE_WIDTH;
		   double y = BALL_ZONE + DISTANCE_VIDE * (1 + i) + (i + 0.5) * BRIQUE_HEIGHT;
		   int durete = 1 + (rand() % 3);

		   build_brique(&(monde->brique[i][j]), x, y, durete);
	   }
   }

   //A FINIR...
}

/* ++++++++++++++++++++++++++ */
/* +++ Fonction Game Over +++ */
/* ++++++++++++++++++++++++++ */
void game_over(World* world) {
	char GO[50];
	sprintf_s(GO, "Game Over");			//Affiche le Game Over
	Color color_gameover;
		color_gameover.red = 0.0;
		color_gameover.green = 1.0;
		color_gameover.blue = 1.0;
	Point position;
		position.x = (WINDOW_WIDTH - 9 * strlen(GO)) / 2;
		position.y = WINDOW_HEIGHT / 2;
	drawBitmapString(GO, GLUT_BITMAP_TIMES_ROMAN_24, &color_gameover, &position);

	char texte[50];
	sprintf_s(texte, "score: %d - niveau : %d", world->currentGameScore, world->currentGameLevel);		//Affiche le score final et le niveau atteint
	Color color;
		color.red = 1.0;
		color.green = 1.0;
		color.blue = 1.0;
	Point score;
		score.x = (WINDOW_WIDTH - 9 * strlen(texte)) / 2;
		score.y = WINDOW_HEIGHT / 2 - 30;
	drawBitmapString(texte, GLUT_BITMAP_9_BY_15, &color, &score);

	char choix[50];
	sprintf_s(choix, "Press [r] to restart     Press [q] to quit");
	Point press;
	press.x = (WINDOW_WIDTH - 9 * strlen(choix)) / 2;
	press.y = WINDOW_HEIGHT / 2 - 60;
	drawBitmapString(choix, GLUT_BITMAP_9_BY_15, &color, &press);
}

void Stop(World* world) {
	char Pause[50];
	sprintf_s(Pause, "Pause");			//Affiche le menu pause
	Color color_pause;
		color_pause.red = 0.0;
		color_pause.green = 1.0;
		color_pause.blue = 1.0;
	Point position;
		position.x = (WINDOW_WIDTH - 9 * strlen(Pause)) / 2;
		position.y = WINDOW_HEIGHT / 2;
	drawBitmapString(Pause, GLUT_BITMAP_TIMES_ROMAN_24, &color_pause, &position);

	char texte[50];
	sprintf_s(texte, "score: %d - niveau : %d", world->currentGameScore, world->currentGameLevel);		//Affiche le score final et le niveau atteint
	Color color;
	color.red = 1.0;
	color.green = 1.0;
	color.blue = 1.0;
	Point score;
	score.x = (WINDOW_WIDTH - 9 * strlen(texte)) / 2;
	score.y = WINDOW_HEIGHT / 2 - 30;
	drawBitmapString(texte, GLUT_BITMAP_9_BY_15, &color, &score);

	char choix[50];
	sprintf_s(choix, "Press [r] to restart     Press [q] to quit");
	Point press;
	press.x = (WINDOW_WIDTH - 9 * strlen(choix)) / 2;
	press.y = WINDOW_HEIGHT / 2 - 60;
	drawBitmapString(choix, GLUT_BITMAP_9_BY_15, &color, &press);

	sprintf_s(choix, "Press [echap] to continue");
	Point echap;
		echap.x = (WINDOW_WIDTH - 9 * strlen(choix)) / 2;
		echap.y = WINDOW_HEIGHT / 2 - 90;
	drawBitmapString(choix, GLUT_BITMAP_9_BY_15, &color, &echap);
}

/* +++++++++++++++++++++++++++++++ */
/* +++ Fonction Niveau suivant +++ */
/* +++++++++++++++++++++++++++++++ */
void next_level(World* world) {
	world->briqueCasse = 0;
	for (int i = 0; i < INITIAL_LIVES_NUMBER; i++) {
		Ball* balleI = &(world->ball[i]);
		if (balleI->isAlive) {
			build_ball(balleI);
			world->restingLives++;
			world->enJeu--;
		}
	}
	for (int i = 0; i < NB_LIGNE_BRIQUE; i++) {				//Construction des briques
		for (int j = 0; j < NB_COLONNE_BRIQUE; j++) {
			double x = DISTANCE_VIDE * (1 + j) + (j + 0.5) * BRIQUE_WIDTH;
			double y = BALL_ZONE + DISTANCE_VIDE * (1 + i) + (i + 0.5) * BRIQUE_HEIGHT;
			int durete = 1 + (rand() % 3);
			build_brique(&(world->brique[i][j]), x, y, durete);
		}
	}
	Sleep(1000);
	world->currentGameLevel++;
}

/* ++++++++++++++++++++++++++++++++ */
/* +++ Fonction animation score +++ */
/* ++++++++++++++++++++++++++++++++ */
void score_up(float axe, float h, double time) {
	char up[3];
	sprintf_s(up, "15");			//Affiche le score qui monte
	Color color;
		color.red = 1.0;
		color.green = 0.0;
		color.blue = 1.0;
	Point position;
		position.x = axe;
		position.y = h + time * SCORE_SPEED;
	drawBitmapString(up, GLUT_BITMAP_9_BY_15, &color, &position);
}

/* +++++++++++++++++++++++++++ */
/* +++ Fonction draw_world +++ */
/* +++++++++++++++++++++++++++ */
void draw_world(World* world){
	if (!world->GameOver) {
		if (!world->pause) {
			/* ============================= */
			/* === Dessin de la raquette === */
			/* ============================= */
			draw_raquette(&(world->raquette));


			/* ==================================== */
			/* === Dessin des briques restantes === */
			/* ==================================== */
			clock_t temps = clock();
			for (int i = 0; i < NB_LIGNE_BRIQUE; i++) {
				for (int j = 0; j < NB_COLONNE_BRIQUE; j++) {
					draw_brique(&(world->brique[i][j]), temps);
					/*else {
						score_up(world->brique[i][j].coin_bas_gauche.x, world->brique[i][j].coin_bas_gauche.y,dt);
					}*/
				}
			}

			/* ============================================ */
			/* === Dessin (de la balle) (ou des balles) === */
			/* ============================================ */
			for (int i = 0; i < INITIAL_LIVES_NUMBER; i++) {
				draw_ball(&(world->ball[i]));
			}

			/* ======================================================== */
			/* === Dessin du panneau d'affichage (score, vies, ...) === */
			/* ======================================================== */
			draw_bandeau(world);


			/* ================================ */
			/* === Autres dessins éventuels === */
			/* ================================ */

			if (world->briqueCasse == NB_BRIQUES) {
				next_level(world);
			}
		}
		else {
			Stop(world);
		}
	}
	else {
		game_over(world);
	}
}

/* +++++++++++++++++++++++++++++ */
/* +++ Fonction draw_bandeau +++ */
/* +++++++++++++++++++++++++++++ */
void draw_bandeau(World* world){
	glColor3d(1.0,1.0,1.0);									//dessin du liseret (plafond)
	glBegin(GL_LINES);
		glVertex2d(0.0,world->hauteur_plafond);
		glVertex2d(WINDOW_WIDTH,world->hauteur_plafond);
	glEnd();

	//ecriture des informations
	char texte[50];											// Pour ecrire score: |____| - niveau: |____| - vies:|___|
	sprintf_s(texte ,"score: %d - niveau : %d - vies : %d", world->currentGameScore, world->currentGameLevel, world->restingLives); // J'avais juste sprintf � la base
	Color color;
		color.red = BANDEAU_COLOR_RED;
		color.green = BANDEAU_COLOR_GREEN;
		color.blue = BANDEAU_COLOR_BLUE;
	Point position;
		position.x = (WINDOW_WIDTH - 9*strlen(texte))/2;
		position.y = world->hauteur_plafond + (HAUTEUR_BANDEAU - 15)/2;
	drawBitmapString(texte,GLUT_BITMAP_9_BY_15, &color, &position);
}


void simul_world(World* monde){
	// Calcul du temps écoulé
	
	static clock_t old_time = clock();
	clock_t new_time = clock();
	double dt = (double)(new_time - old_time) / (double)(CLOCKS_PER_SEC);
	old_time = new_time;
	if (dt == 0.0)return;
	
	if (!monde->pause) {

		for (int i = 0; i < INITIAL_LIVES_NUMBER; i++) {
			Ball* balleI = &(monde->ball[i]);
			if (balleI->isAlive) {
				move_ball(balleI, dt);							// Deplacement des balles
			}
		}
		for (int i = 0; i < INITIAL_LIVES_NUMBER; i++) {
			Ball* balleI = &(monde->ball[i]);
			if (balleI->isAlive) {
				// Collisions
				collision_balle_plafond(balleI, monde->hauteur_plafond);		// Collision sur le plafond
				collision_raquette(balleI, &(monde->raquette));					// Collisions avec la raquette
				collision_balle_mur_gauche(balleI, monde->mur_gauche);			// Collisions sur les murs
				collision_balle_mur_droit(balleI, monde->mur_droit);
				collision_balle_sol(balleI, monde, monde->hauteur_sol);			// Collision sur le sol : la balle meurt --> A mettre dans world.cpp et world.h a la place de le mettre dans ball.cpp et ball.h, voir celui du prof
				for (int i = 0; i < NB_LIGNE_BRIQUE; i++) {						// Collision sur les briques
					for (int j = 0; j < NB_COLONNE_BRIQUE; j++) {
						if (!monde->brique[i][j].Break) {
							//collision_brique(balleI, &(monde->brique[i][j]), monde);
						}
					}
				}
			}
		}

		// Affiche l'écran de game over quand plus de vies et de balles en jeu
		if (monde->restingLives == 0 && monde->enJeu == 0) {
				monde->GameOver = true;
		}
	}

	// Gere les scores
}

/* ++++++++++++++++++++++++++++++ */
/* +++ Fonction collision_sol +++ */
/* ++++++++++++++++++++++++++++++ */
void collision_balle_sol(Ball* balle, World* monde, float hauteur_sol) {
	if (balle->position.y <= hauteur_sol) {
		balle->isAlive = FALSE;
		monde->enJeu--;
	}
}

/* +++++++++++++++++++++++++++++++++++ */
/* +++ Fonction collision_raquette +++ */
/* +++++++++++++++++++++++++++++++++++ */
void collision_raquette(Ball* balle, Raquette* raquette){
	double x2 = raquette->center.x - 0.5*raquette->width;				// Coordonnee x2 de la bordure de la raquette (coin gauche haut)
	double x1 = x2 - balle->radius;										// Coordonnee x1 : la balle est hors de la raquette (gauche)
	double x3 = x2 + raquette->width;									// Coordonnee x3 de la bordure de la raquette (coin droit haut)
	double x4 = x3 + balle->radius;										// Coordonnee x4 : la balle est hors de la raquette (droite)
	double xballe = balle->position.x;
	double yballe = balle->position.y;

	if (xballe<x1){
		return;
	}
	else if(xballe<x2){												//Coin gauche
		Point cb = {xballe-x2, yballe-raquette->height};
		double dist = norm(cb);
		if (dist<=balle->radius){
			Point normale = {cb.x/dist, cb.y/dist};
			double vn = pscal(balle->vitesse, normale);
			if (vn<0){
				Point tgte = {-normale.y, normale.x};
				double vt = pscal(balle->vitesse,tgte);
				balle->vitesse.x = vt*tgte.x - vn*normale.x;
				balle->vitesse.y = -vt*tgte.y - vn*normale.y; 
			}	
		}
	}
	else if(xballe<=x3){
		if(yballe<=raquette->height + balle->radius){
			if(xballe==raquette->center.x){								//Centre
				balle->vitesse.x = 0;
				balle->vitesse.y = -balle->vitesse.y;
			}
			else if(xballe<raquette->center.x && xballe>x2){			//Partie gauche
				double theta = -COURBURE_RAQUETTE*PI/180 + ((xballe-x2)*2*COURBURE_RAQUETTE*PI/180)/raquette->width;
				Point normale ={sin(theta), cos(theta)};
				double vn = pscal(balle->vitesse, normale);
				if (vn<0){
					Point tgte = {-normale.y, normale.x};
					double vt = pscal(balle->vitesse,tgte);
					balle->vitesse.x = vt*tgte.x - vn*normale.x;
					balle->vitesse.y = -vt*tgte.y - vn*normale.y;
				}
			}
			else if(xballe>raquette->center.x && xballe<x3){			//Partie droite
				double theta = -COURBURE_RAQUETTE*PI/180 + ((xballe-x2)*2*COURBURE_RAQUETTE*PI/180)/raquette->width;
				Point normale ={sin(theta), cos(theta)};
				double vn = pscal(balle->vitesse, normale);
				if (vn<0){
					Point tgte = {-normale.y, normale.x};
					double vt = pscal(balle->vitesse,tgte);
					balle->vitesse.x = vt*tgte.x - vn*normale.x;
					balle->vitesse.y = -vt*tgte.y - vn*normale.y;
				}
			}
		}
	}else if(xballe<=x4){												//Coin droit
		Point cb = {xballe-x4, yballe-raquette->height};
		double dist = norm(cb);
		if (dist<=balle->radius){
			Point normale = {cb.x/dist, cb.y/dist};
			double vn = pscal(balle->vitesse, normale);
			if (vn<0){
				Point tgte = {-normale.y, normale.x};
				double vt = pscal(balle->vitesse, tgte);
				balle->vitesse.x = -(vt*tgte.x - vn*normale.x);
				balle->vitesse.y = -vt*tgte.y - vn*normale.y;
			}	
		}
	}else{
		return;
		}
}

/* +++++++++++++++++++++++++++++++++ */
/* +++ Fonction collision_brIque +++ */
/* +++++++++++++++++++++++++++++++++ */
void collision_brique(Ball* balle, Brique* brique, World* world) {
	double x2 = brique->coin_bas_gauche.x;	// Coordonnee x2 de la bordure de la brique (cote gauche)
	double x1 = x2 - balle->radius;			// Coordonnee x1 : la balle est hors de la brique (ârtie gauche)
	double x3 = x2 + brique->width_b;		// Coordonnee x3 de la bordure de la brique (cote droit)
	double x4 = x3 + balle->radius;			// Coordonnee x4 : la balle est hors de la brique (partie droite)

	double y2 = brique->coin_bas_gauche.y;	// Coordonnee y2 de la bordure de la brique (cote bas)
	double y1 = y2 - balle->radius;			// Coordonnee y1 : la balle est hors de la brique (partie basse)
	double y3 = y2 + brique->height_b;		// Coordonnee y3 de la bordure de la brique (cote haut)
	double y4 = y3 + balle->radius;			// Coordonnee y4 : la balle est hors de la brique (partie haute)

	double xballe = balle->position.x;
	double yballe = balle->position.y;

	bool touch = false;

	if (xballe < x1) {											// La balle est en dehors de la brique
		return;
	}
	else if (xballe < x2) {									// Partie Gauche de la brique
		if (yballe < y1) {										// La balle est en dehors de la brique
			return;
		}
		else if (yballe <= y2) {								// Collision balle - coin inf gauche
			Point cb = { xballe - x2, yballe - y1 };
			double dist = norm(cb);
			if (dist <= balle->radius) {
				Point normale = { cb.x / dist, cb.y / dist };
				double vn = pscal(balle->vitesse, normale);
				if (vn > 0) {
					printf("le COIN G INF\n");
					printf("Vx = %lf et Vy = %lf\n", balle->vitesse.x, balle->vitesse.y);
					Point tgte = { -normale.y, normale.x };
					double vt = pscal(balle->vitesse, tgte);
					balle->vitesse.x = vt * tgte.x - vn * normale.x;
					balle->vitesse.y = -vt * tgte.y - vn * normale.y;
					printf("Vx = %lf et Vy = %lf\n", balle->vitesse.x, balle->vitesse.y);
					touch = true;
				}
			}
		}
		else if (yballe <= y3) {								// Collision balle - cote gauche
			if (balle->vitesse.x > 0) {
				//printf("le COTE G\n");
				balle->vitesse.x = -balle->vitesse.x;
				touch = true;
			}
		}
		else if (yballe <= y4) {								// Collision balle - coin sup gauche
			Point cb = { xballe - x2, yballe - y4 };
			double dist = norm(cb);
			if (dist <= balle->radius) {
				Point normale = { cb.x / dist, cb.y / dist };
				double vn = pscal(balle->vitesse, normale);
				if (vn < 0) {
					printf("le COIN G SUP\n");
					printf("Vx = %lf et Vy = %lf\n", balle->vitesse.x, balle->vitesse.y);
					Point tgte = { -normale.y, normale.x };
					double vt = pscal(balle->vitesse, tgte);
					balle->vitesse.x = vt * tgte.x - vn * normale.x;
					balle->vitesse.y = -vt * tgte.y - vn * normale.y;
					printf("Vx = %lf et Vy = %lf\n", balle->vitesse.x, balle->vitesse.y);
					touch = true;
				}
			}
		}
		else {
			return;
		}
	}
	else if (xballe <= x3) {									// Milieu de la brique
		if (yballe < y1) {										// La balle est en dehors de la brique
			return;
		}
		else if (yballe <= y2) {								// Collision balle - partie basse
			if (balle->vitesse.y > 0) {
				//printf("le BAS\n");
				balle->vitesse.y = -balle->vitesse.y;
				touch = true;
			}
		}
		else if (yballe <= y3) {								// La balle est dans la brique
			return;
		}
		else if (yballe <= y4) {								// Collision balle - partie haute
			if (balle->vitesse.y < 0) {
				balle->vitesse.y = -balle->vitesse.y;
				touch = true;
			}
		}
		else {
			return;
		}
	}
	else if (xballe <= x4) {									// Partie droite de la brique
		if (yballe < y1) {										// La balle est en dehors de la brique
			return;
		}
		else if (yballe <= y2) {								// Collison balle - coin inf droit
			Point cb = { xballe - x4, yballe - y1 };
			double dist = norm(cb);
			if (dist <= balle->radius) {
				Point normale = { cb.x / dist, cb.y / dist };
				double vn = pscal(balle->vitesse, normale);
				if (vn > 0) {
					printf("le COIN D INF\n");
					printf("Vx = %lf et Vy = %lf\n", balle->vitesse.x, balle->vitesse.y);
					Point tgte = { -normale.y, normale.x };
					double vt = pscal(balle->vitesse, tgte);
					balle->vitesse.x = -vt * tgte.x - vn * normale.x;
					balle->vitesse.y = -vt * tgte.y - vn * normale.y;
					printf("Vx = %lf et Vy = %lf\n", balle->vitesse.x, balle->vitesse.y);
					touch = true;
				}
			}
		}
		else if (yballe <= y3) {								// Collision balle - cote droit
			if (balle->vitesse.x < 0) {
				//printf("le COTE D\n");
				balle->vitesse.x = -balle->vitesse.x;
				touch = true;
			}
		}
		else if (yballe <= y4) {								// Collision balle - coin sup droit
			Point cb = { xballe - x4, yballe - y4 };
			double dist = norm(cb);
			if (dist <= balle->radius) {
				Point normale = { cb.x / dist, cb.y / dist };
				double vn = pscal(balle->vitesse, normale);
				if (vn < 0) {
					printf("le COIN D SUP\n");
					printf("Vx = %lf et Vy = %lf\n", balle->vitesse.x, balle->vitesse.y);
					Point tgte = { -normale.y, normale.x };
					double vt = pscal(balle->vitesse, tgte);
					balle->vitesse.x = vt * tgte.x - vn * normale.x;
					balle->vitesse.y = -vt * tgte.y - vn * normale.y;
					printf("Vx = %lf et Vy = %lf\n", balle->vitesse.x, balle->vitesse.y);
					touch = true;
				}
			}
		}
		else {
			return;
		}
	}
	else {
		return;
	}
	if (touch) {										// La balle a touche la brique -> la brique se fragilise
		brique->durete--;
		brique->color_b.blue -= 0.3;
		brique->color_b.green -= 0.3;
		brique->color_b.red -= 0.3;
		if (brique->durete == 0) {
			world->currentGameScore += 15;
			world->briqueCasse++;
			brique->Break = true;
			brique->t = clock();
			brique->score_alive = true;
		}
		touch = false;
	}
}



// +++++ Idées +++++
// écran de transition entre les niveaux
// bonus de brique cassée (balle plus puissante, dédoublage des balles,...)
// menu pause (quitter, restart, ...)
// ajouter son si possible
// stockage de bonus, sac avec un bonus qui peut être utilisé si on appuie sur une touche
//faire des niveaux différents
// tous les 5 niveaux un niveau bonus (avec récompense ?)
// score obtenu qui monte/descend quand la brique se casse
//simplifier affichage txte en ajoutant une partie du code dans drawbitmapstring