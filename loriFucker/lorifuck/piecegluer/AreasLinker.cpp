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

//Ближайшая по расстоянию
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

//Ближайшая область по цвету
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
	//Если эталон стоит между двумя близкими альтернативами
	//То следует сделать сравнение по цвету
	if ((
		(etalon->getBegin()>first->getBegin()) && 
		(etalon->getBegin()<second->getBegin())
		)||(
		(etalon->getBegin()<first->getBegin()) && 
		(etalon->getBegin()>second->getBegin())
	)){
		//Если, к тому-же дистанции меньше порогового значения
		if (firstDistance+secondDistance<16){
			//Возвращаем ближайшую по цвету
			return getMoreNearColor(etalon, first, second);
		}
	}

	//По расстоянию
	return getMoreNearDistance(etalon, first, second);

}


//Находит самую близкую к etalon область, из first и second возвращая её
/*
Area *AreasLinker::getMoreNear(Area *etalon, Area *first, Area *second){
	if (first == NULL) return second;
	if (second == NULL) return first;

	int firstDistance = abs(etalon->getDistance(first));
	int secondDistance = abs(etalon->getDistance(second));
	//int firstDistance = etalon->getBegin()-first->getBegin();
	//int secondDistance = etalon->getBegin()-second->getBegin();

	//Если эталон стоит между двумя близкими альтернативами
	//То следует сделать сравнение по цвету
	if ((
		(etalon->getBegin()>first->getBegin()) && 
		(etalon->getBegin()<second->getBegin())
		)||(
		(etalon->getBegin()<first->getBegin()) && 
		(etalon->getBegin()>second->getBegin())
	)){
		//Если, к тому-же дистанции меньше порогового значения
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
	//выполняем первичную связь верхней стороны
	primaryLink(upSideUpLine, upSideDownLine);

	//Выплняем первичную связь со второй стороны
	primaryLink(downSideUpLine, downSideDownLine);

	//Выполняем вторичную связь
	secondaryLink(upSideDownLine, downSideUpLine);
}



//Поиск ближайшей похожей области имеящей связь с низу
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



//Вторичное связывание уже связанных первичным областей
void AreasLinker::secondaryLink(Area *upArea, Area *downArea){
	Area *currentArea = upArea;
	Area *foundArea = NULL;
	while (currentArea != NULL){
		//Если верху есть связь, значит есть смысл поискать похожую область внизу
		if (currentArea->getUpArea() != NULL){
			//Ищем в нижней последовательности областей ближайшую по расположению и по цвету
			foundArea = findProximateLinkedDown(currentArea, downArea);
			//Если найдена область, связываем их
			if (foundArea != NULL){
				currentArea->linkDownArea(foundArea);
			}
		}
		
		currentArea = currentArea->getNextArea();
	}
}


//Первичное связывание, не связанных областе
void AreasLinker::primaryLink(Area *upArea, Area *downArea){
	Area *currentArea = upArea;
	Area *foundArea = NULL;
	while (currentArea != NULL){
		if (currentArea->getBegin() == 127){
			int a = currentArea->getBegin();
		}
		//Если область гардиентна(цвета в начале и конце не равны)
		if (!currentArea->getBeginColor()->equal(currentArea->getEndColor(), 0)){
			//Ищем в нижней последовательности областей ближайшую по расположению и по цвету
			foundArea = searchProximate(currentArea, downArea);
			//Если найдена область, связываем их
			if (foundArea != NULL){
				currentArea->linkDownArea(foundArea);
			}
		}
		
		currentArea = currentArea->getNextArea();
	}

}

//Поиск ближайшей похожей области
Area *AreasLinker::searchProximate(Area *seekingArea,  Area *searchSequence){
	Area *resultArea = NULL;
	Area *currentArea = searchSequence;
	while(currentArea != NULL){
		//Сравниваем текущую область по цвету с искомой
		if (seekingArea->equalColor(currentArea, 100)){//40//80
			//Если следующая найденная область ближе к искомой чем найденная предыдущая, заменяем её
			if (currentArea == getMoreNearDistance(seekingArea, resultArea, currentArea)){

				//Если найденная область уже связанна
				if (currentArea->getUpArea() != NULL){
					//Если искомая область ближе к найденной чем связанная с найденной, 
					//Если расстояние между ними мало, сравнение идёт по цвету
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
