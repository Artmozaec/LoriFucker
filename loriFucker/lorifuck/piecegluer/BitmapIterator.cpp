#include "BitmapIterator.h"

BitmapIterator::BitmapIterator(BitmapContainer *inBitmapContainer){
	bitmapContainer = inBitmapContainer;

	if (bitmapContainer->getShirina()>bitmapContainer->getVisota()){
		orientation = horizontal;
	} else {
		orientation = vertical;
	}

	pointer = 0;
}

bool BitmapIterator::nextPixel(){
	pointer++;
	if (orientation == horizontal){
		if (pointer>bitmapContainer->getShirina()){
			pointer--;
			return false;
		}
	} else if (orientation == vertical){
		if (pointer>bitmapContainer->getVisota()){
			pointer--;
			return false;
		}
	}
	return true;
}


bool BitmapIterator::isEnd(){
	if (orientation == horizontal){
		if ((pointer+1)>bitmapContainer->getShirina()) return true;
	} else if (orientation == vertical){
		if ((pointer+1)>bitmapContainer->getVisota()) return true;
	}
	return false;
}

Color* BitmapIterator::getPixel(){
	if (orientation == horizontal){
		return bitmapContainer->getPixel(pointer, 0);
	} else if (orientation == vertical){
		return bitmapContainer->getPixel(0, pointer);
	}
	return 0;
}


bool BitmapIterator::isNextDarken(){
	int tmpPointer = pointer;
	Color *pervPixel = getPixel();
	if (!nextPixel()) return false;
	Color *nextPixel = getPixel();
	pointer = tmpPointer;

	if (nextPixel->getGrayValue()<pervPixel->getGrayValue()) return true;

	return false;
}

bool BitmapIterator::isNextWhiten(){
	int tmpPointer = pointer;
	Color *pervPixel = getPixel();
	if (!nextPixel()) return false;
	Color *nextPixel = getPixel();
	pointer = tmpPointer;

	if (nextPixel->getGrayValue()>pervPixel->getGrayValue()) return true;

	return false;
}

bool BitmapIterator::isNextEqual(){
	int tmpPointer = pointer;
	Color *pervPixel = getPixel();
	if (!nextPixel()) return false;
	Color *nextPixel = getPixel();
	pointer = tmpPointer;

	if (nextPixel->getGrayValue()==pervPixel->getGrayValue()) return true;

	return false;
}


int BitmapIterator::getPosition(){
	return pointer;
}


void BitmapIterator::setPosition(int newPosition){
	pointer = newPosition;
}