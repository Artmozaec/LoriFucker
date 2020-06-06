#include "PieceGluer.h"

PieceGluer* PieceGluer::instance = NULL;

PieceGluer *PieceGluer::getInstance(){
	if (instance==NULL){
		instance = new PieceGluer();
	}

	return instance;
}

PieceGluer::PieceGluer(){
	//trashAreaCleaner = TrashAreaCleaner::getInstance();
}


//Уничтожает линию
void PieceGluer::destroyLine(Area *beginArea){
	Area *currentArea = beginArea;
	do{
		delete(currentArea->getPervArea());
		currentArea = currentArea->getNextArea();
	}while (currentArea != NULL);

}


void PieceGluer::gluePieces(BitmapContainer *piecesArea){

	
	//piecesArea->workAreaSaved(std::string("C:\\gp.tif"));
	//piecesArea->saveImage(std::string("C:\\gpfull.jpg"));

	//MapAreas *mapAreas = new MapAreas(piecesArea);

	//Определяем ориентацию изображения 
	//и делим его по меньшей стороне на 2 равные области
	
	BitmapContainerArea firstSideAreaBeginLine;
	BitmapContainerArea firstSideAreaEndLine;
	BitmapContainerArea secondSideAreaBeginLine;
	BitmapContainerArea secondSideAreaEndLine;

	
	int median;
	//Устанавливаем ограничительные области
	if (piecesArea->getShirina()>piecesArea->getVisota()){
		
		median = piecesArea->getVisota()/2;

		firstSideAreaBeginLine.left = 0;
		firstSideAreaBeginLine.up = 0;
		firstSideAreaBeginLine.width = piecesArea->getShirina();
		firstSideAreaBeginLine.height = 1;

		firstSideAreaEndLine.left = 0;
		firstSideAreaEndLine.up = median-1;
		firstSideAreaEndLine.width = piecesArea->getShirina();
		firstSideAreaEndLine.height = 1;

		secondSideAreaBeginLine.left = 0;
		secondSideAreaBeginLine.up = median;
		secondSideAreaBeginLine.width = piecesArea->getShirina();
		secondSideAreaBeginLine.height = 1;

		secondSideAreaEndLine.left = 0;
		secondSideAreaEndLine.up = piecesArea->getVisota();
		secondSideAreaEndLine.width = piecesArea->getShirina();
		secondSideAreaEndLine.height = 1; 
	} else {
		//Ветикаль
		median = piecesArea->getShirina()/2;

		firstSideAreaBeginLine.left = 0;
		firstSideAreaBeginLine.up = 0;
		firstSideAreaBeginLine.width = 1;
		firstSideAreaBeginLine.height = piecesArea->getVisota();

		firstSideAreaEndLine.left = median-1;
		firstSideAreaEndLine.up = 0;
		firstSideAreaEndLine.width = 1;
		firstSideAreaEndLine.height = piecesArea->getVisota();

		secondSideAreaBeginLine.left = median;
		secondSideAreaBeginLine.up = 0;
		secondSideAreaBeginLine.width = 1;
		secondSideAreaBeginLine.height = piecesArea->getVisota();

		secondSideAreaEndLine.left = piecesArea->getShirina();
		secondSideAreaEndLine.up = 0;
		secondSideAreaEndLine.width = 1;
		secondSideAreaEndLine.height = piecesArea->getVisota(); 
	}

		
	BitmapContainer *firstSideBitmapBeginLine = piecesArea->clone();
	firstSideBitmapBeginLine->setWorkArea(firstSideAreaBeginLine);
	
	BitmapContainer *firstSideBitmapEndLine = piecesArea->clone();
	firstSideBitmapEndLine->setWorkArea(firstSideAreaEndLine);
	
	BitmapContainer *secondSideBitmapBeginLine = piecesArea->clone();
	secondSideBitmapBeginLine->setWorkArea(secondSideAreaBeginLine);
	
	BitmapContainer *secondSideBitmapEndLine = piecesArea->clone();
	secondSideBitmapEndLine->setWorkArea(secondSideAreaEndLine);

	
	AreaSequenceCreator *areaSequenceCreator = AreaSequenceCreator::getInstance();

	Area *firstSideBeginLine = areaSequenceCreator->generate(firstSideBitmapBeginLine);
	Area *firstSideEndLine = areaSequenceCreator->generate(firstSideBitmapEndLine);
	Area *secondSideBeginLine = areaSequenceCreator->generate(secondSideBitmapBeginLine);
	Area *secondSideEndLine = areaSequenceCreator->generate(secondSideBitmapEndLine);
	
	//Убираем мусорные области
	TrashAreaCleaner *trashAreaCleaner;
	trashAreaCleaner = TrashAreaCleaner::getInstance();
	trashAreaCleaner->clearTrashAreas(firstSideBeginLine);
	trashAreaCleaner->clearTrashAreas(firstSideEndLine);
	trashAreaCleaner->clearTrashAreas(secondSideBeginLine);
	trashAreaCleaner->clearTrashAreas(secondSideEndLine);

	//Вызываем связыватель
	AreasLinker *areasLinker = AreasLinker::getInstance();
	
	areasLinker->linkAreaLinesToGrid(
		firstSideBeginLine,
		firstSideEndLine,
		secondSideBeginLine,
		secondSideEndLine
	);

	//Убираем мусорные связи
	BadChainsCleaner *badChainsCleaner = BadChainsCleaner::getInstance();
	badChainsCleaner->clearBadChains(secondSideEndLine);

	//BitmapContainer *deb = firstSideBitmapBeginLine->getArea(0,0, 30, 50);
	//deb->drawHorizontalLine(1,1, 10, new Color(0,100,100));
	//deb->drawVerticalLine(1,1, 10, new Color(255,0,0));
	//deb->saveImage(std::string("C:\\1111.tif"));

//////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////
#ifdef _MyDEBUG

//Отладочное изображение
	AreaSequenceDebugBitmap *areaSequenceDebugBitmap = AreaSequenceDebugBitmap::getInstance();
	
	
	BitmapContainer *firstSideBeginDebImage = areaSequenceDebugBitmap->getDebugImageAreaLine(firstSideBeginLine);
	BitmapContainer *firstSideEndDebImage = areaSequenceDebugBitmap->getDebugImageAreaLine(firstSideEndLine);
	BitmapContainer *secondSideBeginDebImage = areaSequenceDebugBitmap->getDebugImageAreaLine(secondSideBeginLine);
	BitmapContainer *secondSideEndDebImage = areaSequenceDebugBitmap->getDebugImageAreaLine(secondSideEndLine);
	
	BitmapContainer *firstSideBeginLinkedDebImage = new BitmapContainer(300, 1);
	BitmapContainer *firstSideEndLinkedDebImage = new BitmapContainer(300, 1);
	BitmapContainer *secondSideBeginLinkedDebImage = new BitmapContainer(300, 1);
	BitmapContainer *secondSideEndLinkedDebImage = new BitmapContainer(300, 1);

	areaSequenceDebugBitmap->showLinkedAreasInLines(
		firstSideBeginLine, 
		firstSideBeginLinkedDebImage, 
		firstSideEndLinkedDebImage
	);

	areaSequenceDebugBitmap->showLinkedAreasInLines(
		secondSideBeginLine, 
		secondSideBeginLinkedDebImage, 
		secondSideEndLinkedDebImage
	);

	firstSideBeginLinkedDebImage->saveImage(std::string("C:\\fs.tif"));
	firstSideEndLinkedDebImage->saveImage(std::string("C:\\ss.tif"));

	BitmapContainer *debBitmap = piecesArea->copy();
	
	debBitmap->addFragment(firstSideBeginDebImage, 0, 1);
	debBitmap->addFragment(firstSideBeginLinkedDebImage, 0, 2);

	debBitmap->addFragment(firstSideEndDebImage, 0, median-2);
	debBitmap->addFragment(firstSideEndLinkedDebImage, 0, median-3);
	
	debBitmap->addFragment(secondSideBeginLinkedDebImage, 0, median+2);
	debBitmap->addFragment(secondSideEndLinkedDebImage, 0, debBitmap->getVisota()-3);

	debBitmap->addFragment(secondSideBeginDebImage, 0, median+1);
	debBitmap->addFragment(secondSideEndDebImage, 0, piecesArea->getVisota()-2);
	
	debBitmap->workAreaSaved(std::string("C:\\debarea.tif"));

/////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
	//ПОЛНОСТЬЮ СВЯЗАННЫЕ
	BitmapContainer *firstSideBeginFLImage = new BitmapContainer(300, 1);
	BitmapContainer *firstSideEndFLImage = new BitmapContainer(300, 1);
	BitmapContainer *secondSideBeginFLImage = new BitmapContainer(300, 1);
	BitmapContainer *secondSideEndFLImage = new BitmapContainer(300, 1);	

	
	areaSequenceDebugBitmap->showFullLink(
		secondSideEndLine,
		firstSideBeginFLImage,
		firstSideEndFLImage,
		secondSideBeginFLImage,
		secondSideEndFLImage
	);


	
	BitmapContainer *debFLBitmap = piecesArea->copy();
	
	debFLBitmap->addFragment(firstSideBeginFLImage, 0, 1);
	debFLBitmap->addFragment(firstSideEndFLImage, 0, median-2);
	debFLBitmap->addFragment(secondSideBeginFLImage, 0, median+1);
	debFLBitmap->addFragment(secondSideEndFLImage, 0, piecesArea->getVisota()-2);

	debFLBitmap->workAreaSaved(std::string("C:\\debareaLink.tif"));

///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////
#endif
	
  	Gluer *gluer = Gluer::getInstance();
	gluer->glue(firstSideEndLine, secondSideBeginLine, piecesArea);

	//Уничтожаем области
	destroyLine(firstSideBeginLine);
	destroyLine(firstSideEndLine);
	destroyLine(secondSideBeginLine);
	destroyLine(secondSideEndLine);
}
