/*************************************************************************
 *  CMPSC 457                                                            *
 *  Template code for HW 4                                               *
 *  March 22, 2017                                                       *
 *  Sukmoon Chang                                                        *
 *  sukmoon@psu.edu                                                      *
 *                                                                       *
 *                                                                       *
 *  Description:                                                         *
 *                                                                       *
 *  This is a template code for homework 4.                              *
 *  It reads the vertex and face information of the triangles            *
 *     of a model from Wavefront .obj format.                            *
 *  Then, it draws the model by drawing all triangles one by one.        *
 *                                                                       *
 *  For vectors and matrices, it uses glm library.                       *
 *  - glm library conforms to the OpenGL's shading language (GLSL)       *
 *  - To understand how glm library works, see                           *
 *        www.khronos.org/registry/OpenGL/specs/gl/GLSLangSpec.4.20.pdf  *
 *  - Especially                                                         *
 *        5.10 Vector and Matrix Operations                              *
 *  - glm also provides,                                                 *
 *        glm::cross(u, v)  <= returns cross product of vectors u and v  *
 *        glm::normalize(v) <= returns unit vector of v                  *
 *    that works similar to                                              *
 *        glm::dot(u, v)    <= returns dot product of vectors u and v    *
 *    as explained in 5.10                                               *
 *                                                                       *
 *                                                                       *
 *  User interface:                                                      *
 *                                                                       *
 *  1. When it starts, its shading mode is set to WIREFRAME.             *
 *     WIREFRAME mode is already implemented for your reference.         *
 *  2. For flat shading, press 'f' to put it in FLAT shading mode.       *
 *  3. For Z-buffering, press 'z' to put it in Z-buffering mode          *
 *     while the program is in FLAT shading mode.                        *
 *     Z-buffering does not work for WIREFRAME mode.                     *
 *  4. Press 'w' to go back to WIREFRAME mode.                           *
 *  5. To quit the program, press 'q'.                                   *
 *************************************************************************/


#include <GL/glut.h>
#include <glm/glm.hpp>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include "model.h"

#include <iterator>
#include <algorithm>
#include <vector>
//my include
#include <math.h>

using namespace std;

// callbacks for glut (see main() for what they do)
void reshape(int w, int h);
void display();
void mouse(int button, int state, int x, int y);
void keyboard(unsigned char key, int x, int y);




// helpers
void init(int model_number);

void draw_point(int x, int y, Color c);
void draw_line(int x0, int y0, int x1, int y1, Color c);
void draw_model();


void draw_model_wireframe();
void draw_model_flat_shading();


vec3 world2screen(vec3 v);

bool is_visible(const vec3& p0, const vec3& p1, const vec3& p2);
bool is_inside(const int x, const int y,
	       const vec3& p0, const vec3& p1, const vec3& p2, 
	       float& alpha, float& beta, float& gamma);



std::ostream& operator<< (std::ostream& out, const vec3& v);


    
// Keeps track of current shading mode.
enum ShadingMode { WIREFRAME, FLAT };
ShadingMode shading_mode = WIREFRAME;


// Initial window size
int win_w = 512;
int win_h = 512;


// z-buffer
float *zbuffer { nullptr };
bool zbuffer_on { false };


// Model to render
Model *model{ nullptr };


// Camera position
vec3 cam { 0.0, 0.0, 10.0 };
vec3 light_dir { 0.0, 0.0, 1.0 };   // must be a unit vector


// colors
vec3 c_ambient { 0.0, 0.0, 0.0 };   // ambient light
vec3 c_diffuse { 1.0, 1.0, 1.0 };   // diffuse reflectance
vec3 c_light   { 1.0, 1.0, 1.0 };   // directional light




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
    if (argc > 2) {
	std::cerr << "Usage: ./template [MODEL=model_number]\n"
		  << "  model_number\n"
		  << "    1: test (default)\n"
		  << "    2: sphere\n"
		  << "    3: teapot\n"
		  << "    4: head\n"
		  << "    5: diablo\n"
		  << "    6: beethoven\n";
	std::exit(1);
    }
	    
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
    init(atoi(argv[1]));

    // register callbacks for glut
    glutDisplayFunc(display);   // for display
    glutReshapeFunc(reshape);   // for window move/resize
    glutMouseFunc(mouse);       // for mouse buttons
    glutKeyboardFunc(keyboard); // for keyboard

    // start event processing, i.e., accept user inputs
    glutMainLoop();

    if (zbuffer) delete [] zbuffer;
    if (model)   delete [] model;

    return 0;
}




