#ifndef AreaSequenceDebugBitmapH
#define AreaSequenceDebugBitmapH

#include "..\mytypes\BitmapContainer.h"
#include "..\mytypes\Color.h"
#include "Area.h"

class AreaSequenceDebugBitmap{
public:
	static AreaSequenceDebugBitmap* getInstance();

	BitmapContainer *getDebugImageAreaLine(Area *firstArea);
	
	void showLinkedAreasInLines(Area *firstArea, BitmapContainer *firstImage, BitmapContainer *secondImage);

	//���������� ��������� ��������� ����� �� 4 ������ �������
	void showFullLink(
		Area *firstArea, 
		BitmapContainer *firstUp,
		BitmapContainer *firstDown,
		BitmapContainer *secondUp,
		BitmapContainer *secondDown
	);

	void showFullLinkedAreaInBitmaps(
		Area *area, 
		Color *color,
		BitmapContainer *firstUp,
		BitmapContainer *firstDown,
		BitmapContainer *secondUp,
		BitmapContainer *secondDown
	);
private:
	AreaSequenceDebugBitmap();
	void addAreaToDebugBitmap(Area *area, BitmapContainer *saveBitmap,  Color *color);
	static AreaSequenceDebugBitmap* instance;

	bool areaIsLinked(Area *area);

	//��������� �������-�� ������� �� 4 �����
	//bool isFullLinkedUp(Area *area);

	Color* colorArray[16];
};

#endif