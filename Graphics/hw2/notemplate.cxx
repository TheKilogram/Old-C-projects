/*********************************************************************
 *  CMPSC 457                                                        *
 *  Template code for HW 2                                           *
 *  February 6, 2017                                                 *
 *  Sukmoon Chang                                                    *
 *  sukmoon@psu.edu                                                  *
 *                                                                   *
 *                                                                   *
 *  Description:                                                     *
 *                                                                   *
 *  This is a template code for homework 2.                          *
 *  It takes two points from users through left button click.        *
 *  Then, it draws a line between the two points using               *
 *  Midpoint Algorithm (not implemented in this template).           *
 *                                                                   *
 *                                                                   *
 *  User interface:                                                  *
 *                                                                   *
 *  1. When it starts, its drawing mode is set to NONE.              *
 *     To draw a line, press 'l' to put it in LINE drawing mode.     *
 *     Then, select two points by clicking left mouse button         *
 *     The program draws a line between the two points.              *
 *  2. You can also input the points using keyboard.                 *
 *     To do this, press 'k' and type the coordinates                *
 *     on the terminal (NOTE: This feature is for grading purpose    *
 *     only and has not been tested extensively)                     *
 *  3. To quit the program, press 'q'.                               *
 *  4. Any other keys that are not used to switch drawing modes      *
 *     will put the drawing mode to NONE                             *
 *********************************************************************/

 /*
 Jonathan Engel
 Homework 2
 Part 1 (line program)
 CMPSC_457
 */


#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>


using std::cin;
using std::cerr;
using std::endl;
using namespace std;


// callbacks for glut (see main() for what they do)
void reshape(int w, int h);
void display();
void mouse(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);


// helpers
void init();
void addPoint(int x, int y);
void keyboard_input();
void midpoint_line();



// Simple structure for a point
struct Point
{
    int x;
    int y;
    Point() : x(-1), y(-1) {}
    Point(int x, int y) : x(x), y(y) {}
};


// Keeps track of what I am drawing currently.
enum DrawingMode { NONE, LINE };
DrawingMode drawing_mode = NONE;



// Initial window size
int win_w = 512;
int win_h = 512;


// For lines, 2 points will do.
Point points[2];

// Used to keep track of how many points I have so far
int num_points;



// OpenGL/glut programs typically have the structure shown here,
// although with different args and callbacks.
//
// You should not need to modify main().
// If you want to modify it, do it at your own risk.
//
// For complete description of each glut functions used, see
// glut manual page.
int main(int argc, char* argv[])
{
    // initialize glut
    glutInit(&argc, argv);

    // use double buffering with RGB colors
    // double buffer removes most of the flickering
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    // set window size and position
    glutInitWindowSize(win_w, win_h);
    glutInitWindowPosition(100, 100);

    // now, create window with title "Scan Conversion"
    glutCreateWindow("Scan Conversion");


    // other stuffs like background color, viewing, etc will be
    // set up in this function.
    init();


    // register callbacks for glut
    glutDisplayFunc(display);   // for display
    glutReshapeFunc(reshape);   // for window move/resize
    glutMouseFunc(mouse);       // for mouse buttons
    glutKeyboardFunc(keyboard); // for keyboard


    // start event processing, i.e., accept user inputs
    glutMainLoop();

    return 0;
}



void init()
{
    // set background color to black
    glClearColor(0.0, 0.0, 0.0, 0.0);

    // create viewing volume
    // -- will use orthogonal projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, win_w-1, 0.0, win_h-1, -1.0, 1.0);

}



// called when the window is resized/moved (plus some other cases)
void reshape(int w, int h)
{
    win_w = w;
    win_h = h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, win_w-1, 0.0, win_h-1, -1.0, 1.0);

    glViewport(0, 0, win_w, win_h);
}


// called when the window needs to be redrawn
void display()
{
    // buffer is a raster array provided by OpenGL
    // recall that we are using 2 buffers (double buffering)
    // they are called front buffer and back buffer
    // what you see on the screen is the content of front buffer
    // what you draw is drawn only on back buffer


    // clear back buffer with background color that is set in init()
    glClear(GL_COLOR_BUFFER_BIT);

    // now, draw on back buffer just cleared
    switch (drawing_mode) {
    case LINE:
	midpoint_line();
	break;
    default:
	break;
    }

    // swap the buffers.
    // - all the drawing is done on the back buffer
    // - once drawing is done on the back buffer,
    //       you need to display the content of the back buffer.
    // - swapping buffers means swapping back buffer with front buffer
    //       so that front buffer becomes back buffer and
    //       back buffer becomes front buffer.
    // - once back buffer becomes front buffer, the content of it will be
    //       displayed on the screen, so you can see it.
    glutSwapBuffers();
}


// called when a mouse event (button pressed/released/moved/dragged) occurs
// in glut,
//     mouse buttons are represented as
//           GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, and GLUT_RIGHT_BUTTON
//     status of mouse buttons are represented as
//           GLUT_UP and GLUT_DOWN
//     (x, y) is the mouse position when the event occurred
void mouse(int button, int state, int x, int y)
{
    switch (button) {
    case GLUT_LEFT_BUTTON:
	if (state == GLUT_DOWN)
	    addPoint(x, y);
	break;
    default:
	break;
    }
}


// called when a keyboard event (key typed) occurs
void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 'q':  // quit the program
	exit(0);
    case 'l':  // draw a line
	drawing_mode = LINE;
	num_points = 0;
	break;
    case 'c':  // draw a circle; not implemented
	break;
    case 'k':  // for grading purpose only--do not modify
	keyboard_input();
	num_points = 0;
	break;
    default:
	drawing_mode = NONE;
	break;
    }
}


