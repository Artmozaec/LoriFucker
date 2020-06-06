#ifndef ListBoxH
#define ListBoxH

#include <windows.h>
#include <stdio.h>
#include <string>
#include "..\..\mytypes\StringList.h"

class ListBox{
	public:
		ListBox(int inListBoxID);
		//�������� ��� ������ ������
		void changeAllItems(StringList *);
		
		//�������� ������� � ������ string
		void select(std::string);
		
		//�������� ������� �� �������
		void select(int);
		
		//���������� ������� ���������� ������
		std::string getCurrentSelected();

		//���������� ����������� �������� ����� �� ������ ������
		void setOnDblItemClick(void (_cdecl *handler)(ListBox *callListBox, std::string itemStr));

		//��������� ���������
		BOOL messageIntercept(HWND windowHandle, UINT messageCode, WPARAM wParam, LPARAM lParam);
	private:
		//����� �� ���������� �������� ����� �� ������ ������
		void (*setOnDblItemClickHandler)(ListBox *callListBox, std::string itemStr);
		
		int listBoxID;

		HWND ownerHandle;
		HWND thisHandle;

		//������ ������ ������ �������� �������� ������������� ������� ������������� listBox
		StringList *listTextItems;

};
#endif