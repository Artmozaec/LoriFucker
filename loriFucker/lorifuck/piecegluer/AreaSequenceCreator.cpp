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
		//���� ��������� ������� ������
		if (bitmapIterator->isNextDarken()){
			//�������� ��������� ������� ��������� ����-����
			beginPosition = bitmapIterator->getPosition();
			beginColor = bitmapIterator->getPixel();

			//���� ��� ��������� ��������
			goForwardUntillWhiteDarkGradient(bitmapIterator);

			endPosition = bitmapIterator->getPosition();
			endColor = bitmapIterator->getPixel();
		} else if (bitmapIterator->isNextWhiten()){
			//�������� ��������� ������� ��������� ����-����
			beginPosition = bitmapIterator->getPosition();
			beginColor = bitmapIterator->getPixel();

			//���� ��� ��������� ��������
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
		

		//��������� ��������� ������� �� ��������� �������� ��� �������� �������
		colorDiapazone = abs(beginColor->getGrayValue()-endColor->getGrayValue());
		
		if (
			((endPosition-beginPosition)>areaMinSize) &&
			(colorDiapazone>areaMinColorDiapazone)
		){
			//���� �� ���������� flat �������, �� � ������ ��������� �
			if (!flatAreaAccumulator->isEmpty()){
				addArea(flatAreaAccumulator->getResultArea());
				//������� �����������
				flatAreaAccumulator->reset();
			}
			area = new Area(beginColor, endColor, beginPosition, endPosition-beginPosition);
			addArea(area);
		} else {
			flatAreaAccumulator->addArea(beginPosition, endPosition);
		}
	}

	//���� ���� �� ����������� ������� �������, ���������
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





