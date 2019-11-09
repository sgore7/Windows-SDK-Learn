#pragma once

class ISum : public IUnknown {
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;
};

class ISubtract :public IUnknown {
public:
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;
};

// {DAAE0472-6207-4E87-A9EE-84F4C80C4C54}
const CLSID CLSID_SumSubtract = { 0xdaae0472, 0x6207, 0x4e87, 0xa9, 0xee, 0x84, 0xf4, 0xc8, 0xc, 0x4c, 0x54 };

// {08B6A7C4-D56A-497D-9E7C-F2D5E1C927EB}
const IID IID_ISum = { 0x8b6a7c4, 0xd56a, 0x497d, 0x9e, 0x7c, 0xf2, 0xd5, 0xe1, 0xc9, 0x27, 0xeb };

// {1CC96057-21CD-4BCD-A95B-5EEA4BEF54BC}
const IID IID_ISubtarct = { 0x1cc96057, 0x21cd, 0x4bcd, 0xa9, 0x5b, 0x5e, 0xea, 0x4b, 0xef, 0x54, 0xbc };

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