/*****************
 *   callbacks   *
 *****************/


// called when the window is resized/moved (plus some other cases)
void reshape(int w, int h)
{
    win_w = w;
    win_h = h;

    // recreate zbuufer
    if (zbuffer)
	delete [] zbuffer;
    zbuffer = new float[win_w * win_h];

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, win_w - 1, 0.0, win_h - 1, -1.0, 1.0);

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
    draw_model();
 

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
}


// called when a keyboard event (key typed) occurs
void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 'q':  // quit the program
        exit(0);
    case 'f':  // flat shading
        std::cerr << "shading_mode changed to FLAT\n";
        shading_mode = FLAT;
        glutPostRedisplay();
        break;
    case 'z':
	if (shading_mode == WIREFRAME) {
	    std::cerr << "WIREFRAME mode does not use zbuffer\n";
	}
	else {
	    std::cerr << "turning zbuffer " << (zbuffer_on ? "off\n" : "on\n");
	    zbuffer_on = !zbuffer_on;
	    glutPostRedisplay();
	}
	break;
    case 'w':
        std::cerr << "shading_mode changed to WIREFRAME\n";
        shading_mode = WIREFRAME;
        glutPostRedisplay();
        break;
    }
}




/**************
 *   helpers  *
 **************/


void init(int model_number)
{
    // set background color to black
    glClearColor(0.0, 0.0, 0.0, 0.0);

    // create viewing volume
    // -- will use orthogonal projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, win_w - 1, 0.0, win_h - 1, -1.0, 1.0);

    // create zbuffer
    zbuffer = new float[win_w * win_h];

    // load model to render
    switch (model_number) {
    case 1:
	//model = new Model("../models/test.obj");
	model = new Model("../models/test.obj");
	break;
    case 2:
	model = new Model("../models/sphere-223.obj");
	break;
    case 3:
	model = new Model("../models/teapot.obj");
	break;
    case 4:
	model = new Model("../models/african_head.obj");
	break;
    case 5:
	model = new Model("../models/Diablo.obj");
	break;
    case 6:
	model = new Model("../models/beethoven.obj");
	break;
    }
}


void draw_point(int x, int y, Color c)
{
    glBegin(GL_POINTS);
    {
        glColor3f(c.r, c.g, c.b);
        glVertex2d(x, y);
    }
    glEnd();
}


void draw_line(int x0, int y0, int x1, int y1, Color c)
{
    glBegin(GL_LINES);
    glColor3f(c.r, c.g, c.b);
    glVertex2d(x0, y0);
    glVertex2d(x1, y1);
    glEnd();
}


void draw_model()
{
    switch (shading_mode) {
    case WIREFRAME:
        draw_model_wireframe();
        break;
    case FLAT:
        draw_model_flat_shading();
        break;
    }
}


void draw_model_wireframe()
{
    int cnt = 0;

    // pick a color for wires
    Color color(1.0, 0.0, 0.0);

    /*********************************************************/
    /*            Implement wirefame here                    */
    /*                                                       */
    /*  Here is the rough algorithm                          */
    /*                                                       */
    /*   - for each triangle                                 */
    /*     - if it is visible                                */
    /*       - convert each vertex in world coord sys        */
    /*         to corresponding vertex in screen coord sys   */
    /*       - draw 3 lines connecting the 3 vertices        */
    /*       - cnt++ (count number of triangles drawn)       */
    /*                                                       */
    /*********************************************************/

    //for loop that runst through the number of triangles in the modle
    for(int i=0;i< model->num_faces();i++)
    {
    	//if the triangle with the 3 vertexes is visible aka the eye vecor and the normal vector have a dot product greaterthan or equal to 0
    if(is_visible((model->vertex(model->face(i)[0])),(model->vertex(model->face(i)[1])),(model->vertex(model->face(i)[2]))))
    	{
    		//translates the points fron 3D world space to the 2D screan space
    		int x0=world2screen(model->vertex(model->face(i)[0])).x;
    		int x1=world2screen(model->vertex(model->face(i)[1])).x;
    		int x2=world2screen(model->vertex(model->face(i)[2])).x;

    		int y0=world2screen(model->vertex(model->face(i)[0])).y;
    		int y1=world2screen(model->vertex(model->face(i)[1])).y;
    		int y2=world2screen(model->vertex(model->face(i)[2])).y;
    	
    		//draws the three lines for the current triangle if  it i visible
    		draw_line(x0,y0,x1,y1,color);
    		draw_line(x1,y1,x2,y2,color);
    		draw_line(x0,y0,x2,y2,color);

    		//adds to the number of triangles drawn
 			cnt++;
    	}
    }
    



	

    std::cerr << "draw_model_wireframe: drawn " << cnt << " / " << model->num_faces() << " triangles\n";
}


