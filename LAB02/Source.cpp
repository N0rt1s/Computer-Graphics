#include <GL/glut.h>
#include <math.h>
// #include <Windows.h>


using namespace std;

int screenWidth = 1000;
int screenHeight = 600;

void initGL() {
    glClearColor(0 / 255.0, 0 / 255.0, 0 / 255.0, 1.0f / 255.0);
}

// code for circle
void circle(GLfloat rx, GLfloat ry, GLfloat cx, GLfloat cy)
{
    glBegin(GL_POLYGON);
    glVertex2f(cx, cy);
    for (int i = 0; i <= 360; i++)
    {
        float angle = i * 3.142 / 180;
        float x = rx * cos(angle);
        float y = ry * sin(angle);
        glVertex2f((x + cx), (y + cy));
    }
    glEnd();
}

void myDisplay(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    // River
    glColor3ub(29, 162, 216);
    glBegin(GL_POLYGON);
    glVertex2d(0, 0); 
    glVertex2d(1000, 0); 
    glVertex2d(1000, 300);
    glVertex2d(0, 300);
    glEnd();


    // Boat
    glColor3ub(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2d(325, 220);
    glVertex2d(400, 220);
    glVertex2d(425, 250);
    glVertex2d(300, 250);
    glEnd();

    glColor3ub(205, 133, 63);
    glBegin(GL_POLYGON);
    glVertex2d(325, 250);
    glVertex2d(400, 250);
    glVertex2d(390, 280);
    glVertex2d(335, 280);
    glEnd();

    glColor3ub(160, 82, 45);
    glBegin(GL_POLYGON);
    glVertex2d(360, 280);
    glVertex2d(370, 280);
    glVertex2d(370, 310);
    glVertex2d(360, 310);
    glEnd();


    glColor3ub(219, 39, 134);
    glBegin(GL_TRIANGLES);
    glVertex2d(300, 290);
    glVertex2d(390, 290);
    glVertex2d(390, 335);
    glEnd();


    //Sun
    glColor3ub(255, 215, 0);
    circle(25, 30, 175, 450);


    // Mountains (right side)
     // First Mountain
    glColor3ub(139, 69, 19); 
    glBegin(GL_TRIANGLES);
    glVertex2d(800, 200);   
    glVertex2d(1000, 350); 
    glVertex2d(1200, 200);  
    glEnd();

    // Second Mountain (starts after the first mountain ends)
    glBegin(GL_TRIANGLES);
    glVertex2d(600, 200);   
    glVertex2d(800, 350); 
    glVertex2d(1000, 200);  
    glEnd();


    glFlush();
}



int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(screenWidth, screenHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Noor's Boat scene");

    glOrtho(0, screenWidth, 0, screenHeight, -1, 1); 

    glutDisplayFunc(myDisplay);
    glutMainLoop();
    return 0;
}