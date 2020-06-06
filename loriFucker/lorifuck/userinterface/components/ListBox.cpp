#include "ListBox.h"

ListBox::ListBox(int inListBoxID){
	listBoxID = inListBoxID;

	ownerHandle = NULL;
	thisHandle = NULL;

	listTextItems = NULL;
}


//�������� ��� ������ ������
void ListBox::changeAllItems(StringList *list){
	listTextItems = list;
	
	//������� ������
	SendMessage(thisHandle, LB_RESETCONTENT, (WPARAM)0, (LPARAM)0);
	
	//��������� ������ ���������� ������
	for (int ch=list->length()-1; ch>=0; ch--){
		SendMessage(thisHandle, LB_ADDSTRING, (WPARAM)0, (LPARAM)list->getString(ch).c_str());
	}

	listTextItems->invert();
}

//���������� ������� ���������� ������
std::string ListBox::getCurrentSelected(){
	//����� ������ �������� ����������� ������ ������
	int pos = SendMessage(thisHandle, LB_GETCURSEL, (WPARAM)0, (LPARAM)0);
	
	//������ �� ���������
	if (pos == LB_ERR) return NULL;

	return listTextItems->getString(pos);
}


//�������� ������� �� �������
void ListBox::select(int pos){
	//�������� ����� ������ (pos)
	SendMessage(thisHandle, LB_SETCURSEL, (WPARAM)pos, (LPARAM)0);
}

//�������� ������� � ������ string
void ListBox::select(std::string selectStr){
	//���� ������ ������ string
	int pos = SendMessage(thisHandle, LB_FINDSTRING, (WPARAM)-1, (LPARAM)selectStr.c_str());
	
	//���� ������ �� �������
	if (pos == LB_ERR) return;
	
	//�������� ��������� ���������
	select(pos);
}

void ListBox::setOnDblItemClick(void (_cdecl *handler)(ListBox *callListBox, std::string itemStr)){
	setOnDblItemClickHandler = handler;
}


//��������� ���������
BOOL ListBox::messageIntercept(HWND windowHandle, UINT messageCode, WPARAM wParam, LPARAM lParam){
	
	//ListBox ����� ���������� ������ ��� ��� ���� ���������, ��������� ������������
	if ((messageCode != WM_COMMAND) && (messageCode != WM_INITDIALOG)) return false;
	
	if (messageCode == WM_INITDIALOG){
		ownerHandle = windowHandle;
		//�������� ���������� ������
		thisHandle = GetDlgItem(ownerHandle, listBoxID);
	}
	
	//���� ��������� ���������� �� ����� ��������, �����!
	if ((LOWORD(wParam)) != listBoxID) return false;
	
	switch(HIWORD(wParam)){
		case LBN_DBLCLK://������� ������ �� ������ ������
			//�������� ����������, ������� � ���� ��������� ������
			setOnDblItemClickHandler(this, getCurrentSelected());
	}
	return false;
}
