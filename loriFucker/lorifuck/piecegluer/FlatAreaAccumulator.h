#ifndef FlatAreaAccumulatorH
#define FlatAreaAccumulatorH

#include "BitmapIterator.h"
#include "Area.h"

class FlatAreaAccumulator{
public:
	FlatAreaAccumulator(BitmapIterator &inBitmapIterator);

	//�������� ������� � ����������
	void addArea(int begin, int end);

	//���� �������������� �������
	Area* getResultArea();

	bool isEmpty();

	//���������� ��� ����������� ��������
	void reset();
private:
	BitmapIterator *bitmapIterator;

	int beginPosition;
	int endPosition;

	//������� ������� ���� �� �������
	Color* calculateAverageColor();
	
};

#endif