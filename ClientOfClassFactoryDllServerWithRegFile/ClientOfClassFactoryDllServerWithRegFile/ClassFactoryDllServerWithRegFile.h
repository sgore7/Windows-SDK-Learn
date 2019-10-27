#pragma once

class ISum : public IUnknown {
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*) = 0;
};

class ISubtract : public IUnknown {
public:
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*) = 0;
};

// {15880579-1690-4993-ACD4-332EE731FBA1}
const CLSID CLSID_SumSubtract = { 0x15880579, 0x1690, 0x4993, 0xac, 0xd4, 0x33, 0x2e, 0xe7, 0x31, 0xfb, 0xa1 };

// {E1B9D520-4B6C-4CAC-BA9B-FD7CD404DAF2}
const IID IID_ISum = { 0xe1b9d520, 0x4b6c, 0x4cac, 0xba, 0x9b, 0xfd, 0x7c, 0xd4, 0x4, 0xda, 0xf2 };

// {2FA6B1FE-A75C-4C2B-B3D9-4D09847EE006}
const IID IID_ISubtract = { 0x2fa6b1fe, 0xa75c, 0x4c2b, 0xb3, 0xd9, 0x4d, 0x9, 0x84, 0x7e, 0xe0, 0x6 };
