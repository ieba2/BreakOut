#include "ball.h"
#include "data.h"

#include <windows.h>
#include <gl/gl.h>

#include <math.h>


void build_ball(Ball* balle){
	balle->radius = BALL_RADIUS;
	balle->color.red = BALL_COLOR_RED;
	balle->color.green = BALL_COLOR_GREEN;
	balle->color.blue = BALL_COLOR_BLUE;

	balle->vitesse.x = BALL_SPEED_X;
	balle->vitesse.y = BALL_SPEED_Y;
	balle->isAlive = false;
}

void draw_ball(Ball* balle){
	if (balle-> isAlive){
		glColor3f(balle->color.red,balle->color.green,balle->color.blue);
		glBegin(GL_POLYGON);
		for (int i=0; i<COTES_BALL; i++){
			double angle = DEUX_PI*i/COTES_BALL;
			glVertex2f(balle->position.x + balle->radius*cos(angle),balle->position.y + balle->radius*sin(angle));
		}
		glEnd();
	}
}

void move_ball(Ball* balle, double dt) {
	balle->position.x += balle->vitesse.x*dt;
	balle->position.y += balle->vitesse.y*dt;
}

void collision_balle_plafond(Ball* balle, float hauteur_plafond) {
	if (balle->position.y >= hauteur_plafond - balle->radius) {
		if (balle->vitesse.y > 0) {
			balle->vitesse.y = -balle->vitesse.y;
		}
	}
}

void collision_balle_mur_gauche(Ball* balle, float mur_gauche){
	if (balle->position.x <= mur_gauche + balle->radius) {
		if (balle->vitesse.x < 0) {
			balle->vitesse.x = -balle->vitesse.x;
		}
	}
}

void collision_balle_mur_droit(Ball* balle, float mur_droit){
	if (balle->position.x >= mur_droit - balle->radius) {
		if (balle->vitesse.x > 0) {
			balle->vitesse.x = -balle->vitesse.x;
		}
	}
}