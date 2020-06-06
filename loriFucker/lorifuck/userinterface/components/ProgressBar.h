#ifndef ProgressBarH
#define ProgressBarH

#include <windows.h>
#include <stdio.h>
#include "commctrl.h"

class ProgressBar{
	public:
		ProgressBar(int posX, int posY, int visota, int shirina);

		//Обработка сообщений
		BOOL messageIntercept(HWND windowHandle, UINT messageCode, WPARAM wParam, LPARAM lParam);

		//Изменить процент прогресса
		void setProgressPercent(int percent);
	private:
		
		HWND ownerHandle;
		HWND thisHandle;

		int posX;
		int posY;
		int shirina;
		int visota;
};


#endif