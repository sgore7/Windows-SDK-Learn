#ifndef UNICODE
#define UNICODE
#endif // UNICODE

#include<Windows.h>
#include"ClassFactoryDllServerWithRegFile.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

ISum* pISum = NULL;
ISubtract* pISubtract = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR AppName[] = TEXT("COM Client");
	HRESULT hr;

	hr = CoInitialize(NULL);

	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("COM Library can not be initilized."), TEXT("Program Error"), MB_OK);
		exit(0);
	}

	wndclass.cbClsExtra = 0;
	wndclass.cbSize = sizeof(wndclass);
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = AppName;
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	
	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(AppName, TEXT("COM Client for COM DLL Server"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	CoUninitialize();
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	void SafeInterfaceRelease(void);

	HRESULT hr;
	int n, m, sum;
	TCHAR str[255];

	switch (iMsg)
	{
	case WM_CREATE:
		hr = CoCreateInstance(CLSID_SumSubtract, NULL, CLSCTX_INPROC_SERVER, IID_ISum, (void**)&pISum);
		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("ISum Interface can not be obtained"), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}

		n = 90;
		m = 10;

		pISum->SumOfTwoIntegers(n, m, &sum);

		wsprintf(str, TEXT("Sum is %d"), sum);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);

		pISum->QueryInterface(IID_ISubtract, (void**)&pISubtract);

		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("ISubtract Interface can not be obtained"), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}

		pISum->Release();
		pISum = NULL;

		n = 98;
		m = 8;

		pISubtract->SubtractionOfTwoIntegers(n, m, &sum);
		pISubtract->Release();
		pISubtract = NULL;

		wsprintf(str, TEXT("Subtraction is %d"), sum);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);

		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		SafeInterfaceRelease();

		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

void SafeInterfaceRelease(void) {
	if (pISum) {
		pISum->Release();
		pISum = NULL;
	}
	if (pISubtract) {
		pISubtract->Release();
		pISubtract = NULL;
	}
}