void draw_model_flat_shading()
{
    int cnt = 0;
    
    /*********************************************************************/
    /*                  Implement flat shading here                      */
    /*                                                                   */
    /*                                                                   */
    /*  Here is the rough algorithm                                      */
    /*                                                                   */
    /*   - initialize z-buffer with -infinity                            */
    /*   - for each triangle that is visible                             */
    /*     - calculate face normal in world coord sys                    */
    /*     - calculate face color in world coord sys                     */
    /*       (if n_hat.l_hat is not positive, skip the triangle          */
    /*     - cnt++ (count number of triangles drawn)                     */
    /*     - convert each vertex in world coord sys                      */
    /*         to corresponding vertex in screen coord sys               */
    /*     - for each pixel inside the triangle (i.e., screen coord sys) */
    /*       - if z_buffering is on                                      */
    /*         - calculate z-coord of the pixel in world coord sys       */
    /*           (Note that world2screen() keeps                         */
    /*            the z coordinates unchanged from world coord sys)      */
    /*         - if z-coord of the pixel is closer than current z-value  */
    /*           - update z-buffer                                       */
    /*           - draw the pixel                                        */
    /*         - else                                                    */
    /*           - skip the pixel                                        */
    /*       - else                                                      */
    /*         - draw the pixel                                          */
    /*                                                                   */
    /* Do not implement everything inside this function.                 */
    /* - You should feel free to define helper functions as needed       */
    /*   so that the code is understandable and debuggable               */
    /*                                                                   */
    /*********************************************************************/

	//initializes the z buffer to the size of the raster array
    zbuffer=new float[win_h*win_w];
    //makes every element in the z buffer array negitive infinity
    for(int w=0;w<win_w*win_h;w++){
	zbuffer[w]=-(std::numeric_limits<float>::infinity());
}

	//for loop that runst through the number of triangles in the modle
    for(int i=0;i<model->num_faces();i++)
    {
    		//gets the tree points of the current triangle
    		vec3 p0=model->vertex(model->face(i)[0]);
    		vec3 p1=model->vertex(model->face(i)[1]);
    		vec3 p2=model->vertex(model->face(i)[2]);

    		//if the triangle with the 3 vertexes is visible aka the eye vecor and the normal vector have a dot product greaterthan or equal to 0
    	 if(is_visible(p0,p1,p2))
    	{
    		//calculates the normal vector for the triangle
    		vec3 N=glm::cross(p1-p0, p2-p0);
    	
    	//if the eye vector and normal vector have a dot product that is greater than or equal to 0 then something will be drawn
    	if(glm::dot(glm::normalize(N), glm::normalize(light_dir))>=0)
    	{
    		//adds to the counter that counts how many triangles are drawn
    		cnt++;

    		//translates the points fron 3D world space to the 2D screan space
    		int x0=world2screen(model->vertex(model->face(i)[0])).x;
    		int x1=world2screen(model->vertex(model->face(i)[1])).x;
    		int x2=world2screen(model->vertex(model->face(i)[2])).x;

    		int y0=world2screen(model->vertex(model->face(i)[0])).y;
    		int y1=world2screen(model->vertex(model->face(i)[1])).y;
    		int y2=world2screen(model->vertex(model->face(i)[2])).y;

    		//initializes the max/min x and y for the box around the triangle we are evaluating
    		int xmax=x0;
    		int ymax=y0;
    		int xmin=x0;
    		int ymin=y0;

    		//calculates the max/min x and y for the box around the triangle we are calculating
    		if(x1>x0 && x1>=x2)
    		{
    			xmax=x1;
    		}
    		else if(x2>x0 && x2>=x1)
    		{
    			xmax=x2;
    		}
    		if(y1>y0 && y1>y2)
    		{
    			ymax=y1;
    		}
    		else if(y2>y0 && y2>=y1)
    		{
    			ymax=y2;
    		}
    		if(x1<x0 && x1<=x2)
    		{
    			xmin=x1;
    		}
    		else if(x2<x0 && x2<=x1)
    		{
    			xmin=x2;
    		}
    		if(y1<y0 && y1<=y2)
    		{
    			ymin=y1;
    		}
    		else if(y2<y0 && y2<=y1)
    		{
    			ymin=y2;
    		}

    		//double four loop goes through every element in the box arount the triangle we are evaluating
    		for(int j=xmin;j<xmax;j++)
    		{
    			for(int k=ymin;k<ymax;k++)
    			{
    				//initializes the areas in the triangle A= total area A0-2 are for the areas inside the triangle
    				float A,A0,A1,A2;
    					//calculates the areas for the triangle being evaluated
    					A=((x1-x0)*(y2-y0)-(x2-x0)*(y1-y0))/2;
    					A0=((x1-j)*(y2-k)-(x2-j)*(y1-k))/2;
    					A1=((j-x0)*(y2-y0)-(x2-x0)*(k-y0))/2;
    					A2=((x1-x0)*(k-y0)-(j-x0)*(y1-y0))/2;

    					//initializes alfa beta and gama which is used to determin if the point we are looking at is in the triangle
    					float alfa, beta, gama;
    					//calulates alfa beta gama as a ratio of areas
    					alfa=A0/A;
    					beta=A1/A;
    					gama=A2/A;

    					//calculates the color of the pixle based on the light direction and intesity as well as ambiant light
    					Color c =c_diffuse* c_ambient + c_diffuse*c_light*((float)fmax(0,glm::dot(glm::normalize(N),glm::normalize(light_dir))));

    					//if the z buffer is on
    				if(zbuffer_on==true)
    				{
    					//if the point we are looking at is in the triangle
    					if(alfa>=0 && beta>=0 && gama>=0)
    					{
    						//gets the z corodinate on the triangle
    						float z=(model->vertex(model->face(i)[0]).z*alfa)+(model->vertex(model->face(i)[1]).z*beta)+(model->vertex(model->face(i)[2]).z*gama);

    						//if that corordinate is greater than the current corordinat in that location in the z buffer array
    						if(z>zbuffer[win_w*j+k])
    						{
    							//replave the corodinate with the current one
    							zbuffer[win_w*j+k]=z;
    							//draw the point
    							draw_point(j,k,c);
    						}
    					}
    				}
    				//if z buffer is not on
    				else
    				{
    					//if the current point is in the triangle
    					if(alfa>=0 && beta>=0 && gama>=0)
    					{
    						//draw the point
    						draw_point(j,k,c);
    					}
    					
    				}
    			}
    		}

    	}
    }


    }

    

    std::cerr << "draw_model_flat_shading: drawn " << cnt << " / " << model->num_faces() << " triangles\n";
}




