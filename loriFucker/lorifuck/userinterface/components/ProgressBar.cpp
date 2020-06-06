#include "ProgressBar.h"

ProgressBar::ProgressBar(int inPosX, int inPosY, int inVisota, int inShirina){
	posX = inPosX;
	posY = inPosY;
	visota = inVisota;
	shirina = inShirina;

	//������������� �����������
	INITCOMMONCONTROLSEX icc;

	icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icc.dwICC = ICC_PROGRESS_CLASS;

	InitCommonControlsEx(&icc);
}

//�������� ������� ���������
void ProgressBar::setProgressPercent(int percent){
	SendMessage(thisHandle, PBM_SETPOS, (WPARAM)percent, (LPARAM)0);
}


//��������� ���������
BOOL ProgressBar::messageIntercept(HWND windowHandle, UINT messageCode, WPARAM wParam, LPARAM lParam){
	//ProgressBar ����� ���������� ������ ��� ��� ���� ���������, ��������� ������������
	if (messageCode != WM_INITDIALOG) return false;
	
	ownerHandle = windowHandle;

	//������ progress bar
	thisHandle = CreateWindow(
		PROGRESS_CLASS,
		NULL,
		WS_CHILD|WS_VISIBLE|WS_BORDER|PBS_SMOOTH,
		posX,
		posY,
		shirina,
		visota,
		ownerHandle,
		NULL,
		NULL,
		NULL
	);

	//������������� �������� �� 0 �� 100 ���������
	SendMessage(thisHandle, PBM_SETRANGE, (WPARAM)0, MAKELPARAM(0, 100));
	return false;
}