#pragma once
//#include <Windows.h>

class ISum :public IUnknown {
public:
	virtual HRESULT __stdcall SumOfTwo(int, int, int*) = 0;
};

class ISubstract :public IUnknown {
public:
	virtual HRESULT __stdcall SubOfTwo(int, int, int*) = 0;
};

class IMultiply :public IUnknown {
public:
	virtual HRESULT __stdcall MultiplyOfTwo(int, int, int*) = 0;
};

// {9839B3A4 - 9E2E - 49D1 - 9893 - 3B73F0D26032}
const IID IID_ISum = { 0x9839b3a4, 0x9e2e, 0x49d1, 0x98, 0x93, 0x3b, 0x73, 0xf0, 0xd2, 0x60, 0x32 };

// {DFD292AE-9084-4506-B36C-BF12042FFF14}
const IID IID_ISubtract = { 0xdfd292ae, 0x9084, 0x4506, 0xb3, 0x6c, 0xbf, 0x12, 0x4, 0x2f, 0xff, 0x14 };

// {70568272-E924-4A6F-91EE-0315DD465AA7}
const IID IID_IMultiply = { 0x70568272, 0xe924, 0x4a6f, 0x91, 0xee, 0x3, 0x15, 0xdd, 0x46, 0x5a, 0xa7 };

extern "C" __declspec(dllexport) HRESULT CreateComponentInterface(REFIID, void**);
