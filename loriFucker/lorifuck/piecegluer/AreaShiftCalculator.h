#ifndef AreaShiftCalculatorH
#define AreaShiftCalculatorH
#include "Area.h"
#include "BitmapIterator.h"
#include "..\mytypes\BitmapContainer.h"


class AreaShiftCalculator{
public:
	static AreaShiftCalculator* getInstance();

	void shiftCalculate(Area *upArea, Area *downArea);

	//»нициализаци€ итераторов сторон
	void setUpAreaBitmap(BitmapContainer *upBitmap);
	void setDownAreaBitmap(BitmapContainer *downBitmap);
private:
	AreaShiftCalculator();
	static AreaShiftCalculator* instance;

	//Ќаходит дистанцию ниболее точного совмещени€ верхней области и нижней
	int getDistance(Area *upArea, Area *downArea);

	//¬озвращает среднюю разность, совпадающих пикселей из upArea и downArea
	// смещение 1 - совпадение последнего пиксел€ нижней стороны и первого пиксел€ верхней
	int getAverageDifference(Area *upArea, Area *downArea, int shift);
	
	BitmapIterator *upSideIterator;
	BitmapIterator *downSideIterator;
};
#endif