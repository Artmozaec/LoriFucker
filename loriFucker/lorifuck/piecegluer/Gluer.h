#ifndef GluerH
#define GluerH

#include <windows.h>
#include "Area.h"
#include "..\mytypes\BitmapContainer.h"
#include "BitmapShifter.h"
#include "AreaShiftCalculator.h"
//#include <vector>


class Gluer{
public:
	static Gluer* getInstance();

	void glue(Area *upLine, Area *downLine, BitmapContainer *areaImage);
private:
	Gluer();

	static Gluer* instance;

	//calculateShiftAreas

	//������������ �������� ��� ���� �������� � �������� ������������ � ��� �������
	void calculateShiftingFromAreas(Area *downLine);

	//������������ ���������� �������� ����� ������� � ������ ��������� ��������
	AreaShiftCalculator *areaShiftCalculator;

	//���������� ��������� �������� ��������
	BitmapShifter *bitmapShifter;

	//������� ��� ������� ������� �������� 
	//void shiftSide(Area *firstArea, BitmapContainer *sideBitmap);

	//���������� ������� �� ������� ���������� ����� ���-�� �������� ���� ���� �������
	//�� �������� �������� ������ ������� � �������
	Area *getNextPiece(Area *beginArea);

	//���� �� beginArea ������� ������� �� ������ length
	//� ����������� �����, 
	//���� �� ���� ����������� ������� ������� ������ ����������� ��������
	//��� ����������� �������, ���������� NULL
	Area *searchRightFlatAreaFromShift(Area *beginArea, int length);

	//���� �� beginArea ����� ������� �� ������ length
	//� ����������� �����, 
	//���� �� ���� ����������� ������� ������� ������ ����������� ��������
	//��� ����������� �������, ���������� NULL
	Area *searchRightAnyAreaFromShift(Area *beginArea, int length);

	//���� � ����������� ����� �� beginArea ����� �� ��������� � ������� �������� 
	//����� ������ ������� �� ������ length
	//����� ����� ����� �� ����������� � � ���� �������
	//���� �� ���� ����������� ������� ������� ������ ����������� ��������
	//��� ����������� �������, ���������� NULL
	Area *searechDontChainAreaFromShift(Area *beginArea, int length);
	
	//�� beginArea �������� ����� ������������������ �������� ������� �� � �������
	Area *searchDontLinkSequenceFromShift(Area *beginArea, int length);
	
	
	//������� ������� �� staetArea �� endArea �� shift
	void shiftPieceDownArea(Area *startArea, Area *endArea, int shift);
	void shiftPieceUpArea(Area *startArea, Area *endArea, int shift);

	void correctShiftInAreas(Area *startArea, Area *endArea, int correctShift);

	//������� �������� � �������?
	bool consistsInChain(Area *area);

	//���������� ������ ���� ������������ ������� �� ������ � ������� �������� ��� ������
	bool shiftEquivalent(Area *etalonArea, Area *equalArea, int threshold);
};

#endif