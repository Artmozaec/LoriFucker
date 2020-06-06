#include "FlatAreaAccumulator.h"

FlatAreaAccumulator::FlatAreaAccumulator(BitmapIterator &inBitmapIterator){
	bitmapIterator = &inBitmapIterator;

	reset();
}


//Добавить область в накопитель
void FlatAreaAccumulator::addArea(int begin, int end){
	if (beginPosition == -1){
		beginPosition = begin;
	}

	endPosition = end;
}



//Дать результирующую область
Area* FlatAreaAccumulator::getResultArea(){
	Color *areaColor = new Color(200,255,255);

	Area *resultArea = new Area(
		areaColor,
		areaColor,
		beginPosition,
		endPosition-beginPosition
	);

	return resultArea;
}

Color* FlatAreaAccumulator::calculateAverageColor(){
	//Устанавливаем начальную позицию
	bitmapIterator->setPosition(beginPosition);
	
	int red=0;
	int green=0;
	int blue=0;

	Color *pixel;
	do{
		pixel = bitmapIterator->getPixel();
		
		red += pixel->getRed();
		green += pixel->getGreen();
		blue += pixel->getBlue();

		bitmapIterator->nextPixel();
	}while(bitmapIterator->getPosition()<endPosition);

	Color *resultColor = new Color(
		red/(endPosition-beginPosition),
		green/(endPosition-beginPosition),
		blue/(endPosition-beginPosition)
	);
	return resultColor;
}

bool FlatAreaAccumulator::isEmpty(){
	if (beginPosition == -1) return true;
	return false;
}

void FlatAreaAccumulator::reset(){
	beginPosition = -1;
	endPosition = -1;
}