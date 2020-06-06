#include "BitmapShifter.h"

BitmapShifter* BitmapShifter::instance = NULL;

BitmapShifter *BitmapShifter::getInstance(){
	if (instance==NULL){
		instance = new BitmapShifter();
	}

	return instance;
}

BitmapShifter::BitmapShifter(){
	image = NULL;
}

//Частота сдвига
int BitmapShifter::calculateFrequencyShifting(int shift){
	if (shift>abstractHeighImage){
		return 1;
	} else {
		return abstractHeighImage/shift;
	}
}


//Параметры смещения
void BitmapShifter::calculateShiftParametrs(
		int &periodAccretion, //Период приращения 
		int &accretion, //Пориращение
		int &verticalCorrectionPeriod, //Период вертикальной коррекции в 1 пиксел
		int &horizontalCorrectionPeriod, //Период горизонтальной коррекции 1 пиксел

		int shift
		){
	if (shift>abstractHeighImage){
		verticalCorrectionPeriod = 0; //Выключаем коррекцию, в данной ситуации оно не надо
		periodAccretion = 0;
		
		accretion = shift/abstractHeighImage;
		
		//verticalCorrectionPeriod = (periodAccretion*shift)

	} else {
		horizontalCorrectionPeriod = 0; //Выключаем коррекцию, в данной ситуации оно не надо
		accretion = 1;
		//Период с которым будет приращение в 1 пиксель
		periodAccretion = abstractHeighImage/shift;

		//Погрешность которая появилась
		int lapse = abstractHeighImage - (periodAccretion*shift);

		//Равномерный период с которым эта погрешность будет размазанна
		//По всей высоте смещения
		if (lapse !=0) verticalCorrectionPeriod = abstractHeighImage/lapse;
	}
}


void BitmapShifter::shiftUpArea(int pos, int length, int shift){
	if ((shift == 0) || (length == 0)) return;
	int periodAccretion = 0; //Период приращения 
	int accretion = 0; //Пориращение
	int verticalCorrectionPeriod = 0; //Период вертикальной коррекции в 1 пиксел
	int horizontalCorrectionPeriod = 0; //Период горизонтальной коррекции 1 пиксел


	calculateShiftParametrs(
		periodAccretion,
		accretion,
		verticalCorrectionPeriod,
		horizontalCorrectionPeriod,

		abs(shift)
	);

	//Текущее смещение
	int currentDelta = shift;
	

	for (int 
		lineCh=0, //Общий счётчик линий
		accrCh=0; //Счётчик периода приращения
	
		lineCh<abstractHeighImage; 
		
		lineCh++, 
		accrCh++
	){
		shiftLine(pos, lineCh, length, currentDelta);
	
		if ((verticalCorrectionPeriod != 0) && (lineCh%verticalCorrectionPeriod) == 0){//Настало время внести вертикальную коррекцию!
			//Для этого, отдаляем момент приращения на 1
			if (accrCh != 0) accrCh--;
		}
		if (accrCh>=periodAccretion){
			if (shift>0){
				currentDelta -= accretion;
			} else {
				currentDelta += accretion;
			}
			accrCh=0;
		}
	}
}

void BitmapShifter::shiftDownArea(int pos, int length, int shift){
	if ((shift == 0) || (length == 0)) return;
	int periodAccretion = 0; //Период приращения 
	int accretion = 0; //Пориращение
	int verticalCorrectionPeriod = 0; //Период вертикальной коррекции в 1 пиксел
	int horizontalCorrectionPeriod = 0; //Период горизонтальной коррекции 1 пиксел


	calculateShiftParametrs(
		periodAccretion,
		accretion,
		verticalCorrectionPeriod,
		horizontalCorrectionPeriod,

		abs(shift)
	);

	//Текущее смещение
	int currentDelta = shift;
	

	for (int 
		lineCh=abstractHeighImage, //Общий счётчик линий
		accrCh=0; //Счётчик периода приращения
	
		lineCh>0; 
		
		lineCh--, 
		accrCh++
	){
		shiftLine(pos, lineCh, length, currentDelta);
	
		if ((verticalCorrectionPeriod != 0) && (lineCh%verticalCorrectionPeriod) == 0){//Настало время внести вертикальную коррекцию!
			//Для этого, отдаляем момент приращения на 1
			if (accrCh != 0) accrCh--;
		}
		if (accrCh>=periodAccretion){
			if (shift>0){
				currentDelta -= accretion;
			} else {
				currentDelta += accretion;
			}
			accrCh=0;
		}
	}

}

void BitmapShifter::changeImage(BitmapContainer *inImage){
	image = inImage;

	if (image->getShirina()>image->getVisota()){
		orientation = horizontal;
		abstractHeighImage = image->getVisota();
	} else {
		orientation = vertical;
		abstractHeighImage = image->getShirina();
	}
}


//Смещает линию длинной length на shift пикселей
void BitmapShifter::shiftLine(int posX, int posY, int length, int shift){
	if (orientation == horizontal){
		if (shift>0){//В право
			shiftHorLineRight(posX, posY, length, shift);
		} else {//В лево
			shiftHorLineLeft(posX, posY, length, abs(shift));
		}
	}  else if (orientation == vertical){
		if (shift>0){//В низ
			shiftVertLineDown(posY, posX, length, shift);
		} else {//В вверх
			shiftVertLineUp(posY, posX, length, abs(shift));
		}
	}

}


void BitmapShifter::shiftHorLineLeft(int posX, int posY, int length, int shift){

	Color *fillColor = image->getPixel(posX+length, posY);
	//Получаем перемещаемую линию
	BitmapContainer *movedLine = image->getArea(posX, posY, 1, length);
	//movedLine->saveImage(std::string("C:\\tt.tif"));
	//Вставляем её правее на shift обратно
	image->addFragment(movedLine, posX-shift, posY);

	//Заполняем место линией нужного цвета
	image->drawHorizontalLine((posX+length)-shift, posY, shift, fillColor);
}


void BitmapShifter::shiftHorLineRight(int posX, int posY, int length, int shift){
	Color *fillColor = image->getPixel(posX, posY);

	//Получаем перемещаемую линию
	BitmapContainer *movedLine = image->getArea(posX, posY, 1, length);
	//movedLine->saveImage(std::string("C:\\tt.tif"));
	//Вставляем её правее на shift обратно
	image->addFragment(movedLine, posX+shift, posY);

	//Заполняем место линией нужного цвета
	image->drawHorizontalLine(posX, posY, shift, fillColor);
}

void BitmapShifter::shiftVertLineDown(int posX, int posY, int length, int shift){
	Color *fillColor = image->getPixel(posX, posY);

	//Получаем перемещаемую линию
	BitmapContainer *movedLine = image->getArea(posX, posY, length, 1);
	
	//Вставляем её ниже на shift обратно
	image->addFragment(movedLine, posX, posY+shift);

	//Заполняем место линией нужного цвета
	image->drawVerticalLine(posX, posY, shift, fillColor);
}

void BitmapShifter::shiftVertLineUp(int posX, int posY, int length, int shift){
	Color *fillColor = image->getPixel(posX, posY+length);
	//Получаем перемещаемую линию
	BitmapContainer *movedLine = image->getArea(posX, posY, length, 1);
	//movedLine->saveImage(std::string("C:\\tt.tif"));
	//Вставляем её правее на shift обратно
	image->addFragment(movedLine, posX, posY-shift);

	//Заполняем место линией нужного цвета
	image->drawVerticalLine(posX, (posY+length)-shift, shift, fillColor);
}



