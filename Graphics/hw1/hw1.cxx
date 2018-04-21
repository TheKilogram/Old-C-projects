//CMPSC 457
//Section 1
//Jonathan Bauman
//jzb5636


#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>

using namespace std;

//function prototypes
struct RGB** CreateArr(int, int);						//function creates an array for hight and width of an image

struct RGB** GiveArrRGBVal(struct RGB** arr, int h, int w);			//function gives floating point values from 0-1 to each element in the array

void ConvertToPPM(struct RGB** rester, int hight, int width, string filename);	//function creates an output .ppm file with the array elements as data

//structure decleration for RGB values
struct RGB
{
	float r;	//red
	float g;	//green
	float b;	//blue
};


int main(int argc, char *argv[])
{	
	string filename; //initializes the file name the user gives
	int hight;	 //initializes the hight the user gives
	int width;	 //initializes the width the user gives
	
	
	//checks to see if their where 3 comand line arguments given
	if (argc==4)
		{
		//checks to see if he user input a positive number
		if(argv[1]>0 && argv[2]>0)
			{
			width=atoi(argv[1]);	//sets the width
			hight=atoi(argv[2]);	//sets the hight
			filename=argv[3];		//sets the filename
			//cout<<"helllo"<<endl;
			//calls the functions CreateArr, GiveArrRGBVal, and ConvertToPPM in that order
			ConvertToPPM(GiveArrRGBVal(CreateArr(width,hight), hight, width), hight, width, filename);
			return 0;//returns
			}
		}
		//gives error message if comandline argument is not correct
		cout<<"Invaled comandline argument: needs to be {int int string.ppm}"<<endl;
		return 0;
		
}

//creates 2D array of hight and width given by comandline arguments 
struct RGB** CreateArr(int w, int h)
{
	//pointer array of type RGB (struct) initalization
	RGB** rester = new RGB*[h];
	for(int i =0; i< h; i++)
		{
		rester[i]=new RGB[w];
		}
		
		
	return rester; //returnes the empty 2D array
}

//gives the empty 2D array values for red green and blue for eatch eement in the array
struct RGB** GiveArrRGBVal(RGB** rester, int h, int w)
{
		for(int i=0; i<h;i++)
		{
			for(int j=0; j<w; j++)
			{
				//this line can only give col a 1 or a 0, alternating every 8 pixles
				int col =((j & 0x08) == 0) ^ ((i & 0x08) == 0);
			
				rester[i][j].r = static_cast<float>(col);	//red is either 0 or 1 (0 or 255 at output step)
				rester[i][j].g = static_cast<float>(col & 0x00);//green is zero
				rester[i][j].b = static_cast<float>(col & 0x11);//blue is either 0 or 1 (0 or 255 at output step)
				
			}
	}
		
		
	return rester; //returns the 2D array filled with RGB values in its elements in float 0-1 form

}

//saves 2D array values as a .ppm file (multiplying the float 0-1 by 255 to get the RGB values)
void ConvertToPPM(struct RGB** rester, int hight, int width, string filename)
{	
//initialized output stream					
ofstream outputFile;

	outputFile.open(filename.c_str(), ios::out); //creates a file with the user declared name
	outputFile << "P3" << endl;		//P3 magic number (was directed to uses this by Dr chang	
	outputFile << width<<endl;		//exports the width of the image
	outputFile << hight << endl;		//exports the hight of the image
	outputFile << "255" << endl;		//max intensity
	
	//exports the rgb values for every pixle in the image
	for(int i = 0; i < hight; i++){
		outputFile << endl;
		for (int j = 0; j < width; j++){
			outputFile << rester[i][j].r*255<<" "<<rester[i][j].g*255<<" "<<rester[i][j].b*255<<endl; //multiplies the float elements of the array by 255 to give 0-255 rgb color
			
		}
	}
	//export is done
	outputFile.close();

}
