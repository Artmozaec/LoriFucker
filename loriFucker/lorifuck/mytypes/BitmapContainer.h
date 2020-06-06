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
		void workAreaSaved(std::string patch);//��������� ������ �������������� �������


		//������ � �������� ��������
		Color* getPixel(int posX, int posY);
		void setPixel(int posX, int posY, Color *color);
		
		int getVisota();
		int getShirina();

		//���������� ��������� �� ����������
		void* getPointerToContent();
		//������ ��������� �� ����������
		void setPointerToContent(void* newContent);

		void crop(int newShirina, int newVisota, Align align);

		//������ ����� �������� �������, �������� ������ ������ �� ������� ����������
		BitmapContainer *clone();
		
		//������ ������ ����� �������
		BitmapContainer *copy();

		//���������� ������������
		void setWorkArea(BitmapContainerArea &areaRect);

		BitmapContainer *getArea(int posX, int posY, int height, int width);

		//��������� �����
		void drawVerticalLine(int posX, int posY, int length, Color *color);
		void drawHorizontalLine(int posX, int posY, int length, Color *color);
	private:
		void DisplayError(std::string patch, GFL_ERROR error);
		
		//�������//////////////////
		//������������ ������ � �����������
		int upBound;
		int leftBound;
		int width;
		int height;
		///////////////////////////

		GFL_BITMAP *bitmap;
};

#endif