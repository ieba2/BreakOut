#include "raquette.h"
#include "data.h"

#include <windows.h>
#include <gl/gl.h>

void build_raquette(Raquette* lulu){
	lulu->width = RAQUETTE_WIDTH;
	lulu->height = RAQUETTE_HEIGHT;
	lulu->color.red = RAQUETTE_RED_COLOR;
	lulu->color.green = RAQUETTE_GREEN_COLOR;
	lulu->color.blue = RAQUETTE_BLUE_COLOR;
	lulu->center.x = WINDOW_WIDTH/2;
	lulu->center.y = RAQUETTE_HEIGHT/2;
}

void draw_raquette(Raquette* cam){
	glColor3f(cam->color.red, cam->color.green, cam->color.blue);
	glBegin(GL_QUADS);												//QUADS : 4 sommets
	glVertex2f(cam->center.x - cam->width / 2, 0);					//point raquette en bas � gauche ___ ----> Si on veut que la raquette flotte faut pas 0 en ordonnee mais center.y-height
	glVertex2f(cam->center.x - cam->width / 2, cam->height);		//point raquette en haut � gauche ___ ----> Si on veut que la raquette flotte faut pas height en ordonnee mais center.y+height
	glVertex2f(cam->center.x + cam->width / 2, cam->height);		//point raquette en haut � droite ___ ----> Si on veut que la raquette flotte faut pas height en ordonnee mais center.y+height
	glVertex2f(cam->center.x + cam->width / 2, 0);					//point raquette en bas � droite ___ ----> Si on veut que la raquette flotte faut pas 0 en ordonnee mais center.y-height
	glEnd();
}

