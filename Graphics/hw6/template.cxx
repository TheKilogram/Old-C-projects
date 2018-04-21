/*************************************************************************
 *  CMPSC 457                                                            *
 *  Template code for HW 6                                               *
 *  April 19, 2017                                                       *
 *  Sukmoon Chang                                                        *
 *  sukmoon@psu.edu                                                      *
 *                                                                       *
 *                                                                       *
 *  Description:                                                         *
 *                                                                       *
 *  This is a template code for homework 6.                              *
 *                                                                       *
 *  It should generate a 500x500 ppm image (output.ppm) of 3 shperes     *
 *    by simple ray tracing.                                             *
 *                                                                       *
 *  To remove the dependency on any external libraries,                  *
 *    a simple Vector class is provided.                                 *
 *                                                                       *
 *  Note that, to add, subtract, multiply a scalar (d) to a vector (v)   *
 *  you must write                                                       *
 *    v + d, v - d, v * d                                                *
 *  instead of                                                           *
 *    d + v, d - v, d * v                                                *
 *  (Each of these operators are only implemented as a method)           *
 *                                                                       *
 *                                                                       *
 *  To compile the program, use                                          *
 *     g++ -std=c++0x -Wall -pedantic -O2 template.cxx -o template       *
 *                                                                       *
 *  To run the program, use                                              *
 *     ./template                                                        * 
 *************************************************************************/




#include <cmath>
#include <limits>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cfloat>
#include <vector>


using namespace std;


struct Vector
{
    double x, y, z;

    Vector(double x=0, double y=0, double z=0)
        : x(x), y(y), z(z) {}

    Vector operator+ (const Vector& v) const
    { return Vector(x+v.x, y+v.y, z+v.z); }

    Vector operator- (const Vector& v) const
    { return Vector(x-v.x, y-v.y, z-v.z); }
  
    Vector operator* (double d) const
    { return Vector(x*d, y*d, z*d); }

    Vector operator* (const Vector& v) const
    { return Vector(x*v.x, y*v.y, z*v.z); }

    Vector& norm() 
    { return *this = *this * (1 / sqrt(x*x + y*y + z*z)); }

    double dot(const Vector& v) const
    { return x*v.x + y*v.y + z*v.z; }

    Vector cross(const Vector& v) const
    { return Vector(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x); }
};


struct Ray
{
    Vector o, d;

    // arg d should always be normalized vector
    Ray (Vector o, Vector d) : o(o), d(d) {} 
};



// types of the surface
// - DIFFuse, SPECular, REREective
// - only DIFF is used in this assignment
enum Refl_t { DIFF, SPEC, REFR };

const double eps = 1e-4;


struct Sphere
{
    double r;      // radius of sphere
    Vector p;      // position (center) of sphere
    Vector e;      // emission (not used in this assignment)
    Vector c;      // color of sphere
    Refl_t refl;   // reflection type (DIFFuse, SPECular, REFRactive)
                   // - in this assignment, only DIFF is used

    Sphere(double r, Vector p, Vector e, Vector c, Refl_t refl)
        : r{r}, p{p}, e{e}, c{c}, refl{refl} {}

    double intersect(const Ray& ray) const
    {
        // solve
        //        (d.d)t^2 + 2d.(o-c)t + (o-c).(o-c) - R^2 = 0
        // and return the paramter t if the ray intersects this sphere
        // Otherwise, return 0
        double t00,t01;
        double t10,t11;
        Vector o=ray.o;
        Vector d=ray.d;
        Vector d2;
        /*d2.x=(2*ray.d.x);
        d2.y=(2*ray.d.y);
        d2.z=(2*ray.d.z);*/
        
        double dotD=d.dot(d);          //a
        double dot2DOC =2*(d).dot(o-p); //b
        double dotOC = (o-p).dot(o-p)-(r*r); //c
        double dis=((dot2DOC*dot2DOC)-4*dotD*dotOC);
        if(dis==0)//***************Future me, if you get errors it is probably this****************
        {
        	//t1=-(dot2DOC)-( sqrt((dot2DOC*dot2DOC)-4*dotD*dotOC)/(2*dotD));
		t11=-dot2DOC+sqrt(dis)/(2*dotD);
        	return t11;
        }
        else if(dis>0)
        {
        	t00=-1*dot2DOC+sqrt(dis);
        	t10=-1*dot2DOC-sqrt(dis);
        	
        		t01=t00/(2*dotD);
        		t11=t10/(2*dotD);
        		//std::cout<<t01<<" "<<t11<<endl;
        	if(t01<t11)
        	{
        		return t01;
        	}
        	else
        	{
        		return t11;
        	}
        }
        else
        {
        	return -1;
        }

        
    }

