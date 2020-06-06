#ifndef FlatAreaAccumulatorH
#define FlatAreaAccumulatorH

#include "BitmapIterator.h"
#include "Area.h"

class FlatAreaAccumulator{
public:
	FlatAreaAccumulator(BitmapIterator &inBitmapIterator);

	//Добавить область в накопитель
	void addArea(int begin, int end);

	//Дать результирующую область
	Area* getResultArea();

	bool isEmpty();

	//Сбрасывает все накопленные значения
	void reset();
private:
	BitmapIterator *bitmapIterator;

	int beginPosition;
	int endPosition;

	//Находит средний цвет на отрезке
	Color* calculateAverageColor();
	
};

#endif