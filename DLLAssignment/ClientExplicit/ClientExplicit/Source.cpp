#include <Windows.h>
#include "include/MyMath.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {
	WNDCLASSEX wndclass;
	MSG iMsg;
	HWND hwnd;

	TCHAR szAppName[] = TEXT("DLLClientExplicitNonDef");

	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hCursor = LoadCursor(NULL,IDC_ARROW);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName, TEXT("DLL Explicit without DEF"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&iMsg, NULL, 0, 0)) {
		TranslateMessage(&iMsg);
		DispatchMessage(&iMsg);
	}

	return((int)iMsg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	TCHAR str[255];
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rc;
	wsprintf(str, TEXT("DLLExplicit"));
	HMODULE hDll;
	hDll = LoadLibrary(TEXT("MyMath.dll"));
	int i = 7;
	TCHAR resultStr[255];
	int (*pFunMakeSquare)(int);
	pFunMakeSquare = (int (*)(int))GetProcAddress(hDll, "MakeSquare");


	switch (iMsg) {
	case WM_CREATE:
		wsprintf(resultStr, TEXT("Sqaure of number %d is %d."), i, pFunMakeSquare(i));
		FreeLibrary(hDll);
		MessageBox(hwnd, resultStr, str, MB_OK | MB_ICONWARNING);
		break;

	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rc);

		SetTextColor(hdc, RGB(0, 255, 0));
		TextOut(hdc, 10, 10, resultStr, 27);
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		MessageBox(hwnd, TEXT("Destroying Window"), str, MB_OK | MB_ICONWARNING);
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
