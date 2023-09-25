#define STB_IMAGE_IMPLEMENTATION
#include <GL/glut.h>
#include <iostream>
#include <stdio.h>
#include "pixMap.h"
#include "stb_image.h"
#include <vector>

using namespace std;

class Bullet
{
public:
    float xOffset, yOffset;
    bool isMoving;
    GLuint textureId;
    Bullet(GLuint textureId, float x);
    void ChangePosition(float dy);
    void render();
};

class SpaceShip
{
public:
    float xOffset, yOffset;
    bool isEnemy;
    vector<Bullet *> bullets;
    enum State
    {
        ALIVE,
        DEAD
    } state;

    RGBApixmap pix[2];

    SpaceShip(bool isenemy);

    void changePosition(float dx);

    void setState(State s);

    void render(GLuint textureId, float xOffset,float y);
};

Bullet::Bullet(GLuint Id, float x)
{
    this->textureId = Id;
    this->isMoving = true;
    this->yOffset = -0.9;
    this->xOffset = x;
}

void Bullet::ChangePosition(float dy)
{
    cout << "called";
    this->yOffset = dy;
    // glutPostRedisplay();
}
void Bullet::render()
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, this->textureId);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glTranslatef(this->xOffset, this->yOffset, 0);

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-0.01, 0.01, 0); // top left
    glTexCoord2f(1.0, 0.0);
    glVertex3f(0.01, 0.01, 0); // top right
    glTexCoord2f(1.0, 1.0);
    glVertex3f(0.01, 0.08, 0); // bottom right
    glTexCoord2f(0.0, 1.0);
    glVertex3f(-0.01, 0.08, 0); // bottom left
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glutSwapBuffers();
}
SpaceShip::SpaceShip(bool isenemy)
{
    this->isEnemy = isenemy;
    this->state = ALIVE;
    this->yOffset = -1.0;
    this->xOffset = 0.0;
}

void SpaceShip::render(GLuint textureId, float x,float y)
{
    if (this->isEnemy)
    {
        this->xOffset=x;
        this->yOffset=y;
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureId);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glTranslatef(this->xOffset, this->yOffset, 0);

        glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-0.1, 0.1, 0); // top left
        glTexCoord2f(1.0, 0.0);
        glVertex3f(0.1, 0.1, 0); // top right
        glTexCoord2f(1.0, 1.0);
        glVertex3f(0.1, 0.2, 0); // bottom right
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-0.1, 0.2, 0); // bottom left
        glEnd();

        glDisable(GL_TEXTURE_2D);
        glutSwapBuffers();
    }
    else
    {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, textureId);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

        glTranslatef(this->xOffset, this->yOffset, 0);

        glBegin(GL_QUADS);
        glTexCoord2f(0.0, 0.0);
        glVertex3f(-0.1, 0.1, 0); // top left
        glTexCoord2f(1.0, 0.0);
        glVertex3f(0.1, 0.1, 0); // top right
        glTexCoord2f(1.0, 1.0);
        glVertex3f(0.1, 0.2, 0); // bottom right
        glTexCoord2f(0.0, 1.0);
        glVertex3f(-0.1, 0.2, 0); // bottom left
        glEnd();

        glDisable(GL_TEXTURE_2D);
        glutSwapBuffers();
    }
}

void SpaceShip::changePosition(float dx)
{
    if (this->state == ALIVE)
    {
        this->xOffset = dx;
        // glTranslatef(this->xOffset, -1.0, 0);
        // glutPostRedisplay();
    }
}

void SpaceShip::setState(State s)
{
    this->state = s;
}
