#include "TrashAreaCleaner.h"

TrashAreaCleaner* TrashAreaCleaner::instance = NULL;

TrashAreaCleaner *TrashAreaCleaner::getInstance(){
	if (instance==NULL){
		instance = new TrashAreaCleaner();
	}

	return instance;
}

TrashAreaCleaner::TrashAreaCleaner(){
}


//������������������ �������� ����������?
bool TrashAreaCleaner::areasIsSolid(Area *firstArea, Area *secondArea){
	if ((firstArea == NULL) || (secondArea == NULL)) return false;

	//���� ����-�� ���� �� �������� flat ����� ��� �� ������������������ � �����!
	if (firstArea->getBeginColor()->getGrayValue() == firstArea->getEndColor()->getGrayValue()) return false;
	if (secondArea->getBeginColor()->getGrayValue() == secondArea->getEndColor()->getGrayValue()) return false;

	//����������� ��������� ������ ���� � ����� ��������  � ���� �������
	//����� false
	if((
		(firstArea->getBeginColor()->getGrayValue()>firstArea->getEndColor()->getGrayValue()) &&
		(secondArea->getBeginColor()->getGrayValue()<secondArea->getEndColor()->getGrayValue())
	)||(
		(firstArea->getBeginColor()->getGrayValue()<firstArea->getEndColor()->getGrayValue()) &&
		(secondArea->getBeginColor()->getGrayValue()>secondArea->getEndColor()->getGrayValue())
	)) return false;

	//������� ��������� ����� ������ ������� ������ ��������� � ������ ������ ������ �������
	if (!firstArea->getEndColor()->equal(secondArea->getBeginColor(), 30)) return false;
	return true;
}


//��������� ������� ��������?
bool TrashAreaCleaner::isTrashNextArea(Area *area){
	Area *nextArea = area->getNextArea();

	if (nextArea == NULL) return false;
	
	//���� ������ ������� ������ ���������
	if (nextArea->getLength()<5){
		//����� ����� ��������-�� ������������� �������
		//����������� ����������
		if (areasIsSolid(area, nextArea->getNextArea())) return true;
	}

	return false;
}

void TrashAreaCleaner::clearTrashAreas(Area *firstArea){
	Area *currnetArea = firstArea;
	while (currnetArea != NULL){
		//���� ��������� ������� ��������
		if (isTrashNextArea(currnetArea)){
			
			//currnetArea = takeoverAreas(currnetArea->getPervArea(), currnetArea->getNextArea());
			//������� ������� ������� � ����, ��������� �������� ������� � ������� ����� ��
			currnetArea->expand(currnetArea->getNextArea()->getNextArea());

		}

		currnetArea = currnetArea->getNextArea();
	}
}