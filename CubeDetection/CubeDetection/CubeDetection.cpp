  // CubeDetection.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <numeric>
#include "C:\Projects\CImg-2.6.1\CImg.h"

using namespace cimg_library;
using namespace std;
void pix_color(int x, int y); 
void average(int r, int g, int b);
int max(vector<int>rgb);
int min(vector<int>rgb);
int red_pix(int x, int y);
int green_pix(int x, int y);
int blue_pix(int x, int y);
int size(int arr[9]);
int sum(int rgb[9]);

const CImg<float> img("C:\\Projects\\C++\\git\\rubiksCube\\Rubiks-Cube\\CubeDetection\\test2.bmp");

//I hate my ife
	// sume of rgb elements
int red_sum=0;
int blue_sum=0;
int green_sum=0;
vector<int> red;
vector<int> green;
vector<int> blue;

int main()
{
	// Main data array for cube realization
	//[side][section][pixel][rgb]
	unsigned char faces[3][9][9][3];

	// Store pixel variables
	int R = 0;
	int G = 1;
	int B = 2;

	// for loop variables
	int face, piece, pixel, rgb;

	// Load x,y data, predetermined from our still image
	//    [side][section][pixel][xy]
	int xy[3][9][9][2] = {
		{ // Face 1
			{ {1600,200}, {1625,195}, {1625,205}, {1650,195}, {1650,200}, {1650,205}, {1675,195}, {1675,205}, {1700,200} }, // Piece 1, Pixels 1-9
			{ {2000,325}, {2025,320}, {2025,330}, {2050,320}, {2050,325}, {2050,330}, {2075,320}, {2075,330}, {2100,325} }, // Piece 2, Pixels 1-9
			{ {2550,450}, {2525,445}, {2525,455}, {2550,445}, {2550,450}, {2550,455}, {2575,445}, {2575,455}, {2600,450} }, // Piece 3, Pixels 1-9
			{ {1250,375}, {1275,370}, {1275,380}, {1300,370}, {1300,375}, {1300,380}, {1325,370}, {1325,380}, {1350,375} }, // Piece 4, Pixels 1-9
			{ {1600,525}, {1625,520}, {1625,530}, {1650,520}, {1650,525}, {1650,530}, {1675,520}, {1675,530}, {1700,525} }, // Piece 5, Pixels 1-9
			{ {2150,725}, {2175,720}, {2175,730}, {2200,720}, {2200,725}, {2200,730}, {2225,720}, {2225,730}, {2250,725} }, // Piece 6, Pixels 1-9
			{ {750,575}, {775,570}, {775,580}, {800,570}, {800,575}, {800,580}, {825,570}, {825,580}, {850,575} }, // Piece 7, Pixels 1-9
			{ {1150,775}, {1175,770}, {1175,780}, {1200,770}, {1200,775}, {1200,780}, {1225,770}, {1225,780}, {1250,775} }, // Piece 8, Pixels 1-9
			{ {1650,1050}, {1675,1045}, {1675,1055}, {1700,1045}, {1700,1050}, {1700,1055}, {1725,1045}, {1725,1055}, {1750,1050} }  // Piece 9, Pixels 1-9
		},
		{ // Face 2
			{ {550,845}, {550,850}, {550,855}, {575,845}, {575,850}, {575,855}, {600,845}, {600,855}, {600,855} }, // Piece 1, Pixels 1-9
			{ {925,1145}, {925,1150}, {925,1155}, {950,1145}, {950,1150}, {950,1155}, {975,1145}, {975,1150}, {975,1155} },
			{ {1375,1470}, {1375,1475}, {1375,1480}, {1400,1470}, {1400,1475}, {1400,1480}, {1425,1470}, {1425,1475}, {1425,1480} },
			{ {750,1320}, {750,1325}, {750,1330}, {775,1320}, {775,1325}, {775,1330}, {800,1320}, {800,1325}, {800,1330} },
			{ {1050,1545}, {1050,1550}, {1050,1555}, {1075,1545}, {1075,1550}, {1075,1555}, {1100,1545}, {1100,1550}, {1100,1555} },
			{ {1425,1955}, {1425,1960}, {1425,1965}, {1450,1955}, {1450,1960}, {1450,1965}, {1475,1955}, {1475,1960}, {1475,1965} },
			{ {875,1660}, {875,1665}, {875,1670}, {885,1660}, {885,1665}, {885,1670}, {900,1660}, {900,1665}, {900,1670} },
			{ {1175,1930}, {1175,1935}, {1175,1940}, {1200,1930}, {1200,1935}, {1200,1940}, {1225,1930}, {1225,1935}, {1225,1940} },
			{ {1425,2170}, {1425,2175}, {1425,2180}, {1450,2170}, {1450,2175}, {1450,2180}, {1475,2170}, {1475,2175}, {1475,2180} }
		},
		{ // Face 3
			{ {1852,1464}, {1892,1448}, {1945,1442}, {2000,1397}, {2031,1429}, {1975,1491}, {1916,1518}, {1937,1475}, {1900,1555} }, // Piece 1, Pixels 1-9
			{ {2364,1096}, {2366,1097}, {2370,1098}, {2367,1152}, {2370,1156}, {2375,1152}, {2388,1174}, {2390,1174}, {2395,1158} },
			{ {2732,835}, {2735,835}, {2740,835}, {2710,870}, {2720,870}, {2725,870}, {2694,932}, {2696,932}, {2698,932} },
			{ {1880,1940}, {1885,1940}, {1890,1940}, {1875,1993}, {1880,1993}, {1885,1993}, {1835,2030}, {1840,2030}, {1845,2030} },
			{ {2265,1580}, {2270,1580}, {2275,1580}, {2235,1650}, {2240,1650}, {2245,1650}, {2300,1570}, {2305,1570}, {2310,1570} },
			{ {2640,1230}, {2645,1230}, {2650,1230}, {2590,1295}, {2595,1295}, {2600,1295}, {2580,1375}, {2585,1375}, {2590,1375} },
			{ {1900,2260}, {1905,2260}, {1910,2260}, {1875,2290}, {1880,2290}, {1885,2290}, {1985,2170}, {1990,2170}, {1995,2170} },
			{ {2225,1925}, {2230,1925}, {2235,1925}, {2240,1960}, {2245,1960}, {2250,1960}, {2200,2000}, {2205,2000}, {2210,2000} },
			{ {2510,1605}, {2515,1605}, {2520,1605}, {2580,1540}, {2585,1540}, {2590,1540}, {2500,1650}, {2505,1650}, {2510,1650} }
		}
	};
	
	
	/* Image Indexing*/
	// img(x,y,z,c) pixel x, y, z, color channel

	const CImg<float> img("C:\\Projects\\C++\\git\\rubiksCube\\Rubiks-Cube\\CubeDetection\\test2.bmp");
	img.display();
	cout << endl; 

	// Take in Pixel Data
	// Step 1. Develop img
	// const CImg<float> img("cube.bmp");
	
	vector<int> test; 

	// Untested
	// Store RGB value per pixel
	for (face = 0; face < 3; face++) {
		for (piece = 0; piece < 9; piece++) {
			for (int pix = 0; pix < 9; pix++) {      // (x,y,0,C)
				cout << "Side:" << face + 1 << " | " << "Section" << piece + 1 <<
					" | " << "Pixel:" << pix << endl;
				faces[face][piece][pix][R] = img(xy[face][piece][pix][0], xy[face][piece][pix][1], 0, R);
				faces[face][piece][pix][G] = img(xy[face][piece][pix][0], xy[face][piece][pix][1], 0, G);
				faces[face][piece][pix][B] = img(xy[face][piece][pix][0], xy[face][piece][pix][1], 0, B);
				cout << "(" << xy[face][piece][pix][0] << "," << xy[face][piece][pix][1] << ")" << endl;
				pix_color(xy[face][piece][pix][0], xy[face][piece][pix][1]);

				test.push_back(faces[face][piece][pix][R]);
				int sum, avg; 
				if (test.size() >= 9) {
					sum = accumulate(test.begin(), test.end(), 0);
					cout << "Sum: " << sum << endl;
					avg = sum / test.size(); 
					cout << "Average: " << avg << endl<<endl; 
					test.clear(); //clear the vector DUH??
				
					
				}
				

			}
		}
	}
	//vector<int> red;
	//vector<int> green;
	//vector<int> blue;
	//int r, g, b; 
		// [side][section][pixel][xy]
	//for (int side = 0; side < 3; side++) {
	//	for (int section = 0; section < 9; section++) {
	//		for (int pixel = 0; pixel < 9; pixel++) {
	//			cout << "Side:" << side + 1 << " | " << "Section" << section + 1 <<
	//				      " | " << "Pixel:" << pixel<< endl;

	//			for (int coord = 0; coord < 1; coord++) {
	//				cout << "(" << xy[side][section][pixel][coord] << "," << xy[side][section][pixel][coord + 1] << ")" << endl;
	//				//pix_color(xy[side][section][pixel][coord], xy[side][section][pixel][coord + 1]);
	//				cout << red_pix(xy[side][section][pixel][coord], xy[side][section][pixel][coord + 1]) << ", ";
	//				cout << green_pix(xy[side][section][pixel][coord], xy[side][section][pixel][coord + 1])<<", ";
	//				cout << blue_pix(xy[side][section][pixel][coord], xy[side][section][pixel][coord + 1])<<endl;
	//				
	//				// update the vectors
	//				r = red_pix(xy[side][section][pixel][coord], xy[side][section][pixel][coord + 1]);
	//				g = green_pix(xy[side][section][pixel][coord], xy[side][section][pixel][coord + 1]);
	//				b = blue_pix(xy[side][section][pixel][coord], xy[side][section][pixel][coord + 1]); 

	//				red.push_back(r); 
	//				green.push_back(g);
	//				blue.push_back(b);

	//			}
	//			cout << endl; 
	//		}
	//	}
	//}
	
	// Compare and average, store as "R", "G", "B", "W", "Y", "O"


	while(1); // for debug only
}

