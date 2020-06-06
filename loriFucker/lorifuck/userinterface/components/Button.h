#ifndef ButtonH
#define ButtonH


#include <windows.h>
#include <stdio.h>


class Button{
	public:
		Button(int inButtonID);
		//��������� ���������
		BOOL messageIntercept(HWND windowHandle, UINT messageCode, WPARAM wParam, LPARAM lParam);
		void setOnClickHandler(void (_cdecl *handler)(Button *callButton));
		
		//��������� ����������� ������
		void setEnableImage(HBITMAP inEnableImage);
		void setDisableImage(HBITMAP inDisableImage);


		void enable();
		void disable();
		//void repaint();
	private:
		//����� �� ���������� ����� �� ������
		void (*onClickHandler)(Button *callButton);

		int buttonID;
		
		//����������� ����������� ������
		HBITMAP enableImage;
		HBITMAP disableImage;


		HWND ownerHandle;
		HWND thisHandle;
		bool enableButton;
};

#endif