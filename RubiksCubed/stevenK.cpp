#include <cmath>
#include <cstring>
//#include <bit/stdc++.h>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

//int euclidDist(int r1, int r2, int g1, int g2, int b1, int b2);
//bool different_centroids(int A[6][3], int B[6][3]);

// 3 columns, 3 rows, 3 rgb
							//orange		yellow		green
int test_bench[3][3][3] = { {{250,126,2}, {250,209,2}, {104,201,58}},
							//blue			red			white
							{{15,103,191}, {201,32,32}, {235,230,230}},
							//yellow		orange		red
							{{232,203,14}, {237,176,7}, {237,72,7}}
							};

// one face, 9 pieces, 3 rgb vals
							//orange		yellow	   green
int stvn_bench[2][9][3] ={{ {250,126,2}, {250,209,2},{104,201,58},
							//blue			red			white
							{15,103,191},{201,32,32},{235,230,230},
							//yellow		orange		redish/orange
							{232,203,14},{237,176,7},{237,72,7}},
					//===============Second Face================
							//blue			green	   blue
					   {	{3,119,252}, {13,181,41},{13,66,181},
							//green		 orange			yello
							{2,209,19},{255,106,0}, {255,204,0},
							//red		 dark red 		orange
							{222,56,31},{120,26,26},{212,120,17}}
		
					};

void stevenK() {
	// predined locations for clusters 6 colors, 3 rgb values
							//red		green		blue
	int centroids[6][3] = { {175,26,26}, {0,128,0}, {0,0,128},
							// yellow		white			orange
							{255,255,0}, {255,255,255}, {255,140,0}};
	int old_centroid[6][3]; 

	vector <vector <int>> cluster_pc;
	cluster_pc.resize(6);

	char select_color[7] = "rgbywo"; //string color 
	int k = 6; // 6 clusters
	int test_distance; 
	int distance, min_distance, min_element;
	min_element = 0;


	while (different_centroids(centroids, old_centroid)) {
		cluster_pc.clear();
		cluster_pc.resize(6);

		// Update old centroid
		for (int x = 0; x < 6; x++) {
			for (int y = 0; y < 3; y++) {
				old_centroid[x][y] = centroids[x][y];
			}
		}

		// thru the data set given which is one face, 9 pieces, 6 different colors
		for (int side = 0; side < 2; side++) {
			cout << "SIDE: " << side << endl;
			for (int piece = 0; piece < 9; piece++) {
				min_distance = 443; // reset min

				// for each piece we need to compare for all 6 centroids
				for (int centroid_color = 0; centroid_color < 6; centroid_color++) {

					distance = euclidDist(centroids[centroid_color][0], stvn_bench[side][piece][0],
						centroids[centroid_color][1], stvn_bench[side][piece][1],
						centroids[centroid_color][2], stvn_bench[side][piece][2]);

					//cout << "distance:" << distance << endl;
					// find the minumum distance and element that it's at
					if (distance < min_distance) {
						min_distance = distance;
						min_element = centroid_color;
					}
				}

				cout << "Piece: " << piece << endl;
				cout << "minimum distance: " << min_distance << endl;
				cout << "minimum element/cluster: " << min_element << endl << endl;
				cluster_pc[min_element].push_back(side);
				cluster_pc[min_element].push_back(piece);

			}// 9 pieces for loop
			//getchar();
		}

		int averages[6][3];
		int side, piece, size, sumx, sumy, sumz;

		for (int x = 0; x < 6; x++) {
			cout << "Cluster: " << x << endl;
			side = 0;
			piece = 0;
			sumx = 0;
			sumy = 0;
			sumz = 0;
			size = cluster_pc[x].size();
			for (int y = 0; y < size; y++) {
				if (y % 2 == 0) {
					side = cluster_pc[x].at(y);
					cout << "Side: " << side << endl;
				}
				else {
					piece = cluster_pc[x].at(y);
					cout << "Piece: " << piece << endl << endl;

					sumx += stvn_bench[side][piece][0];
					sumy += stvn_bench[side][piece][1];
					sumz += stvn_bench[side][piece][2];
				}
				
			}
			centroids[x][0] = sumx / (size / 2);
			centroids[x][1] = sumy / (size / 2);
			centroids[x][2] = sumz / (size / 2);
		}

		for (int x = 0; x < 6; x++) {
			cout << endl;
			cout << "Old Centroid: (" << old_centroid[x][0] << ", " << old_centroid[x][1] << ", " << old_centroid[x][2] << ")" << endl;
			cout << "New Centroid: (" << centroids[x][0] << ", " << centroids[x][1] << ", " << centroids[x][2] << ")" << endl << endl;
		}

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
	//Freeze Terminal
	getchar();
}


