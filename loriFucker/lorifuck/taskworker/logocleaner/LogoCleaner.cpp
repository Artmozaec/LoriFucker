#include "LogoCleaner.h"
#include <windows.h>

LogoCleaner::LogoCleaner(){
}

void LogoCleaner::debugSave(GFL_BITMAP *saveBitmap, char *patch){
	GFL_SAVE_PARAMS saveParameters;
	saveParameters.Flags = GFL_SAVE_ANYWAY;
	saveParameters.FormatIndex = 0;
	saveParameters.Compression = GFL_NO_COMPRESSION;
	saveParameters.Quality = 100;
	saveParameters.CompressionLevel = 0;
	saveParameters.Interlaced = 0;
	saveParameters.Progressive = 0;
	saveParameters.OptimizeHuffmanTable = 0;
	saveParameters.InAscii = 0;
	saveParameters.Offset = 0;
	saveParameters.ChannelOrder = 0;
	saveParameters.ChannelType = GFL_CTYPE_RGB;

	gflSaveBitmap(
		patch,
		saveBitmap,
		&saveParameters
	);

	pieceGluer = PieceGluer::getInstance();
}



//Делает выбранный участок прозрачным(оставляя остальные каналы неизменными)
void LogoCleaner::makeTransparency(GFL_BITMAP *bitmap, int left, int up, int right, int down){
	GFL_COLOR color;

	//Получаем цвет пикселя
	for(int chY=up; chY<down; chY++){
		for(int chX=left; chX<right; chX++){
			gflGetColorAt(
				bitmap,
				chX,
				chY,
				&color
			);

			//Меняем прозрачность
			color.Alpha = 0;

			//Записываем цвет на место
			gflSetColorAt(
				bitmap,
				chX,
				chY,
				&color
			);
		}
	}

}


//Удаляет прозрачность на выделенном участке(оставляя остальные каналы неизменными)
void LogoCleaner::deleteTransparency(GFL_BITMAP *bitmap, int left, int up, int right, int down){
	GFL_COLOR color;

	//Получаем цвет пикселя
	for(int chY=up; chY<down; chY++){
		for(int chX=left; chX<right; chX++){
			gflGetColorAt(
				bitmap,
				chX,
				chY,
				&color
			);

			//Меняем прозрачность
			color.Alpha = 255;

			//Записываем цвет на место
			gflSetColorAt(
				bitmap,
				chX,
				chY,
				&color
			);
		}
	}

}


void LogoCleaner::transparentPaste(GFL_BITMAP *sourceBitmap, GFL_RECT *sourceRect, GFL_BITMAP *destBitmap, int posX, int posY){
	GFL_RECT rect;
	
	//Если прясоугольник региона исходного копирования не задан
	//Копируется вся область исходного изображения
	if (sourceRect == NULL){
		sourceRect = &rect;
		sourceRect->x = 0;
		sourceRect->y = 0;
		sourceRect->h = sourceBitmap->Height;
		sourceRect->w = sourceBitmap->Width;
	}
	
	deleteTransparency(
		destBitmap,
		posX,
		posY,
		posX+sourceRect->w,
		posY+sourceRect->h
	);
	
	gflBitbltEx(
		sourceBitmap,
		sourceRect,
		destBitmap,
		posX,
		posY
	);

}


