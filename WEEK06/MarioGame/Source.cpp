#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include "Mario.h"

using namespace std;

int screenWidth = 640;
int screenHeight = 480;



void Mario::render()
{

	switch (mode)
	{
	case STAY:
		glRasterPos2i(this->pos_X, this->pos_Y);
		pix[0].Draw();
		break;
	case RUN:
		run();
		break;
	case JUMP:
		// body
		break;
	case DEAD:
		// body
		break;
	}
};

void Mario::run()
{
	switch (state)
	{
	case RUNNING1:
		state = RUNNING2;
		break;
	case RUNNING2:
		state = RUNNING3;
		break;
	case RUNNING3:
		state = RUNNING1;
		break;
	}
}

void Mario::changeMode(ModeType m){
	// printf(m);
}
Mario m;

void myInit()
{
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_EQUAL, 1.0);
	m.changeMode(Mario::STAY);
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0, screenWidth, 0, screenHeight);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void myKB_Handler(unsigned char key, int mx, int my)
{
	switch (key)
	{
	case 'r':

		break;
	}
	glutPostRedisplay();
}

void pressKeySpecial(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:
		m.setPosition(-20, 0);
		m.changeMode(Mario::RUN);
		break;

	case GLUT_KEY_RIGHT:
		m.setPosition(20, 0);
		m.changeMode(Mario::RUN);
		break;

	case GLUT_KEY_UP:
		if (m.pos_Y < 12)
			m.setPosition(4, 5);
		m.changeMode(Mario::JUMP);
		break;

	case GLUT_KEY_DOWN:

		break;
	}
	glutPostRedisplay();
}

void releaseKeySpecial(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_LEFT:

		break;
	case GLUT_KEY_RIGHT:

		break;

	case GLUT_KEY_UP:
		if (m.pos_Y != 0)
		{
			m.setPosition(m.pos_X, 0);
			m.changeMode(Mario::STAY);
		}
		break;

	case GLUT_KEY_DOWN:

		break;
	}
	glutPostRedisplay();
}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m.render();
	glutSwapBuffers();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(10, 10);
    glutCreateWindow("MY Mario");

    glutDisplayFunc(myDisplay);
    glutSpecialFunc(pressKeySpecial);
    glutSpecialUpFunc(releaseKeySpecial);
    glutKeyboardFunc(myKB_Handler);

    myInit();
    
    // Start the GLUT main loop
    glutMainLoop();

    return 0;
}

