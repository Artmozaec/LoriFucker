#ifndef ColorH
#define ColorH
#include "stdio.h"
#include <vector>
class Color{
	public:
		Color(int r, int g, int b);

		int getRed();
		int getGreen();
		int getBlue();

		int getGrayValue();

		bool equal(Color *color, int deviation);

		int colorDifference(Color *color);
	private:
		int red;
		int green;
		int blue;
};
#endif