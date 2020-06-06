#ifndef LogoCleanerH
#define LogoCleanerH

#include "..\..\mytypes\BitmapContainer.h";
#include "..\..\mytypes\gfl\stdint.h";
#include "..\..\mytypes\gfl\libgfl.h";
#include "..\..\piecegluer\PieceGluer.h"
//#include "..\..\mytypes\gfl\libgfle.h";

struct Rect{
  int x;  
  int y;  
  int x1;  
  int y1;
};

/*
enum Anchor{
	UP,
	DOWN,
	RIGHT,
	LEFT
};
*/

class LogoCleaner{
	public:
		LogoCleaner();
		void clearLogo(BitmapContainer *frame);
	private:
		void debugSave(GFL_BITMAP *saveBitmap, char *patch);

		//��������� ����������� pasteBitmap � destBitmap � ���������� ������������
		void transparentPaste(GFL_BITMAP *pasteBitmap, GFL_RECT *pasteRect, GFL_BITMAP *destBitmap, int posX, int posY);

		//������ ��������� ������� ����������(�������� ��������� ������ �����������)
		void makeTransparency(GFL_BITMAP *bitmap, int left, int up, int right, int down);

		//������� ������������ �� ���������� �������(�������� ��������� ������ �����������)
		void deleteTransparency(GFL_BITMAP *bitmap, int left, int up, int right, int down);

		//�������� ����� �� ���������� ����������� �������
		void logoProcessing(GFL_BITMAP *bitmap);
		
		//��������� �������� ������������� ������� �� �����������
		void resizeRectangle(GFL_BITMAP *bitmap, Rect *size, Rect *newSize);

		void gluePieces(GFL_BITMAP *frame);

		//��������� �������
		PieceGluer *pieceGluer;
};

#endif