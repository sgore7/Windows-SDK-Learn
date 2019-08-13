#include<Windows.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow) {
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szAppName[] = TEXT("MessageBoxHandling");

	wndclass.cbClsExtra = 0;
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(szAppName, TEXT("MESSAGE BOX USE"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	MessageBox(hwnd, TEXT("Check WinMain has message box"), TEXT("WinMain"), MB_OK | MB_ICONQUESTION);

	while (GetMessage(&msg,NULL,0,0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	TCHAR str[255]; //caption string for message box
	wsprintf(str, TEXT("MessageBox Handling"));

	switch (iMsg) {
	case WM_CREATE:
		MessageBox(hwnd, TEXT("Window is creating"), str, MB_OK | MB_ICONINFORMATION);
		break;
	case WM_LBUTTONDOWN:
		MessageBox(hwnd, TEXT("Mouse left Click"), str, MB_OK | MB_ICONERROR);
		break;
	case WM_KEYDOWN:
		CHAR carrChars[26];
		INT iVal;
		iVal = 65;

		TCHAR strMsgForMB[255]; //Message in string for MB

		for (int i = 0; i < 26; i++) {
			carrChars[i] = (CHAR)iVal;
			iVal++;
		}

		for (int i = 0; i < 26; i++) {
			if (wParam == carrChars[i]) {
				wsprintf(strMsgForMB, TEXT("Key Pressed: %c char Key"),carrChars[i]);
				MessageBox(hwnd, strMsgForMB, str, MB_OK);
				break;
			}
		}

		switch (wParam) {
		case VK_LEFT:
			MessageBox(hwnd, TEXT("Key Pressed: Left Key"), str, MB_OK);
			break;
		case VK_RIGHT:
			MessageBox(hwnd, TEXT("Key Pressed: Right Key"), str, MB_OK);
			break;
		case VK_UP:
			MessageBox(hwnd, TEXT("Key Pressed: Up Key"), str, MB_OK);
			break;
		case VK_DOWN:
			MessageBox(hwnd, TEXT("Key Pressed: Down Key"), str, MB_OK);
			break;
		}
		break;
	case WM_DESTROY:
		MessageBox(hwnd, TEXT("Destroying Window"), str, MB_OK | MB_ICONWARNING);
		PostQuitMessage(0);
		break;
	}
	return (DefWindowProc(hwnd, iMsg, wParam, lParam));
}
