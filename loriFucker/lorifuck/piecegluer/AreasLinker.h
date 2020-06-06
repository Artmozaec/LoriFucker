#ifndef AreasLinkerH
#define AreasLinkerH

#include "Area.h"

class AreasLinker{
public:
	static AreasLinker* getInstance();

	//Ќа самом деле линии областей могут быт и вертикальными, но это не важно, в данном случае
	//дл€ большей пон€тности делаем их горизонтальными

	// ажда€ ссылка - это перва€ область в последовательности областей
	//‘ункци€ находит близкие области между лини€ми и св€зывает их образу€ сеть
	void linkAreaLinesToGrid(Area* upSideUpLine, Area* upSideDownLine, Area* downSideUpLine, Area* downSideDownLine);
private:
	AreasLinker();
	static AreasLinker* instance;

	//ѕервичное св€зывание, не св€занных областе
	void primaryLink(Area *upArea, Area *downArea);

	//¬торичное св€зывание уже св€занных первичным областей
	void secondaryLink(Area *upArea, Area *downArea);

	//Ќаходит самую близкую к etalon область, из first и second возвраща€ еЄ
	//Area *getMoreNear(Area *etalon, Area *first, Area *second);
	Area *getMoreNearDistanceAndColor(Area *etalon, Area *first, Area *second);
	Area *getMoreNearDistance(Area *etalon, Area *first, Area *second);
	Area *getMoreNearColor(Area *etalon, Area *first, Area *second);
	
	//ѕоиск ближайшей похожей области
	Area *searchProximate(Area *seekingArea, Area *searchSequence);

	//ѕоиск ближайшей похожей области име€щей св€зь с низу
	Area *findProximateLinkedDown(Area *seekingArea, Area *searchSequence);
};

#endif
