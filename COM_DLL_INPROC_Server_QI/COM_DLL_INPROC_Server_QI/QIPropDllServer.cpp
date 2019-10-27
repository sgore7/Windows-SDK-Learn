#include<Windows.h>
#include"QIPropDllServer.h"

class CSumSubtractMultiply :public ISum, public ISubstract, public IMultiply {
private:
	ULONG m_cRef;
public:
	CSumSubtractMultiply(void);
	~CSumSubtractMultiply(void);

	HRESULT __stdcall QueryInterface(REFIID, void**);
	ULONG __stdcall AddRef(void);
	ULONG __stdcall Release(void);

	HRESULT __stdcall SumOfTwo(int,int,int*);
	HRESULT __stdcall SubOfTwo(int, int, int*);
	HRESULT __stdcall MultiplyOfTwo(int, int, int*);
};

BOOL WINAPI DllMain(HINSTANCE hDll, DWORD dwReason, LPVOID Reserved) {
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	default:
		break;
	}

	return(TRUE);
}

CSumSubtractMultiply::CSumSubtractMultiply(void) {
	m_cRef = 0;
}

CSumSubtractMultiply::~CSumSubtractMultiply(void) {

}

HRESULT CSumSubtractMultiply::QueryInterface(REFIID riid, void** ppv) {
	if (riid == IID_IUnknown) {
		*ppv = static_cast<ISum*> (this);
	}
	else if (riid == IID_ISum) {
		*ppv = static_cast<ISum*> (this);
	}
	else if (riid == IID_ISubtract) {
		*ppv = static_cast<ISubstract*> (this);
	}
	else if (riid == IID_IMultiply) {
		*ppv = static_cast<IMultiply*> (this);
	}
	else {
		*ppv = NULL;
		return(E_NOINTERFACE);
	}
	reinterpret_cast<IUnknown*> (*ppv)->AddRef();

	return(S_OK);
}

ULONG CSumSubtractMultiply::AddRef(void) {
	++m_cRef;
	return(m_cRef);
}

ULONG CSumSubtractMultiply::Release(void) {
	--m_cRef;

	if (m_cRef == 0) {
		delete (this);
		return 0;
	}
	return (m_cRef);
}

HRESULT CSumSubtractMultiply::SumOfTwo(int n, int m, int *r) {
	*r = n + m;
	return(S_OK);
}

HRESULT CSumSubtractMultiply::SubOfTwo(int n, int m, int *r) {
	*r = n - m;
	return(S_OK);
}

HRESULT CSumSubtractMultiply::MultiplyOfTwo(int n, int m, int *r) {
	*r = n * m;
	return(S_OK);
}

extern "C" __declspec(dllexport) HRESULT CreateComponentInstance(REFIID riid, void **ppv) {
	CSumSubtractMultiply *pCSumSubtractMultiply = NULL;

	pCSumSubtractMultiply = new CSumSubtractMultiply;

	if (pCSumSubtractMultiply == NULL) {
		return(E_OUTOFMEMORY);
	}

	pCSumSubtractMultiply->QueryInterface(riid, ppv);
	return(S_OK);
}
