#include<Windows.h>
#define MY_TIMER 101

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR lpszCmdLine, int iCmdShow) {
	TCHAR szAppName[] = TEXT("TVScreen");

	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;

	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClass(&wndclass);

	hwnd = CreateWindow(szAppName, TEXT("TV Screen"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);

	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	static int flag = -1;
	HBRUSH hBrush;
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rc, rectTemp;

	switch (iMsg) {
	case WM_CREATE:
		SetTimer(hwnd, MY_TIMER, 2000, NULL);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_TIMER:
		KillTimer(hwnd, MY_TIMER);
		flag++;
		if (flag > 7)
			break;
		InvalidateRect(hwnd, NULL, TRUE);
		SetTimer(hwnd, MY_TIMER, 2000, NULL);
		break;

	case WM_PAINT:
		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);
		
		if (flag >= 0)
		{
			hBrush = CreateSolidBrush(RGB(0, 0, 0));
			SelectObject(hdc, hBrush);
			rectTemp.bottom = rc.bottom;
			rectTemp.left = rc.left;
			rectTemp.top = rc.top;
			rectTemp.right = rc.right / 8;
			FillRect(hdc, &rectTemp, hBrush);
			DeleteObject((HGDIOBJ)hBrush);
		}

		if (flag >= 1)
		{
			hBrush = CreateSolidBrush(RGB(255, 0, 0));
			SelectObject(hdc, hBrush);
			rectTemp.bottom = rc.bottom;
			rectTemp.left = rectTemp.right;
			rectTemp.top = rc.top;
			rectTemp.right = rectTemp.right + (rc.right / 8);
			FillRect(hdc, &rectTemp, hBrush);
			DeleteObject((HGDIOBJ)hBrush);
		}

		if (flag >= 2)
		{
			hBrush = CreateSolidBrush(RGB(0, 255, 0));
			SelectObject(hdc, hBrush);
			rectTemp.bottom = rc.bottom;
			rectTemp.left = rectTemp.right;
			rectTemp.top = rc.top;
			rectTemp.right = rectTemp.right + (rc.right / 8);
			FillRect(hdc, &rectTemp, hBrush);
			DeleteObject((HGDIOBJ)hBrush);
		}

		if (flag >= 3)
		{
			hBrush = CreateSolidBrush(RGB(0, 0, 255));
			SelectObject(hdc, hBrush);
			rectTemp.bottom = rc.bottom;
			rectTemp.left = rectTemp.right;
			rectTemp.top = rc.top;
			rectTemp.right = rectTemp.right + (rc.right / 8);
			FillRect(hdc, &rectTemp, hBrush);
			DeleteObject((HGDIOBJ)hBrush);
		}
		if (flag >= 4)
		{
			hBrush = CreateSolidBrush(RGB(0, 255, 255));
			SelectObject(hdc, hBrush);
			rectTemp.bottom = rc.bottom;
			rectTemp.left = rectTemp.right;
			rectTemp.top = rc.top;
			rectTemp.right = rectTemp.right + (rc.right / 8);
			FillRect(hdc, &rectTemp, hBrush);
			DeleteObject((HGDIOBJ)hBrush);
		}

		if (flag >= 5)
		{
			hBrush = CreateSolidBrush(RGB(255, 0, 255));
			SelectObject(hdc, hBrush);
			rectTemp.bottom = rc.bottom;
			rectTemp.left = rectTemp.right;
			rectTemp.top = rc.top;
			rectTemp.right = rectTemp.right + (rc.right / 8);
			FillRect(hdc, &rectTemp, hBrush);
			DeleteObject((HGDIOBJ)hBrush);
		}

		if (flag >= 6)
		{
			hBrush = CreateSolidBrush(RGB(255, 255, 0));
			SelectObject(hdc, hBrush);
			rectTemp.bottom = rc.bottom;
			rectTemp.left = rectTemp.right;
			rectTemp.top = rc.top;
			rectTemp.right = rectTemp.right + (rc.right / 8);
			FillRect(hdc, &rectTemp, hBrush);
			DeleteObject((HGDIOBJ)hBrush);
		}

		if (flag >= 7)
		{
			hBrush = CreateSolidBrush(RGB(255, 255, 255));
			SelectObject(hdc, hBrush);
			rectTemp.bottom = rc.bottom;
			rectTemp.left = rectTemp.right;
			rectTemp.top = rc.top;
			rectTemp.right = rectTemp.right + (rc.right / 8);
			FillRect(hdc, &rectTemp, hBrush);
			DeleteObject((HGDIOBJ)hBrush);
		}
		EndPaint(hwnd, &ps);
		break;
	}
	return (DefWindowProc(hwnd,iMsg,wParam,lParam));
}