//#define UNICODE
#include<Windows.h>
#include"QIPropDllServer.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void SafeInterfaceRelease(void);

ISum* pISum=NULL;
ISubstract* pISubtract=NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR AppName[] = TEXT("ComClient");

	wndclass.cbSize = sizeof(wndclass);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = AppName;
	wndclass.lpszMenuName = NULL;
	
	RegisterClassEx(&wndclass);

	hwnd = CreateWindow(AppName, TEXT("COM Client QI Properties"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	BOOL CheckIdentity(ISum*, ISubstract*);
	BOOL CheckPredictability(ISum*);
	BOOL CheckSymmetry(ISum*);
	BOOL CheckReflexivity(ISum*);
	BOOL CheckTransitivity(ISum*);

	static HMODULE hServerLib = NULL;
	typedef HRESULT(*PFN_FUNCTION) (REFIID, void**);
	PFN_FUNCTION pfnCreateComponentInstance = NULL;
	HRESULT hr;
	//TCHAR str[255];
	wchar_t str[255];


	switch (iMsg){
	case WM_CREATE:
		hServerLib = LoadLibrary(TEXT("COM_DLL_INPROC_Server_QI.dll"));
		if (hServerLib == NULL) {
			MessageBox(hwnd, TEXT("Failed to load library."), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}

		pfnCreateComponentInstance = (PFN_FUNCTION)GetProcAddress(hServerLib, "CreateComponentInstance");

		if (pfnCreateComponentInstance == NULL) {
			MessageBox(hwnd, TEXT("Failed to load function from library."), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}

		hr = pfnCreateComponentInstance(IID_ISum, (void**)&pISum);
		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("Trobule while getting ISum interface."), TEXT("Error"), MB_OK);
			DestroyWindow(hwnd);
		}

		hr = pfnCreateComponentInstance(IID_ISum, (void**)&pISubtract);

		if (FAILED(hr)) {
			MessageBox(hwnd, TEXT("Trobule while getting ISubtract interface."), TEXT("Error"), MB_OK);
			pISum->Release();
			pISum = NULL;
			DestroyWindow(hwnd);
		}

		if (CheckIdentity(pISum, pISubtract) == TRUE) {
			const TCHAR s[256] = TEXT("ISUM and ISubtract interface belong to same component.");
			wcscpy_s(str, TEXT("ISUM and ISubtract interface belong to same component."));
		}
		else {
			const TCHAR s[256] = TEXT("ISUM and ISubtract interface belong to different component.");
			wcscpy_s(str, TEXT("ISUM and ISubtract interface belong to different component."));
		}
		MessageBox(hwnd, str, TEXT("Message"), MB_OK);
		pISubtract->Release();
		pISubtract = NULL;

		if (CheckPredictability(pISum) == TRUE) {
			TCHAR s[256] = TEXT("The component is predictable and its interface do not change over time.");
			wcscpy_s(str, TEXT("The component is predictable and its interface do not change over time."));
		}
		else {
			TCHAR s[256] = TEXT("The component is not predictable and its interface do not change over time.");
			wcscpy_s(str, TEXT("The component is not predictable and its interface do not change over time."));
		}
		MessageBox(hwnd, str, TEXT("Message"), MB_OK);

		if (CheckSymmetry(pISum) == TRUE) {
			TCHAR s[256] = TEXT("The component is symmetric.");
			wcscpy_s(str, TEXT("The component is symmetric."));
		}
		else {
			TCHAR s[256] = TEXT("The component is not symmetric");
			wcscpy_s(str, TEXT("The component is not symmetric"));
		}
		MessageBox(hwnd, str, TEXT("Message"), MB_OK);

		if (CheckReflexivity(pISum) == TRUE) {
			TCHAR s[256] = TEXT("The Component is reflexive.");
			wcscpy_s(str, TEXT("The Component is reflexive."));
		}
		else {
			TCHAR s[256] = TEXT("The component is not reflexive.");
			wcscpy_s(str, TEXT("The component is not reflexive."));
		}
		MessageBox(hwnd, str, TEXT("Message"), MB_OK);

		if (CheckTransitivity(pISum) == TRUE) {
			TCHAR s[256] = TEXT("The component is transitive.");
			wcscpy_s(str, TEXT("The component is transitive."));
		}
		else {
			TCHAR s[256] = TEXT("The component is not transitive.");
			wcscpy_s(str, TEXT("The component is not transitive."));
		}
		MessageBox(hwnd, str, TEXT("Message"), MB_OK);

		DestroyWindow(hwnd);
		
		break;
	case WM_DESTROY:
		SafeInterfaceRelease();

		if (hServerLib) {
			FreeLibrary(hServerLib);
			hServerLib = NULL;
		}
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

BOOL CheckIdentity(ISum* ptrIsum, ISubstract* ptrISubtract) {
	IUnknown *pIUnknownFromISum = NULL;
	IUnknown *pIUnknownFromISubtract = NULL;

	HRESULT hr;

	hr = ptrIsum->QueryInterface(IID_IUnknown, (void**)(& pIUnknownFromISum));

	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("Can not Obtain IUnkown from ISum."), TEXT("CheckIdentity() Error"), MB_OK);
	}

	hr = ptrISubtract->QueryInterface(IID_IUnknown, (void**)&pIUnknownFromISubtract);

	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("Can not Obtain IUnkown from ISubtract."), TEXT("CheckIdentity() Error"), MB_OK);
	}

	if (pIUnknownFromISubtract == pIUnknownFromISum) {
		return(TRUE);
	}
	return(FALSE);
}

