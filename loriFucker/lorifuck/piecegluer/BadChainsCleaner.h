#ifndef BadLinksCleanerH
#define BadLinksCleanerH
#include <windows.h>
#include "Area.h"

class BadChainsCleaner{
public:
	static BadChainsCleaner* getInstance();

	void clearBadChains(Area *area);
private:
	BadChainsCleaner();
	static BadChainsCleaner* instance;

	//Начиная от области beginArea ищет пересечение с областью currentArea и влозвращает пересечение
	Area* findCrossChain(Area* crossFindedArea, Area* beginArea);

	//Разрушает все связи в цепочке вверх начиная c area
	void destroyChain(Area* downArea);

	//Области прересекаются или идут парралельно?
	bool isCrossedChain(Area *firstChain, Area *secondChain);

	//Ищет следующую область которая связанна на 4 области вверх
	Area *findNextChain(Area *beginArea);

	//Качество цепочки (насколько она последовательна)
	int getQualityChain(Area *chain);

	//Возвращает true если начало firstArea располагается перед secondArea
	bool isTrueSequence(Area *firstArea, Area *secondArea);

	//Разрушает худшую цепочку
	void clearBadChain(Area *firstArea, Area *secondArea);

	//Полная ширина цепочки
	int getWeightChain(Area *chain);

	//Если расстояние между связанными областями больше чем порог
	bool chainLengthLinksIsBad(Area *chain);

};

#endif