#include <iostream>
#include <GL/glut.h>
#include "/usr/include/asoundlib.h"
#include <fstream>
#include "SpaceShip.h"
#include <iterator>
int screenWidth = 840;
int screenHeight = 680;

SpaceShip ship(false);
vector<SpaceShip> Enemies;

GLuint LoadImage(char *path)
{
    GLuint Id;
    int width, height, numChannels;
    width = 10;
    height = 10;
    numChannels = 50;
    unsigned char *data = stbi_load(path, &width, &height, &numChannels, 0);

    if (data)
    {
        glGenTextures(1, &Id);
        glBindTexture(GL_TEXTURE_2D, Id);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        stbi_image_free(data);
        return Id;
    }
    else
    {
        printf("Failed to load image\n");
    }
}

void renderBackGround()
{

    glClear(GL_COLOR_BUFFER_BIT);

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, LoadImage("./PNG/jeremy-thomas-E0AHdsENmDg-unsplash.jpg"));

    glBegin(GL_QUADS);
    glTexCoord2f(0.0, 0.0);
    glVertex3f(-1.0, -1.0, 0.0); // bottom left

    glTexCoord2f(1.0, 0.0);
    glVertex3f(1.0, -1.0, 0.0); // bottom right

    glTexCoord2f(1.0, 1.0);
    glVertex3f(1.0, 1.0, 0.0); // top right

    glTexCoord2f(0.0, 1.0);
    glVertex3f(-1.0, 1.0, 0.0); // top left
    glEnd();

    glDisable(GL_TEXTURE_2D);
    glutSwapBuffers();
}

bool checkCollision(Rect rect1, Rect rect2)
{
    printf("rect1.width=>%f rect1.x=>%f rect1.y=>%f rect1.height=>%f\n", rect1.width, rect1.x, rect1.y, rect1.height);
    // cout<<endl;
    printf("rect2.width=>%f rect2.x=>%f rect2.y=>%f rect2.height=>%f\n", rect2.width, rect2.x, rect2.y, rect2.height);
    // cout<<endl;
    bool collision = rect2.width + rect2.x <= rect1.x && rect2.width - rect2.x >= rect1.x && rect2.height - rect2.y >= rect1.y && rect2.height + rect2.y <= rect1.y;
    return (collision);
}

void bullet_movement(int y)
{
    if (!ship.bullets.empty())
    {
        for (int i = 0; i < ship.bullets.size(); i++)
        {
            if (ship.bullets[i])
            {
                Bullet *bullet = ship.bullets[i];
                Rect bulletBox = bullet->getBoundingBox();
                if (bullet->isMoving)
                {
                    bullet->ChangePosition(bullet->yOffset + 0.01);

                    if (bullet->yOffset > 1.0)
                    {

                        // cout << "out" << endl;
                        bullet->isMoving = false;
                        glDeleteTextures(1, &bullet->textureId);
                        delete bullet;
                        ship.bullets.erase(ship.bullets.begin() + i);
                    }
                    else
                    {
                        int j = 0;
                        for (SpaceShip enemy : Enemies)
                        {
                            // Use 'element' inside the loop
                            Rect enemyBox = enemy.getBoundingBox();
                            cout << "ENEMY CHANGEd......." << j << endl;
                            if (checkCollision(bulletBox, enemyBox))
                            {
                                cout << "COLLISION" << endl;
                                // Collision detected, do something (e.g., remove bullet and enemy)
                                bullet->isMoving = false;
                                ship.bullets.erase(ship.bullets.begin() + i);
                                delete bullet;
                                enemy.state = SpaceShip::DEAD;
                                break;
                                // Handle enemy destruction...
                            }
                            j++;
                        }
                    }
                }
            }
        }
        // glutPostRedisplay();
        glutTimerFunc(100, bullet_movement, 0);
    }
}

void moveShip(float xOffset)
{
    ship.changePosition(xOffset);
}

void pressKeySpecial(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_LEFT:
        if (ship.xOffset > -0.9)
        {
            moveShip(ship.xOffset - 0.1);
        }
        break;
    case GLUT_KEY_RIGHT:
        if (ship.xOffset < 0.9)
        {
            moveShip(ship.xOffset + 0.1);
        }
        break;
    case GLUT_KEY_UP:
        if (ship.state == SpaceShip::ALIVE)
        {
            for (int i = 0; i <= 5; i++)
            {
                GLuint textureId = LoadImage("./PNG/Lasers/laserBlue01.png");
                Bullet *b = new Bullet(textureId, ship.xOffset);
                ship.bullets.push_back(b);
            }
            // glutPostRedisplay();
            // glutTimerFunc(10, bullet_movement, 0);
        }
        break;
    case GLUT_KEY_DOWN:
        ship.state = SpaceShip::DEAD;
        glutPostRedisplay();
        break;
    }
}

void timer(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000 / 60, timer, 0);
}

void Round(int number)
{
    cout<<"item created"<<endl;
    for (int i = 0; i < number; i++)
    {
        SpaceShip enemy(true);
        Enemies.push_back(enemy);
    }
}

void myDisplay(void)
{
    // std::cout << "Displaying..." << std::endl;
    GLuint fireId = LoadImage("./PNG/v6pic6d6flcoj9blmchmg1btmk.png");
    GLuint enemyId = LoadImage("./PNG/Enemies/enemyBlack2.png");
    GLuint shipId = LoadImage("./PNG/playerShip1_blue.png");
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // renderBackGround();
    float yvertex = 0.7;
    float xvertex = -0.7;
    int i = 0;
    for (SpaceShip enemy : Enemies)
    {
        float xvertex = xvertex + 0.3;
        if (i % 4 == 0)
        {
            xvertex = -0.7;
            yvertex -= 0.4;
        }
        if (enemy.state == SpaceShip::ALIVE)
        {

            enemy.render(enemyId, xvertex, yvertex);
        }
        else
        {
            enemy.render(fireId, xvertex, yvertex);
        }
        i++;
    }

    if (ship.state == SpaceShip::ALIVE)
    {
        ship.render(shipId, 0.0, 0.0);
    }
    else
    {
        ship.render(fireId, 0.0, 0.0);
    }
    if (!ship.bullets.empty())
    {
        bullet_movement(0);

        for (int i = 0; i < ship.bullets.size(); i++)
        {

            Bullet *bullet = ship.bullets[i];
            if (bullet->isMoving)
            {
                bullet->render();
            }
        }
    }
    // glFlush();glutPostRedisplay();
}

void closeWindow()
{
    exit(0);
}

int main(int argc, char **argv)
{
    Round(8);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(screenWidth, screenHeight);
    // glutInitWindowPosition(30, 30);
    glutCreateWindow("Shooting Stars");
    glutDisplayFunc(myDisplay);
    timer(1); // Get into the loop
    glutSpecialFunc(pressKeySpecial);

    // playSound("Sickick.wav");
    // glutMouseFunc(closeWindow);
    // myInit();
    glutMainLoop();
    return 0;
}