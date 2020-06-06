#ifndef AreaShifterH
#define AreaShifterH

#include <windows.h>
#include "Area.h"
#include "Orientation.h"
#include "..\mytypes\BitmapContainer.h"
#include "..\mytypes\Color.h"


class BitmapShifter{
public:
	static BitmapShifter* getInstance();

	//�������������� �������������� ����������
	void shiftUpArea(int pos, int length, int shift);
	void shiftDownArea(int pos, int length, int shift);

	void changeImage(BitmapContainer *inImage);
private:
	BitmapShifter();

	//����������� ������� �������� ����� ���������
	BitmapContainer *image;

	static BitmapShifter* instance;

	Orientation orientation;

	//������� ����� ������� length �� shift ��������
	void shiftLine(int posX, int posY, int length, int shift);

	//���������� ������� �������� �����, ��� ������� ���������� ��������
	void shiftHorLineLeft(int posX, int posY, int length, int shift);
	void shiftHorLineRight(int posX, int posY, int length, int shift);
	void shiftVertLineUp(int posX, int posY, int length, int shift);
	void shiftVertLineDown(int posX, int posY, int length, int shift);
	
	//����������� ������� ��� ������������� ����� ����������� ��� ������������� ���������������
	int abstractHeighImage;
	int abstractWidthImage;

	//������� ������
	int calculateFrequencyShifting(int shift);


	//��������� ��������
	void calculateShiftParametrs(
		int &periodAccretion, //������ ���������� 
		int &accretion, //�����������
		int &verticalCorrectionPeriod, //������ ������������ ��������� � 1 ������
		int &horizontalCorrectionPeriod, //������ �������������� ��������� 1 ������

		int shift
	);
};

#endif
