#include "BadChainsCleaner.h"

BadChainsCleaner* BadChainsCleaner::instance = NULL;

BadChainsCleaner* BadChainsCleaner::getInstance(){
	if (instance==NULL){
		instance = new BadChainsCleaner();
	}

	return instance;
}

BadChainsCleaner::BadChainsCleaner(){
}

//���� ��������� ������� ������� �������� �� 4 ������� �����
Area *BadChainsCleaner::findNextChain(Area *beginArea){
	Area *currentArea = beginArea;
	Area *chain = NULL;
	while (currentArea != NULL){
		if (currentArea->AmountLinksToUpBound() >=3) return currentArea;
		currentArea = currentArea->getNextArea();
	}
	return chain;
}

//���������� true ���� ������ firstArea ������������� ����� secondArea
bool BadChainsCleaner::isTrueSequence(Area *firstArea, Area *secondArea){
	if (firstArea->getBegin()<secondArea->getBegin()) return true;
	return false;
}

//������� �������� ������������� ��� ���� �����������?
bool BadChainsCleaner::isCrossedChain(Area *firstChain, Area *secondChain){
	Area *firstChainArea = firstChain;
	Area *secondChainArea = secondChain;
	
	//���������� ���� ������������ ��������
	//true - c ����� �� ����
	//false - ��������
	bool dirKey = isTrueSequence(firstChain, secondChain);
	
	//���� � ����� ����� ���������� ��������� �����������
	//������ ����� ����� ������������ ������������ �������
	while ((firstChainArea!=NULL) && (secondChainArea!=NULL)){

		if (isTrueSequence(firstChainArea, secondChainArea) != dirKey) return true;

		firstChainArea = firstChainArea->getUpArea();
		secondChainArea = secondChainArea->getUpArea();
	}

	return false;
}

//������� �� ������� beginArea ���� ����������� � �������� currentArea � ����������� �����������
Area* BadChainsCleaner::findCrossChain(Area* crossFindedChain, Area* beginArea){
	Area *currentChain = findNextChain(beginArea);
	while (currentChain != NULL){
		//���� ���� ����������� ������� 
		if (isCrossedChain(crossFindedChain, currentChain)){ 
			return currentChain;
		}
		
		//������� ��������� �������
		currentChain = findNextChain(currentChain->getNextArea());
	}

	return NULL;
}

//������ ������ �������
int BadChainsCleaner::getWeightChain(Area *chain){
	Area *currentArea = NULL;

	//���� ����� ����� �������
	currentArea = chain;
	int leftPosition = currentArea->getBegin();
	while (currentArea != NULL){
		if (currentArea->getBegin() < leftPosition){
			leftPosition = currentArea->getBegin(); 
		}
		currentArea = currentArea->getUpArea();
	}


	//���� ����� ������ �������
	currentArea = chain;
	int rightPosition = currentArea->getBegin()+currentArea->getLength();
	while (currentArea != NULL){
		if (currentArea->getBegin()+currentArea->getLength() > rightPosition){
			rightPosition = currentArea->getBegin()+currentArea->getLength(); 
		}
		currentArea = currentArea->getUpArea();
	}

	return rightPosition-leftPosition;
}



//�������� �������
int BadChainsCleaner::getQualityChain(Area *chain){
	int toRight = 0;
	int toLeft = 0;

	Area *currentArea = chain;
	while ((currentArea != NULL) && (currentArea->getUpArea() != NULL)){
		if (isTrueSequence(currentArea, currentArea->getUpArea())){
			toRight++;
		} else {
			toLeft++;
		}

		currentArea = currentArea->getUpArea();
	}

	if ((toRight == 0) || (toLeft == 0)) return 1;
	return 0;
}

//��������� ������ �������
void BadChainsCleaner::clearBadChain(Area *firstChain, Area *secondChain){
	int qualityFirstChain = getQualityChain(firstChain);
	int qualitySecondChain = getQualityChain(secondChain);

	if (qualityFirstChain>qualitySecondChain){
		destroyChain(secondChain);
	}
	if (qualityFirstChain<qualitySecondChain){
		destroyChain(firstChain);
	}

	//� ������ ������� � ������ ������, �� �������� ������ ������ ����!
	//���� ������ �� ������� ����
	if (qualityFirstChain==qualitySecondChain){
		if (getWeightChain(firstChain)>getWeightChain(secondChain)){
			destroyChain(firstChain);
		} else {
			destroyChain(secondChain);
		}
	}
}


//���� ���������� ����� ���������� ��������� ������ ��� �����
bool BadChainsCleaner::chainLengthLinksIsBad(Area *chain){
	Area *currentArea = chain;
	int threshold = 50;
	int leftPosition = currentArea->getBegin();
	while (currentArea->getUpArea() != NULL){
		
		if (abs(currentArea->getBegin() - currentArea->getUpArea()->getBegin()) > threshold) return true;
		
		currentArea = currentArea->getUpArea();
	}
	return false;
}


//���� �������������� ������� ��������
//�� ������� ������� ����� ������� �������� ���������
void BadChainsCleaner::clearBadChains(Area *beginArea){
	Area *currentChain = findNextChain(beginArea);
	Area *crossChain = NULL;

	while (currentChain != NULL){
		

		//���� ���������� ����� ��������� ������ ��� �����
		if (chainLengthLinksIsBad(currentChain)){
			destroyChain(currentChain);
		} else {
			//���� ������� ������������ �������
			crossChain = findCrossChain(currentChain, beginArea);
			//���� �����
			if (crossChain != NULL){
				//������� ����� ������ �������
				clearBadChain(crossChain, currentChain);
			}
		}


		//������� ��������� �������
		currentChain = findNextChain(currentChain->getNextArea());
	}
}


/*
//�������� ������� (��������� ��� ���������������)
int BadChainsCleaner::getQualityChain(Area *chain){
	return 0;
}
*/



//��������� ��� ����� ����� ������� c area
void BadChainsCleaner::destroyChain(Area* downArea){
	Area *currentArea = downArea;
	do{
		//��������� ����� � ����
		currentArea->linkDownArea(NULL);

		//�������� �������, ���������
		currentArea = currentArea->getUpArea();
	}while (currentArea != NULL);
}