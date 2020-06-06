#ifndef EditBoxH
#define EditBoxH


#include <windows.h>
#include <stdio.h>
#include <string>

class EditBox{
	public:
		EditBox(int inEditBoxID);
		
		//��������� ���������
		BOOL messageIntercept(HWND windowHandle, UINT messageCode, WPARAM wParam, LPARAM lParam);
		
		void setOnChangeHandler(void (_cdecl *handler)(EditBox *editBox));

		//������ � �������
		void setText(std::string);
		std::string getText();

	private:
		//����� �� ���������� ����� �� ������
		void (*OnChangeHandler)(EditBox *editBox);

		int editBoxID;

		HWND ownerHandle;
		HWND thisHandle;

		//������ ������ ����� �� ������������� (����������� ��������� WM_INITDIALOG)
		//� �������� ���������, ��������������� ��� ��������
		std::string initString;
};

#endif