vec3 world2screen(vec3 v)
{
    float width = win_w / 1.0;
    float height = win_h / 1.0;

    // note that z-coordinate is not changed
    // that is,
    //   x and y coords are in screen coord sys
    //   z coord is in world coord sys
    // so that you can use z coord for z-buffering
    return vec3(static_cast<int>((v.x + 1.0) * width / 2.0 + 0.5),
		static_cast<int>((v.y + 1.0) * height / 2.0 + 0.5),
		v.z);
}


// for back-face culling
// - if face normal and eye (camera) vector have the angle greater that 90 degree,
//   no need to draw the face since the eye cannot see the front side of the face.
// - returns
//     true if visible (ie, less than 90 <= dot product is not negative)
//     false if invisible (ie, over 90 <= dot product is negative)
//
// can be used by draw_model_wire_frame and draw_model_flat_shading
//
bool is_visible(const vec3& p0, const vec3& p1, const vec3& p2)
{
    /**********************************/
    /*     Replace the next line      */
    /*         with your code         */             
    /**********************************/
	//if eye vector * normal vector is greater than or equal to 0 draw triangle/line

	//p0,p1
	//p1,p2
	//p2,p0
//calculates the normal vector of the triangle
vec3 N=glm::cross(p1-p0, p2-p0);
//gets the dot product of the normal anf eye vectors
double test = glm::dot(cam,N);

//if the dot product of the normal vector and eye vector is greater than or equal to zero the retun true aka draw the point
if(test>=0)
{
return true;
}
else return false;


}



// is pixel (x, y) inside the triangle p0-p1-p2?
//   returns
//     true if it is inside, false otherwise
//   also returns
//     alpha, beta, gamma
//
// can be used by draw_model_flat_shading
//
bool is_inside(const int x, const int y,
	       const vec3& p0, const vec3& p1, const vec3& p2, 
	       float& alpha, float& beta, float& gamma)
{
    /**********************************/
    /*     Replace the next line      */
    /*         with your code         */             
    /**********************************/



    return true;
}



// for debugging purpose,
// overload operator<< for vec3
std::ostream& operator<< (std::ostream& out, const vec3& v)
{
    out << "R: " << v.r << ", G: " << v.g << ", B: " << v.b << ")";
    return out;
}
