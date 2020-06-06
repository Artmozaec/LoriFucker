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


//Последовательность областей непрерывна?
bool TrashAreaCleaner::areasIsSolid(Area *firstArea, Area *secondArea){
	if ((firstArea == NULL) || (secondArea == NULL)) return false;

	//Если хотя-бы одна из областей flat тогда это не последовательность а гамно!
	if (firstArea->getBeginColor()->getGrayValue() == firstArea->getEndColor()->getGrayValue()) return false;
	if (secondArea->getBeginColor()->getGrayValue() == secondArea->getEndColor()->getGrayValue()) return false;

	//Направление градиента должно быть в обоих областях  в одну сторону
	//Иначе false
	if((
		(firstArea->getBeginColor()->getGrayValue()>firstArea->getEndColor()->getGrayValue()) &&
		(secondArea->getBeginColor()->getGrayValue()<secondArea->getEndColor()->getGrayValue())
	)||(
		(firstArea->getBeginColor()->getGrayValue()<firstArea->getEndColor()->getGrayValue()) &&
		(secondArea->getBeginColor()->getGrayValue()>secondArea->getEndColor()->getGrayValue())
	)) return false;

	//оттенок конечного цвета первой области должен совпадать с первым цветом второй области
	if (!firstArea->getEndColor()->equal(secondArea->getBeginColor(), 30)) return false;
	return true;
}


//Следующая область мусорная?
bool TrashAreaCleaner::isTrashNextArea(Area *area){
	Area *nextArea = area->getNextArea();

	if (nextArea == NULL) return false;
	
	//Если размер области меньше пороговой
	if (nextArea->getLength()<5){
		//Тогда узнаём являются-ли соседствующие области
		//непрерывным градиентом
		if (areasIsSolid(area, nextArea->getNextArea())) return true;
	}

	return false;
}

void TrashAreaCleaner::clearTrashAreas(Area *firstArea){
	Area *currnetArea = firstArea;
	while (currnetArea != NULL){
		//Если следующая область мусорная
		if (isTrashNextArea(currnetArea)){
			
			//currnetArea = takeoverAreas(currnetArea->getPervArea(), currnetArea->getNextArea());
			//Текущая область включит в себя, следующую мусорную область и область после неё
			currnetArea->expand(currnetArea->getNextArea()->getNextArea());

		}

		currnetArea = currnetArea->getNextArea();
	}
}