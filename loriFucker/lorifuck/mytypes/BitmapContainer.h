#ifndef BitmapContainerH
#define BitmapContainerH

#include <string>
#include "gfl\stdint.h"
#include "gfl\libgfl.h"
#include "Color.h"

#pragma comment(lib, "libgfl.lib")

enum Align{
	TOP_LEFT,
	TOP_RIGHT,
	BOTTOM_LEFT,
	BOTTOM_RIGHT,
	CENTER
};

struct BitmapContainerArea{
	int up;
	int left;
	int width;
	int height;
};

class BitmapContainer{
	public:


		BitmapContainer(int shirina, int visota);
		BitmapContainer(std::string patch);
		BitmapContainer();
		
		~BitmapContainer();

		void addFragment(BitmapContainer *inBitmapContainer, int posX, int posY);

		void saveImage();
		void saveImage(std::string patch);
		void workAreaSaved(std::string patch);//Сохраняет только ограничивающую область


		//Работа с массивом пикселей
		Color* getPixel(int posX, int posY);
		void setPixel(int posX, int posY, Color *color);
		
		int getVisota();
		int getShirina();

		//Возвращает указатель на содержимое
		void* getPointerToContent();
		//Меняет указатель на содержимое
		void setPointerToContent(void* newContent);

		void crop(int newShirina, int newVisota, Align align);

		//создаёт копию текущего объекта, оставляя внутри ссылку на текущее содержимое
		BitmapContainer *clone();
		
		//Создаёт полную копию объекта
		BitmapContainer *copy();

		//Установить ограничители
		void setWorkArea(BitmapContainerArea &areaRect);

		BitmapContainer *getArea(int posX, int posY, int height, int width);

		//Отрисовка линий
		void drawVerticalLine(int posX, int posY, int length, Color *color);
		void drawHorizontalLine(int posX, int posY, int length, Color *color);
	private:
		void DisplayError(std::string patch, GFL_ERROR error);
		
		//ГРАНИЦЫ//////////////////
		//Ограничивают доступ к изображению
		int upBound;
		int leftBound;
		int width;
		int height;
		///////////////////////////

		GFL_BITMAP *bitmap;
};

#endif