int sum(vector<int>test) {
	int sum = 0;
	//unsigned char faces[3][9][9][3];
	
	for (int i = 0; i < 9; i++) {
		sum += test[i]; 
	}
	return sum; 
}

int size(int arr[9]) {
	int count = 0; 
	for (int i = 0; i < 9; i++) count++;
	return count;
}

int red_pix(int x, int y) {
	int r = (int)img(x, y, 0, 0);
	return r; 
}
int green_pix(int x, int y) {
	int g = (int)img(x, y, 0, 1);
	return g;
}
int blue_pix(int x, int y) {
	int b = (int)img(x, y, 0, 2);
	return b;
}

void pix_color(int x, int y) {
	// R:0 G:1 B:2
	//vector<int> red;
	//vector<int> green;
	//vector<int> blue;

	int r = (int)img(x, y, 0, 0);
	int g = (int)img(x, y, 0, 1);
	int b = (int)img(x, y, 0, 2);

	cout << "R:" << r <<
		" G:" << g <<
		" B:" << b << endl<<endl;
	//average(r, g, b);

	//// trying a switch case statement for choosing which color it is
	//if (r > 99 && g < 20 && b < 99) cout << "RED" << endl << endl;
	//else if (r < 5 && g < 140 && b > 120) cout << "BLUE" << endl << endl;
	//else if (r < 10 && g > 80 && b < 110) cout << "GREEN" << endl << endl;
	//else if (r > 120 && g > 55 && 3 < b && b < 20) cout << "ORANGE" << endl << endl;
	//else if (r > 155 && g > 150 && b < 7) cout << "YELLOW" << endl << endl;
	//else if (r > 100 && g > 120 && b > 130) cout << "WHITE" << endl << endl;
}
void average(int r, int g, int b) {
	//vector<int> red;
	//vector<int> green; 
	//vector<int> blue; 
	int counter; // counter to get the max value in vector

	// max and min of each rgb?? DO we need this??
	int rmin, rmax,
		gmin, gmax,
		bmin, bmax; 
	
	// reset the vectors

	// add new rgb elements in appropriate 
	if (blue.size() < 9) {
		red.push_back(r);
		green.push_back(g);
		blue.push_back(b);
	} 
	else if (blue.size() >= 9) {
		// add up all hte elements in the vecotr
		red_sum = accumulate(red.begin(), red.end(), 0); 
		green_sum = accumulate(green.begin(), green.end(), 0);
		blue_sum = accumulate(blue.begin(), blue.end(), 0);
		cout <<"the Sum of red rgb is "<< red_sum << endl;
		
		//clear vectors
		red.clear();
		/*green.clear();
		blue.clear();*/
	}

	for (int i = 0; i < red.size(); i++) {
		cout << red[i] << endl;
	}

	/*cout << green_sum << endl; 
	cout << blue_sum << endl;*/ 
	
}
void color(int r, int g, int b){

}

int max(vector<int>rgb) {
	int max = rgb[0];
	
	for (int i = 0; i < rgb.size(); i++) {
		if (max < rgb[i]) max = rgb[i]; 
	}
	return max;
}
int min(vector<int>rgb) {
	int min = rgb[0];

	for (int i = 0; i < rgb.size(); i++) {
		if (min < rgb[i]) min = rgb[i];
	}
	return min;
}