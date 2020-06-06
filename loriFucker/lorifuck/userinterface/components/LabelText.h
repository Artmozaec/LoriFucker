#ifndef TextH
#define TextH


#include <windows.h>
#include <stdio.h>
#include <string>

class LabelText{
	public:
		LabelText(int inTextID);
		
		//��������� ���������
		BOOL messageIntercept(HWND windowHandle, UINT messageCode, WPARAM wParam, LPARAM lParam);
		
		//����� ������
		void setCaption(std::string newText);

		//���� �����
		std::string getCaption();
	private:
		int LabelTextID;

		HWND ownerHandle;
		HWND thisHandle;

		//�����
		std::string text;
};

#endif