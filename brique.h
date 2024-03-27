#ifndef BRIQUE
#define BRIQUE

#include "color.h"
#include "point.h"
#include <time.h>


typedef struct Brique {
	int width_b;
	int height_b;
	int durete;
	bool Break;
	bool score_alive;
	int score;
	clock_t t;

	Color color_b;

	Point center_b;
	Point coin_bas_gauche;
	Point coin_haut_droit;
}Brique;

void build_brique(Brique*, double, double, int);
void draw_brique(Brique*, clock_t);

#endif