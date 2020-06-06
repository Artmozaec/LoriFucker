#ifndef AreaShiftCalculatorH
#define AreaShiftCalculatorH
#include "Area.h"
#include "BitmapIterator.h"
#include "..\mytypes\BitmapContainer.h"


class AreaShiftCalculator{
public:
	static AreaShiftCalculator* getInstance();

	void shiftCalculate(Area *upArea, Area *downArea);

	//������������� ���������� ������
	void setUpAreaBitmap(BitmapContainer *upBitmap);
	void setDownAreaBitmap(BitmapContainer *downBitmap);
private:
	AreaShiftCalculator();
	static AreaShiftCalculator* instance;

	//������� ��������� ������� ������� ���������� ������� ������� � ������
	int getDistance(Area *upArea, Area *downArea);

	//���������� ������� ��������, ����������� �������� �� upArea � downArea
	// �������� 1 - ���������� ���������� ������� ������ ������� � ������� ������� �������
	int getAverageDifference(Area *upArea, Area *downArea, int shift);
	
	BitmapIterator *upSideIterator;
	BitmapIterator *downSideIterator;
};
#endif