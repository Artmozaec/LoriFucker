#ifndef PieceGluerH
#define PieceGluerH

#include "stdio.h"
#include <windows.h>
#include "..\mytypes\BitmapContainer.h"
//#include "..\mytypes\Color.h"
#include "AreaSequenceCreator.h"
#include "AreasLinker.h"
#include "Area.h"
#include "AreaSequenceDebugBitmap.h"
#include "BadChainsCleaner.h"
#include "Gluer.h"
#include "BitmapShifter.h"
#include "TrashAreaCleaner.h"

class PieceGluer{
public:
	static PieceGluer* getInstance();

	void gluePieces(BitmapContainer *piecesArea);
private:
	PieceGluer();

	static PieceGluer* instance;

	//¬ыполн€ет очистку мусорных областей, прерывающих гладкие градиенты
	//static TrashAreaCleaner *trashAreaCleaner;

	//”ничтожает линию
	void destroyLine(Area *beginArea);
};

#endif


