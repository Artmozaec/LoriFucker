#ifndef BitmapIteratorH
#define BitmapIteratorH

#include "..\mytypes\BitmapContainer.h"
#include "..\mytypes\Color.h"

#include "Orientation.h"


class BitmapIterator{
	public:
		BitmapIterator(BitmapContainer *inBitmapContainer);

		bool nextPixel();

		Color* getPixel();
		
		bool isNextDarken();
		bool isNextWhiten();
		bool isNextEqual();

		bool isEnd();

		int getPosition();
		void setPosition(int newPosition);
	private:
		BitmapContainer *bitmapContainer;

		int pointer;

		Orientation orientation;
};

#endif