// k means
#include <cmath>
#include <cstring>
#include <bit/stdc++.h>
#include <iostream>

array test_bench[6][3][3]; 


void k_mean(){
	// predined locations for clusters 6 faces, 3 rgb
	array int centroids[6][3] = [(255,51,51), (0,153,76), (0,102,204),
							     (255,178,102), (255,255,255), (255,69,0)]; 
	array select_color [6] = ["r", "g", "b", "y", "w", "o"]; //string color 
	k = 6 // 6 clusters

	//6 faces, 9 pieces, 3 colors
	array rgb_val[6][9][3]; 
	array centroids_old[6][3]; 

	array cluster_piece[6][54][2] // 6 colors, 54 possible pieces, side and piece
	vector<int> cluster[6];
	
	int iteration = 0;

		while (different_centroids(centroids, old_centroids)) {
			iteration++; 

			// this for loopiterates through all 6 sides and 9pieces and finds the closest cluster
			for (int side = 0; side < 6; side++) {
				for (int piece = 0; piece < 9; piece++) {
					// store cluster color for one piece
					array dist_eulcid [6];

					for (int clust = 0; clust < 6; clust++)[
						dist_euclid[clust] = sqrt(pow(centroids[side][piece][0] - rgb_val[side][piece][0],2) +
												  pow(centroids[side][piece][1] - rgb_val[side][piece][1],2) +
												  pow(centroids[side][piece][2] - rgb_val[side][piece][2],2));

						// the piece is assigned a cluster 
						if (clust == 5) {
							int closest = min_distance(dist_euclid);
							cluster[closest].push_back({ side, piece });
							//TODO: assign the selected piece a color
						}
				}
			}
		
			// determine cluster mean
			for (int clust = 0; clust < 6; clust++) {
				int sum_r, sum_g, sum_b;
				int clust_size = cluster.size(); 
				int side, piece;

				for (int x = 0; x < clust_size; x++) {
					{side, piece} = cluster[clust].at(x);
					sum_x += rgb_val[side][piece][0];
					sum_y += rgb_val[side][piece][1];
					sum_z += rgb_val[side][piece][2];
				}

				centroids[clust] = [(sum_x / clust_size), (sum_y / clust_size), (sum_z / clust_size)];
			}
			

	}
}

bool different_centroids(array int A[6][3], array int B[6][3]) {
	for (int x = 0; x < 6; x++) {
		for (int y = 0; y < 3; y++) {
			if (A[x][y])  != B[x][y]
				return true
		}
	}
	return false
}

int min_distance(array dist_euclid[6]) {
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