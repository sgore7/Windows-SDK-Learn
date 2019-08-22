#include<Windows.h>

BOOL DllMain(HINSTANCE hDll,DWORD dwReason, LPVOID lpReserved){
	switch(dwReason){

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

extern "C" __declspec(dllexport) int MakeSquare(int num){
	return (num*num);
}

extern "C" BOOL IsNumberNegative(int num){
	return (num < 0 ? TRUE: FALSE);
}