void LogoCleaner::logoProcessing(GFL_BITMAP *bitmap){
/////////////////ЛЕВЫЙ ВЕРХНИЙ/////////////////////
	Rect leftUp;
	leftUp.x = 102;
	leftUp.y = 273;
	leftUp.x1 = 256;
	leftUp.y1 = 278; //276

	Rect leftUpResize;
	leftUpResize.x = 102;
	leftUpResize.y = 273;
	leftUpResize.x1 = 256;
	leftUpResize.y1 = 283; //

	resizeRectangle(bitmap, &leftUp, &leftUpResize);
/////////////////ЛЕВЫЙ НИЖНИЙ/////////////////////
	Rect leftDown;
	leftDown.x = 102;
	leftDown.y = 286;//286
	leftDown.x1 = 256;
	leftDown.y1 = 291;

	Rect leftDownResize;
	leftDownResize.x = 102;
	leftDownResize.y = 282;//
	leftDownResize.x1 = 256;
	leftDownResize.y1 = 291;

	resizeRectangle(bitmap, &leftDown, &leftDownResize);
/////////////////ПРАВЫЙ ВЕРХНИЙ/////////////////////
	Rect rightUp;
	rightUp.x = 309;
	rightUp.y = 273;
	rightUp.x1 = 463;
	rightUp.y1 = 278; //276

	Rect rightUpResize;
	rightUpResize.x = 309;
	rightUpResize.y = 273;
	rightUpResize.x1 = 463;
	rightUpResize.y1 = 283;

	resizeRectangle(bitmap, &rightUp, &rightUpResize);
/////////////////ПРАВЫЙ НИЖНИЙ/////////////////////
	Rect rightDown;
	rightDown.x = 309;
	rightDown.y = 286; //288
	rightDown.x1 = 463;
	rightDown.y1 = 291;

	Rect rightDownResize;
	rightDownResize.x = 309;
	rightDownResize.y = 282; //
	rightDownResize.x1 = 463;
	rightDownResize.y1 = 291;

	resizeRectangle(bitmap, &rightDown, &rightDownResize);
/////////////////ВЕРХНИЙ ЛЕВЫЙ/////////////////////
	Rect upLeft;
	upLeft.x = 273;
	upLeft.y = 101; 
	upLeft.x1 = 278; //276
	upLeft.y1 = 255;

	Rect upLeftResize;
	upLeftResize.x = 273;
	upLeftResize.y = 101; 
	upLeftResize.x1 = 282;//
	upLeftResize.y1 = 255;

	resizeRectangle(bitmap, &upLeft, &upLeftResize);
/////////////////ВЕРХНИЙ ПРАВЫЙ/////////////////////
	Rect upRight;
	upRight.x = 286; //287
	upRight.y = 101; 
	upRight.x1 = 291; 
	upRight.y1 = 255;

	Rect upRightResize;
	upRightResize.x = 282; //
	upRightResize.y = 101; 
	upRightResize.x1 = 291;
	upRightResize.y1 = 255;

	resizeRectangle(bitmap, &upRight, &upRightResize);
/////////////////НИЖНИЙ ЛЕВЫЙ/////////////////////
	Rect downLeft;
	downLeft.x = 273; 
	downLeft.y = 310; 
	downLeft.x1 = 278; //276
	downLeft.y1 = 464;

	Rect downLeftResize;
	downLeftResize.x = 273;
	downLeftResize.y = 310; 
	downLeftResize.x1 = 282; //
	downLeftResize.y1 = 464;

	resizeRectangle(bitmap, &downLeft, &downLeftResize);
/////////////////НИЖНИЙ ПРАВЫЙ/////////////////////
	Rect downRight;
	downRight.x = 286; //287
	downRight.y = 310; 
	downRight.x1 = 291; 
	downRight.y1 = 464;

	Rect downRightResize;
	downRightResize.x = 282; //
	downRightResize.y = 310; 
	downRightResize.x1 = 291;
	downRightResize.y1 = 464;

	resizeRectangle(bitmap, &downRight, &downRightResize);

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////
	//Подчищаем края
///////////////////ЛЕВЫЙ КРАЙ/////////////////////////////
	Rect leftEdge;
	leftEdge.x = 112; 
	leftEdge.y = 273; 
	leftEdge.x1 = 118; 
	leftEdge.y1 = 291;

	Rect leftEdgeResize;
	leftEdgeResize.x = 102;
	leftEdgeResize.y = 273; 
	leftEdgeResize.x1 = 118;
	leftEdgeResize.y1 = 291;

	resizeRectangle(bitmap, &leftEdge, &leftEdgeResize);

///////////////////ПРАВЫЙ КРАЙ/////////////////////////////
	Rect rightEdge;
	rightEdge.x = 447; 
	rightEdge.y = 273; 
	rightEdge.x1 = 453; 
	rightEdge.y1 = 291;

	Rect rightEdgeResize;
	rightEdgeResize.x = 447;
	rightEdgeResize.y = 273; 
	rightEdgeResize.x1 = 463;
	rightEdgeResize.y1 = 291;

	resizeRectangle(bitmap, &rightEdge, &rightEdgeResize);


///////////////////ВЕРХНИЙ КРАЙ/////////////////////////////
	Rect upEdge;
	upEdge.x = 273; 
	upEdge.y = 111; 
	upEdge.x1 = 291; 
	upEdge.y1 = 117;

	Rect upEdgeResize;
	upEdgeResize.x = 273;
	upEdgeResize.y = 101; 
	upEdgeResize.x1 = 291;
	upEdgeResize.y1 = 117;

	resizeRectangle(bitmap, &upEdge, &upEdgeResize);

///////////////////НИЖНИЙ КРАЙ/////////////////////////////
	Rect downEdge;
	downEdge.x = 273; 
	downEdge.y = 447; 
	downEdge.x1 = 291; 
	downEdge.y1 = 453;

	Rect downEdgeResize;
	downEdgeResize.x = 273;
	downEdgeResize.y = 447; 
	downEdgeResize.x1 = 291;
	downEdgeResize.y1 = 464;

	resizeRectangle(bitmap, &downEdge, &downEdgeResize);
}


