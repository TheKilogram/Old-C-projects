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
 

#include <GL/glut.h>
#include <stdlib.h>
#include <iostream>
#include <math.h>


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
void midpoint_circle();



// Simple structure for a point
struct Point
{
    int x;
    int y;
    Point() : x(-1), y(-1) {}
    Point(int x, int y) : x(x), y(y) {}
};


// Keeps track of what I am drawing currently.
enum DrawingMode { NONE, LINE,Circle};
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
	case Circle:
	midpoint_circle();
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
    drawing_mode =  Circle;
    num_points=0;

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

	case Circle:
	points[num_points++] = Point(x, y);
	if (num_points == 2) {
	  
	    num_points = 0;

	    
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
    // Or, even glColor3f() may appear there, if you want o change the color
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
    //glBegin(GL_LINES);
    //glVertex2d(points[0].x, win_h - points[0].y);
    //glVertex2d(points[1].x, win_h - points[1].y);
   // glEnd();
/////////////////////////////////////////////////////////////////////////////////////////////////	



glBegin(GL_POINTS);

glVertex2d(points[1].x, win_h - points[1].y);//draw the last point just in case the loop does not hit it
    
    //initialization/ decleration of points
    int y;
    int y0=points[0].y;
    int y1=points[1].y;
    int x0=points[0].x;
    int x1=points[1].x;

    //bool tells the program to go to the main algorithm or not
 	bool dontGo=false;


//if it is a horizontal line, only change the x values
 if(y0==y1)
{
	for(int x=x0; x<x1; x++)
	{
		glVertex2d(x, win_h - y0);
	}
	dontGo=true;	//dont go to the main algorythm
}
//if it is a vertical line, only change the y values
else if(x1==x0)
{
	for(int ycur=y0; ycur<y1; ycur++)
	{
		glVertex2d(x0, win_h - ycur);
	}
	dontGo=true;	//dont go to the main algorythm

}
//initializes the case_ variable used for the switch statment
int case_=0;

//if the line is the second mouse click is to the left of the first
if(x1<x0)
{
	//swap the first x with the second x
	int tmp=x0;
	x0=x1;
	x1=tmp;

	//swap the first y with the second y
	tmp=y0;
	y0=y1;
	y1=tmp;
}


//if the slope is steaper than 1 but less than infinity
if(x1-x0<y1-y0 && y0<y1)
{
	//swap the first x value with the first y value
	int tmp=x0;
	x0=y0;
	y0=tmp;
	//swap the second x value with the second y value
	tmp=x1;
	x1=y1;
	y1=tmp;

	//set the case to 1 (for the later switch statment)
	case_=1;


}
//if the slope is steaper than -1 but less than infinity
else if (-(x1-x0)> y1-y0 && y0>y1)
{
	//negate the y values
	y0= -y0;
	y1= -y1;

//swap the first x value with the first y value
int tmp=x0;
x0=y0;
y0=tmp;

//swap the second x value with the second y value
tmp=x1;
x1=y1;
y1=tmp;

//set the case to 2 (for the later switch statment)
case_=2;
}

//if slope is larger than -1 but less than 0
else if (-(x1-x0)<y1-y0 && y0>y1)
{
	//negate the y values
	y0= -y0;
	y1= -y1;
	case_=3;

}
//sets y to the first points y value 
y=y0;

//if the line is not horizontal or vertical
if(dontGo==false)
{
	//calculates the d value that tells why to incramet or not
int d=2*((y0 - y1)*(x0 + 1) + (x1 - x0)*(y0 + 0.5) + (x0* y1) - (x1 * y0)); 

    for (int xCur=x0;xCur<x1;xCur++)
    {
    	//switch statment that tells opengl to draw where nessisary
    	switch(case_)
    	{
		
		//this is the base, slope is between 0 and 1
    		//thus it prints 1 pint for every x value and uses the y value calculated by seeing if d is <0
    	case 0 : glVertex2d(xCur, win_h - y);
    	break;

    	//this is slope greater than 1 but less than infinity
    	//thus prints 1 point for every y value and sees if x should change based on the result of d
    	case 1 : glVertex2d(y, win_h - xCur);
    	break;

    	//this is slope greater than -1 but less than infinity
    	//thus prints 1 point for every y value and sees if x should change bases on the resut of d
    	case 2: glVertex2d(y, win_h - (-xCur));
    	break;

    	//this is slope between -1 and 0
    	//thus prints 1 point for every x value and sees if y should change based on the result of d
    	case 3: glVertex2d(xCur, win_h - (-y));
    	break;

    	}
 
 	//if the d value is less than 0
    if(d<0)
    {
    	//increment y by 1
    	//and calculete the next d value
    	y++;
    	d=d+2*(y0-y1)+2*(x1-x0);
		
    }	
    //if d is greater than or equal 0
    else
    {
    	//calculate d next
    	d=d+2*(y0-y1);
    	
    }
    

}
}

//end of drawing
glEnd();

}
//function calculates and draws a midpoint circle
void midpoint_circle(){
	//sets color to red
glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);

//init of center point
int cx=points[0].x;
int cy=points[0].y;

glVertex2d(cx,win_h-cy); //draw center point

//calculates the radius length
float r=sqrt(((points[1].x-points[0].x)*(points[1].x-points[0].x))+((points[1].y-points[0].y)*(points[1].y-points[0].y)));
//sets the first y value to the radius
int y=r;
int d=(5-4*r);//mutiplied by 4 to get rid of floating point numbers



//loops to calculat 1/8 th of the circle then uses that to get the rest of the circle
for(int x=0;x<y;x++)
{
//prints 1/8 th segments of the circle to add up to a full circle (after the loop is done)
glVertex2d( (cx+x) , win_h - (cy+y));//bace case
glVertex2d( (cx+x) , win_h -  (cy-y));
glVertex2d( (cx-x) , win_h -  (cy+y));
glVertex2d( (cx-x) , win_h -  (cy-y));
glVertex2d( (cx+y) , win_h -  (cy+x));
glVertex2d( (cx-y) , win_h -  (cy+x));
glVertex2d( (cx+y) , win_h -  (cy-x));
glVertex2d( (cx-y) , win_h -  (cy-x));

//if d<0 then keep y the same
	if(d<0)
	{
		d=d+(4*(2*x))+12; //mutiplied by 4 to get rid of floating point numbers
	}
	//if d>0 minus y by 1
	else
	{
		d=d+(4*(2*(x-y)))+20;	//mutiplied by 4 to get rid of floating point numbers
		y=y-1;
	}
}

//end drwaing
glEnd();
}




      
