#include "ComboBox.h"

ComboBox::ComboBox(int inComboBoxID){
	comboBoxID = inComboBoxID;
	ownerHandle = NULL;
	thisHandle = NULL;


	comboBoxItems = new StringList();
}

//���������� ������ � ������
void ComboBox::addString(std::string newStr){
	comboBoxItems->addString(newStr);

	//�������� ��� ������
	showComboBoxStrings();
}

//��������� ������
void ComboBox::selectString(std::string str){
	currentSelectedIndex = comboBoxItems->findString(str);
	//��������� ��� ����������
	showComboBoxStrings();
}

//����������� ����� � ������
void ComboBox::showComboBoxStrings(){
	if (thisHandle == NULL) return;

	//������� ��� �������� ������
	SendMessage(thisHandle, CB_RESETCONTENT, (WPARAM)0, (LPARAM)0);

	std::string str;
	for (int ch=0; ch<comboBoxItems->length(); ch++){
		str = comboBoxItems->getString(ch);
		SendMessage(thisHandle, CB_ADDSTRING, (WPARAM)0, (LPARAM)str.c_str());
	}

	//������������� ���������
	SendMessage(thisHandle, CB_SETCURSEL, (WPARAM)currentSelectedIndex, (LPARAM)0);

}

//���� ���������� �����
std::string ComboBox::getCurrentSelected(){
	//����� ������ �������� ����������� ������ ������
	int pos = SendMessage(thisHandle, CB_GETCURSEL, (WPARAM)0, (LPARAM)0);
	
	//������ �� ���������
	if (pos == LB_ERR) return NULL;

	return comboBoxItems->getString(pos);
}

void ComboBox::setOnChangeSelectionHandler(void (_cdecl *handler)(ComboBox *callComboBox, std::string)){
	OnChangeSelectionHandler = handler;
}


//��������� ���������
BOOL ComboBox::messageIntercept(HWND windowHandle, UINT messageCode, WPARAM wParam, LPARAM lParam){

	//ComboBox ����� ���������� ������ ��� ��� ���� ���������, ��������� ������������
	if ((messageCode != WM_COMMAND) && (messageCode != WM_INITDIALOG)) return false;
	
	if (messageCode == WM_INITDIALOG){
		ownerHandle = windowHandle;
		//�������� ���������� ����� �����
		thisHandle = GetDlgItem(ownerHandle, comboBoxID);

		//���������� ������
		showComboBoxStrings();
	}

	switch(HIWORD(wParam)){
		case CBN_SELCHANGE:
			//���� ��� ��� ���������
			if ((HWND)lParam == thisHandle){
				//����� �������� ���������� ������ � ������� ��� � ���������� ������
				std::string str = getCurrentSelected();
				OnChangeSelectionHandler(this, str);
			}
	}

	return false;
}