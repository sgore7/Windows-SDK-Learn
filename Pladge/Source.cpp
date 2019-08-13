#include <windows.h>
#include <cstdio>
#define COUNT_OF( array ) ( sizeof( array )/sizeof( array[0] ) )

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrecInstance, LPSTR lpszCmdLine, int iCmdShow) {

	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("Pladge");

	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName,TEXT("Pladge App"),WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,hInstance,NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	TEXTMETRIC tm;
	static int cyChar;
	static FILE *pfLogFile;

	int i, X, Y;
	PAINTSTRUCT ps;
	RECT rc;

	int iLenPladge;
	TCHAR lpszPladge[] = TEXT( "India is my country. All Indians are my Brothers and Sisters. I love my country and I am proud of its rich and varied heritage. I shall always strive to be worthy of it. I shall give my parents,teachers and all elders respect and treat everyone with courtesy. To my country and my people, I pledge my devotion. In their well being and prosperity alone, lies my happiness.");

	iLenPladge = COUNT_OF(lpszPladge);

	switch (iMsg)
	{
	case WM_DESTROY:
		fclose(pfLogFile);
		PostQuitMessage(0);
		break;

	case WM_CREATE:
		fopen_s(&pfLogFile, "./log.txt", "w");
		if (pfLogFile == NULL) {
			PostQuitMessage(0);
		}
		hdc = GetDC(hwnd);
		GetTextMetrics(hdc, &tm);
		ReleaseDC(hwnd, hdc);
		cyChar = tm.tmHeight + tm.tmExternalLeading;
		break;

	case WM_PAINT:
		GetClientRect(hwnd, &rc);
		hdc = BeginPaint(hwnd, &ps);
		X = rc.right / 2;
		Y = rc.bottom / 2;
		Y = 0;
		SetBkColor(hdc, RGB(0, 0, 0));
		int ind = 0, count = 20;
		for (i = 0; i < iLenPladge; i++)
		{
			if (i < (iLenPladge/3))
			{
				fprintf_s(pfLogFile, "%d is the i value \n",i);
				SetTextColor(hdc, RGB(255, 200, 0));
				//SetTextColor(hdc, RGB(255, 255, 255));
				TextOut(hdc, X, Y, &lpszPladge[ind], count);
			}
			else if(i < ((iLenPladge / 3)+(iLenPladge / 3)))
			{
				fprintf_s(pfLogFile, "%d is the i value1 \n", i);
				SetTextColor(hdc, RGB(255, 255, 255));
				TextOut(hdc, X, Y, &lpszPladge[ind], count);
			}
			else
			{
				fprintf_s(pfLogFile, "%d is the i value2 \n", i);
				SetTextColor(hdc, RGB(0, 255, 0));
				TextOut(hdc, X, Y, &lpszPladge[ind], count);
			}
			
			//TextOut(hdc, X, Y, &lpszPladge[ind], count);
			Y = Y + cyChar;
			ind = ind + 20;
			if (ind+20 > iLenPladge) {
				count = iLenPladge - (ind);
			}

		}
		EndPaint(hwnd, &ps);

		break;

	}

	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}
