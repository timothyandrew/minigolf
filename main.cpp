// A simple OpenGL and glut program
#include <vector>
#include <iostream>
#include "Camera.h"
#include "gllib.h"
#include "Parser.h"
#include "DrawFunctions.h"
#include "Hole.h"
#include "Ball.h"
#include "Physics.h"
#include "Game.h"
#include "Course.h"

using namespace std;

Game* game;

GLfloat light_ambient[] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat light_diffuse[] = { 0.6, 0.6, 0.6, 1.0 };
GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_position[] = { 0.0, 10.0, 0.0, 1.0 };
GLfloat spot_direction[] = { 0.0, -1.0, 0.0 };

void newGame(int numPlayers, const char* file)
{
	game = new Game();
	game->create(numPlayers, file);
	game->initHole(game->curHole);
}

void enable()
{
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 60.0);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, spot_direction);
	glLightf(GL_LIGHT0, GL_SPOT_EXPONENT, 2.0);

	glEnable(GL_LIGHT0);
	glEnable (GL_LIGHTING);
	glEnable (GL_DEPTH_TEST);
	glShadeModel (GL_SMOOTH);
}

void display()
{
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glColor3f(0.0, 1.0, 0.0);
	glLoadIdentity();
	enable();
	gluLookAt (Camera::camPos.coords[0], Camera::camPos.coords[1], Camera::camPos.coords[2],
			Camera::camPos.coords[0]-Camera::camLook.coords[0],
			Camera::camPos.coords[1]-Camera::camLook.coords[1],
			Camera::camPos.coords[2]-Camera::camLook.coords[2], 0.0, 1.0, 0.0);

	glRotatef(Camera::xRot,1.0,0.0,0.0);
	glRotatef(Camera::yRot,0.0,1.0,0.0);
	glRotatef(Camera::zRot,0.0,0.0,1.0);

	//draw level
	game->balls->at(game->curBall)->draw();
	game->course->holes->at(game->curHole)->draw();

	glFlush();
	glutSwapBuffers();
}

void move()
{
	if(!game->balls->at(game->curBall)->moving)
	{
		return;
	}
	gravity(game->balls->at(game->curBall),game->course->holes->at(game->curHole));
	hitWall(game->balls->at(game->curBall),game->course->holes->at(game->curHole));
	checkGradient(game->balls->at(game->curBall),game->course->holes->at(game->curHole));
	game->balls->at(game->curBall)->move();
	checkBall(game->balls->at(game->curBall),game->course->holes->at(game->curHole));

	if(game->balls->at(game->curBall)->curTile == game->course->holes->at(game->curHole)->cup->tile)
	{
		game->course->holes->at(game->curHole)->checkCup(game->balls->at(game->curBall));
	}
	game->nextPlayer();
	glutPostRedisplay();
}

void reshape (int w, int h)
{
   glViewport (0, 0, (GLsizei) w, (GLsizei) h);
   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ();
   glFrustum (-1.0, 1.0, -1.0, 1.0, 1.5, 20.0);
   glMatrixMode (GL_MODELVIEW);
   glutPostRedisplay();
}

void mouseMove(int x, int y)
{

}

void keydown(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'w':
			Camera::camPos.coords[2] -= 0.1f;
			break;

		case 's':
			Camera::camPos.coords[2] += 0.1f;
			break;

		case 'a':
			Camera::camPos.coords[0] -= 0.1f;
			break;

		case 'd':
			Camera::camPos.coords[0] += 0.1f;
			break;

		case '+':
			Camera::camPos.coords[1] += 0.1f;
			break;

		case '-':
			Camera::camPos.coords[1] -= 0.1f;
			break;

		case 't':
			if(!game->balls->at(game->curBall)->moving)
			{
				game->balls->at(game->curBall)->moving = !game->balls->at(game->curBall)->moving;
				game->balls->at(game->curBall)->velocity = game->balls->at(game->curBall)->velocity.unit();
				game->balls->at(game->curBall)->velocity = game->balls->at(game->curBall)->velocity.scale(game->balls->at(game->curBall)->speed);
			}
			break;

		case 'g':
			game->balls->at(game->curBall)->changeDir(-1.0f);
			break;

		case 'h':
			game->balls->at(game->curBall)->changeDir(1.0f);
			break;

		case 'u':
			game->balls->at(game->curBall)->speed += 0.00001f;
			game->balls->at(game->curBall)->startSpeed = game->balls->at(game->curBall)->speed;
			cout << game->balls->at(game->curBall)->speed << endl;
			break;

		case 'j':
			game->balls->at(game->curBall)->speed -= 0.00001f;
			game->balls->at(game->curBall)->startSpeed = game->balls->at(game->curBall)->speed;
			cout << game->balls->at(game->curBall)->speed << endl;
			break;

		case 'o':
			game->nextHole();
			break;

		case 'r':
			game->initHole(game->curHole);
			break;
	}
	glutPostRedisplay();
}

void specialKeyDown(int key, int x, int y)
{
	switch (key)
	{
		case GLUT_KEY_UP:
			Camera::xRot += 5.0;
			break;
		case GLUT_KEY_DOWN:
			Camera::xRot -= 5.0;
			break;
		case GLUT_KEY_LEFT:
			Camera::yRot -= 5.0;
			break;
		case GLUT_KEY_RIGHT:
			Camera::yRot += 5.0;
			break;
	} // end of switch
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (500, 500);
	glutInitWindowPosition (100, 100);
	glutCreateWindow("Minigolf");
	newGame(1, "data.txt");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMotionFunc(mouseMove);
	glutKeyboardFunc(keydown);
	glutSpecialFunc(specialKeyDown);
	glutIdleFunc(move);
	glutMainLoop();

	return 0;
}
