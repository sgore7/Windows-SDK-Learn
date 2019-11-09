#ifndef UNICODE
#define UNICODE
#endif // UNICODE

#include<Windows.h>
#include"ClientOfContainmentWithRegFile.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

ISum* pISum = NULL;
ISubtract* pISubtract = NULL;
IMultiplication* pIMultiplication = NULL;
IDivision* pIDivision = NULL;

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
	int n, m, sum, subtract, multiply, division;
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

		hr =pISum->QueryInterface(IID_ISubtarct, (void**)&pISubtract);

		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("ISubtract Interface can not be obtained"), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}

		pISum->Release();
		pISum = NULL;

		n = 98;
		m = 8;

		pISubtract->SubtractionOfTwoIntegers(n, m, &subtract);

		wsprintf(str, TEXT("Subtraction is %d"), subtract);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);

		hr= pISubtract->QueryInterface(IID_IMultiplication, (void**)&pIMultiplication);

		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("IMultiplication Interface can not be obtained"), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}

		pISubtract->Release();
		pISubtract = NULL;

		m = 3;
		n = 2;

		pIMultiplication->MultiplicationOfTwoIntegers(m, n, &multiply);

		wsprintf(str, TEXT("Multiplication is %d"), multiply);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);

		hr = pIMultiplication->QueryInterface(IID_IDivision, (void**)&pIDivision);

		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("IDivision Interface can not be obtained"), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}

		pIMultiplication->Release();
		pIMultiplication = NULL;

		m = 4;
		n = 2;

		pIDivision->DivisionOfTwoIntegers(m, n, &division);

		wsprintf(str, TEXT("Division is %d"), division);
		MessageBox(hwnd, str, TEXT("Result"), MB_OK);

		pIDivision->Release();
		pIDivision = NULL;

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
	if (pIMultiplication) {
		pIMultiplication->Release();
		pIMultiplication = NULL;
	}
	if (pIDivision) {
		pIDivision->Release();
		pIDivision = NULL;
	}
}
