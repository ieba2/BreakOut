#include <windows.h>
#include <gl/glut.h>
#include <iostream>
#include "world.h"
#include <stdlib.h>
#include <time.h>
#include "data.h"

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++ */
/* +++ Prototypes des fonctions pour l'affichage 2D +++ */
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++ */
void init2D();
void display2D();
void keyboard2D(unsigned char, int, int);
void specialKeyboard2D(int, int, int);
void mouse2D(int, int, int, int);
void movingMouse2D(int, int);
void simule2D();
void casseBriqueExit(int);

/* ++++++++++++++++++++++++++++++++++++ */
/* +++ Variables globales generales +++ */
/* ++++++++++++++++++++++++++++++++++++ */
int      width;                        // Largeur courante de la fenetre de visualisation
int      height;                       // Hauteur courante de la fenetre de visualisation
int      mainWindow;                   // Id OpenGL de la fenetre generale de visualisation
GLenum   errCodeOpenGL;                // Code d'erreur OpenGL
World    world;                        // Le "monde"

/* +++++++++++++++++++++++++++ */
/* +++ Fonction principale +++ */
/* +++++++++++++++++++++++++++ */
int main(int argc, char** argv){

/* ======================================== */
/* === Creation de la fenetre graphique === */
/* ======================================== */
   glutInit(&argc,argv);
   glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
   width = WINDOW_WIDTH;
   height = WINDOW_HEIGHT;
   glutInitWindowSize(width,height);
   glutInitWindowPosition(1,1);
   mainWindow = glutCreateWindow("CASSE BRIQUE V1.0");
   init2D();
   glutDisplayFunc(display2D);
   glutKeyboardFunc(keyboard2D);
   glutSpecialFunc(specialKeyboard2D);
   glutIdleFunc(simule2D);
   glutMouseFunc(mouse2D);
   glutPassiveMotionFunc( movingMouse2D );
   glutMainLoop();

/* ================================ */
/* === Fin normale du programme === */
/* ================================ */
   return 1;
}

/* +++++++++++++++++++++++ */
/* +++ Fonction init2D +++ */
/* +++++++++++++++++++++++ */
void init2D(){
/* ======================================================== */
/* === Specification de la couleur de vidage de l'ecran === */
/* ======================================================== */
   glClearColor( 0.0 , 0.0 , 0.0 , 1.0 );

/* =============================== */
/* === Construction du "monde" === */
/* =============================== */
   build_world(&world);

/* ====================================== */
/* === Activation des fonctionnalites === */
/* ====================================== */
   glEnable(GL_DEPTH_TEST);

/* ============================== */
/* === Autres initialisations === */
/* ============================== */
   srand(time(NULL));
}

/* ++++++++++++++++++++++++++ */
/* +++ Fonction display2D +++ */
/* ++++++++++++++++++++++++++ */
void display2D(){
/* =============================================================== */
/* === Vidage du tampon chromatique et du tampon de profondeur === */
/* =============================================================== */
   glutSetWindow(mainWindow);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

/* ========================================================= */
/* === Matrice de projection de coordonnees 2D a l'ecran === */
/* ========================================================= */
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluOrtho2D((GLdouble)0.0,(GLdouble)width,(GLdouble)0.0,(GLdouble)height);

/* ================================ */
/* === Matrice de visualisation === */
/* ================================ */
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   
/* ========================= */
/* === Dessin du "monde" === */
/* ========================= */
   draw_world(&world);

/* ============================================================= */
/* === On verifie qu'il n'y a pas eu d'erreur OpenGL generee === */
/* === depuis le dernier appel de la fonction de display2D   === */
/* ============================================================= */
   if ((errCodeOpenGL = glGetError()) != GL_NO_ERROR){
      std::cerr << "ERROR: Probleme lors du rendu visuel 2D OpenGL : " << (char*)gluErrorString(errCodeOpenGL) << std::endl;
      exit(0);
   }

/* ========================================================== */
/* === Echange des tampons et declenchement du traitement === */
/* ========================================================== */
   glutSwapBuffers();
   glFlush();
}

/* +++++++++++++++++++++++++++ */
/* +++ Fonction keyboard2D +++ */
/* +++++++++++++++++++++++++++ */
void keyboard2D(unsigned char key, int x, int y){
/* ========================= */
/* === Peigne des appels === */
/* ========================= */
   glutSetWindow(mainWindow);
   switch (key){
/* ---------------------------------------- */
/* --- 'q' : pour sortir definitivement --- */
/* ---------------------------------------- */
   case 'q':
      casseBriqueExit(0);
      break;

/* ---------------------------------------- */
/* --- 'espace' : pour lancer une balle --- */
/* ---------------------------------------- */
   case ' ':
	  if (world.restingLives > 0){
		  world.restingLives --;
		  world.enJeu++;
		  world.ball[world.restingLives].isAlive = true;
		  world.ball[world.restingLives].position.x = world.raquette.center.x;
		  world.ball[world.restingLives].position.y = world.raquette.height + world.ball[world.restingLives].radius;
		  display2D();
	  }
      break;

/* -------------------------------------- */
/* --- 'r' : pour relancer une partie --- */
/* -------------------------------------- */
   case 'r' :
	   if (world.GameOver || world.pause) {
		   world.restingLives = INITIAL_LIVES_NUMBER;
		   world.GameOver = false;
		   world.pause = false;
		   init2D();
		   display2D();
	   }
	   break;
   case 27:
	   //casseBriqueExit(0);
	   if (!world.pause) {
		   world.pause = true;
	   }
	   else {
		   world.pause = false;
	   }
	   break;
   }
}

/* ++++++++++++++++++++++++++++++++++ */
/* +++ Fonction specialKeyboard2D +++ */
/* ++++++++++++++++++++++++++++++++++ */

void specialKeyboard2D(int specialKey, int x, int y){

}

/* ++++++++++++++++++++++++ */
/* +++ Fonction mouse2D +++ */
/* ++++++++++++++++++++++++ */

void mouse2D(int button, int state, int x, int y){
   //A FAIRE...
}

/* ++++++++++++++++++++++++++++++ */
/* +++ Fonction movingMouse2D +++ */
/* ++++++++++++++++++++++++++++++ */
void movingMouse2D(int x, int y){
	float d = world.raquette.width/2;
	if (x<d)
	{
		world.raquette.center.x = d;
	}
	else if (x>WINDOW_WIDTH-d)
	{
		world.raquette.center.x = WINDOW_WIDTH-d;
	}
	else
	{
		world.raquette.center.x = x;	
		//______world.raquette.center.y = -y; <--- si on veut que la raquette flotte
	}
	display2D();

	//A FAIRE...

};

/* +++++++++++++++++++++++++ */
/* +++ Fonction simule2D +++ */
/* +++++++++++++++++++++++++ */
void simule2D(){
	simul_world(&world);					//Sert à gérer les collisions, les départ de balles, les vitesses,...
	display2D();


   //A FAIRE...
}

/* ++++++++++++++++++++++++++++++++ */
/* +++ Fonction casseBriqueExit +++ */
/* ++++++++++++++++++++++++++++++++ */
void casseBriqueExit(int code){
/* --------------------------------------- */
/* --- Libérations mémoire éventuelles --- */
/* --------------------------------------- */
   //A FAIRE...

/* -------------------------- */
/* --- Arret du programme --- */
/* -------------------------- */
   exit(code);
}