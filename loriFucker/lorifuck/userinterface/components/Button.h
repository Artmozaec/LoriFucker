#ifndef ButtonH
#define ButtonH


#include <windows.h>
#include <stdio.h>


class Button{
	public:
		Button(int inButtonID);
		//Обработка сообщений
		BOOL messageIntercept(HWND windowHandle, UINT messageCode, WPARAM wParam, LPARAM lParam);
		void setOnClickHandler(void (_cdecl *handler)(Button *callButton));
		
		//Установка изображений кнопки
		void setEnableImage(HBITMAP inEnableImage);
		void setDisableImage(HBITMAP inDisableImage);


		void enable();
		void disable();
		//void repaint();
	private:
		//Ссыла на обработчик клика на кнопке
		void (*onClickHandler)(Button *callButton);

		int buttonID;
		
		//Дескрипторы изображений кнопки
		HBITMAP enableImage;
		HBITMAP disableImage;


		HWND ownerHandle;
		HWND thisHandle;
		bool enableButton;
};

#endif