BOOL CheckPredictability(ISum *ptrISum) {
	ISubstract *pISubtract = NULL;
	HRESULT hr;

	hr = ptrISum->QueryInterface(IID_ISubtract, (void**)&pISubtract);
	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("Can not get ISubtract from ISum."), TEXT("CheckPredictability() Error"), MB_OK);
	}
	else {
		pISubtract->Release();
		pISubtract = NULL;
		return(TRUE);
	}
}

BOOL CheckSymmetry(ISum *ptrISum) {
	ISubstract *pISubtract = NULL;
	ISum *pISumAgain = NULL;
	HRESULT hr;

	hr = pISum->QueryInterface(IID_ISubtract, (void**)&pISubtract);
	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("Can not get ISutract from ISum."), TEXT("CheckSymmetry() Error"), MB_OK);
	}
	else {
		hr = pISubtract->QueryInterface(IID_ISum, (void**)&pISumAgain);
		if (FAILED(hr)) {
			MessageBox(NULL, TEXT("Can not get ISum from ISubtract."), TEXT("CheckSymmetry() Error"), MB_OK);
		}
		else {
			if (ptrISum == pISumAgain) {
				pISumAgain->Release();
				pISumAgain = NULL;
				return(TRUE);
			}
			else {
				pISumAgain->Release();
				pISumAgain = NULL;
				return(FALSE);
			}
		}
	}
	return(FALSE);
}

BOOL CheckReflexivity(ISum* ptrISum) {
	ISum *pISumAgain = NULL;
	HRESULT hr;

	hr = ptrISum->QueryInterface(IID_ISum, (void**)&pISumAgain);
	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("Can not get ISum from ISum itself."), TEXT("CheckSymmetry() Error"), MB_OK);
	}
	else {
		if (ptrISum == pISumAgain) {
			pISumAgain->Release();
			pISumAgain = NULL;
			return(TRUE);
		}
		else {
			pISumAgain->Release();
			pISumAgain = NULL;
			return(FALSE);
		}
	}
	return(FALSE);
}

BOOL CheckTransitivity(ISum *ptrISum) {
	ISum *pISumAgain = NULL;
	ISubstract *pISubtract = NULL;
	IMultiply *pIMultiply = NULL;

	HRESULT hr;

	hr = ptrISum->QueryInterface(IID_ISubtract, (void**)&pISubtract);
	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("Can not get ISubtract from ISum."), TEXT("CheckTransitivity() Error"), MB_OK);
	}

	hr = pISubtract->QueryInterface(IID_IMultiply, (void**)&pIMultiply);
	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("Can not get IMultiply from ISubtract."), TEXT("CheckTransitivity() Error"), MB_OK);
	}

	hr = ptrISum->QueryInterface(IID_ISum, (void**)&pISumAgain);
	if (FAILED(hr)) {
		MessageBox(NULL, TEXT("Can not get ISum from IMultiply itself."), TEXT("CheckTransitivity() Error"), MB_OK);
	}
	else {
		if (ptrISum == pISumAgain) {
			pISumAgain->Release();
			pISumAgain = NULL;
			pIMultiply->Release();
			pIMultiply = NULL;
			pISubtract->Release();
			pISubtract = NULL;
			return(TRUE);
		}
		else {
			pISumAgain->Release();
			pISumAgain = NULL;
			pIMultiply->Release();
			pIMultiply = NULL;
			pISubtract->Release();
			pISubtract = NULL;
			return(FALSE);
		}
	}
	return(FALSE);
}