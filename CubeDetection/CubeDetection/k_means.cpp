// k means
#include <cmath>
#include <cstring>
//#include <bit/stdc++.h>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std; 


bool different_centroids(int A[6][3],  int B[6][3]); 
int min_distance(int dist_euclid[6]);

// 3 columns, 3 rows, 3 rgb
							//orange		yellow		green
int test_bench[3][3][3] = {{{250,126,2}, {250,209,2,}, {104,201,58}},
							//blue			red			white
							{{15,103,191}, {201,32,32}, {235,230,230}},
							//yellow		orange		red
							{{232,203,14}, {237,176,7}, {237,72,7}}
							};

int test[3][3][1]; //3 columns, 3 rows, 1 cluster


void k_mean(){
	// predined locations for clusters 6 faces, 3 rgb
	int centroids[6][3] = { (255,51,51), (0,153,76), (0,102,204),
						  (255,178,102), (255,255,255), (255,69,0) };

	char select_color[7] = "rgbywo"; //string color 
	int k = 6; // 6 clusters

	//6 faces, 9 pieces, 3 colors
	int rgb_val[6][9][3];
 
	int centroids_old [6][3]; 

	int cluster_piece[6][54][2]; // 6 colors, 54 possible pieces, side and piece
	std::vector <std::vector<int>> cluster;
	cluster.resize(6);
	
	int iteration = 0;

		while (different_centroids(centroids, centroids_old)) {
			iteration++; 
			
			for (int x = 0; x < 6; x++) {
				for (int y = 0; y < 3; y++) {
					centroids_old[x][y] = centroids[x][y]; 
				}
			}

			// this for loopiterates through all 6 sides and 9pieces and finds the closest cluster
			for (int side = 0; side < 3; side++) {
				for (int piece = 0; piece < 3; piece++) {
					// store cluster color for one piece
					int dist_euclid [6];

					for (int clust = 0; clust < 6; clust++) {
							dist_euclid[clust] = sqrt(pow(centroids[clust][0] - test_bench[side][piece][0], 2) +
							pow(centroids[clust][1] - test_bench[side][piece][1], 2) +
							pow(centroids[clust][2] - test_bench[side][piece][2], 2));

						// the piece is assigned a cluster 
						if (clust == 5) {
							int closest = min_distance(dist_euclid);
							cluster[closest].push_back(side);
							cluster[closest].push_back(piece);
							//TODO: assign the selected piece a color
							test[side][piece][0] = closest;
						}
					}
				}
			}
		
			// determine cluster mean
			for (int clust = 0; clust < 6; clust++) {
				int sum_r, sum_g, sum_b;
				int sum_x=0, sum_y=0, sum_z = 0;
				int side, piece;
				int len = cluster[clust].size();
				for (int x = 0; x < len; x++) {
					if (x % 2 == 0) {
						side = cluster[clust].at(x);
					}
					else {
						piece = cluster[clust].at(x);
						sum_x += test_bench[side][piece][0];
						sum_y += test_bench[side][piece][1];
						sum_z += test_bench[side][piece][2];
					}
					

				}
				centroids[clust][0] = (sum_x / (len / 2));
				centroids[clust][1] = (sum_y / (len / 2));
				centroids[clust][2] = (sum_z / (len / 2));
			}

		}
			
		for (int col = 0; col < 3; col++) {
			for (int row = 0; row < 3; row++) {
				cout << test[col][row];
			}
		}
}

bool different_centroids(int A[6][3], int B[6][3]){
	for (int x = 0; x < 6; x++) {
		for (int y = 0; y < 3; y++) {
			if (A[x][y] != B[x][y]) return true; 
		}
	}
	return false; 
}

int min_distance(int dist_euclid[6]){
	int min_val = 500;
	int min_index; 

	for (int indx = 0; indx < 6; indx++) {
		if (dist_euclid[indx] < min_val) {
			min_val = dist_euclid[indx];
			min_index = indx;
		}
	}
	return min_index; 

}