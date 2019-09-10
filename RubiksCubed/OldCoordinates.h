#pragma once

#include <vector>

using namespace std;

// Create 54 integer vector sets

// top
vector<int> s0x({ 27,30,24,27,27,30,24,24,30 });
vector<int> s1x({ 42,42,42,39,45,45,45,39,39 });
vector<int> s2x({ 53,53,53,50,50,50,56,56,56 });
vector<int> s3x({ 16,16,16,19,19,19,13,13,13 });
vector<int> s4x({ 30,30,30,33,33,33,17,17,17 });
vector<int> s5x({ 40,40,40,37,37,37,43,43,43 });
vector<int> s6x({ 7,7,7,10,10,10,4,4,4 });
vector<int> s7x({ 20,20,20,17,17,17,23,23,23});
vector<int> s8x({ 29,29,29,30,30,30,27,27,27 });

// right
vector<int> s9x({ 36,36,36,33,33,33,39,39,39});
vector<int> s10x({ 48,48,48,51,51,51,45,45,45});
vector<int> s11x({ 57,57,57,59,59,59,55,55,55});
vector<int> s12x({ 37,37,37,35,35,35,39,39,39});
vector<int> s13x({ 47,47,47,45,45,45,49,49,49});
vector<int> s14x({ 55,55,55,56,56,56,54,54,54});
vector<int> s15x({ 38,38,38,40,40,40,36,36,36});
vector<int> s16x({ 47,47,47,48,48,48,46,46,46});
vector<int> s17x({ 54,54,54,55,55,55,53,53,53});

// left
vector<int> s18x({ 3,3,3,4,4,4,2,2,2});
vector<int> s19x({ 10,10,10,9,9,9,11,11,11});
vector<int> s20x({ 23,23,23,21,21,21,25,25,25 });
vector<int> s21x({ 7,7,7,8,8,8,6,6,6});
vector<int> s22x({ 15,15,15,14,14,14,16,16,16});
vector<int> s23x({ 26,26,26,27,27,27,25,25,25});
vector<int> s24x({ 12,12,12,13,13,13,11,11,11});
vector<int> s25x({ 18,18,18,19,19,19,17,17,17});
vector<int> s26x({ 27,27,27,26,26,26,28,28,28});


// vector<int> s2()
// ...
// vector<int> s53()

// top
vector<int> s0y({ 28,28,28,31,25,31,25,31,25});
vector<int> s1y({ 19,16,22,19,19,16,22,22,16});
vector<int> s2y({ 12,15,9,12,15,9,12,15,9 });
vector<int> s3y({ 20,23,17,20,23,17,20,23,17 });
vector<int> s4y({ 13,16,10,13,16,10,13,16,10 });
vector<int> s5y({ 8, 10,6,8,10,6,8,10,6 });
vector<int> s6y({ 15,17,13,15,17,13,15,17,13 });
vector<int> s7y({  9,12, 6, 9,12, 6, 9,12, 6 });
vector<int> s8y({  6, 4, 8, 6, 4, 8, 6, 4, 8 });

// right
vector<int> s9y({ 39,42,36,39,42,36,39,42,36 });
vector<int> s10y({ 29,32,26,29,32,26,29,32,26 });
vector<int> s11y({ 22,23,21,22,23,21,22,23,21});
vector<int> s12y({ 50,52,48,50,52,48,50,52,48});
vector<int> s13y({ 40,42,38,40,42,38,40,42,38});
vector<int> s14y({ 33,34,32,33,34,32,33,34,32});
vector<int> s15y({ 58,59,57,58,59,57,58,59,57});
vector<int> s16y({ 49,48,50,49,48,50,49,48,50});
vector<int> s17y({ 42,43,41,42,43,41,42,43,41});

// left
vector<int> s18y({ 24,23,25,24,23,25,24,23,25 });
vector<int> s19y({ 30,31,29,30,21,29,30,31,29 });
vector<int> s20y({ 40,41,29,40,41,29,40,41,29});
vector<int> s21y({ 36,35,37,36,35,37,36,35,37});
vector<int> s22y({ 42,41,43,42,41,43,42,41,43});
vector<int> s23y({ 52,51,53,52,51,53,52,51,53});
vector<int> s24y({ 43,42,44,43,42,44,43,42,44});
vector<int> s25y({ 51,50,52,51,50,52,51,50,52});
vector<int> s26y({ 60,61,59,60,61,59,60,61,59});


/*
.
.
.
.
*/

vector<vector<int>> X({ s0x,s1x,s2x,s3x,s4x,s5x,s6x,s7x,s8x,s9x,s10x,s11x,s12x,s13x,s14x,
						s15x,s16x,s17x,s18x,s19x,s20x,s21x,s22x,s23x,s24x,s25x,s26x}); // add s2, ..., s53
vector<vector<int>> Y({ s0y,s1y,s2y,s3y,s4y,s5y,s6y,s7y,s8y,s9y,s10y,s11y,s12y,s13y,
						s14y,s15y,s16y,s17y,s18y,s19y,s20y,s21y,s22y,s23y,s24y,s25y,s26y});