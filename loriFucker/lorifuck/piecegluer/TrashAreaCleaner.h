#ifndef TrashAreaCleanerH
#define TrashAreaCleanerH

#include "Area.h"

class TrashAreaCleaner{
public:
	static TrashAreaCleaner* getInstance();

	//Очистить градиенты от мусора
	void clearTrashAreas(Area *firstArea);
private:
	TrashAreaCleaner();
	static TrashAreaCleaner* instance;

	//Следующая область мусорная?
	bool isTrashNextArea(Area *area);

	//Последовательность областей непрерывна?
	bool areasIsSolid(Area *firstArea, Area *secondArea);

	//Замещение диапазона областей от firstArea до endArea одной областью
	//И возвращает следующую за объединённой областью
	//Area *takeoverAreas(Area *firstArea, Area *endArea);
};

#endif