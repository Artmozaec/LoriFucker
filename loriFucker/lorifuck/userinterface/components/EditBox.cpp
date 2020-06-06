#include "EditBox.h"

EditBox::EditBox(int inEditBoxID){
	editBoxID = inEditBoxID;

	ownerHandle = NULL;
	thisHandle = NULL;

	initString = "";
}

void EditBox::setOnChangeHandler(void (_cdecl *handler)(EditBox *editBox)){
	OnChangeHandler = handler;
}

void EditBox::setText(std::string str){
	if (thisHandle == NULL){
		initString = str;
	}

	LPCSTR szText = str.c_str();
	SetWindowText(thisHandle, szText);
}

std::string EditBox::getText(){
	return NULL;
}


BOOL EditBox::messageIntercept(HWND windowHandle, UINT messageCode, WPARAM wParam, LPARAM lParam){

	//EditBox может воспринять только эти два типа сообщения, остальные игнорируются
	if ((messageCode != WM_COMMAND) && (messageCode != WM_INITDIALOG)) return false;

	if (messageCode == WM_INITDIALOG){
		ownerHandle = windowHandle;

		//Получаем дескриптор кнопки
		thisHandle = GetDlgItem(ownerHandle, editBoxID);
		
		//Показываем возможно изменённый текст
		setText(initString);
	}
	return false;
}


