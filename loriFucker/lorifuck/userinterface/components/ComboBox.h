#ifndef ComboBoxH
#define ComboBoxH

#include <string>
#include "..\..\mytypes\StringList.h"
#include <windows.h>

class ComboBox{
	public:
		ComboBox(int inComboBoxID);
		
		//��������� ���������
		BOOL messageIntercept(HWND windowHandle, UINT messageCode, WPARAM wParam, LPARAM lParam);
		
		//���������� ������ � ������
		void addString(std::string newStr);

		//��������� ������
		void selectString(std::string str);

		//���� ���������� �����
		std::string getCurrentSelected();

		void setOnChangeSelectionHandler(void (_cdecl *handler)(ComboBox *callComboBox, std::string));
	private:
		//����� �� ���������� ����� ����������� ��������
		void (*OnChangeSelectionHandler)(ComboBox *callComboBox, std::string);
		
		//������ �������� ����������� ��������
		int currentSelectedIndex;

		//����������� ����� � ������
		void showComboBoxStrings();

		//��������� ����������� ������
		int comboBoxID;

		//�������� ������ �����
		StringList *comboBoxItems;

		HWND ownerHandle;
		HWND thisHandle;
};

#endif