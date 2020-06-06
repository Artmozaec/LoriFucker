#include "ListBox.h"

ListBox::ListBox(int inListBoxID){
	listBoxID = inListBoxID;

	ownerHandle = NULL;
	thisHandle = NULL;

	listTextItems = NULL;
}


//Заменяет все пункты списка
void ListBox::changeAllItems(StringList *list){
	listTextItems = list;
	
	//Очищаем список
	SendMessage(thisHandle, LB_RESETCONTENT, (WPARAM)0, (LPARAM)0);
	
	//Заполняем список переданным листом
	for (int ch=list->length()-1; ch>=0; ch--){
		SendMessage(thisHandle, LB_ADDSTRING, (WPARAM)0, (LPARAM)list->getString(ch).c_str());
	}

	listTextItems->invert();
}

//Возвращает текущую выделенную строку
std::string ListBox::getCurrentSelected(){
	//Узнаём индекс текущего выделенного пункта списка
	int pos = SendMessage(thisHandle, LB_GETCURSEL, (WPARAM)0, (LPARAM)0);
	
	//Ничего не выделенно
	if (pos == LB_ERR) return NULL;

	return listTextItems->getString(pos);
}


//Выделяет элемент по индексу
void ListBox::select(int pos){
	//Выделяем пункт списка (pos)
	SendMessage(thisHandle, LB_SETCURSEL, (WPARAM)pos, (LPARAM)0);
}

//Выделяет элемент с именем string
void ListBox::select(std::string selectStr){
	//Ищем индекс строки string
	int pos = SendMessage(thisHandle, LB_FINDSTRING, (WPARAM)-1, (LPARAM)selectStr.c_str());
	
	//Если ничего не найдено
	if (pos == LB_ERR) return;
	
	//Посылаем сообщение выделения
	select(pos);
}

void ListBox::setOnDblItemClick(void (_cdecl *handler)(ListBox *callListBox, std::string itemStr)){
	setOnDblItemClickHandler = handler;
}


//Обработка сообщений
BOOL ListBox::messageIntercept(HWND windowHandle, UINT messageCode, WPARAM wParam, LPARAM lParam){
	
	//ListBox может воспринять только эти два типа сообщения, остальные игнорируются
	if ((messageCode != WM_COMMAND) && (messageCode != WM_INITDIALOG)) return false;
	
	if (messageCode == WM_INITDIALOG){
		ownerHandle = windowHandle;
		//Получаем дескриптор кнопки
		thisHandle = GetDlgItem(ownerHandle, listBoxID);
	}
	
	//Если сообщение адресовано не этому элементу, нахуй!
	if ((LOWORD(wParam)) != listBoxID) return false;
	
	switch(HIWORD(wParam)){
		case LBN_DBLCLK://Двойной щелчек на строке списка
			//Вызываем обработчик, передаём в него выбранную строку
			setOnDblItemClickHandler(this, getCurrentSelected());
	}
	return false;
}
