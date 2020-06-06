#include "RectangleProportions.h"

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


RectangleProportions *rectangleProportions;
RectangleProportions::RectangleProportions(int posX, int posY, int inShirina, int inVisota, HWND inOwnerHandle){
	
	rectangleProportions = this;

	shapeRect.top = 5;
	shapeRect.left = 5;
	shapeRect.bottom = 30;
	shapeRect.right = 60;

	shadowRect.top = 0;
	shadowRect.left = 0;
	shadowRect.bottom = 0;
	shadowRect.right = 0;

	//Рассчёт размера области
	int ident;//Отступ от края области
	if (inShirina>inVisota){
		ident = inVisota/20;
		sideAreaSize = inVisota - (ident*2);
		startUp = ident;
		startLeft = (inShirina - sideAreaSize)/2;
	} else {
		ident = inShirina/10;
	}

	char RectProportionName[] = "Rectangle_proportion_window";
	WNDCLASSEX recProp;

	recProp.cbSize = sizeof(recProp);
	recProp.style = CS_GLOBALCLASS;
	recProp.lpfnWndProc = WndProc;
	recProp.cbClsExtra = 0;
	recProp.cbWndExtra = 0;
	recProp.hInstance = GetModuleHandle(NULL);
	recProp.hIcon = NULL;
	recProp.hCursor = NULL;
	recProp.hbrBackground = (HBRUSH)GetStockObject(GRAY_BRUSH);
	recProp.lpszMenuName = NULL;
	recProp.lpszClassName = RectProportionName;
	recProp.hIcon = NULL;
	recProp.hIconSm = NULL;
	
	if (!RegisterClassEx(&recProp)){
		int err = GetLastError();
		//MessageBox(NULL, "Пиздец", "Ы", MB_OK);
	}


	thisHandle = CreateWindow(
		RectProportionName,
		"rectprp",
		WS_CHILD|WS_VISIBLE|WS_BORDER,
		posX,
		posY,
		inShirina,
		inVisota,
		inOwnerHandle,
		NULL,
		NULL,
		NULL
	);
	
	//ShowWindow(thisHandle, SW_MAXIMIZE);
}


void RectangleProportions::setRectangleProportions(int shirina, int visota){
	int rectShirina;
	int rectVisota;
	
	if (shirina>visota){
		rectShirina = sideAreaSize;
		rectVisota = (visota*sideAreaSize)/shirina;

		shapeRect.top = startUp+(sideAreaSize-rectVisota)/2;
		shapeRect.left = startLeft;
		
	} else {
		rectVisota = sideAreaSize;
		rectShirina = (shirina*sideAreaSize)/visota;

		shapeRect.left = startLeft+(sideAreaSize-rectShirina)/2;
		shapeRect.top = startUp;
		
		
		
		
	}

		shapeRect.right = shapeRect.left+rectShirina;
		shapeRect.bottom = shapeRect.top+rectVisota;

		//Обновляем область, вызываем генерацию сообщения WM_PAINT
		InvalidateRect(thisHandle, NULL, TRUE);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
	HDC hDC;
	HBRUSH whiteBrush = (HBRUSH)GetStockObject(WHITE_BRUSH);
	PAINTSTRUCT ps;
	

	
	switch (uMsg){
		case WM_PAINT:
			//MessageBox(NULL, "зфшт", "Ы", MB_OK);
			hDC = BeginPaint(hWnd, &ps);
			
			FillRect(hDC, &rectangleProportions->shapeRect, whiteBrush);
			
			EndPaint(hWnd, &ps);
			break;
		default:
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}