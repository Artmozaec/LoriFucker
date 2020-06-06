#ifndef RectangleProportionsH
#define RectangleProportionsH

#include <windows.h>

class RectangleProportions{
	public:
		RectangleProportions(int posX, int posY, int inShirina, int inVisota, HWND inOwnerHandle);
		void setRectangleProportions(int inSideShirna, int inSideVisota);

		RECT shapeRect; //Прямоугольник описывающий! прямоугольник описывающий соотношение сторон
		RECT shadowRect; //Тень под shapeRect
	private:
		HWND thisHandle;
		HWND ownerHandle;

		//Начало координат отрисовки
		int startUp;
		int startLeft;


		//Размер стороны области(всегда квадратная)
		int sideAreaSize;

};
#endif