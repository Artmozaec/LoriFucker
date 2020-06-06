#include "Gluer.h"

Gluer* Gluer::instance = NULL;

Gluer *Gluer::getInstance(){
	if (instance==NULL){
		instance = new Gluer();
	}

	return instance;
}

Gluer::Gluer(){
	areaShiftCalculator = AreaShiftCalculator::getInstance();
	bitmapShifter = BitmapShifter::getInstance();
}

//Рассчитывает смещения для всех областей и смещения записываются в эти области
void Gluer::calculateShiftingFromAreas(Area *downLine){
	Area *currentArea = downLine;
	while (currentArea != NULL){
		//Если область связанна с верхней
		//То это сразу означает что это полная цепочка
		if (currentArea->getUpArea() != NULL){
			areaShiftCalculator->shiftCalculate(currentArea->getUpArea(), currentArea);
		}

		currentArea = currentArea->getNextArea();
	}

}

//Возвращает правду если сравниваемая область не меньше в сторону смещения чем эталон
bool Gluer::shiftEquivalent(Area *etalonArea, Area *equalArea, int threshold){
/*	
	if (((etalonArea->getShift() < 0) && (equalArea->getShift() > 0)) ||
		((etalonArea->getShift() > 0) && (equalArea->getShift() < 0))) return false;
*/
	//Обе области смещаются в право
	if ((etalonArea->getShift() >= 0) && (equalArea->getShift() >= 0)){
		//Если смещение сравнивоемой больше эталонной, смещение эталона не затронет сравниваемое
		if (equalArea->getShift() > etalonArea->getShift()) return true;

		int shiftDelta = equalArea->getShift() - etalonArea->getShift();
		if (shiftDelta > threshold) return false;
		return true;
	}
	//Обе области смещаются в лево
	if ((etalonArea->getShift() < 0) && (equalArea->getShift() < 0)){
		//Смещение эталона не повредит сравниваемое! А наоборот, чуть чуть сдвинет к цели
		if (equalArea->getShift() < etalonArea->getShift()) return true;
		
		int shiftDelta = equalArea->getShift() - etalonArea->getShift();
		if ((shiftDelta < 0) && (abs(shiftDelta) > threshold)) return false;
		return true;
	}

	return false;
}


//Ищет от beginArea гладкую область не меньше длинны length
Area *Gluer::searchRightFlatAreaFromShift(Area *beginArea, int length){
	Area *currentArea = beginArea;
	//signed int shiftDelta = 0;
	while (currentArea != NULL){
		//Если область значимая - в цепочке
		//Если область имеет смещение меньше или противоположное
		//Выход нахрен
		
		if (!shiftEquivalent(beginArea, currentArea, 3)) return NULL;

		//Если область гладкая
		if (currentArea->getBeginColor()->getGrayValue() == currentArea->getEndColor()->getGrayValue()){
			//Если длинна достаточна
			if (currentArea->getLength() >= length) return currentArea;
		}
		currentArea = currentArea->getNextArea();
	}
	return NULL;
}

//Ищет от beginArea любую область не меньше длинны length
Area *Gluer::searchRightAnyAreaFromShift(Area *beginArea, int length){
	Area *currentArea = beginArea;
	currentArea = currentArea->getNextArea();
	while (currentArea != NULL){
		if (!shiftEquivalent(beginArea, currentArea, 3)) return NULL;

		if (currentArea->getLength()>length) return currentArea;
		currentArea = currentArea->getNextArea();
	}

	return NULL;
}


//От beginArea пытаемся найти последовательность областей которые не в цепочке
Area *Gluer::searchDontLinkSequenceFromShift(Area *beginArea, int length){
	Area *currentArea = beginArea;
	int totalLength = 0;
	while ((currentArea != NULL) && (!consistsInChain(currentArea))){
		totalLength += currentArea->getLength();
		
		if (totalLength >= length) return currentArea;

		currentArea = currentArea->getNextArea();
	}

	return NULL;
}

Area *Gluer::searechDontChainAreaFromShift(Area *beginArea, int length){
	Area *currentArea = beginArea;
	Area *endSequenceArea = NULL;
	while (currentArea != NULL){
		//Если смещение не обдинаково с beginArea, 
		//значит при смещении мы можем повредить его правильное положение
		//Разница в смещениях, в меньшую сторону 3
		if (!shiftEquivalent(beginArea, currentArea, 3)) return NULL;	
		
			//Если от текущего места есть последовательность не связанных в цепочки областей
			//Достаточных для того что-бы сместится туда
			if ((endSequenceArea = searchDontLinkSequenceFromShift(currentArea, length)) != NULL){
				//Объединяем секрию в одну область
				currentArea->expand(endSequenceArea);

				return currentArea;
			}

		currentArea = currentArea->getNextArea();
	}

	return NULL;
}


