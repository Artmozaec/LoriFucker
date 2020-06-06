#ifndef TextH
#define TextH


#include <windows.h>
#include <stdio.h>
#include <string>

class LabelText{
	public:
		LabelText(int inTextID);
		
		//Обработка сообщений
		BOOL messageIntercept(HWND windowHandle, UINT messageCode, WPARAM wParam, LPARAM lParam);
		
		//Смена текста
		void setCaption(std::string newText);

		//Дать текст
		std::string getCaption();
	private:
		int LabelTextID;

		HWND ownerHandle;
		HWND thisHandle;

		//Текст
		std::string text;
};

#endif