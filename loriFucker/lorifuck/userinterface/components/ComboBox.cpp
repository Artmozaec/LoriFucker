#include "ComboBox.h"

ComboBox::ComboBox(int inComboBoxID){
	comboBoxID = inComboBoxID;
	ownerHandle = NULL;
	thisHandle = NULL;


	comboBoxItems = new StringList();
}

//Добавление пункта в список
void ComboBox::addString(std::string newStr){
	comboBoxItems->addString(newStr);

	//Показать все строки
	showComboBoxStrings();
}

//Выделение строки
void ComboBox::selectString(std::string str){
	currentSelectedIndex = comboBoxItems->findString(str);
	//Обновляем вид комбобокса
	showComboBoxStrings();
}

//Отображение строк в список
void ComboBox::showComboBoxStrings(){
	if (thisHandle == NULL) return;

	//Удаляем все элементы списка
	SendMessage(thisHandle, CB_RESETCONTENT, (WPARAM)0, (LPARAM)0);

	std::string str;
	for (int ch=0; ch<comboBoxItems->length(); ch++){
		str = comboBoxItems->getString(ch);
		SendMessage(thisHandle, CB_ADDSTRING, (WPARAM)0, (LPARAM)str.c_str());
	}

	//Устанавливаем выделение
	SendMessage(thisHandle, CB_SETCURSEL, (WPARAM)currentSelectedIndex, (LPARAM)0);

}

//Дать выделенный пункт
std::string ComboBox::getCurrentSelected(){
	//Узнаём индекс текущего выделенного пункта списка
	int pos = SendMessage(thisHandle, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
	
	//Ничего не выделенно
	if (pos == LB_ERR) return NULL;

	return comboBoxItems->getString(pos);
}

void ComboBox::setOnChangeSelectionHandler(void (_cdecl *handler)(ComboBox *callComboBox, std::string)){
	OnChangeSelectionHandler = handler;
}


//Обработка сообщений
BOOL ComboBox::messageIntercept(HWND windowHandle, UINT messageCode, WPARAM wParam, LPARAM lParam){

	//ComboBox может воспринять только эти два типа сообщения, остальные игнорируются
	if ((messageCode != WM_COMMAND) && (messageCode != WM_INITDIALOG)) return false;
	
	if (messageCode == WM_INITDIALOG){
		ownerHandle = windowHandle;
		//Получаем дескриптор комбо бокса
		thisHandle = GetDlgItem(ownerHandle, comboBoxID);

		//Отображаем строки
		showComboBoxStrings();
	}

	switch(HIWORD(wParam)){
		case CBN_SELCHANGE:
			//Если это нам сообщение
			if ((HWND)lParam == thisHandle){
				//Узнаём значение выделенной строки и передаём это в обработчик выбора
				std::string str = getCurrentSelected();
				OnChangeSelectionHandler(this, str);
			}
	}

	return false;
}