#ifndef AreaSequenceCreatorH
#define AreaSequenceCreatorH

#include "..\mytypes\BitmapContainer.h"
#include "BitmapIterator.h"
#include "Area.h"
#include "FlatAreaAccumulator.h"
#include <string>

class AreaSequenceCreator{
public:
	static AreaSequenceCreator* getInstance();

	Area *generate(BitmapContainer *bitmapContainer);
private:
	static AreaSequenceCreator* instance;

	AreaSequenceCreator();

	void generateAreas(BitmapIterator *bitmapIterator);

	//���������� �������� ����� ���� �������� ������������
	void goForwardUntillWhiteDarkGradient(BitmapIterator *bitmapIterator);
	void goForwardUntillDarkWhiteGradient(BitmapIterator *bitmapIterator);

	//��������� �������� �������� ����� � ��������� ����������� ��� �������� �������
	int areaMinColorDiapazone;
	
	//��������� ������ ��������� ����������� ��� �������� �������
	int areaMinSize;
	
	Area *firstArea;
	Area *lastArea;

	void addArea(Area *newArea);
};

#endif