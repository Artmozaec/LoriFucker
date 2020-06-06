#ifndef ListBoxH
#define ListBoxH

#include <windows.h>
#include <stdio.h>
#include <string>
#include "..\..\mytypes\StringList.h"

class ListBox{
	public:
		ListBox(int inListBoxID);
		//Заменяет все пункты списка
		void changeAllItems(StringList *);
		
		//Выделяет элемент с именем string
		void select(std::string);
		
		//Выделяет элемент по индексу
		void select(int);
		
		//Возвращает текущую выделенную строку
		std::string getCurrentSelected();

		//Назначение обработчика двойного клика на пункте списка
		void setOnDblItemClick(void (_cdecl *handler)(ListBox *callListBox, std::string itemStr));

		//Обработка сообщений
		BOOL messageIntercept(HWND windowHandle, UINT messageCode, WPARAM wParam, LPARAM lParam);
	private:
		//Ссыла на обработчик двойного клика на пункте списка
		void (*setOnDblItemClickHandler)(ListBox *callListBox, std::string itemStr);
		
		int listBoxID;

		HWND ownerHandle;
		HWND thisHandle;

		//Хранит список текста элементы которого соответствуют индексу отображаемого listBox
		StringList *listTextItems;

};
#endif