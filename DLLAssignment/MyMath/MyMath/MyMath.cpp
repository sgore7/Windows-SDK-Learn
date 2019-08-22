#include<Windows.h>

BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved) {
	
	switch (dwReason) {
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}

	return TRUE;
}

extern "C" __declspec(dllexport) int MakeSquare(int num) {
	return (num*num);
}

extern "C" BOOL isNumberNegative(int num) {
	return (num < 0 ? TRUE : FALSE);
}