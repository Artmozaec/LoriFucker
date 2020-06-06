#include "ProgressBar.h"

ProgressBar::ProgressBar(int inPosX, int inPosY, int inVisota, int inShirina){
	posX = inPosX;
	posY = inPosY;
	visota = inVisota;
	shirina = inShirina;

	//Инициализация процессбара
	INITCOMMONCONTROLSEX icc;

	icc.dwSize = sizeof(INITCOMMONCONTROLSEX);
	icc.dwICC = ICC_PROGRESS_CLASS;

	InitCommonControlsEx(&icc);
}

//Изменить процент прогресса
void ProgressBar::setProgressPercent(int percent){
	SendMessage(thisHandle, PBM_SETPOS, (WPARAM)percent, (LPARAM)0);
}


//Обработка сообщений
BOOL ProgressBar::messageIntercept(HWND windowHandle, UINT messageCode, WPARAM wParam, LPARAM lParam){
	//ProgressBar может воспринять только эти два типа сообщения, остальные игнорируются
	if (messageCode != WM_INITDIALOG) return false;
	
	ownerHandle = windowHandle;

	//Создаём progress bar
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

	//Устанавливаем диапазон от 0 до 100 процентов
	SendMessage(thisHandle, PBM_SETRANGE, (WPARAM)0, MAKELPARAM(0, 100));
	return false;
}