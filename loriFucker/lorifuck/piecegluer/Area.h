#ifndef AreaH
#define AreaH

#include "stdio.h"
#include "..\mytypes\Color.h"
#include <vector>
class Area{
	public:
		Area(
			Color* inBeginColor, 
			Color* inEndColor, 
			int inBegin,
			int inLength
		);
		void setLength(int newLength);
		int getLength();

		void setBegin(int newBegin);
		int getBegin();
		
		void setBeginColor(Color *newBeginColor);
		Color *getBeginColor();
		
		void setEndColor(Color *newEndColor);
		Color *getEndColor();

		//Поддерживаем абстракцию горизонтальной сетки
		//На самом деле относительно изображения области могут располагаться перевёрнуто на 90 градусов
		//Но для простоты мы считаем что все они горизонтальны
		void linkPervArea(Area *area);
		void linkNextArea(Area *area);
		void linkUpArea(Area *area);
		void linkDownArea(Area *area);
		
		void unlinkUpArea();
		void unlinkDownArea();
		void unlinkNextArea();
		void unlinkPervArea();

		Area* getNextArea();
		Area* getPervArea();
		Area* getUpArea();
		Area* getDownArea();

		bool equalColor(Area *area, int deviation);

		int getDistance(Area *area);

		//Колличество связей до верхней границы
		int AmountLinksToUpBound();


		//Смещение верха области при склейке
		void setShift(int newShift);
		int getShift();


		//Расщиряет область до endArea, 
		//конечный цвет области endArea становиться конечным цветом расширенной области
		//Следующая область с которой была связанна endArea становится связанной с текущей областью
		void expand(Area *endArea);
	private:
		Color* beginColor;
		Color* endColor;
		int length;
		int begin;

		Area* upArea;
		Area* downArea;
		Area* nextArea;
		Area* pervArea;

		//Смещение при склейке
		int shift;
};
#endif