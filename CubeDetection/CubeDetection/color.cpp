// CubeDetection.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// *** NOTE: CHANGE THE LOCATION OF THE THE YOU WANT TO OPEN OR LOOK AT***
#include "C:\Projects\C++\Rubiks\Rubiks\pch.h"
#include <iostream>
#include "C:\Projects\CImg-2.6.1\CImg.h"


using namespace cimg_library;
using namespace std;
void pix_color(int x, int y); 

int main()
{
	const CImg<float> img("C:\\Projects\\C++\\Project1\\cubeTri_640x480.bmp");

	cout << "inside the main" << endl;
	// Main data array for cube realization
	unsigned char faces[3][9][9][3];

	// Store pixel variables
	int R = 0;
	int G = 1;
	int B = 2;

	// Size of the image 
	int w = img.width(); 
	int h = img.height(); 
	cout << "width: " << w << endl;
	cout << "height: " << h << endl;

	// for loop variables
	int face, piece, pix;

	// Load x,y data, predetermined from our still image

	// [sides][pieces][pix][times]?????
	int xy[3][9][9][2] = {
		{ // Face 1
			{ {}, {}, {}, {}, {}, {}, {}, {}, {} }, // Piece 1, Pixels 1-9
			{ {}, {}, {}, {}, {}, {}, {}, {}, {} }, // Piece 2, Pixels 1-9
			{ {}, {}, {}, {}, {}, {}, {}, {}, {} }, // Piece 3, Pixels 1-9
			{ {}, {}, {}, {}, {}, {}, {}, {}, {} }, // Piece 4, Pixels 1-9
			{ {}, {}, {}, {}, {}, {}, {}, {}, {} }, // Piece 6, Pixels 1-9
			{ {}, {}, {}, {}, {}, {}, {}, {}, {} }, // Piece 5, Pixels 1-9
			{ {}, {}, {}, {}, {}, {}, {}, {}, {} }, // Piece 7, Pixels 1-9
			{ {}, {}, {}, {}, {}, {}, {}, {}, {} }, // Piece 8, Pixels 1-9
			{ {}, {}, {}, {}, {}, {}, {}, {}, {} }  // Piece 9, Pixels 1-9
		},
		{ // Face 2
			{ {}, {}, {}, {}, {}, {}, {}, {}, {} }, // Piece 1, Pixels 1-9
			{ {}, {}, {}, {}, {}, {}, {}, {}, {} },
			{ {}, {}, {}, {}, {}, {}, {}, {}, {} },
			{ {}, {}, {}, {}, {}, {}, {}, {}, {} },
			{ {}, {}, {}, {}, {}, {}, {}, {}, {} },
			{ {}, {}, {}, {}, {}, {}, {}, {}, {} },
			{ {}, {}, {}, {}, {}, {}, {}, {}, {} },
			{ {}, {}, {}, {}, {}, {}, {}, {}, {} },
			{ {}, {}, {}, {}, {}, {}, {}, {}, {} }
		},
		{ // Face 3
			{ {}, {}, {}, {}, {}, {}, {}, {}, {} }, // Piece 1, Pixels 1-9
			{ {}, {}, {}, {}, {}, {}, {}, {}, {} },
			{ {}, {}, {}, {}, {}, {}, {}, {}, {} },
			{ {}, {}, {}, {}, {}, {}, {}, {}, {} },
			{ {}, {}, {}, {}, {}, {}, {}, {}, {} },
			{ {}, {}, {}, {}, {}, {}, {}, {}, {} },
			{ {}, {}, {}, {}, {}, {}, {}, {}, {} },
			{ {}, {}, {}, {}, {}, {}, {}, {}, {} },
			{ {}, {}, {}, {}, {}, {}, {}, {}, {} }
		}
	};


	/* Image Indexing*/
	// img(x,y,z,c) pixel x, y, z, color channel

	
	img.display(); 
	cout << "Display Passed :p" << endl;
	//cout << img(); // c = 0, 1, or 2 for RGB

	// Take in Pixel Data
	// Step 1. Develop img
	// const CImg<float> img("cube.bmp");

	// Untested
	// Store RGB value per pixel
	//for (face = 0; face < 3; face++) {
	//	for (piece = 0; piece < 9; piece++) {
	//		for (pix = 0; pix < 9; pix++) {      // (x,y,0,C)
	//			faces[face][piece][pix][R] = img(xy[face][piece][pix][0], xy[face][piece][pix][1], 0, R);
	//			cout << faces[face][piece][pix][R] << endl;
	//			faces[face][piece][pix][G] = img(xy[face][piece][pix][0], xy[face][piece][pix][1], 0, G);
	//			faces[face][piece][pix][B] = img(xy[face][piece][pix][0], xy[face][piece][pix][1], 0, B);
	//		}
	//	}
	//}
	
	cout << "about to get the VALUES"<<endl<<endl; 
	/*for (int x = 0; x < h; x++) {
		for (int y = 0; y < w; y++) {
			cout << "X: " << x << "Y: " << y << "=" <<
				"R:" << (int)img(x, y, 0, 1) <<
				"G:" << (int)img(x, y, 0, 2) <<
				"B:" << (int)img(x, y, 0, 3)<<endl;

		}
	}*/

	//int array[3][9][2][3] = {
	//	{{{245,131},{}},{{245,131},{}},{{338,129},{}},{{196,151},{}},{{290,145},{}},{{394,142},{}},{{236,171},{}},{{334,160},{}},{{296,183},{}}}, // top 
	//	{{{325,235},{}},{{371,205},{}},{{419,186},{}},{{314,305},{}},{{369,229},{}},{{414,249},{}},{{319,376},{}},{{368,331},{}},{{410,308},{}}}, // right
	//	{{{169,189},{}},{{211,213},{}},{{271,227},{}},{{178,247},{}},{{205,254},{}},{{264,303},{}},{{183,302},{}},{{221,330},{}},{{264,364},{}}}, // left
	//};
	// array to cycle through all sidesXsection of cube
	//[side][section][xy]
	int stvnArr[3][9][2]= {
			{{294,118},{245,131},{338,129},{196,151},{290,145},{394,142},{236,171},{334,160},{296,183}}, // top 
			{{325,235},{371,205},{419,186},{314,305},{369,279},{414,249},{319,376},{368,331},{410,308}}, // right
			{{169,189},{211,213},{271,227},{178,247},{205,254},{264,303},{183,302},{221,330},{264,364}}, // left
	};

	for (int side = 0; side < 3; side++) {
		for (int section = 0; section < 9; section++) {
			for (int xy = 0; xy < 1; xy++) {
				cout << "Side:" << side+1 << " | " << "Section:" << section+1 << endl; 
				cout <<"(" <<  stvnArr[side][section][xy]<<","<< stvnArr[side][section][xy+1]<<")" << endl;
				pix_color(stvnArr[side][section][xy], stvnArr[side][section][xy+1]);
			}
		}
	}

	cout << "Passed Thru Mother Fucker HAHA" << endl;

	//int x = 292; int y = 186; 
	//cout << "X:" << x << "Y:" << y << endl<<
	//	"R:" << (int)img(x, y, 0, 0) <<
	//	" G:" << (int)img(x, y, 0, 1) <<
	//	" B:" << (int)img(x, y, 0, 2) << endl;

	//

	// Compare and average, store as "R", "G", "B", "W", "Y", "O"


	while (1); // for debug only
}

void pix_color(int x, int y) {
	// R:0 G:1 B:2
	const CImg<float> img("C:\\Projects\\C++\\Project1\\cubeTri_640x480.bmp");

	int r = (int)img(x, y, 0, 0); 
	int g = (int)img(x, y, 0, 1);
	int b = (int)img(x, y, 0, 2);

	cout <<  "R:" << r <<
			" G:" <<g <<
			" B:" << b << endl;
 
	// trying a switch case statement for choosing which color it is
	if (r > 99 && g < 20 && b < 99) cout << "RED" << endl<<endl; 
	else if (r < 5   && g < 140 && b > 120) cout << "BLUE" << endl<<endl;
	else if (r < 10  && g > 80  && b < 110) cout << "GREEN" << endl<<endl;
	else if (r > 120 && g > 55 && 3<b && b < 20) cout << "ORANGE" << endl<<endl;
	else if (r > 155 && g > 150 && b < 7) cout << "YELLOW" << endl<<endl;
	else if (r >100  && g > 120  && b > 130) cout << "WHITE"   << endl<<endl;
}