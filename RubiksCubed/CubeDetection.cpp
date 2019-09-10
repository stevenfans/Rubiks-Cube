// CubeDetection.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <numeric>
#include "CImg\CImg.h"
#include "Square.h"
//#include "Piece.h"
//#include "Cube.h"
//#include "Face.h"
#include "Coordinates.h"

using namespace cimg_library;
using namespace std;

const CImg<float> cube_1("cube_1.bmp");	// Red Face
const CImg<float> cube_2("cube_2.bmp");	// Green Face
const CImg<float> cube_3("cube_3.bmp");	// Blue Face
const CImg<float> cube_4("cube_4.bmp");	// Yellow Face
const CImg<float> cube_5("cube_5.bmp");	// White Face
const CImg<float> cube_6("cube_6.bmp");	// Red Face


//Function Prototypes
int euclidDist(int r1, int r2, int g1, int g2, int b1, int b2);
bool different_centroids(int A[6][3], int B[6][3]);


int red_sum = 0;
int blue_sum = 0;
int green_sum = 0;
vector<int> red;
vector<int> green;
vector<int> blue;


vector<Square> allSquares(54);


// Begin by creating 21 faces to create 1 side

int main(){

	vector<float> RGBVals(3);
	//vector<int> xs(9); debug
	//vector<int> ys(9);
	//vector<float> rs(9); debug

	for (int n = 0; n < 54; n++) { // Scale to 54 for full square amount, will crash if Coordinates.h is empty
		cout << "n = " << n << "\n";
		allSquares[n].setX(X[n%9]);
		allSquares[n].setY(Y[n%9]);

		/* Debug - verify X/Y are being stored properly
		xs = allSquares[n].getX();
		ys = allSquares[n].getY();
		for (auto z = xs.begin(); z != xs.end(); z++) cout << *z << "\t";
		cout << "\n";
		for (auto z = ys.begin(); z != ys.end(); z++) cout << *z << "\t";
		cout << "\n";

		*/
		switch (int(n / 9))
		{
			case 0: allSquares[n].setPixels(cube_1);
				break;
			case 1: allSquares[n].setPixels(cube_2);
				break;
			case 2: allSquares[n].setPixels(cube_3);
				break;
			case 3: allSquares[n].setPixels(cube_4);
				break;
			case 4: allSquares[n].setPixels(cube_5);
				break;
			case 5: allSquares[n].setPixels(cube_6);
				break;
		}
		

		/* Debug - Verify RGB values are being stored properly
		rs = allSquares[n].getB();
		for (auto z = rs.begin(); z != rs.end(); z++) cout << *z << "\t";
		cout << "\n";
		*/

		allSquares[n].setRGB();

		//- Debug - Console print R, G, and B
		RGBVals = allSquares[n].getRGB();
		cout << "RGB Values:\t";
		for (auto l = RGBVals.begin(); l != RGBVals.end(); l++) cout << *l << "\t";
		//RGBVals.clear();
		cout << "\n\n";
		//

		//retrieve your RGB values via allSquares[n].getRGB() into a vector<int> of 3 index size
	}

	////////////////////
	// Classify Color //
	////////////////////

	// predined locations for clusters 6 colors, 3 rgb values
							//red		green		blue
	int centroids[6][3] = { {150,21,11}, {87,219,11}, {12,97,235},
		// yellow		white			orange
		{200,140,15}, {255,255,255}, {215,70,30} };
	int old_centroid[6][3];
	int iterations = 0;

	vector <vector <int>> clusters;
	clusters.resize(6);

	int min_dist, dist, min_centroid;

	while (different_centroids(centroids, old_centroid)) {
		iterations++;
		clusters.clear();
		clusters.resize(6);

		// Update old centroid
		for (int x = 0; x < 6; x++) {
			for (int y = 0; y < 3; y++) {
				old_centroid[x][y] = centroids[x][y];
			}
		}

		// Find closest centroid
		for (int x = 0; x < 54; x++) {
			min_dist = 443;	// Reset Min
			min_centroid = 0;

			for (int y = 0; y < 6; y++) {
				vector <float> RGB =  allSquares[x].getRGB();
				dist = euclidDist(centroids[y][0], (int) RGB[0],
								centroids[y][1], (int) RGB[1],
								centroids[y][2], (int) RGB[2]);

				// Check if closest cluster
				if (dist < min_dist) {
					min_dist = dist;
					min_centroid = y;
				}
			}
			allSquares[x].setColor(min_centroid);
			clusters[min_centroid].push_back(x);
		}


		int size, sumx, sumy, sumz, loc;

		// Find Means
		for (int x = 0; x < 6; x++) {
			size = clusters[x].size();
			sumx = 0;
			sumy = 0;
			sumz = 0;
			for (int y = 0; y < size; y++) {
				loc = clusters[x].at(y);
				vector <float> RGB = allSquares[loc].getRGB();

				sumx += (int) RGB[0];
				sumy += (int) RGB[1];
				sumz += (int) RGB[2];
			}

			if (size > 0) {
				centroids[x][0] = sumx / size;
				centroids[x][1] = sumy / size;
				centroids[x][2] = sumz / size;
			}
		}

		cout << "Iteration: " << iterations << endl;

		for (int x = 0; x < 6; x++) {
			cout << "Cluster: " << x << endl;
			cout << "Size: " << clusters[x].size() << endl;
			cout << "Old Centroid: (" << old_centroid[x][0] << ", " << old_centroid[x][1] << ", " << old_centroid[x][2] << ")" << endl;
			cout << "New Centroid: (" << centroids[x][0] << ", " << centroids[x][1] << ", " << centroids[x][2] << ")" << endl << endl;
		}
	}

	cout << "Colors: " << endl;
	for (int x = 0; x < 54; x++) {
		if (x % 9 == 0)
			cout << endl;
		
		Square::Color c;

		c = allSquares[x].getColor();

		switch (c) {
			case Square::Color::RED:	cout << "R ";
				break;
			case Square::Color::GREEN:	cout << "G ";
				break;
			case Square::Color::BLUE:	cout << "B ";
				break;
			case Square::Color::YELLOW:	cout << "Y ";
				break;
			case Square::Color::WHITE:	cout << "W ";
				break;
			case Square::Color::ORANGE:	cout << "O ";
				break;
		}
	}



	/*
	// Debug: Shows color setting
	allSquares[2].setColor(Square::Color::GREEN);

	Square::Color o;

	o = allSquares[2].getColor();

	if (o == Square::Color::GREEN) cout << "Color is green";
	else cout << "Color is not green";
	//
	*/

	// Debug - Does nothing tbh
	char a;
	cin >> a; // pls hold
	//
}


// calculate the euclid distance for rgb values to the rgb centroid values
int euclidDist(int r2, int r1, int g2, int g1, int b2, int b1) {
	// distance answer 
	int distance;
	distance = sqrt(pow(r2 - r1, 2) + pow(g2 - g1, 2) + pow(b2 - b1, 2));
	return distance;
}


// Check if centroids are different
bool different_centroids(int A[6][3], int B[6][3]) {
	for (int x = 0; x < 6; x++) {
		for (int y = 0; y < 3; y++) {
			if (A[x][y] != B[x][y]) return true;
		}
	}
	return false;
}

