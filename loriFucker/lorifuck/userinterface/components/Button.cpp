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
	//���� ������� ���������� �� ��������� WM_INITDIALOG ������� ���� � ���� ���������� ������������� ����, �� �������� ����������� ���������� ���� ������
	if (thisHandle == NULL) return;

	//���� �������� ���
	if (enableImage == NULL){
		//����� ��������� ������� ������ ����� ���������� ������
		EnableWindow(thisHandle, true);
		return;
	}

	//���������� �������� �������� ������
	SendMessage(thisHandle, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)enableImage);
	SendMessage(thisHandle, BM_SETSTATE, (WPARAM)FALSE, (LPARAM)0);
}


void Button::disable(){
	enableButton = false;
	//���� ������� ���������� �� ��������� WM_INITDIALOG ������� ���� � ���� ���������� ������������� ����, �� �������� ����������� ���������� ���� ������
	if (thisHandle == NULL) return;
	
	//���� �������� ���
	if (disableImage == NULL){
		//����� ��������� ������� ������ ����� ���������� ������
		EnableWindow(thisHandle, false);
		return;
	}
	
	//���������� �������� ��������� ������
	SendMessage(thisHandle, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)disableImage);
	SendMessage(thisHandle, BM_SETSTATE, (WPARAM)TRUE, (LPARAM)0);
}



BOOL Button::messageIntercept(HWND windowHandle, UINT messageCode, WPARAM wParam, LPARAM lParam){
	
	//������ ����� ���������� ������ ��� ��� ���� ���������, ��������� ������������
	if ((messageCode != WM_COMMAND) && (messageCode != WM_INITDIALOG)) return false;
	
	if (messageCode == WM_INITDIALOG){
		ownerHandle = windowHandle;
		//�������� ���������� ������
		thisHandle = GetDlgItem(ownerHandle, buttonID);

		if (enableButton){ 
			enable();
		}else{
			disable();
		}
	}

	//���� ��������� ���������� �� ����� ��������, �����!
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

