#pragma once

class IMultiplication :public IUnknown {
public:
	virtual HRESULT __stdcall MultiplicationOfTwoIntegers(int, int, int*) = 0;
};

class IDivision : public IUnknown {
public:
	virtual HRESULT __stdcall DivisionOfTwoIntegers(int, int, int*) = 0;
};

// {FB8827BF-AF11-4891-867B-EB7AF33DE45A}
const CLSID CLSID_MultiplicationDivision = { 0xfb8827bf, 0xaf11, 0x4891, 0x86, 0x7b, 0xeb, 0x7a, 0xf3, 0x3d, 0xe4, 0x5a };

// {072E55BC-46FD-46A5-A9B1-5FACCF0EE007}
const IID IID_IMultiplication = { 0x72e55bc, 0x46fd, 0x46a5, 0xa9, 0xb1, 0x5f, 0xac, 0xcf, 0xe, 0xe0, 0x7 };

// {AFAF069E-7116-499C-8793-7EC9015379F6}
const IID IID_IDivision = { 0xafaf069e, 0x7116, 0x499c, 0x87, 0x93, 0x7e, 0xc9, 0x1, 0x53, 0x79, 0xf6 };
