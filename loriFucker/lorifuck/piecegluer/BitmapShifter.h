#ifndef AreaShifterH
#define AreaShifterH

#include <windows.h>
#include "Area.h"
#include "Orientation.h"
#include "..\mytypes\BitmapContainer.h"
#include "..\mytypes\Color.h"


class BitmapShifter{
public:
	static BitmapShifter* getInstance();

	//Придерживаемся горизонтальной абстракции
	void shiftUpArea(int pos, int length, int shift);
	void shiftDownArea(int pos, int length, int shift);

	void changeImage(BitmapContainer *inImage);
private:
	BitmapShifter();

	//Изображение области которого будут смещаться
	BitmapContainer *image;

	static BitmapShifter* instance;

	Orientation orientation;

	//Смещает линию длинной length на shift пикселей
	void shiftLine(int posX, int posY, int length, int shift);

	//Внутренние функции смещения линии, для каждого возможного варианта
	void shiftHorLineLeft(int posX, int posY, int length, int shift);
	void shiftHorLineRight(int posX, int posY, int length, int shift);
	void shiftVertLineUp(int posX, int posY, int length, int shift);
	void shiftVertLineDown(int posX, int posY, int length, int shift);
	
	//Абстрактные размеры для представления лбого изображения как горизонтально ориентированное
	int abstractHeighImage;
	int abstractWidthImage;

	//Частота сдвига
	int calculateFrequencyShifting(int shift);


	//Параметры смещения
	void calculateShiftParametrs(
		int &periodAccretion, //Период приращения 
		int &accretion, //Пориращение
		int &verticalCorrectionPeriod, //Период вертикальной коррекции в 1 пиксел
		int &horizontalCorrectionPeriod, //Период горизонтальной коррекции 1 пиксел

		int shift
	);
};

#endif
