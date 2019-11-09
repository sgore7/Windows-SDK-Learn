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
