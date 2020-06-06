#include "LabelText.h"

LabelText::LabelText(int inLabelTextID){
	LabelTextID = inLabelTextID;

	ownerHandle = NULL;
	thisHandle = NULL;
}
		
//Смена текста
void LabelText::setCaption(std::string newText){
	text = newText;

	if (thisHandle == NULL) return;

	SetWindowText(thisHandle, text.c_str());
}

//Дать текст
std::string LabelText::getCaption(){
	return NULL;
}


//Обработка сообщений
BOOL LabelText::messageIntercept(HWND windowHandle, UINT messageCode, WPARAM wParam, LPARAM lParam){
	
	//LabelText может воспринять только эти два типа сообщения, остальные игнорируются
	if ((messageCode != WM_COMMAND) && (messageCode != WM_INITDIALOG)) return false;
	
	if (messageCode == WM_INITDIALOG){
		ownerHandle = windowHandle;
		//Получаем дескриптор кнопки
		thisHandle = GetDlgItem(ownerHandle, LabelTextID);
		
		//Инициализируем текст
		setCaption(text);
	}
	
	return false;
}