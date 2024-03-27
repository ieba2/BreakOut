#ifndef BALL_H
#define BALL_H

#include "color.h"
#include "point.h"

typedef struct Ball{
	float radius;
	Color color;
	Point position;
	Point vitesse;
	bool isAlive;

}Ball;

void build_ball(Ball*);
void draw_ball(Ball*);

void move_ball(Ball*, double);
void collision_balle_plafond(Ball*, float);
void collision_balle_mur_gauche(Ball*, float);
void collision_balle_mur_droit(Ball*, float);

#endif