Area *Gluer::getNextPiece(Area *beginArea){
	Area *resultArea;
	//Если смещение в право
	if (beginArea->getShift()>0){
		//Ищем в право блищайшую гладкую область
		resultArea = searchRightFlatAreaFromShift(beginArea, beginArea->getShift());
		
		if (resultArea != NULL) return resultArea;
		
		//Если нужной гладкой области не найденно
		//Ищем ближайшую область, длинны которой хватит для смещения в неё обрывка
		//resultArea = searchRightAnyAreaFromShift(beginArea, beginArea->getShift());
		resultArea = searechDontChainAreaFromShift(beginArea, beginArea->getShift());

		if (resultArea != NULL) return resultArea;
		
		//Если не найденна любая ближайшая область
		//То ничего не остаётся кроме как чместиться далее в следующую
		resultArea = beginArea->getNextArea();
	} else { //Если смещение в лево
		//Ищем в право блищайшую гладкую область
		resultArea = searchRightFlatAreaFromShift(beginArea, 1);

		if (resultArea != NULL) return resultArea;

		resultArea = beginArea->getNextArea();
	}
	
	return resultArea;
}

void Gluer::shiftPieceUpArea(Area *startArea, Area *endArea, int shift){
	if (endArea == NULL) return;
	Area *pervEndArea = endArea->getPervArea();
	if (pervEndArea == NULL) pervEndArea = endArea;

/*
	//Вычисляем полную длинну области смещения
	//Прринимая во внимания связанные области в низу стороны
	int leftBoundUp = startArea->getBegin();
	int leftBoundDown = leftBoundUp;

	if (startArea->getDownArea() != NULL){
		leftBoundDown = startArea->getDownArea()->getBegin();
	}

	int rightBoundUp = pervEndArea->getBegin()+pervEndArea->getLength();
	int rightBoundDown = rightBoundUp;
	
	if (pervEndArea->getDownArea() != NULL){
		rightBoundDown = pervEndArea->getDownArea()->getBegin()+pervEndArea->getDownArea()->getLength();
	}

	int leftBound = 0;
	int rightBound = 0;
	//Теперь сравниваем и выбираем области
	if (leftBoundUp <= leftBoundDown){
		leftBound = leftBoundUp;
	} else {
		leftBound = leftBoundDown;
	}

	if (rightBoundUp >= rightBoundDown){
		rightBound = rightBoundUp;
	} else {
		rightBound = rightBoundDown;
	}

	int shiftAreaStart = leftBound;
	int shiftAreaLength = rightBound - leftBound;
*/
	int shiftAreaStart = startArea->getBegin();
	int shiftAreaLength = (pervEndArea->getBegin()+pervEndArea->getLength()) - shiftAreaStart;

	//Смещаем на изображении
	bitmapShifter->shiftUpArea(
		shiftAreaStart, 
		shiftAreaLength, 
		shift
	);

	//Компенсируем смещения
	correctShiftInAreas(startArea, endArea, shift);
}

void Gluer::shiftPieceDownArea(Area *startArea, Area *endArea, int shift){
	if (endArea == NULL) return;
	Area *pervEndArea = endArea->getPervArea();
	if (pervEndArea == NULL) pervEndArea = endArea;
/*	
	//Вычисляем полную длинну области смещения
	//Прринимая во внимания связанные области в верху стороны
	int leftBoundDown = startArea->getBegin();
	int leftBoundUp = leftBoundDown;

	if (startArea->getUpArea() != NULL){
		leftBoundUp = startArea->getUpArea()->getBegin();
	}
	
	int rightBoundDown = pervEndArea->getBegin()+pervEndArea->getLength();
	int rightBoundUp = rightBoundDown;
	
	if (pervEndArea->getUpArea() != NULL){
		rightBoundUp = pervEndArea->getUpArea()->getBegin()+pervEndArea->getUpArea()->getLength();
	}
	
	int leftBound = 0;
	int rightBound = 0;
	//Теперь сравниваем и выбираем области
	if (leftBoundUp <= leftBoundDown){
		leftBound = leftBoundUp;
	} else {
		leftBound = leftBoundDown;
	}

	if (rightBoundUp >= rightBoundDown){
		rightBound = rightBoundUp;
	} else {
		rightBound = rightBoundDown;
	}
*/
	
	//int shiftAreaStart = leftBound;
	//int shiftAreaLength = rightBound - leftBound;
	
	int shiftAreaStart = startArea->getBegin();
	int shiftAreaLength = (pervEndArea->getBegin()+pervEndArea->getLength()) - shiftAreaStart;

	//Смещаем на изображении
	bitmapShifter->shiftDownArea(
		shiftAreaStart, 
		shiftAreaLength, 
		shift
	);

	//Компенсируем смещения
	correctShiftInAreas(startArea, endArea, shift);
}

