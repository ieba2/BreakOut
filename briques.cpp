#include "data.h"
#include "brique.h"

#include <windows.h>
#include <stdio.h>

#include <gl/gl.h>

void build_brique(Brique* bri, double x, double y, int durete) {
	bri->width_b = BRIQUE_WIDTH;
	bri->height_b = BRIQUE_HEIGHT;

	bri->Break = false;

	bri->durete = durete;

	bri->color_b.red = BRIQUE_RED_COLOR - ((3 - durete) * 0.3f);
	bri->color_b.green = BRIQUE_GREEN_COLOR - ((3 - durete) * 0.3f);
	bri->color_b.blue = BRIQUE_BLUE_COLOR - ((3 - durete) * 0.3f);

	bri->coin_bas_gauche.x = x - 0.5 * BRIQUE_WIDTH;
	bri->coin_bas_gauche.y = y - 0.5 * BRIQUE_HEIGHT;
	bri->coin_haut_droit.x = x + 0.5 * BRIQUE_WIDTH;
	bri->coin_haut_droit.y = y + 0.5 * BRIQUE_HEIGHT;

	bri->center_b.x = BRIQUE_WIDTH / 2;
	bri->center_b.y = BRIQUE_HEIGHT / 2;
}

void draw_brique(Brique* bri, clock_t temps) {
	if (!bri->Break) {
		glColor3f(bri->color_b.red, bri->color_b.green, bri->color_b.blue);
		glBegin(GL_QUADS);														//QUADS : 4 sommets
		glVertex2f(bri->coin_bas_gauche.x, bri->coin_bas_gauche.y);			//point brique en bas à gauche
		glVertex2f(bri->coin_bas_gauche.x, bri->coin_haut_droit.y);			//point brique en haut à gauche
		glVertex2f(bri->coin_haut_droit.x, bri->coin_haut_droit.y);			//point brique en haut à droite
		glVertex2f(bri->coin_haut_droit.x, bri->coin_bas_gauche.y);			//point brique en bas à droite
		glEnd();
	}
	else if(bri->score_alive) {
		double dt = (double)(temps - bri->t) / (double)(CLOCKS_PER_SEC);

	}
}