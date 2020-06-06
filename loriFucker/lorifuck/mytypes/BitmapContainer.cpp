#include "BitmapContainer.h"
#include <windows.h>

BitmapContainer::BitmapContainer(int shirina, int visota){
	bitmap = gflAllockBitmap(
		GFL_RGB, //Тип растра
		shirina,
		visota,
		1,
		NULL
	);

	upBound = 0;
	leftBound = 0;
	height = visota;
	width = shirina;
}

BitmapContainer::BitmapContainer(){
	bitmap = NULL;

	upBound = 0;
	leftBound = 0;
	height = 0;
	width = 0;
}

BitmapContainer::BitmapContainer(std::string patch){
	gflLibraryInit();

	GFL_LOAD_PARAMS load_option;
	GFL_FILE_INFORMATION file_info; 
	GFL_ERROR error; 

	//Опции по умолчанию
	gflGetDefaultLoadParams( &load_option ); 
	
	error = gflLoadBitmap( patch.c_str(), &bitmap, &load_option, &file_info ); 
	
	if (error) DisplayError(patch, error);
	
	upBound = 0;
	leftBound = 0;
	height = bitmap->Height;
	width =  bitmap->Width;
}

void BitmapContainer::crop(int newShirina, int newVisota, Align align){
	GFL_CANVASRESIZE mode;
	switch(align){
		case TOP_LEFT:
			mode = GFL_CANVASRESIZE_TOPLEFT;
			break;
		case TOP_RIGHT:
			mode = GFL_CANVASRESIZE_TOPRIGHT;
			break;
		case BOTTOM_LEFT:
			mode = GFL_CANVASRESIZE_BOTTOMLEFT;
			break;
		case BOTTOM_RIGHT:
			mode = GFL_CANVASRESIZE_BOTTOMRIGHT;
			break;
		case CENTER:
			mode = GFL_CANVASRESIZE_CENTER;
	}
	GFL_COLOR color;	
	color.Red = 0;
	color.Blue = 0;
	color.Green = 0;
	color.Alpha = 0;

	gflResizeCanvas(
		bitmap,
		NULL,
		newShirina,
		newVisota,
		mode,
		&color
	);

	height = newVisota;
	width = newShirina;
}




BitmapContainer::~BitmapContainer(){
	gflFreeBitmap(bitmap);
}

void BitmapContainer::DisplayError(std::string patch, GFL_ERROR error){
	const char *str = gflGetErrorString(error);
	patch += "  ошибка : ";
	patch += str; 
	MessageBox(NULL, patch.c_str(), "Ошибка контейнера изображения", MB_ICONERROR);
}

void BitmapContainer::addFragment(BitmapContainer *inBitmapContainer, int posX, int posY){
	//Достаём указатель на внутреннюю структуру
	GFL_BITMAP *pasetBitmap = (GFL_BITMAP*)inBitmapContainer->getPointerToContent();
	
	GFL_RECT rect;
	rect.x = 0;
	rect.y = 0;
	rect.w = pasetBitmap->Width;
	rect.h = pasetBitmap->Height;
	
	//Вставляем в соответствующей позиции
	GFL_ERROR error = gflBitblt(
		pasetBitmap,
		&rect,
		bitmap,
		leftBound+posX,
		upBound+posY
		//posX,
		//posY
	);

	if (error) DisplayError(std::string("Добавление фрагмента, ошибка!!!! А-а-аааа пиздец!"), error);
}

void BitmapContainer::setPixel(int posX, int posY, Color *color){
	GFL_COLOR point_color;
	point_color.Red = color->getRed();
	point_color.Green = color->getGreen();
	point_color.Blue = color->getBlue();

	gflSetColorAt(
		bitmap,
		(posX+leftBound),
		(posY+upBound),
		&point_color
	);
}


//Работа с массивом пикселей
Color *BitmapContainer::getPixel(int posX, int posY){
	GFL_COLOR point_color;

	GFL_ERROR error = gflGetColorAt(
		bitmap,
		(posX+leftBound),
		(posY+upBound),
		&point_color
	);

	if (error) DisplayError(std::string("getPixel, ошибка!!!! А-а-аааа пиздец!"), error);
	
	return new Color(
		point_color.Red,
		point_color.Green,
		point_color.Blue
		
	);
}

int BitmapContainer::getVisota(){
	return height;
	//return bitmap->Height;
}

int BitmapContainer::getShirina(){
	return width;
	//return bitmap->Width;
}


void* BitmapContainer::getPointerToContent(){
	return (void *)bitmap;
}

