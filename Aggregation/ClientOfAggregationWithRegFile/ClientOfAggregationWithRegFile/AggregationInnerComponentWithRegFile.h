#pragma once
class IMultiplication :public IUnknown {
public:
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*) = 0;
};

class IDivision : public IUnknown {
public:
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*) = 0;
};

// {F14D941D-E6C5-4E6D-B26E-179D629A02E9}
const CLSID CLSID_IMultiplicationDivision = { 0xf14d941d, 0xe6c5, 0x4e6d, 0xb2, 0x6e, 0x17, 0x9d, 0x62, 0x9a, 0x2, 0xe9 };

// {C8DEB84B-4FB2-4860-81D9-443B27FD81EF}
const IID IID_IMultiplication = { 0xc8deb84b, 0x4fb2, 0x4860, 0x81, 0xd9, 0x44, 0x3b, 0x27, 0xfd, 0x81, 0xef };

// {87815B93-315F-496E-B261-D4FD0FDDD5B3}
const IID IID_IDivision = { 0x87815b93, 0x315f, 0x496e, 0xb2, 0x61, 0xd4, 0xfd, 0xf, 0xdd, 0xd5, 0xb3 };
