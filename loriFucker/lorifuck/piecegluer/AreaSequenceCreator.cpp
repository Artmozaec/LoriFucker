#include "AreaSequenceCreator.h"

AreaSequenceCreator* AreaSequenceCreator::instance = NULL;

AreaSequenceCreator* AreaSequenceCreator::getInstance(){
	if (instance==NULL){
		instance = new AreaSequenceCreator();
	}

	return instance;
}


AreaSequenceCreator::AreaSequenceCreator(){
	//areaMinColorDiapazone = 75;
	areaMinColorDiapazone = 30;
	areaMinSize = 1;	
}


Area* AreaSequenceCreator::generate(BitmapContainer *bitmapContainer){
	int beginPosition = 0;
	int endPosition = 0;
	Color* beginColor = NULL;
	Color* endColor = NULL;
	int colorDiapazone;
	firstArea = NULL;
	lastArea = NULL;
	Area *area;
	
	BitmapIterator* bitmapIterator = new BitmapIterator(bitmapContainer);
	FlatAreaAccumulator *flatAreaAccumulator = new FlatAreaAccumulator(*bitmapIterator);
	
	while(!bitmapIterator->isEnd()){
		//Если следующий пиксель темнее
		if (bitmapIterator->isNextDarken()){
			//Начинаем создавать область градиента свет-тень
			beginPosition = bitmapIterator->getPosition();
			beginColor = bitmapIterator->getPixel();

			//Ищем где кончается градиент
			goForwardUntillWhiteDarkGradient(bitmapIterator);

			endPosition = bitmapIterator->getPosition();
			endColor = bitmapIterator->getPixel();
		} else if (bitmapIterator->isNextWhiten()){
			//Начинаем создавать область градиента тень-свет
			beginPosition = bitmapIterator->getPosition();
			beginColor = bitmapIterator->getPixel();

			//Ищем где кончается градиент
			goForwardUntillDarkWhiteGradient(bitmapIterator);

			endPosition = bitmapIterator->getPosition();
			endColor = bitmapIterator->getPixel();
		} else if (bitmapIterator->isNextEqual()){
			beginPosition = bitmapIterator->getPosition();
			bitmapIterator->nextPixel();
			endPosition = bitmapIterator->getPosition();
			flatAreaAccumulator->addArea(beginPosition, endPosition);
			continue;
		}
		

		//Оцениваем найденный участок на пороговые значения для создания области
		colorDiapazone = abs(beginColor->getGrayValue()-endColor->getGrayValue());
		
		if (
			((endPosition-beginPosition)>areaMinSize) &&
			(colorDiapazone>areaMinColorDiapazone)
		){
			//Если мы насобирали flat область, то с начала добавляем её
			if (!flatAreaAccumulator->isEmpty()){
				addArea(flatAreaAccumulator->getResultArea());
				//Очищаем аккумулятор
				flatAreaAccumulator->reset();
			}
			area = new Area(beginColor, endColor, beginPosition, endPosition-beginPosition);
			addArea(area);
		} else {
			flatAreaAccumulator->addArea(beginPosition, endPosition);
		}
	}

	//Если была не законченная гладкая область, добавляем
	if (!flatAreaAccumulator->isEmpty()){
		addArea(flatAreaAccumulator->getResultArea());
	}

	return firstArea;
}

void AreaSequenceCreator::goForwardUntillWhiteDarkGradient(BitmapIterator *bitmapIterator){
	while (bitmapIterator->isNextDarken()){
		bitmapIterator->nextPixel();
	}
}

void AreaSequenceCreator::goForwardUntillDarkWhiteGradient(BitmapIterator *bitmapIterator){
	while (bitmapIterator->isNextWhiten()){
		bitmapIterator->nextPixel();
	}
}


void AreaSequenceCreator::addArea(Area *newArea){
	if (firstArea==NULL){
		firstArea = newArea;
	} else {
		lastArea->linkNextArea(newArea);
	}
	
	lastArea = newArea;
}





