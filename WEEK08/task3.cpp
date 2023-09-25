// #include "canvas.h"
#include "task1.cpp"
#include <GL/glut.h>

Canvas cvs(640, 480, "Relative Drawing");

void drawHouse() {
    //square base of the house
    cvs.setColor(1.0, 0.0, 0.0);  
    glBegin(GL_QUADS);
    glVertex2f(-5, -5);
    glVertex2f(5, -5);
    glVertex2f(5, 5);
    glVertex2f(-5, 5);
    glEnd();

    //roof of the house
    cvs.setColor(0.0, 0.0, 1.0);  
    glBegin(GL_TRIANGLES);
    glVertex2f(-5, 5);
    glVertex2f(5, 5);
    glVertex2f(0, 10);
    glEnd();
}

void display(void) {
    cvs.setBackgroundColor(0.0, 0.0, 0.0);  
    cvs.clearScreen();  

    cvs.setWindow(-10.0, 10.0, -10.0, 10.0);  
    cvs.setViewport(10, 460, 10, 460);  

    drawHouse();  

    glFlush(); 
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutCreateWindow("House"); 
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
