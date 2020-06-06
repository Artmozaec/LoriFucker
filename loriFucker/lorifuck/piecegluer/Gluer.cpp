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

//������������ �������� ��� ���� �������� � �������� ������������ � ��� �������
void Gluer::calculateShiftingFromAreas(Area *downLine){
	Area *currentArea = downLine;
	while (currentArea != NULL){
		//���� ������� �������� � �������
		//�� ��� ����� �������� ��� ��� ������ �������
		if (currentArea->getUpArea() != NULL){
			areaShiftCalculator->shiftCalculate(currentArea->getUpArea(), currentArea);
		}

		currentArea = currentArea->getNextArea();
	}

}

//���������� ������ ���� ������������ ������� �� ������ � ������� �������� ��� ������
bool Gluer::shiftEquivalent(Area *etalonArea, Area *equalArea, int threshold){
/*	
	if (((etalonArea->getShift() < 0) && (equalArea->getShift() > 0)) ||
		((etalonArea->getShift() > 0) && (equalArea->getShift() < 0))) return false;
*/
	//��� ������� ��������� � �����
	if ((etalonArea->getShift() >= 0) && (equalArea->getShift() >= 0)){
		//���� �������� ������������ ������ ���������, �������� ������� �� �������� ������������
		if (equalArea->getShift() > etalonArea->getShift()) return true;

		int shiftDelta = equalArea->getShift() - etalonArea->getShift();
		if (shiftDelta > threshold) return false;
		return true;
	}
	//��� ������� ��������� � ����
	if ((etalonArea->getShift() < 0) && (equalArea->getShift() < 0)){
		//�������� ������� �� �������� ������������! � ��������, ���� ���� ������� � ����
		if (equalArea->getShift() < etalonArea->getShift()) return true;
		
		int shiftDelta = equalArea->getShift() - etalonArea->getShift();
		if ((shiftDelta < 0) && (abs(shiftDelta) > threshold)) return false;
		return true;
	}

	return false;
}


//���� �� beginArea ������� ������� �� ������ ������ length
Area *Gluer::searchRightFlatAreaFromShift(Area *beginArea, int length){
	Area *currentArea = beginArea;
	//signed int shiftDelta = 0;
	while (currentArea != NULL){
		//���� ������� �������� - � �������
		//���� ������� ����� �������� ������ ��� ���������������
		//����� ������
		
		if (!shiftEquivalent(beginArea, currentArea, 3)) return NULL;

		//���� ������� �������
		if (currentArea->getBeginColor()->getGrayValue() == currentArea->getEndColor()->getGrayValue()){
			//���� ������ ����������
			if (currentArea->getLength() >= length) return currentArea;
		}
		currentArea = currentArea->getNextArea();
	}
	return NULL;
}

//���� �� beginArea ����� ������� �� ������ ������ length
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


//�� beginArea �������� ����� ������������������ �������� ������� �� � �������
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
		//���� �������� �� ���������� � beginArea, 
		//������ ��� �������� �� ����� ��������� ��� ���������� ���������
		//������� � ���������, � ������� ������� 3
		if (!shiftEquivalent(beginArea, currentArea, 3)) return NULL;	
		
			//���� �� �������� ����� ���� ������������������ �� ��������� � ������� ��������
			//����������� ��� ���� ���-�� ��������� ����
			if ((endSequenceArea = searchDontLinkSequenceFromShift(currentArea, length)) != NULL){
				//���������� ������ � ���� �������
				currentArea->expand(endSequenceArea);

				return currentArea;
			}

		currentArea = currentArea->getNextArea();
	}

	return NULL;
}


