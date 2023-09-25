#include "canvas.h"

#include <GL/glut.h>
//#include <iostream>
//#include <fstream>
#include <math.h>


#define M_PI  3.14157

// display

//using namespace std;

Canvas cvs(640,480,"Test Canvas");



void display(void)
{
  cvs.setBackgroundColor(1.0, 1.0, 1.0); //background color is white 
  cvs.clearScreen(); //clear screen
  
  cvs.setColor(1.0, 0.0, 0.0); //drawing color is red 
  cvs.setWindow(-10.0, 10.0, -10.0, 10.0);
  cvs.setViewport(10, 460, 10, 460);
  
 // ***************PRACTICING Simple Line DRAWING************//
 
    // call moveTo() and lineTo();
  
  // ***************END RELATIVE DRAWING*********************//
 
  
  
  
  glFlush();
}// end display





int main(int argc, char ** argv)
{
  // the window is opened in the Canvas constructor
  glutDisplayFunc(display);
  glutMainLoop();
}//end main