//Изменение размеров прямоугольной области на изображении
void LogoCleaner::resizeRectangle(GFL_BITMAP *bitmap, Rect *size, Rect *newSize){
	GFL_COLOR color;
	color.Red = 255;
	color.Green = 255;
	color.Blue = 255;
	
	//Создаём операционное изображение
	GFL_BITMAP *operationImage = gflAllockBitmap(
		GFL_RGB,
		size->x1-size->x,
		size->y1-size->y,
		1,
		&color
	);

	GFL_RECT rect;
	rect.x = size->x;
	rect.y = size->y;
	rect.h = size->y1 - size->y;
	rect.w = size->x1 - size->x;
	
	//копируем в него участок основного изображения
	gflBitblt(
		bitmap,
		&rect,
		operationImage,
		0,
		0
	);
	
	//Изменяем размер операционного изображения
	gflResize(
		operationImage,
		NULL,
		newSize->x1-newSize->x,
		newSize->y1-newSize->y,
		GFL_RESIZE_BILINEAR,
		0
	);
	
	//Копируем операционное изображение обратно
	rect.x = 0;
	rect.y = 0;
	rect.h = operationImage->Height;
	rect.w = operationImage->Width;
	
	gflBitblt(
		operationImage,
		&rect,
		bitmap,
		newSize->x,
		newSize->y
	);
}

void LogoCleaner::gluePieces(GFL_BITMAP *frame){
	BitmapContainerArea rightArea;
	BitmapContainerArea leftArea;
	BitmapContainerArea upArea;
	BitmapContainerArea downArea;

	leftArea.left = 102;
	leftArea.up = 273;
	leftArea.height = 18;
	leftArea.width = 154;

	rightArea.left = 309;
	rightArea.up = 273;
	rightArea.height = 18;
	rightArea.width = 154;

	upArea.left = 273;
	upArea.up = 101;
	upArea.height = 154;
	upArea.width = 18;

	downArea.left = 273;
	downArea.up = 310;
	downArea.height = 154;
	downArea.width = 18;

	BitmapContainer *rightBC = new BitmapContainer();
	rightBC->setPointerToContent(frame);
	rightBC->setWorkArea(rightArea);
	
	BitmapContainer *leftBC = new BitmapContainer();
	leftBC->setPointerToContent(frame);
	leftBC->setWorkArea(leftArea);

	BitmapContainer *upBC = new BitmapContainer();
	upBC->setPointerToContent(frame);
	upBC->setWorkArea(upArea);

	BitmapContainer *downBC = new BitmapContainer();
	downBC->setPointerToContent(frame);
	downBC->setWorkArea(downArea);

	pieceGluer->gluePieces(rightBC);
	pieceGluer->gluePieces(leftBC);
	pieceGluer->gluePieces(upBC);
	pieceGluer->gluePieces(downBC);
}

