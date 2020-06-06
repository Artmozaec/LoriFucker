#ifndef RectangleProportionsH
#define RectangleProportionsH

#include <windows.h>

class RectangleProportions{
	public:
		RectangleProportions(int posX, int posY, int inShirina, int inVisota, HWND inOwnerHandle);
		void setRectangleProportions(int inSideShirna, int inSideVisota);

		RECT shapeRect; //������������� �����������! ������������� ����������� ����������� ������
		RECT shadowRect; //���� ��� shapeRect
	private:
		HWND thisHandle;
		HWND ownerHandle;

		//������ ��������� ���������
		int startUp;
		int startLeft;


		//������ ������� �������(������ ����������)
		int sideAreaSize;

};
#endif