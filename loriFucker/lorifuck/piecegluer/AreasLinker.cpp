#include "AreasLinker.h"

AreasLinker* AreasLinker::instance = NULL;

AreasLinker::AreasLinker(){

}

AreasLinker *AreasLinker::getInstance(){
	if (instance==NULL){
		instance = new AreasLinker();
	}

	return instance;
}

//��������� �� ����������
Area *AreasLinker::getMoreNearDistance(Area *etalon, Area *first, Area *second){
	if (first == NULL) return second;
	if (second == NULL) return first;
	int firstDistance = abs(etalon->getDistance(first));
	int secondDistance = abs(etalon->getDistance(second));
	
	if (firstDistance>secondDistance){
		return second;
	} else {
		return first;
	}
}

//��������� ������� �� �����
Area *AreasLinker::getMoreNearColor(Area *etalon, Area *first, Area *second){
	if (first == NULL) return second;
	if (second == NULL) return first;
	int firstColorDistance = etalon->getBeginColor()->colorDifference(first->getBeginColor());
	int secondColorDistance = etalon->getBeginColor()->colorDifference(second->getBeginColor());

	if (firstColorDistance>secondColorDistance){
		return second;
	} else {
		return first;
	}
	
}


Area *AreasLinker::getMoreNearDistanceAndColor(Area *etalon, Area *first, Area *second){
	if (first == NULL) return second;
	if (second == NULL) return first;
	int firstDistance = abs(etalon->getDistance(first));
	int secondDistance = abs(etalon->getDistance(second));
	//���� ������ ����� ����� ����� �������� ��������������
	//�� ������� ������� ��������� �� �����
	if ((
		(etalon->getBegin()>first->getBegin()) && 
		(etalon->getBegin()<second->getBegin())
		)||(
		(etalon->getBegin()<first->getBegin()) && 
		(etalon->getBegin()>second->getBegin())
	)){
		//����, � ����-�� ��������� ������ ���������� ��������
		if (firstDistance+secondDistance<16){
			//���������� ��������� �� �����
			return getMoreNearColor(etalon, first, second);
		}
	}

	//�� ����������
	return getMoreNearDistance(etalon, first, second);

}


//������� ����� ������� � etalon �������, �� first � second ��������� �
/*
Area *AreasLinker::getMoreNear(Area *etalon, Area *first, Area *second){
	if (first == NULL) return second;
	if (second == NULL) return first;

	int firstDistance = abs(etalon->getDistance(first));
	int secondDistance = abs(etalon->getDistance(second));
	//int firstDistance = etalon->getBegin()-first->getBegin();
	//int secondDistance = etalon->getBegin()-second->getBegin();

	//���� ������ ����� ����� ����� �������� ��������������
	//�� ������� ������� ��������� �� �����
	if ((
		(etalon->getBegin()>first->getBegin()) && 
		(etalon->getBegin()<second->getBegin())
		)||(
		(etalon->getBegin()<first->getBegin()) && 
		(etalon->getBegin()>second->getBegin())
	)){
		//����, � ����-�� ��������� ������ ���������� ��������
		if (firstDistance+secondDistance<16){
			int firstColorDistance = etalon->getBeginColor()->colorDifference(first->getBeginColor());
			int secondColorDistance = etalon->getBeginColor()->colorDifference(second->getBeginColor());

			if (firstColorDistance>secondColorDistance){
				return second;
			} else {
				return first;
			}
		}
	}

	if (firstDistance>secondDistance){
		return second;
	} else {
		return first;
	}
}
*/

void AreasLinker::linkAreaLinesToGrid(Area* upSideUpLine, Area* upSideDownLine, Area* downSideUpLine, Area* downSideDownLine){
	//��������� ��������� ����� ������� �������
	primaryLink(upSideUpLine, upSideDownLine);

	//�������� ��������� ����� �� ������ �������
	primaryLink(downSideUpLine, downSideDownLine);

	//��������� ��������� �����
	secondaryLink(upSideDownLine, downSideUpLine);
}



//����� ��������� ������� ������� ������� ����� � ����
Area *AreasLinker::findProximateLinkedDown(Area *seekingArea, Area *searchSequence){
	Area *foundArea = NULL;
	do{
		foundArea = searchProximate(seekingArea, searchSequence);
		if (foundArea == NULL) return foundArea;
		if (foundArea->getDownArea() != NULL){
			return foundArea; 
		} else {
			searchSequence = foundArea->getNextArea();
		}
		
	}while(true);
}



//��������� ���������� ��� ��������� ��������� ��������
void AreasLinker::secondaryLink(Area *upArea, Area *downArea){
	Area *currentArea = upArea;
	Area *foundArea = NULL;
	while (currentArea != NULL){
		//���� ����� ���� �����, ������ ���� ����� �������� ������� ������� �����
		if (currentArea->getUpArea() != NULL){
			//���� � ������ ������������������ �������� ��������� �� ������������ � �� �����
			foundArea = findProximateLinkedDown(currentArea, downArea);
			//���� ������� �������, ��������� ��
			if (foundArea != NULL){
				currentArea->linkDownArea(foundArea);
			}
		}
		
		currentArea = currentArea->getNextArea();
	}
}


//��������� ����������, �� ��������� �������
void AreasLinker::primaryLink(Area *upArea, Area *downArea){
	Area *currentArea = upArea;
	Area *foundArea = NULL;
	while (currentArea != NULL){
		if (currentArea->getBegin() == 127){
			int a = currentArea->getBegin();
		}
		//���� ������� ����������(����� � ������ � ����� �� �����)
		if (!currentArea->getBeginColor()->equal(currentArea->getEndColor(), 0)){
			//���� � ������ ������������������ �������� ��������� �� ������������ � �� �����
			foundArea = searchProximate(currentArea, downArea);
			//���� ������� �������, ��������� ��
			if (foundArea != NULL){
				currentArea->linkDownArea(foundArea);
			}
		}
		
		currentArea = currentArea->getNextArea();
	}

}

//����� ��������� ������� �������
Area *AreasLinker::searchProximate(Area *seekingArea,  Area *searchSequence){
	Area *resultArea = NULL;
	Area *currentArea = searchSequence;
	while(currentArea != NULL){
		//���������� ������� ������� �� ����� � �������
		if (seekingArea->equalColor(currentArea, 100)){//40//80
			//���� ��������� ��������� ������� ����� � ������� ��� ��������� ����������, �������� �
			if (currentArea == getMoreNearDistance(seekingArea, resultArea, currentArea)){

				//���� ��������� ������� ��� ��������
				if (currentArea->getUpArea() != NULL){
					//���� ������� ������� ����� � ��������� ��� ��������� � ���������, 
					//���� ���������� ����� ���� ����, ��������� ��� �� �����
					if (seekingArea == getMoreNearDistanceAndColor(currentArea, seekingArea, currentArea->getUpArea())){
						resultArea = currentArea;
					}
				} else {
					resultArea = currentArea;
				}
			}
		}
		currentArea = currentArea->getNextArea();
	}

	return resultArea;
}
