#include "pch.h"
#include "Square.h"
#include <iostream>
using namespace std;


Square::Square()
{
	R.resize(9);
	B.resize(9);
	G.resize(9);
	RGB.resize(3);
	x.resize(9);
	y.resize(9);
}


Square::~Square()
{
}

void Square::setX(vector<int> newX) {
	for(int v = 0; v < 9; v++) x[v] = newX[v];
};


vector<int> Square::getX(){
	return x;
};


void Square::setY(vector<int> newY) {
	for (int v = 0; v < 9; v++) y[v] = newY[v];
}

vector<int> Square::getY() {
	return y;
};

void Square::setPixels(CImg<float> img) {
	for (int p = 0; p < 9; p++) { 
		R[p] = img(x[p], y[p], 0, 0);
		G[p] = img(x[p], y[p], 0, 1);
		B[p] = img(x[p], y[p], 0, 2);
	}
};

vector<float> Square::getR() {
	return R;
};
vector<float> Square::getG() {
	return G;
};
vector<float> Square::getB() {
	return B;
};

void Square::setRGB() {
	vector<float> r = getR();
	vector<float> g = getG();
	vector<float> b = getB();
	
	int rAvg = 0; int gAvg = 0; int bAvg = 0;

	for (int c = 0; c < 9; c++) {
		rAvg += r[c];
		gAvg += g[c];
		bAvg += b[c];
	}

	rAvg /= 9;
	gAvg /= 9;
	bAvg /= 9;
	//cout << rAvg << "\t" << gAvg << "\t" << bAvg << "\n" debug;

	RGB[0] = rAvg;
	RGB[1] = gAvg;
	RGB[2] = bAvg;
};

vector<float> Square::getRGB() {
	return RGB;
};


void Square::setColor(int c) {
	switch (c) {
		case 0: color = Square::Color::RED;
			break;
		case 1: color = Square::Color::GREEN;
			break;
		case 2: color = Square::Color::BLUE;
			break;
		case 3: color = Square::Color::YELLOW;
			break;
		case 4: color = Square::Color::WHITE;
			break;
		case 5: color = Square::Color::ORANGE;
			break;
	}
};

Square::Color Square::getColor() {
	return color;
};

/*
void Square::setPieceType(PieceType p) {

};

int Square::getPieceType() {

};
artifact */