Area *Gluer::getNextPiece(Area *beginArea){
	Area *resultArea;
	//���� �������� � �����
	if (beginArea->getShift()>0){
		//���� � ����� ��������� ������� �������
		resultArea = searchRightFlatAreaFromShift(beginArea, beginArea->getShift());
		
		if (resultArea != NULL) return resultArea;
		
		//���� ������ ������� ������� �� ��������
		//���� ��������� �������, ������ ������� ������ ��� �������� � �� �������
		//resultArea = searchRightAnyAreaFromShift(beginArea, beginArea->getShift());
		resultArea = searechDontChainAreaFromShift(beginArea, beginArea->getShift());

		if (resultArea != NULL) return resultArea;
		
		//���� �� �������� ����� ��������� �������
		//�� ������ �� ������� ����� ��� ���������� ����� � ���������
		resultArea = beginArea->getNextArea();
	} else { //���� �������� � ����
		//���� � ����� ��������� ������� �������
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
	//��������� ������ ������ ������� ��������
	//��������� �� �������� ��������� ������� � ���� �������
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
	//������ ���������� � �������� �������
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

	//������� �� �����������
	bitmapShifter->shiftUpArea(
		shiftAreaStart, 
		shiftAreaLength, 
		shift
	);

	//������������ ��������
	correctShiftInAreas(startArea, endArea, shift);
}

void Gluer::shiftPieceDownArea(Area *startArea, Area *endArea, int shift){
	if (endArea == NULL) return;
	Area *pervEndArea = endArea->getPervArea();
	if (pervEndArea == NULL) pervEndArea = endArea;
/*	
	//��������� ������ ������ ������� ��������
	//��������� �� �������� ��������� ������� � ����� �������
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
	//������ ���������� � �������� �������
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

	//������� �� �����������
	bitmapShifter->shiftDownArea(
		shiftAreaStart, 
		shiftAreaLength, 
		shift
	);

	//������������ ��������
	correctShiftInAreas(startArea, endArea, shift);
}

//������� �������� � �������?
bool Gluer::consistsInChain(Area *area){
	//������ ��� ����� ��� �����, ���� ����� ������� ������� �����
	//������ ������� ����! �� ��� ����������� �����!
	//�������
	if ((area->getDownArea() != NULL) && (area->getUpArea() != NULL)) return true;
	return false;
}

void Gluer::correctShiftInAreas(Area *startArea, Area *endArea, int correctShift){
	Area *currentArea = startArea;
	while (currentArea != endArea){
		currentArea->setBegin(currentArea->getBegin() + correctShift);
		//���� ������� ������� ��������� � �������, ������ ��������� ������� �����
		if (consistsInChain(currentArea)){
			currentArea->setShift(currentArea->getShift() - correctShift);
		}
		currentArea = currentArea->getNextArea();
	}
	
	//���� �������� � �����
	if (correctShift>0){
		//��������� �������, ���� ���������� ��������, ������ ���������� � ��������
		//� ������ ������ ���������
		currentArea->setBegin(currentArea->getBegin() + correctShift);
		currentArea->setLength(currentArea->getLength() - correctShift);
	}

	//�������� � ���� ��� �� ����������, ���������, �������� �������� ��������� �������� ��� � �����
	//� ���������� � ����, ������ ������� ��� �� �����������, � ����� ��� ��������� ��������� ����������
	
}





void Gluer::glue(Area *upLine, Area *downLine, BitmapContainer *areaImage){
	//��������� ����������� �� ������� � ������ �������
	

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

	//�������������� ����������� ��������
	areaShiftCalculator->setDownAreaBitmap(downBitmap);
	areaShiftCalculator->setUpAreaBitmap(upBitmap);

	//������������ ��������
	calculateShiftingFromAreas(downLine);

////////////////////////////////////////////////////////////////
////////////////��������� ������ �������///////////////////////

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
			//�������� ������� ���� ����� ��������
			endPiece = getNextPiece(currentArea);

			//������� �������
			shiftPieceUpArea(currentArea, endPiece, currentArea->getShift());
		}
		currentArea = currentArea->getNextArea();
	}

////////////////////////////////////////////////////////////////
////////////////��������� ������� �������///////////////////////
	currentArea = upLine;

	bitmapShifter->changeImage(upBitmap);
	while (currentArea != NULL){

		if ((consistsInChain(currentArea)) && (currentArea->getShift() != 0)){
			//�������� ������� ���� ����� ��������
			if (currentArea->getBegin() == 146){
				
				
				
				
				
				
				int a= 0;



			}
			endPiece = getNextPiece(currentArea);

			//������� �������
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
