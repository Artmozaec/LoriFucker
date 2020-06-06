#include "AreaShiftCalculator.h"

AreaShiftCalculator* AreaShiftCalculator::instance = NULL;


AreaShiftCalculator *AreaShiftCalculator::getInstance(){
	if (instance==NULL){
		instance = new AreaShiftCalculator();
	}

	return instance;
}

AreaShiftCalculator::AreaShiftCalculator(){
	upSideIterator = NULL;
	downSideIterator = NULL;
}


//¬озвращает среднюю разность, совпадающих пикселей из upArea и downArea
// смещение 1 - совпадение последнего пиксел€ нижней стороны и первого пиксел€ верхней
int AreaShiftCalculator::getAverageDifference(Area *upArea, Area *downArea, int shift){
	int upBegin;
	int downBegin;

	if (shift>downArea->getLength()){
		downBegin = 0;
		upBegin = shift-downArea->getLength();
	} else {
		downBegin = downArea->getLength()-shift;
		upBegin = 0;
	}

	//”станавливаем итераторы
	upSideIterator->setPosition(upBegin+upArea->getBegin());
	downSideIterator->setPosition(downBegin+downArea->getBegin());

	int differenceSize;// олличество совпадающиих пикселей сравниваемых сторон, размер сравниваемых областей

	if ((upArea->getLength()-upBegin)>(downArea->getLength()-downBegin)){
		differenceSize = downArea->getLength()-downBegin;
	} else {
		differenceSize = upArea->getLength()-upBegin;
	}

	int ch;
	int sum=0;
	Color *upSidePixel = NULL;
	Color *downSidePixel = NULL;

	
	for (ch=0; ch<differenceSize; ch++){
		upSidePixel = upSideIterator->getPixel();
		downSidePixel = downSideIterator->getPixel();
		sum += upSidePixel->colorDifference(downSidePixel);

		upSideIterator->nextPixel();
		downSideIterator->nextPixel();
	}
	
	if (ch == 0) return -1;
	
	return sum/ch;

	
}


//Ќаходит дистанцию ниболее точного совмещени€ верхней области и нижней
int AreaShiftCalculator::getDistance(Area *upArea, Area *downArea){
	int shiftMax = upArea->getLength()+downArea->getLength();
	int resultShift = 0;
	int minAverage = 999;
	int average = 0;

	for (int shift=1; shift<shiftMax; shift++){
		average = getAverageDifference(upArea, downArea, shift);
		if (average<minAverage){
			resultShift = shift;
			minAverage = average;
		}
	}

	//ѕриводим смещение к правильному формату
	resultShift = downArea->getLength() - resultShift;

	return (upArea->getBegin()-downArea->getBegin()) - resultShift;
}


void AreaShiftCalculator::setUpAreaBitmap(BitmapContainer *upBitmap){
	//upBitmap->workAreaSaved(std::string("C:\\upBitmap.tif"));
	BitmapContainerArea area;
	if (upBitmap->getShirina() > upBitmap->getVisota()){
		area.up = upBitmap->getVisota();
		area.left = 0;
		area.height = 1;
		area.width = upBitmap->getShirina();
	} else {
		area.up = 0;
		area.left = upBitmap->getShirina();
		area.height = upBitmap->getVisota();
		area.width = 1;
	}

	BitmapContainer *bc = upBitmap->clone();
	bc->setWorkArea(area);

	//bc->workAreaSaved(std::string("C:\\upBitmap.tif"));
	upSideIterator = new BitmapIterator(bc);
}


void AreaShiftCalculator::setDownAreaBitmap(BitmapContainer *downBitmap){
	//downBitmap->workAreaSaved(std::string("C:\\downBitmap.tif"));
	BitmapContainerArea area;
	if (downBitmap->getShirina() > downBitmap->getVisota()){
		area.up = 0;
		area.left = 0;
		area.height = 1;
		area.width = downBitmap->getShirina();
	} else {
		area.up = 0;
		area.left = 0;
		area.height = downBitmap->getVisota();
		area.width = 1;
	}

	BitmapContainer *bc = downBitmap->clone();
	bc->setWorkArea(area);

	//bc->workAreaSaved(std::string("C:\\downBitmap.tif"));
	downSideIterator = new BitmapIterator(bc);
}

void AreaShiftCalculator::shiftCalculate(Area *upArea, Area *downArea){
	//¬ременное решение 
	//int distance = upArea->getBegin() - downArea->getBegin();
	int distance = getDistance(upArea, downArea);
	if (distance>0){
		//ƒистанци€ делЄнна€ на 2
		upArea->setShift(-distance/2);
		downArea->setShift(distance-(distance/2));
	} else {
		upArea->setShift(abs(distance)-(abs(distance)/2));
		downArea->setShift(distance/2); //distance и так отрицательно, по этому без "-"
	}	
}