// CubeDetection.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "CImg\CImg.h"


using namespace cimg_library;
using namespace std;

int main()
{
	// Main data array for cube realization
	unsigned char faces[3][9][9][3];

	// Store pixel variables
	int R = 0;
	int G = 1;
	int B = 2;

	// for loop variables
	int face, piece, pix;

	// Load x,y data, predetermined from our still image
	
	int xy[3][9][9][2] = {
		{ // Face 1
			{ {}, {}, {}, {}, {}, {}, {}, {}, {} }, // Piece 1, Pixels 1-9
			{ {}, {}, {}, {}, {}, {}, {}, {}, {} }, // Piece 2, Pixels 1-9
			{ {}, {}, {}, {}, {}, {}, {}, {}, {} }, // Piece 3, Pixels 1-9
			{ {}, {}, {}, {}, {}, {}, {}, {}, {} }, // Piece 4, Pixels 1-9
			{ {}, {}, {}, {}, {}, {}, {}, {}, {} }, // Piece 5, Pixels 1-9
			{ {}, {}, {}, {}, {}, {}, {}, {}, {} }, // Piece 6, Pixels 1-9
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

	const CImg<float> img("ryu2.bmp");
	img.display();
	//cout << img(); // c = 0, 1, or 2 for RGB

	// Take in Pixel Data
	// Step 1. Develop img
	// const CImg<float> img("cube.bmp");
	
	// Untested
	// Store RGB value per pixel
	for (face = 0; face < 3; face++) {
		for (piece = 0; piece < 9; piece++) {
			for (pix = 0; pix < 9; pix++) {      // (x,y,0,C)
				faces[face][piece][pix][R] = img(xy[face][piece][pix][0], xy[face][piece][pix][1], 0, R);
				faces[face][piece][pix][G] = img(xy[face][piece][pix][0], xy[face][piece][pix][1], 0, G);
				faces[face][piece][pix][B] = img(xy[face][piece][pix][0], xy[face][piece][pix][1], 0, B);
			}
		}
	}
	
	// Compare and average, store as "R", "G", "B", "W", "Y", "O"


	while(1); // for debug only
}