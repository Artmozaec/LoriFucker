#include "Color.h"

Color::Color(int r, int g, int b){
	red = r;
	green = g;
	blue = b;
}


int Color::getRed(){
	return red;
}

int Color::getGreen(){
	return green;
}

int Color::getBlue(){
	return blue;
}

int Color::colorDifference(Color *color){
	int diff = 0;
	diff += abs(red - color->getRed());
	diff += abs(blue - color->getBlue());
	diff += abs(green - color->getGreen());

	return diff;
}

int Color::getGrayValue(){
	//60% зелёного
	//30% красного
	//10% синего
	return green+(red/2)+(blue/3);
}

bool Color::equal(Color *color, int deviation){
	if (abs(red-color->getRed()) > deviation) return false;
	if (abs(green-color->getGreen()) > deviation) return false;
	if (abs(blue-color->getBlue()) > deviation) return false;

	return true;
}