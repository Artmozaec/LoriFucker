#include "LabelText.h"

LabelText::LabelText(int inLabelTextID){
	LabelTextID = inLabelTextID;

	ownerHandle = NULL;
	thisHandle = NULL;
}
		
//����� ������
void LabelText::setCaption(std::string newText){
	text = newText;

	if (thisHandle == NULL) return;

	SetWindowText(thisHandle, text.c_str());
}

//���� �����
std::string LabelText::getCaption(){
	return NULL;
}


//��������� ���������
BOOL LabelText::messageIntercept(HWND windowHandle, UINT messageCode, WPARAM wParam, LPARAM lParam){
	
	//LabelText ����� ���������� ������ ��� ��� ���� ���������, ��������� ������������
	if ((messageCode != WM_COMMAND) && (messageCode != WM_INITDIALOG)) return false;
	
	if (messageCode == WM_INITDIALOG){
		ownerHandle = windowHandle;
		//�������� ���������� ������
		thisHandle = GetDlgItem(ownerHandle, LabelTextID);
		
		//�������������� �����
		setCaption(text);
	}
	
	return false;
}