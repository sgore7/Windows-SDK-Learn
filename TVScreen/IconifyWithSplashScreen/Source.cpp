#include<Windows.h>
#include "IconSplash.h"

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {

	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("IconSplashApp");

	wndclass.cbClsExtra = 0;
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.cbWndExtra = 0;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MY_ICON));
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH) GetStockObject(WHITE_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MY_ICON));

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName, TEXT("ICON SPLASH App"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while(GetMessage(&msg, NULL, 0, 0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam){
	HINSTANCE hInstanceForUse;
	static HBITMAP hBitmap = NULL;
	HGDIOBJ hPrevSelectObj;
	HDC hdcMain, hdcTemp;
	BITMAP bmpImage;
	RECT rc;
	PAINTSTRUCT ps;

	switch(iMsg){
		case WM_CREATE:
			hInstanceForUse = GetModuleHandle(NULL);
			hBitmap = LoadBitmap(hInstanceForUse, MAKEINTRESOURCE(MY_BITMAP));
		break;
		case WM_PAINT:
			GetClientRect(hwnd, &rc);
			hdcMain = BeginPaint(hwnd, &ps);

			hdcTemp = CreateCompatibleDC(NULL);
			hPrevSelectObj = SelectObject(hdcTemp, hBitmap);
			GetObject(hBitmap, sizeof(BITMAP), &bmpImage);
			StretchBlt(hdcMain, 0, 0, rc.right, rc.bottom, hdcTemp, 0, 0, bmpImage.bmWidth, bmpImage.bmHeight, SRCCOPY);
			SelectObject(hdcTemp, hPrevSelectObj);
			DeleteDC(hdcTemp);
			EndPaint(hwnd, &ps);

		break;
		case WM_DESTROY:
			DeleteObject(hBitmap);
			PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd,iMsg,wParam,lParam));
}
