#pragma once

//TODO: include instructions on how to use class
//TODO: we need pixel coordinates atm

#include "CImg\CImg.h"
#include <vector>

using namespace std;

using namespace cimg_library;

class Square
{

public:
	enum class Color { RED, GREEN, BLUE, WHITE, ORANGE, YELLOW };
	Square();
	~Square(); // destructor, dont know how to use yet

   /**
    Set X pixel coordinates of Square
    
    @param Integer vector of 9 X-coordinate values
    */
	void setX(vector<int>);

	/**
	 Get X pixel coordinates of Square

	 @return An int vector with 9 values
	*/
	vector<int> getX();


	void setY(vector<int>);
	vector<int> getY();

	void setPixels(CImg<float>); //change this later to pointing to image 
	vector<float> getR();
	vector<float> getG();
	vector<float> getB();

	//int averagePixels(); unneeded, taken care of in setRGB now

	void setRGB();
	vector<float> getRGB();

	void setColor(int);
	Color getColor();

private:
	vector<int> x; // pixel location x9
	vector<int> y;
	vector<float> R; // RGB values x9
	vector<float> G;
	vector<float> B;
	Color color;
	vector<float> RGB; // 3 length vector
};

