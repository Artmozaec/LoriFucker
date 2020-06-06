#ifndef EditBoxH
#define EditBoxH


#include <windows.h>
#include <stdio.h>
#include <string>

class EditBox{
	public:
		EditBox(int inEditBoxID);
		
		//Обработка сообщений
		BOOL messageIntercept(HWND windowHandle, UINT messageCode, WPARAM wParam, LPARAM lParam);
		
		void setOnChangeHandler(void (_cdecl *handler)(EditBox *editBox));

		//Работа с текстом
		void setText(std::string);
		std::string getText();

	private:
		//Ссыла на обработчик клика на кнопке
		void (*OnChangeHandler)(EditBox *editBox);

		int editBoxID;

		HWND ownerHandle;
		HWND thisHandle;

		//Строка хранит текст до инициализации (поступления сообщения WM_INITDIALOG)
		//В процессе обработки, устанавливается это значение
		std::string initString;
};

#endif