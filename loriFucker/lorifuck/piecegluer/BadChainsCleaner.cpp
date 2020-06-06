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

//Ищет следующую область которая связанна на 4 области вверх
Area *BadChainsCleaner::findNextChain(Area *beginArea){
	Area *currentArea = beginArea;
	Area *chain = NULL;
	while (currentArea != NULL){
		if (currentArea->AmountLinksToUpBound() >=3) return currentArea;
		currentArea = currentArea->getNextArea();
	}
	return chain;
}

//Возвращает true если начало firstArea располагается перед secondArea
bool BadChainsCleaner::isTrueSequence(Area *firstArea, Area *secondArea){
	if (firstArea->getBegin()<secondArea->getBegin()) return true;
	return false;
}

//Цепочки областей прересекаются или идут парралельно?
bool BadChainsCleaner::isCrossedChain(Area *firstChain, Area *secondChain){
	Area *firstChainArea = firstChain;
	Area *secondChainArea = secondChain;
	
	//Определяем куда направляется смещение
	//true - c право на лево
	//false - наоборот
	bool dirKey = isTrueSequence(firstChain, secondChain);
	
	//Если в цикле будет обнаружено изменение направления
	//Значит имеет место перекрестное расположение цепочек
	while ((firstChainArea!=NULL) && (secondChainArea!=NULL)){

		if (isTrueSequence(firstChainArea, secondChainArea) != dirKey) return true;

		firstChainArea = firstChainArea->getUpArea();
		secondChainArea = secondChainArea->getUpArea();
	}

	return false;
}

//Начиная от области beginArea ищет пересечение с областью currentArea и влозвращает пересечение
Area* BadChainsCleaner::findCrossChain(Area* crossFindedChain, Area* beginArea){
	Area *currentChain = findNextChain(beginArea);
	while (currentChain != NULL){
		//Если есть пересечение искомой 
		if (isCrossedChain(crossFindedChain, currentChain)){ 
			return currentChain;
		}
		
		//Находим следующую цепочку
		currentChain = findNextChain(currentChain->getNextArea());
	}

	return NULL;
}

//Полная ширина цепочки
int BadChainsCleaner::getWeightChain(Area *chain){
	Area *currentArea = NULL;

	//Ищем самую левую позицию
	currentArea = chain;
	int leftPosition = currentArea->getBegin();
	while (currentArea != NULL){
		if (currentArea->getBegin() < leftPosition){
			leftPosition = currentArea->getBegin(); 
		}
		currentArea = currentArea->getUpArea();
	}


	//Ищем самую правую позицию
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



//Качество цепочки
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

//Разрушает худшую цепочку
void BadChainsCleaner::clearBadChain(Area *firstChain, Area *secondChain){
	int qualityFirstChain = getQualityChain(firstChain);
	int qualitySecondChain = getQualityChain(secondChain);

	if (qualityFirstChain>qualitySecondChain){
		destroyChain(secondChain);
	}
	if (qualityFirstChain<qualitySecondChain){
		destroyChain(firstChain);
	}

	//И первая цепочка и вторая плохие, но остаться должна только одна!
	//Хуже обычно та которая шире
	if (qualityFirstChain==qualitySecondChain){
		if (getWeightChain(firstChain)>getWeightChain(secondChain)){
			destroyChain(firstChain);
		} else {
			destroyChain(secondChain);
		}
	}
}


//Если расстояние между связанными областями больше чем порог
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


//Ищем пересекающиеся цепочки областей
//та цепочка которая имеет меньшее качество удаляестя
void BadChainsCleaner::clearBadChains(Area *beginArea){
	Area *currentChain = findNextChain(beginArea);
	Area *crossChain = NULL;

	while (currentChain != NULL){
		

		//Если расстояние между областями больше чем порог
		if (chainLengthLinksIsBad(currentChain)){
			destroyChain(currentChain);
		} else {
			//Ищем цепочку пересекающую текущую
			crossChain = findCrossChain(currentChain, beginArea);
			//Если нашли
			if (crossChain != NULL){
				//Убираем самую плохую цепочку
				clearBadChain(crossChain, currentChain);
			}
		}


		//Находим следующую цепочку
		currentChain = findNextChain(currentChain->getNextArea());
	}
}


/*
//Качество цепочки (насколько она последовательна)
int BadChainsCleaner::getQualityChain(Area *chain){
	return 0;
}
*/



//Разрушает все связи вверх начиная c area
void BadChainsCleaner::destroyChain(Area* downArea){
	Area *currentArea = downArea;
	do{
		//Разрываем связь с низу
		currentArea->linkDownArea(NULL);

		//Получаем верхний, следующий
		currentArea = currentArea->getUpArea();
	}while (currentArea != NULL);
}