//Область связанна в цепочку?
bool Gluer::consistsInChain(Area *area){
	//Вообще тут нужно два цикла, один будет считать области вверх
	//Другой области вниз! Но это утомительно долго!
	//Поэтому
	if ((area->getDownArea() != NULL) && (area->getUpArea() != NULL)) return true;
	return false;
}

void Gluer::correctShiftInAreas(Area *startArea, Area *endArea, int correctShift){
	Area *currentArea = startArea;
	while (currentArea != endArea){
		currentArea->setBegin(currentArea->getBegin() + correctShift);
		//Если текущая область находится в цепочке, только связанные области важны
		if (consistsInChain(currentArea)){
			currentArea->setShift(currentArea->getShift() - correctShift);
		}
		currentArea = currentArea->getNextArea();
	}
	
	//Если смещение в право
	if (correctShift>0){
		//Последняя область, куда происходит смещение, должна уменьшится в размерах
		//И начало должно сдвинутся
		currentArea->setBegin(currentArea->getBegin() + correctShift);
		currentArea->setLength(currentArea->getLength() - correctShift);
	}

	//Смещение в лево нас не интересует, поскольку, основное движение обработки областей идёт в право
	//А оставшиеся с лева, позади области нам не понадобятся, и какая там билебержа останется безразницы
	
}





void Gluer::glue(Area *upLine, Area *downLine, BitmapContainer *areaImage){
	//Разбиваем изображение на верхнюю и нижнюю область
	

	BitmapContainerArea upArea;
	BitmapContainerArea downArea;

	int median;
	if (areaImage->getShirina()>areaImage->getVisota()){
		median = areaImage->getVisota()/2;

		upArea.up = 0;
		upArea.left = 0;
		upArea.width = areaImage->getShirina();
		upArea.height = median-1;

		downArea.up = median;
		downArea.left = 0;
		downArea.width = areaImage->getShirina();
		downArea.height = median;

	} else {
		median = areaImage->getShirina()/2;

		upArea.up = 0;
		upArea.left = 0;
		upArea.width = median-1;
		upArea.height = areaImage->getVisota();
		
		downArea.up = 0;
		downArea.left = median;
		downArea.width = median;
		downArea.height = areaImage->getVisota();
	}

	BitmapContainer *upBitmap = areaImage->clone();
	upBitmap->setWorkArea(upArea);
	BitmapContainer *downBitmap = areaImage->clone();
	downBitmap->setWorkArea(downArea);

	//Инициализируем калькулятор смещений
	areaShiftCalculator->setDownAreaBitmap(downBitmap);
	areaShiftCalculator->setUpAreaBitmap(upBitmap);

	//Рассчитываем смещения
	calculateShiftingFromAreas(downLine);

////////////////////////////////////////////////////////////////
////////////////ОБРАБОТКА НИЖНЕЙ СТОРОНЫ///////////////////////

	Area *currentArea = downLine;
	Area *endPiece;

	#ifdef _MyDEBUG
		areaImage->workAreaSaved(std::string("C:\\before.tif"));
	#endif

	bitmapShifter->changeImage(downBitmap);
	while (currentArea != NULL){
		if ((consistsInChain(currentArea)) && (currentArea->getShift() != 0)){
			if (currentArea->getBegin() == 138){
				int q=0;
			}
			//Получаем область куда можно сместить
			endPiece = getNextPiece(currentArea);

			//Смещаем области
			shiftPieceUpArea(currentArea, endPiece, currentArea->getShift());
		}
		currentArea = currentArea->getNextArea();
	}

////////////////////////////////////////////////////////////////
////////////////ОБРАБОТКА ВЕРХНЕЙ СТОРОНЫ///////////////////////
	currentArea = upLine;

	bitmapShifter->changeImage(upBitmap);
	while (currentArea != NULL){

		if ((consistsInChain(currentArea)) && (currentArea->getShift() != 0)){
			//Получаем область куда можно сместить
			if (currentArea->getBegin() == 146){
				
				
				
				
				
				
				int a= 0;



			}
			endPiece = getNextPiece(currentArea);

			//Смещаем области
			shiftPieceDownArea(currentArea, endPiece, currentArea->getShift());

			//areaImage->workAreaSaved(std::string("C:\\aftertmp.tif"));
		}
		currentArea = currentArea->getNextArea();
	}

///////////////////////////////////////////////////////////////
	#ifdef _MyDEBUG
		areaImage->workAreaSaved(std::string("C:\\after.tif"));
	#endif

}