// add the point just selected by mouse button
void addPoint(int x, int y)
{
    switch (drawing_mode) {
    case LINE:  // save the points until we have 2 points
	points[num_points++] = Point(x, y);
	if (num_points == 2) {
	    // we have 2 points now, so we can draw a line

	    // reset the num_points to 0 for next line
	    num_points = 0;

	    // tell glut that the current window needs to be redisplayed.
	    // glut will then redisplay the current window.
	    // this means display() callback will be called.
	    // display() in turn will draw a midpoint line on back buffer
	    //   and swap the back buffer with the front buffer
	    // by swapping the buffers, the back buffer becomes visible,
	    //   ie, displayed on the window
	    glutPostRedisplay();
	}
	break;
    default:
	break;
    }
}


// for grading purpose only
// do not modify this function
// do not use this function
//   -- it's not tested fully and does not work correctly
void keyboard_input()
{
    if (drawing_mode == NONE) {
	cerr << "Select drawing mode first...\n";
	return;
    }

    int x, y;
    num_points = 0;
    for (int i=0; i<2; i++) {
	cerr << "Enter point " << i << " => ";
	cin >> x >> y;
	cerr << endl;
	addPoint(x, y);
    }
}



// a helper function to draw a line
// you need to modify this function for midpoint algorithm
// anything you draw here goes to back buffer
void midpoint_line()
{
    // select a line color of your choice
    glColor3f(1.0, 0.0, 0.0);

    // now, draw a line between 2 end points
    // you need to draw a line using incremental midpoint algorithm
    //     without any floating point calculations, so remove
    //     next 4 lines and implement incremental midpoint algorithm here.
    //
    // you cannot use GL_LINES for this assignment.
    // you must use GL_POINTS instead.
    //
    // To draw a pixel (x,y) with the color you set above, use
    //         glBegin(GL_POINTS);
    //            glVertex2d(x, y);
    //         glEnd();
    // Any number of glVertex2d() may appear between glBegin() and glEnd()
    // Or, even glColor3f() may appear there, if you want to change the color
    //      of each point.
    // Also, any c++ code can appear between glBegin() and glEnd()
    //
    // Note: GL provides commands for drawing.
    //       glut provides gui, including window on which you are drawing.
    //       The origin (0,0) of the coordinate system is
    //          at bottom left in GL and
    //          at top left in glut.
    //       You must compensate the difference between the coordinate
    //       systems used by GL and glut, when drawing.
    glBegin(GL_POINTS);
      glVertex2d(points[0].x, win_h - points[0].y); // Draw first point
      glVertex2d(points[1].x, win_h - points[1].y); // Draw second point



      //Changed variable names to make it a bit more readable
      int init_x = points[0].x;
      int end_x = points[1].x;

      int init_y = points[0].y;
      int end_y = points[1].y;


      //If the x value goes from right to left ("negative x") flip the values to work with algorithm
      if (end_x < init_x){
        swap(init_x, end_x);
        swap(init_y, end_y);
      }

      //Conditions to alter the output in the main loop based on the slope (see below if statement)
      bool cond_1 = false;
      bool cond_2 = false;
      bool cond_3 = false;

      //The purpose of the below 'if' statements is to make sure that the slope of the lines remain within 0 and 1.
      //The algorithm is designed assuming that 0 < m < 1: Do nothing this statement
      if ((init_y < end_y) && (end_x - init_x > end_y - init_y)){
        //Do nothing
      }
      //If 1 < m < inf, swap x and y values to bring it back within 0 < m < 1, then in loop change x and y.
      else if ((init_y < end_y) && (end_x - init_x < end_y - init_y)){
        swap(init_x, init_y);
        swap(end_x, end_y);
        cond_1 = true;
      }
      //If -1 < m < 0, multiply by -1 to calculate line, then multiply again to print the line.
      else if ((init_y > end_y) && (-1*(end_x - init_x) < end_y - init_y)){
        init_y = -1*init_y;
        end_y = -1*end_y;
        cond_2 = true;
      }
      //If -1 < m < inf, multiply by -1 AND swap x and y, later in loop swap again and multiply again.
      else if ((init_y > end_y) && (-1*(end_x - init_x) > end_y - init_y)){
        init_y = -1*init_y;
        end_y = -1*end_y;
        swap(init_x, init_y);
        swap(end_x, end_y);
        cond_3 = true;
      }

      //Assign y as y0
      int y = init_y;
      //Used to determine which pixel to turn on.
      int d = 2*((init_y - end_y)*(init_x + 1) + (end_x - init_x)*(init_y + 0.5) + (init_x*end_y) - (end_x*init_y));

      //Main loop
      for (int x = init_x; x < end_x; x++){
        //Depending on the condition from earlier, modify the 'print' function.
        if (cond_1){
          glVertex2d(y, win_h - x);
        }
        else if (cond_2){
          glVertex2d(x, win_h - (-1*y));
        }
        else if (cond_3){
          glVertex2d(y, win_h - (-1*x));
        }
        else{
          glVertex2d(x, win_h - y);
        }
        //Depending on the sign of d, keep y the same, or incremant by 1.
        if (d < 0){
          y = y+1;
          d = d + 2*(init_y - end_y) + 2*(end_x - init_x);
        }
        else{
          d = d + 2*(init_y - end_y);
        }
      }
    glEnd();
}
