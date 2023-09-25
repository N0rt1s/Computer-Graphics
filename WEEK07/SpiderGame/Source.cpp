#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
// #include <gl/RGBpixmap.h>
#include "pixMap.h"

using namespace std;

int screenWidth = 640;
int screenHeight = 480;

class Point2
{
public:
	// constructor 1
	Point2()
	{
		x = y = 0.0f;
	}
	// constructor 2
	Point2(float xx, float yy)
	{
		x = xx;
		y = yy;
	}
	void set(float xx, float yy)
	{
		x = xx;
		y = yy;
	}
	float getX() { return x; }
	float getY() { return y; }
	void draw(void)
	{
		glPointSize(2.0);

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
		glEnable(GL_POINT_SMOOTH);

		glBegin(GL_POINTS); // draw this point
		glVertex2f((GLfloat)x, (GLfloat)y);
		glEnd();

		glDisable(GL_POINT_SMOOTH);

	} // end draw
private:
	float x, y;
}; // end class Point2

class Spider
{
private:
	enum State
	{
		ALIVE,
		DEAD
	} state;
	RGBApixmap pix[2];

public:
	float pos_X, pos_Y;
	bool isMoving;
	float spiderSpeed;
	float theta;
	float rateOfChange;

	Spider() {}

	Spider(Point2 pos)
	{
		isMoving = true;
		spiderSpeed = 400.0f;
		theta = 0.0;
		rateOfChange = 1.0;
		this->pos_X = pos.getX();
		this->pos_Y = pos.getY();

		string fname[2] = {"spider.bmp", "mak3.bmp"}; 
		for (int i = 0; i < 2; i++)
		{
			pix[i].readBMPFile(fname[i], 1);
			pix[i].setChromaKey(255, 255, 255);
		}
	}
	void setState(int i)
	{
		if (i == 1)
			this->state = DEAD;
		else
		{
			this->state = ALIVE;
		}
	}

	int getState()
	{
		if (this->state == DEAD)
		{
			return 1;
		}
		return 0;
	}

	void changePosition(float dx, float dy)
	{
		float xs = this->pos_X + dx;
		float ys = this->pos_Y + dy;

		if (xs < 580 && xs > 80 && ys > 80 && ys < 420)
		{
			this->pos_X = xs;
			this->pos_Y = ys;
		}
	}

	void die();
	void render();
};

void Spider::die()
{
	this->isMoving = false;
	this->state = DEAD;
}

void Spider::render()
{
	glRasterPos2f(this->pos_X, this->pos_Y);

	if (this->isMoving)
	{
		pix[0].mDraw();
	}
	else
	{
		pix[1].mDraw();
		cout << "Spider is dead!" << endl;
	}
}

Spider spider(Point2(300, 220));

bool isBulletFired = false;
bool isBulletMoving = false;
float bulletX = screenWidth / 2;
float bulletY = 40.0f;
float bulletSpeed = 5.0f;

void updateBullet()
{
	if (isBulletMoving)
	{
		bulletY += bulletSpeed;

		if (bulletY >= screenHeight)
		{
			isBulletMoving = false;
		}
	}
}

class Bullet
{
public:
	float x, y;
	Bullet(float initialX, float initialY) : x(initialX), y(initialY){};

	void render()
	{
		glPushMatrix();
		glTranslatef(x, y, 0.0);

		glColor3f(0.5, 0.1, 0.2);
		glBegin(GL_TRIANGLES);
		glVertex2f(0, 0);
		glVertex2f(-3, -5);
		glVertex2f(3, -5);
		glEnd();

		glBegin(GL_POLYGON);
		glVertex2f(3, -5);
		glVertex2f(-3, -5);
		glVertex2f(-3, -15);
		glVertex2f(3, -15);
		glEnd();
		glPopMatrix();
	};

	void setPosition(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	void changePosition(float dx, float dy)
	{
		float xs = x + dx;
		float ys = y + dy;
	};
};

Bullet bullet(bulletX, bulletY);

void myKB_Handler(unsigned char key, int mx, int my)
{
	switch (key)
	{
	case ' ':
		if (!isBulletFired)
		{
			isBulletFired = true;
			isBulletMoving = true;
			bullet.changePosition(0, 20);
		}
		break;
	}
	glutPostRedisplay();
}

void bullet_movement(int y)
{
	cout << isBulletMoving;
	if (isBulletMoving)
	{
		bullet.setPosition(bullet.x, bullet.y + 10); // Move bullet upwards

		if (bullet.y > screenHeight)
		{
			cout << "phat" << endl;
			isBulletMoving = false;
			bullet.setPosition(bullet.x, 40); // Reset bullet position
		}

		// Check for collision with spider
		if (spider.getState() == 0 && bullet.x >= spider.pos_X && bullet.x <= (spider.pos_X + 40) && bullet.y >= spider.pos_Y && bullet.y <= (spider.pos_Y + 40))
		{
			cout << "phat2";
			spider.die();
			isBulletMoving = false;
			bullet.setPosition(bullet.x, 40); // Reset bullet position
		}

		glutPostRedisplay();
		glutTimerFunc(10, bullet_movement, 0);
	}
}

void pressKeySpecial(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		cout << "not called" << isBulletMoving << endl;
		if (!isBulletMoving)
		{
			cout << " called" << endl;
			isBulletMoving = true;
			glutTimerFunc(10, bullet_movement, 0); // Start bullet movement
		}
		break;

	case GLUT_KEY_LEFT:
		// isBulletMoving = true;

		if (bullet.x - 5 > 20)
		{
			bullet.setPosition(bullet.x - 5, bullet.y);
		}
		break;
	case GLUT_KEY_RIGHT:
		// isBulletMoving = true;

		if (bullet.x + 5 < 620)
		{
			bullet.setPosition(bullet.x + 5, bullet.y);
		}
		break;
	}
}

void updateSpider(int value)
{
	if (spider.getState() == 0) // Check if spider is alive
	{
		// Generate random values for spider movement
		int randomNum = rand() % 19 + (-9);
		float dx = rand() % 71 + (-35); // Random value between -2 and 2 for horizontal movement
		float dy = rand() % 71 + (-35); // Random value between -2 and 2 for vertical movement
		spider.changePosition(dx, dy);
		glutPostRedisplay();
	}

	// Set the timer to call this function again after a certain interval
	glutTimerFunc(500, updateSpider, 0);
}

void releaseKeySpecial(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_UP:
		break;

	case ' ':
		break;
	}

	glutPostRedisplay();
}

void myDisplay(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	updateBullet();

	spider.render();
	bullet.render();
	glFlush();
}

void myInit(void)
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	glViewport(0, 0, screenWidth, screenHeight);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0, screenWidth, 0, screenHeight);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glutTimerFunc(500, updateSpider, 0);

	glEnable(GL_ALPHA_TEST); // in dono ko comment krne se full pic arhi hai with BG
	glAlphaFunc(GL_EQUAL, 1.0);
	// accept fragment if segment alpha = reference alpha i.e. 1.0
	//  or glAlphaFunc(GL_NOTEQUAL,0.0);
	// accept fragment if fragment alpha not = reference alpha i.e. 0.0
}

int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(10, 10);
	glutCreateWindow("Spider Game");

	glutDisplayFunc(myDisplay);
	// PlaySound(L"MarioSong.wav", NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
	glutSpecialFunc(pressKeySpecial);
	glutSpecialUpFunc(releaseKeySpecial);
	glutKeyboardFunc(myKB_Handler);

	myInit();
	// glutIdleFunc(myDisplay);
	// bullet_movement(50);
	glutMainLoop();
}