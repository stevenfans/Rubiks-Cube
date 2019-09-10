#pragma once

#include <vector>

using namespace std;

// Create 18 integer vector sets
// 1 face 

// bottom: right to left
vector<int> s0x({ 47,47,47,50,50,50,44,44,44 });
vector<int> s1x({ 29,29,29,32,32,32,26,26,26 });
vector<int> s2x({ 11,11,11,14,14,14,8,8,8 });

// middle: right to left
vector<int> s3x({ 48,48,48,45,45,45,51,51,51 });
vector<int> s4x({ 29,29,29,32,32,32,26,26,26 });
vector<int> s5x({ 11,11,11,14,14,14,8,8,8 });

// top: right to left
vector<int> s6x({ 48,48,48,45,45,45,51,51,51 });
vector<int> s7x({ 29,29,29,32,32,32,26,26,26 });
vector<int> s8x({ 11,11,11,14,14,14,8,8,8 });


// vector<int> s2()
// ...
// vector<int> s8()

// bottom: right to left
vector<int> s0y({ 51,54,48,51,54,48,51,54,48 });
vector<int> s1y({ 50,53,47,50,53,47,50,53,47 });
vector<int> s2y({ 50,53,47,50,53,47,50,53,47 });

// middle: right to left
vector<int> s3y({ 33,30,36,33,30,36,33,30,36 });
vector<int> s4y({ 33,30,36,33,30,36,33,30,36 });
vector<int> s5y({ 33,30,36,33,30,36,33,30,36 });

// top: right to left
vector<int> s6y({ 16,19,13,16,19,13,16,19,13 });
vector<int> s7y({ 16,19,13,16,19,13,16,19,13 });
vector<int> s8y({ 16,19,13,16,19,13,16,19,13 });




/*
.
.
.
.
*/

vector<vector<int>> X({ s0x,s1x,s2x,s3x,s4x,s5x,s6x,s7x,s8x}); // add s2, ..., s53
vector<vector<int>> Y({ s0y,s1y,s2y,s3y,s4y,s5y,s6y,s7y,s8y});