void BitmapContainer::setPointerToContent(void *newContent){
	bitmap = (GFL_BITMAP *)newContent;
}


void BitmapContainer::saveImage(std::string patch){
	GFL_SAVE_PARAMS saveParameters;
	saveParameters.Flags = GFL_SAVE_REPLACE_EXTENSION;
	saveParameters.FormatIndex = 2;
	saveParameters.Compression = GFL_LZW;
	saveParameters.Quality = 100;
	saveParameters.CompressionLevel = 0;
	saveParameters.Interlaced = 0;
	saveParameters.Progressive = 0;
	saveParameters.OptimizeHuffmanTable = 0;
	saveParameters.InAscii = 0;
	saveParameters.Offset = 0;
	saveParameters.ChannelOrder = 0;
	saveParameters.ChannelType = GFL_CTYPE_RGB;

	GFL_ERROR error = gflSaveBitmap(
		(char *)patch.c_str(),
		bitmap,
		&saveParameters
	);
}


void BitmapContainer::workAreaSaved(std::string patch){
	//Растр куда скопируется текущая активная область

	GFL_BITMAP *areaBitmap = gflAllockBitmap(
		GFL_RGB, //Тип растра
		width,
		height,
		1,
		NULL
	);
	
	//Прямоугольник области
	GFL_RECT rect;
	rect.x = leftBound;
	rect.y = upBound;
	rect.h = height;
	rect.w = width;


	gflBitblt(
		bitmap,
		&rect,
		areaBitmap,
		0,
		0
	);

	//Создаём контейнер специально для этого дела
	BitmapContainer *savedBC = new BitmapContainer();
	savedBC->setPointerToContent(areaBitmap);



	//Делаем копию растра
	//savedBC->setPointerToContent(gflCloneBitmap(bitmap));

	//Урезаем этот растр до нужного размера
	//savedBC->crop(width, height, CENTER);

	//Сохраняем
	savedBC->saveImage(patch);
}


//создаёт копию текущего объекта, оставляя внутри ссылку на текущее содержимое
BitmapContainer *BitmapContainer::clone(){
	BitmapContainer *cloneBC = new BitmapContainer();
	cloneBC->setPointerToContent((void *)bitmap);

	//Копируем границы
	BitmapContainerArea copyArea;
	copyArea.left = leftBound;
	copyArea.up = upBound;
	copyArea.width = width;
	copyArea.height = height;
	cloneBC->setWorkArea(copyArea);

	return cloneBC;
}

//Создаёт полную копию объекта
BitmapContainer *BitmapContainer::copy(){
	BitmapContainer *cloneBC = new BitmapContainer();

	cloneBC->setPointerToContent((void *)gflCloneBitmap(bitmap));

	//Копируем границы
	BitmapContainerArea copyArea;
	copyArea.left = leftBound;
	copyArea.up = upBound;
	copyArea.width = width;
	copyArea.height = height;
	cloneBC->setWorkArea(copyArea);

	return cloneBC;
}


//Установить ограничители
void BitmapContainer::setWorkArea(BitmapContainerArea &areaRect){
	upBound += areaRect.up;
	leftBound += areaRect.left;
	height = areaRect.height;
	width = areaRect.width;
}


BitmapContainer *BitmapContainer::getArea(int posX, int posY, int height, int width){
	GFL_BITMAP *areaBitmap = gflAllockBitmap(
		GFL_RGB, //Тип растра
		width,
		height,
		1,
		NULL
	);
	
	//Прямоугольник области
	GFL_RECT rect;
	rect.x = leftBound+posX;
	rect.y = upBound+posY;
	rect.h = height;
	rect.w = width;


	gflBitblt(
		bitmap,
		&rect,
		areaBitmap,
		0,
		0
	);

	BitmapContainer *areaBC = new BitmapContainer();
	
	areaBC->setPointerToContent(areaBitmap);

	BitmapContainerArea area;
	area.left = 0;
	area.up = 0;
	area.height = height;
	area.width = width;

	areaBC->setWorkArea(area);

	return areaBC;	
}


//Отрисовка линий
void BitmapContainer::drawVerticalLine(int posX, int posY, int length, Color *color){
	for(int ch=0; ch<length; ch++){
		setPixel(posX, posY+ch, color);
	}
}


void BitmapContainer::drawHorizontalLine(int posX, int posY, int length, Color *color){
	for(int ch=0; ch<length; ch++){
		setPixel(posX+ch, posY, color);
	}
}