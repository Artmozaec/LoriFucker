#ifndef AreaSequenceCreatorH
#define AreaSequenceCreatorH

#include "..\mytypes\BitmapContainer.h"
#include "BitmapIterator.h"
#include "Area.h"
#include "FlatAreaAccumulator.h"
#include <string>

class AreaSequenceCreator{
public:
	static AreaSequenceCreator* getInstance();

	Area *generate(BitmapContainer *bitmapContainer);
private:
	static AreaSequenceCreator* instance;

	AreaSequenceCreator();

	void generateAreas(BitmapIterator *bitmapIterator);

	//Перемещает итератор вперёд пока градиент присутствует
	void goForwardUntillWhiteDarkGradient(BitmapIterator *bitmapIterator);
	void goForwardUntillDarkWhiteGradient(BitmapIterator *bitmapIterator);

	//Пороговое значение изменеия цвета в градиенте достаточное для создания области
	int areaMinColorDiapazone;
	
	//Пороговая длинна градиента достаточная для создания области
	int areaMinSize;
	
	Area *firstArea;
	Area *lastArea;

	void addArea(Area *newArea);
};

#endif