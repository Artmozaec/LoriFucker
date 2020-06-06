#ifndef ComboBoxH
#define ComboBoxH

#include <string>
#include "..\..\mytypes\StringList.h"
#include <windows.h>

class ComboBox{
	public:
		ComboBox(int inComboBoxID);
		
		//Обработка сообщений
		BOOL messageIntercept(HWND windowHandle, UINT messageCode, WPARAM wParam, LPARAM lParam);
		
		//Добавление пункта в список
		void addString(std::string newStr);

		//Выделение строки
		void selectString(std::string str);

		//Дать выделенный пункт
		std::string getCurrentSelected();

		void setOnChangeSelectionHandler(void (_cdecl *handler)(ComboBox *callComboBox, std::string));
	private:
		//Ссыла на обработчик смены выделенного элемента
		void (*OnChangeSelectionHandler)(ComboBox *callComboBox, std::string);
		
		//Индекс текущего выделенного элемента
		int currentSelectedIndex;

		//Отображение строк в список
		void showComboBoxStrings();

		//Индикатор выпадающего списка
		int comboBoxID;

		//Содержит список строк
		StringList *comboBoxItems;

		HWND ownerHandle;
		HWND thisHandle;
};

#endif