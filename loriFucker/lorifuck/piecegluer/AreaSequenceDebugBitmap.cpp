#include "AreaSequenceDebugBitmap.h"

AreaSequenceDebugBitmap* AreaSequenceDebugBitmap::instance = NULL;

AreaSequenceDebugBitmap::AreaSequenceDebugBitmap(){
	colorArray[0] = new Color(0,255,255);
	colorArray[1] = new Color(255,0,255);
	colorArray[2] = new Color(255,255,0);
	colorArray[3] = new Color(255,128,255);

	colorArray[4] = new Color(190,50,50);
	colorArray[5] = new Color(50,50,190);

	colorArray[6] = new Color(0,128,255);
	colorArray[7] = new Color(255,0,128);
	colorArray[8] = new Color(128,0,255);
	colorArray[9] = new Color(128,255,0);

	colorArray[10] = new Color(125,144,0);
	colorArray[11] = new Color(242,187,139);
	colorArray[12] = new Color(60,95,106);
	colorArray[13] = new Color(172,215,146);
	colorArray[14] = new Color(0,132,0);
	colorArray[15] = new Color(255,200,200);
}

AreaSequenceDebugBitmap *AreaSequenceDebugBitmap::getInstance(){
	if (instance==NULL){
		instance = new AreaSequenceDebugBitmap();
	}

	return instance;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
void AreaSequenceDebugBitmap::addAreaToDebugBitmap(Area *area, BitmapContainer *saveBitmap, Color *color){
	for(int ch=0; ch<area->getLength(); ch++){
		saveBitmap->setPixel(area->getBegin()+ch, 0, color);
	}
}

BitmapContainer *AreaSequenceDebugBitmap::getDebugImageAreaLine(Area *firstArea){
	BitmapContainer *resultImage = new BitmapContainer(300, 1);
	Area *area = firstArea;
	Color *darkWhiteColor = new Color(200, 100, 0);
	Color *whiteDarkColor = new Color(0, 100, 200);
	Color *flatColor = new Color(200, 200, 200);

	do{
		if (area->getBeginColor()->getGrayValue()> area->getEndColor()->getGrayValue()){
			addAreaToDebugBitmap(area, resultImage, whiteDarkColor);
		}
		if (area->getBeginColor()->getGrayValue()< area->getEndColor()->getGrayValue()){
			addAreaToDebugBitmap(area, resultImage, darkWhiteColor);
		}
		if (area->getBeginColor()->getGrayValue()== area->getEndColor()->getGrayValue()){
			addAreaToDebugBitmap(area, resultImage, area->getBeginColor());
		}
		area = area->getNextArea();
	}while(area != NULL);

	return resultImage;

}
/////////////////////////////////////////////////////////////////////////////////////////////////

bool AreaSequenceDebugBitmap::areaIsLinked(Area *area){
	Area *up = area->getUpArea();
	Area *down = area->getDownArea();

	if ((up != NULL) || (down != NULL)) return true;

	return false;
}


void AreaSequenceDebugBitmap::showLinkedAreasInLines(Area *firstArea, BitmapContainer *firstImage, BitmapContainer *secondImage){

	int index = 0;

	do{
		if (areaIsLinked(firstArea)){
			addAreaToDebugBitmap(firstArea, firstImage, colorArray[index]);
			if (firstArea->getDownArea() != NULL){
				addAreaToDebugBitmap(firstArea->getDownArea(), secondImage, colorArray[index]);
			}
			//if (firstArea->getUpArea() != NULL){
				//addAreaToDebugBitmap(firstArea->getUpArea(), secondImage, colorArray[index]);
			//}
			index++;
			if (index>15) index = 0;
		}
		firstArea = firstArea->getNextArea();
	}while(firstArea != NULL);

}

/*
//Проверяет связана-ли область на 4 вверх
bool AreaSequenceDebugBitmap::isFullLinkedUp(Area *area){
	int ch=0;
	while (area->getUpArea() != NULL){
		area = area->getUpArea();
		ch++;
	}
	if (ch>=3){
		return true;
	} else {
		return false;
	}
}
*/

void AreaSequenceDebugBitmap::showFullLinkedAreaInBitmaps(
		Area *area, 
		Color *color,
		BitmapContainer *firstUp,
		BitmapContainer *firstDown,
		BitmapContainer *secondUp,
		BitmapContainer *secondDown
){
	Area *secondDownArea = area;
	Area *secondUpArea = secondDownArea->getUpArea();
	Area *firstDownArea = secondUpArea->getUpArea();
	Area *firstUpArea = firstDownArea->getUpArea();
	
	addAreaToDebugBitmap(secondDownArea, secondDown, color);
	addAreaToDebugBitmap(secondUpArea, secondUp, color);
	addAreaToDebugBitmap(firstDownArea, firstDown, color);
	addAreaToDebugBitmap(firstUpArea, firstUp, color);
}



void AreaSequenceDebugBitmap::showFullLink(
		Area *firstArea, 
		BitmapContainer *firstUp,
		BitmapContainer *firstDown,
		BitmapContainer *secondUp,
		BitmapContainer *secondDown
){
	Area* currentArea = firstArea;
	int colorIndex = 0;

	do{
		//Еслии вверх есть 3 связи
		if(currentArea->AmountLinksToUpBound()>=3){
			//Отображаем каждую из связей в своей картинке цветом colorIndex
			showFullLinkedAreaInBitmaps(
				currentArea,
				colorArray[colorIndex],
				firstUp,
				firstDown,
				secondUp,
				secondDown
			);
			
			//firstUp->workAreaSaved(std::string("C:\\firstUp.tif"));
			//firstDown->workAreaSaved(std::string("C:\\firstDown.tif"));
			//secondUp->workAreaSaved(std::string("C:\\secondUp.tif"));
			//secondDown->workAreaSaved(std::string("C:\\secondDown.tif"));
			
			colorIndex++;
			if (colorIndex>15) colorIndex = 0;	
		}
		currentArea = currentArea->getNextArea();
	}while(currentArea != NULL);
}