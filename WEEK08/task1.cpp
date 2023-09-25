#include "canvas.h"
#include <GL/glut.h>

// Constructor to initialize the Canvas
Canvas::Canvas(int width, int height, char* windowTitle) {
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(width, height);
    // glutCreateWindow(windowTitle);
}

// Method to set the background color
void Canvas::setBackgroundColor(float r, float g, float b) {
    glClearColor(r, g, b, 0.0);
}

// Method to clear the screen
void Canvas::clearScreen() {
    glClear(GL_COLOR_BUFFER_BIT);
}

// Method to set the drawing color
void Canvas::setColor(float r, float g, float b) {
    glColor3f(r, g, b);
}

// Method to set the window dimensions
void Canvas::setWindow(float l, float r, float b, float t) {
    gluOrtho2D(l, r, b, t);
}

// Method to set the viewport dimensions
void Canvas::setViewport(int l, int r, int b, int t) {
    glViewport(l, b, r-l, t-b);
}
