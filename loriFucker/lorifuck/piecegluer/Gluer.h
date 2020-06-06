#ifndef GluerH
#define GluerH

#include <windows.h>
#include "Area.h"
#include "..\mytypes\BitmapContainer.h"
#include "BitmapShifter.h"
#include "AreaShiftCalculator.h"
//#include <vector>


class Gluer{
public:
	static Gluer* getInstance();

	void glue(Area *upLine, Area *downLine, BitmapContainer *areaImage);
private:
	Gluer();

	static Gluer* instance;

	//calculateShiftAreas

	//Рассчитывает смещения для всех областей и смещения записываются в эти области
	void calculateShiftingFromAreas(Area *downLine);

	//Рассчитывает правильное смещение между верхней и нижней связанной областью
	AreaShiftCalculator *areaShiftCalculator;

	//Занимается смещением областей картинок
	BitmapShifter *bitmapShifter;

	//Смещает все области имеющие смещение 
	//void shiftSide(Area *firstArea, BitmapContainer *sideBitmap);

	//Возвращает область за которой достаточно места что-бы сместить туда весь обрывок
	//На величину смещения первой области в обрывке
	Area *getNextPiece(Area *beginArea);

	//Ищет от beginArea гладкую область не меньше length
	//В направлении право, 
	//если по пути встречается область имеющая другое направление смещения
	//или значительно меньшее, возвращает NULL
	Area *searchRightFlatAreaFromShift(Area *beginArea, int length);

	//Ищет от beginArea любую область не меньше length
	//В направлении право, 
	//если по пути встречается область имеющая другое направление смещения
	//или значительно меньшее, возвращает NULL
	Area *searchRightAnyAreaFromShift(Area *beginArea, int length);

	//Ищет в направлении право от beginArea серию не связанных в цепочки областей 
	//общая длинна которых не меньше length
	//Найдя такую серию мы преобразуем её в одну область
	//если по пути встречается область имеющая другое направление смещения
	//или значительно меньшее, возвращает NULL
	Area *searechDontChainAreaFromShift(Area *beginArea, int length);
	
	//От beginArea пытаемся найти последовательность областей которые не в цепочке
	Area *searchDontLinkSequenceFromShift(Area *beginArea, int length);
	
	
	//Смещает области от staetArea до endArea на shift
	void shiftPieceDownArea(Area *startArea, Area *endArea, int shift);
	void shiftPieceUpArea(Area *startArea, Area *endArea, int shift);

	void correctShiftInAreas(Area *startArea, Area *endArea, int correctShift);

	//Область связанна в цепочку?
	bool consistsInChain(Area *area);

	//Возвращает правду если сравниваемая область не меньше в сторону смещения чем эталон
	bool shiftEquivalent(Area *etalonArea, Area *equalArea, int threshold);
};

#endif