void LogoCleaner::clearLogo(BitmapContainer *frame){
	//Делаем дубликат исходного изображения с которым будем работать
	//Для того что-бы взять из перевёрнутого изображения только нужные для работы места
	//и оригинальное изображение не будет испорчено поворотом
	GFL_BITMAP  *originalFrame = (GFL_BITMAP *)frame->getPointerToContent();
	GFL_BITMAP  *rotateFrame = gflCloneBitmap(originalFrame);



	//Меняем режим копии на RGBA
	gflChangeColorDepth(
		rotateFrame,
		NULL,
		GFL_MODE_TO_RGBA,
		GFL_MODE_NO_DITHER
	);
	
	GFL_COLOR color;
	color.Red = 255;
	color.Green = 255;
	color.Blue = 255;
	color.Alpha = 0;

	//Расширяем копию для возможности поворота
	gflResizeCanvas(
		rotateFrame,
		NULL,
		400,
		400,
		GFL_CANVASRESIZE_CENTER,
		&color
	);

	//Поворачиваем копию на 45
	gflRotateFine(
		rotateFrame,
		NULL,
		45,
		NULL
	);

	//С начала, вся область не прозрачна
	makeTransparency(
		rotateFrame,
		0,
		0,
		rotateFrame->Width,
		rotateFrame->Height
	);
	
	//debugSave(rotateFrame, "C:\\1.jpg");

////////////////////Удаляем прозрачность на участках логотипа/////////////////////
	deleteTransparency(//Левый
		rotateFrame,
		102,
		273,
		256,
		291
	);
	
	deleteTransparency(//Правый
		rotateFrame,
		309,
		273,
		463,
		291
	);

	deleteTransparency(//Верхний
		rotateFrame,
		273,
		101,
		291,
		255
	);
	
	deleteTransparency(//Нижний
		rotateFrame,
		273,
		310,
		291,
		463
	);
////////////////////////////////////////////////////////////////////////////

	//Стираем полоски
	logoProcessing(rotateFrame);

	
	//Очищаем область
	BitmapContainerArea gluerArea;
	
	//Склеиваем разорванные области
	gluePieces(rotateFrame);
	

	//debugSave(rotateFrame, "C:\\1.jpg");
	//Поворачиваем фрейм обратно
	gflRotateFine(
		rotateFrame,
		NULL,
		-45,
		NULL
	);

	gflResizeCanvas(
		rotateFrame,
		NULL,
		256,
		256,
		GFL_CANVASRESIZE_CENTER,
		&color
	);
	GFL_RECT rect;
	rect.x = 0;
	rect.y = 0;
	rect.h = rotateFrame->Height,
	rect.w = rotateFrame->Width,

	transparentPaste(
		rotateFrame,
		&rect,
		originalFrame,
		0,
		0
	);


////////////////////////////////УБИРАЕМ ЦЕНТРАЛЬНЫЙ ЛОГОТИП////////////////////
/////////НИЗ/////////////
	Rect downEdge;
	downEdge.x = 89; 
	downEdge.y = 138; 
	downEdge.x1 = 166; 
	downEdge.y1 = 144;

	Rect downEdgeResize;
	downEdgeResize.x = 89;
	downEdgeResize.y = 127; 
	downEdgeResize.x1 = 166;
	downEdgeResize.y1 = 144;

	resizeRectangle(originalFrame, &downEdge, &downEdgeResize);
/////////ВЕРХ/////////////
	Rect upEdge;
	upEdge.x = 89; 
	upEdge.y = 110; 
	upEdge.x1 = 166; 
	upEdge.y1 = 116;

	Rect upEdgeResize;
	upEdgeResize.x = 89;
	upEdgeResize.y = 110; 
	upEdgeResize.x1 = 166;
	upEdgeResize.y1 = 127;

	resizeRectangle(originalFrame, &upEdge, &upEdgeResize);
//////////////////////////////////////////////////////////////////////
	BitmapContainerArea centerLogoArea;
	centerLogoArea.left = 89;
	centerLogoArea.up = 110;
	centerLogoArea.height = 35;
	centerLogoArea.width = 78;

	BitmapContainer *logoBC = new BitmapContainer();
	logoBC->setPointerToContent(originalFrame);
	logoBC->setWorkArea(centerLogoArea);
	pieceGluer->gluePieces(logoBC);

	debugSave(originalFrame, "C:\\1.tif");
}