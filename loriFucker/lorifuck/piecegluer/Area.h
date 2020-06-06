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

		//������������ ���������� �������������� �����
		//�� ����� ���� ������������ ����������� ������� ����� ������������� ���������� �� 90 ��������
		//�� ��� �������� �� ������� ��� ��� ��� �������������
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

		//����������� ������ �� ������� �������
		int AmountLinksToUpBound();


		//�������� ����� ������� ��� �������
		void setShift(int newShift);
		int getShift();


		//��������� ������� �� endArea, 
		//�������� ���� ������� endArea ����������� �������� ������ ����������� �������
		//��������� ������� � ������� ���� �������� endArea ���������� ��������� � ������� ��������
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

		//�������� ��� �������
		int shift;
};
#endif