    Vector normal(Vector& v)
    {
        return Vector(v.x-p.x, v.y-p.y, v.z-p.z).norm();
    }

};


// 3 spheres to render
vector<Sphere> spheres = {
    Sphere(200, Vector(  0, -300, -1200), Vector(), Vector(.8, .8, .8), DIFF),
    Sphere(200, Vector(-80, -150, -1200), Vector(), Vector(.7, .7, .7), DIFF),
    Sphere(200, Vector( 70, -100, -1200), Vector(), Vector(.9, .9, .9), DIFF)
};


Vector eye(0, 0, 200);      // camera position
Vector light(0, 0, 200);    // light source position



// Does this ray hit any of the spheres?
// if so,
// - return t using the reference parameter
// - return the index of the surface using the reference parameter
// - return true
// if not,
// - return false
bool hit(const Ray& ray, double& t, int& surface_idx)
{
    bool is_hit = false;
    t = std::numeric_limits<double>::max();

    /*********************************/
    /*        Your code here         */
    /*********************************/
    for(int i=0;i<3;i++)
    {

    //	std::cout<<spheres[i].intersect(ray)<<endl;
  	  if(spheres[i].intersect(ray)>0&&t>spheres[i].intersect(ray))
  	  {

  		  	t=spheres[i].intersect(ray);

    		surface_idx=i;

   		 	is_hit=true;
    	}
    }




    return is_hit;
}


// Calculate the intensity using Lambert's law
// ie, dot product of l_hat and n_hat (or 0 if dot product is negative)
// - n_hat is a unit normal vector at the point where the ray hits the surface
double lambert(int surface_idx, Ray& ray, double t)
{
    /*********************************/
    /*        Your code here         */
    /*********************************/

Vector p(ray.o+ray.d*t);
Vector l_hat=light-p;

Vector n_hat=spheres[surface_idx].normal(p);

l_hat = l_hat.norm();
double lam=fmax(0,(n_hat.dot(l_hat)));
if(lam<0)
{
	//std::cout<<lam<<endl;
return 0;	
}


    else
    {
    	//std::cout<<lam<<endl;
    	return lam;    
    }
    
}


// Calculate the color of the ray
// If ray hits any surface,
// - color of the ray is the Lambert's intensity * color at the hit point
// If not
// - color of the ray is the background color (black)
Vector ray_color(Ray& ray)
{
    /*********************************/
    /*        Your code here         */
    /*********************************/

/*
		Vector l_hat=light.norm();
Vector n_hat=((ray.o+light*ray.d)-spheres[i].p).norm();
*/
	int surface_idx=0;
	double t=0;


		if(hit(ray,t,surface_idx)==true)
   		{
   			//std::cout<<t<<" "<<surface_idx<<endl;
   			double lam= lambert(surface_idx,ray,t);
   			//Vector cl(1.0,1.0,1.0);
   		Vector c(0.0,0.0,0.0);
   	//	std::cout<<lam<<endl;
   		c.x=((spheres[surface_idx].c.x)*lam);
   		c.y=((spheres[surface_idx].c.y)*lam);
   		c.z=((spheres[surface_idx].c.z)*lam);
   		
		return c;//*lambert(i,ray,t);
    	}

    	else
    	{
    	//back greound color
    	return Vector{0.0, 0.0, 0.0};
    	}
	
//return Vector{0.0, 0.0, 0.0};
    	
}
    

    



// Generate 500x500 ppm image
//
// for every pixel in 500x500 raster
//    find the ray passing through the pixel
//    calculate the color of the ray
//    write the pixel to the raster
// write the raster to the output file in ppm format
void tracer(ofstream& fout)
{
    fout << "P3" << endl << 500 << " " << 500 << endl << 255 << endl ;

    /*********************************/
    /*        Your code here         */
    /*********************************/
    
    for(double i=-50;i<50;i+=0.2)
    {
    	for(double j=-50;j<50;j+=0.2)
    	{
    	
    		Vector w(j, i, 0);
    		Vector d=w-eye;
    		d=d.norm();

    		Ray ray(eye,d);

    		Vector c=ray_color(ray) * 255;
    		
    		fout<< (int)c.x<<" ";
    		fout<< (int)c.y<<" ";
    		fout<< (int)c.z<<" ";
    		fout<<" ";

    	}
    	fout<<std::endl;
    }
    
}




int main()
{
    const char *fname = "output.ppm";

    ofstream fout(fname);
    if (!fout) {
        cerr << "tracer: cannot open input file " << fname << endl;
        exit(1);
    }

    tracer(fout);

    fout.close();

    return 0;
}




