#include "Area.h"

Area::Area(
	Color* inBeginColor, 
	Color* inEndColor, 
	int inBegin,
	int inLength
){
	beginColor = inBeginColor;
	endColor = inEndColor;
	length = inLength;
	begin = inBegin;

	upArea = NULL;
	downArea = NULL;
	nextArea = NULL;
	pervArea = NULL;

	//В начале смещения нет
	shift = 0;
}



int Area::getLength(){
	return length;
}

void Area::setLength(int newLength){
	if (newLength > 0){
		length = newLength;
	} else {
		length = 0;
	}
}

int Area::getBegin(){
	return begin;
}

void Area::setBegin(int newBegin){
	begin = newBegin;
}


Color *Area::getBeginColor(){
	return beginColor;
}
void Area::setBeginColor(Color *newBeginColor){
	beginColor = newBeginColor;
}


Color *Area::getEndColor(){
	return endColor;
}
void Area::setEndColor(Color *newEndColor){
	endColor = newEndColor;
}


bool Area::equalColor(Area *area, int deviation){
	Color *equalAreaBeginColor = area->getBeginColor();
	Color *equalAreaEndColor = area->getEndColor();

	//Проверяем на направление градиента
	if ((equalAreaBeginColor->getGrayValue()>equalAreaEndColor->getGrayValue())&&
		(beginColor->getGrayValue()<endColor->getGrayValue())
		){
		return false;
	}

	if ((equalAreaBeginColor->getGrayValue()<equalAreaEndColor->getGrayValue())&&
		(beginColor->getGrayValue()>endColor->getGrayValue())
		){
		return false;
	}
	
	if ((equalAreaBeginColor->getGrayValue()==equalAreaEndColor->getGrayValue())&&
		(beginColor->getGrayValue()!=endColor->getGrayValue())
		){
		return false;
	}

	if ((equalAreaBeginColor->getGrayValue()!=equalAreaEndColor->getGrayValue())&&
		(beginColor->getGrayValue()==endColor->getGrayValue())
		){
		return false;
	}
/*
	if (abs(equalAreaBeginColor->getRed()-beginColor->getRed())>deviation) return false;
	if (abs(equalAreaBeginColor->getGreen()-beginColor->getGreen())>deviation) return false;
	if (abs(equalAreaBeginColor->getBlue()-beginColor->getBlue())>deviation) return false;

	if (abs(equalAreaEndColor->getRed()-endColor->getRed())>deviation) return false;
	if (abs(equalAreaEndColor->getGreen()-endColor->getGreen())>deviation) return false;
	if (abs(equalAreaEndColor->getBlue()-endColor->getBlue())>deviation) return false;
*/
	if (!equalAreaBeginColor->equal(beginColor, deviation)) return false;
	if (!equalAreaEndColor->equal(endColor, deviation)) return false;
	return true;
}

int Area::getDistance(Area *area){
	return begin - area->getBegin();
}



void Area::linkPervArea(Area *area){
	if ((pervArea != NULL) && (pervArea != area)){ 
		pervArea->unlinkNextArea();
	}
	if (pervArea != area){
		pervArea = area;
		if (pervArea != NULL) pervArea->linkNextArea(this);
	}
}


void Area::linkNextArea(Area *area){
	if ((nextArea != NULL) && (nextArea != area)){ 
		nextArea->unlinkPervArea();
	}
	if (nextArea != area){
		nextArea = area;
		if (nextArea != NULL) nextArea->linkPervArea(this);
	}
}


void Area::linkUpArea(Area *area){
	if ((upArea != NULL) && (upArea != area)){ 
		upArea->unlinkDownArea();
	}
	if (upArea != area){
		upArea = area;
		if (upArea != NULL) upArea->linkDownArea(this);
	}
}


void Area::linkDownArea(Area *area){
	if ((downArea != NULL) && (downArea != area)){ 
		downArea->unlinkUpArea();
	}
	if (downArea != area){
		downArea = area;
		if (downArea!= NULL) downArea->linkUpArea(this);
	}
}


////////////////////////////////////////////////////////////////////
void Area::unlinkUpArea(){
	upArea = NULL;
}

void Area::unlinkDownArea(){
	downArea = NULL;
}

void Area::unlinkNextArea(){
	nextArea = NULL;
}

void Area::unlinkPervArea(){
	pervArea = NULL;
}
//////////////////////////////////////////////////////////////////////
		
Area* Area::getNextArea(){
	return nextArea;
}


Area* Area::getPervArea(){
	return pervArea;
}


Area* Area::getUpArea(){
	return upArea;
}


Area* Area::getDownArea(){
	return downArea;
}
////////////////////////////////////////////////////////////////////////


//Колличество связей до верхней границы
int Area::AmountLinksToUpBound(){
	int ch = 0;
	Area *cur = upArea;
	while (cur != NULL){
		cur = cur->getUpArea();
		ch++;
	}
	return ch;
}


//Смещение верха области при склейке
void Area::setShift(int newShift){
	shift = newShift;
}


int Area::getShift(){
	return shift;
}

void Area::expand(Area *endArea){
	if (endArea == this) return;

	length = (endArea->getBegin()+endArea->getLength())-begin;

	endColor = endArea->getEndColor();

	linkNextArea(endArea->getNextArea());
	
	//delete(endArea->getPervArea());
	//delete(endArea);
}
