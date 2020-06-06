#include "Button.h"

Button::Button(int inButtonID){
	ownerHandle = NULL;
	enableButton = true;
	buttonID = inButtonID;
	enableImage = NULL;
	disableImage = NULL;
}

void Button::setEnableImage(HBITMAP inEnableImage){
	enableImage = inEnableImage;
}

void Button::setDisableImage(HBITMAP inDisableImage){
	disableImage = inDisableImage;
}

void Button::setOnClickHandler(void (_cdecl *handler)(Button *callButton)){
	onClickHandler = handler;
}


void Button::enable(){
	enableButton = true;
	//Если функция вызывается до сообщения WM_INITDIALOG которое несёт в себе дескриптор родительского окна, из которого вычисляется дескриптор этой кнопки
	if (thisHandle == NULL) return;

	//Если картинки нет
	if (enableImage == NULL){
		//Тогда применяем обычные методы смены активности кнопки
		EnableWindow(thisHandle, true);
		return;
	}

	//Установить картинку активной кнопки
	SendMessage(thisHandle, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)enableImage);
	SendMessage(thisHandle, BM_SETSTATE, (WPARAM)FALSE, (LPARAM)0);
}


void Button::disable(){
	enableButton = false;
	//Если функция вызывается до сообщения WM_INITDIALOG которое несёт в себе дескриптор родительского окна, из которого вычисляется дескриптор этой кнопки
	if (thisHandle == NULL) return;
	
	//Если картинки нет
	if (disableImage == NULL){
		//Тогда применяем обычные методы смены активности кнопки
		EnableWindow(thisHandle, false);
		return;
	}
	
	//Установить картинку пассивной кнопки
	SendMessage(thisHandle, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)disableImage);
	SendMessage(thisHandle, BM_SETSTATE, (WPARAM)TRUE, (LPARAM)0);
}



BOOL Button::messageIntercept(HWND windowHandle, UINT messageCode, WPARAM wParam, LPARAM lParam){
	
	//Кнопка может воспринять только эти два типа сообщения, остальные игнорируются
	if ((messageCode != WM_COMMAND) && (messageCode != WM_INITDIALOG)) return false;
	
	if (messageCode == WM_INITDIALOG){
		ownerHandle = windowHandle;
		//Получаем дескриптор кнопки
		thisHandle = GetDlgItem(ownerHandle, buttonID);

		if (enableButton){ 
			enable();
		}else{
			disable();
		}
	}

	//Если сообщение адресовано не этому элементу, нахуй!
	if ((LOWORD(wParam)) != buttonID) return false;


	switch(HIWORD(wParam)){
		case BN_CLICKED:
			if (enableButton){
			
			if (onClickHandler!=NULL){
				onClickHandler(this);
				return true;
			}
			
			} else {

				SendMessage(thisHandle, BM_SETSTATE, (WPARAM)TRUE, (LPARAM)0);
			}
	}

	return false;
}

