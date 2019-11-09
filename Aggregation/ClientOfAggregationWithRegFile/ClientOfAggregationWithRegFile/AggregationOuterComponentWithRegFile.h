#pragma once
class ISum :public IUnknown {
public:
	virtual HRESULT __stdcall SumOfTwoIntegers(int, int, int*);
};

class ISubtract : public IUnknown {
public:
	virtual HRESULT __stdcall SubtractionOfTwoIntegers(int, int, int*);
};

// {331E6BD2-8BCE-4C0A-AD55-9D0B5E4A21EF}
const CLSID CLSID_ICSumSubtract = { 0x331e6bd2, 0x8bce, 0x4c0a, 0xad, 0x55, 0x9d, 0xb, 0x5e, 0x4a, 0x21, 0xef };

// {94DAC3B2-D697-405D-8EB4-59B95E1EABB9}
const IID IID_ISum = { 0x94dac3b2, 0xd697, 0x405d, 0x8e, 0xb4, 0x59, 0xb9, 0x5e, 0x1e, 0xab, 0xb9 };

// {C2EED3D4-57FD-4BC1-BFED-DE8E007F2DF5}
const IID IID_ISubtact = { 0xc2eed3d4, 0x57fd, 0x4bc1, 0xbf, 0xed, 0xde, 0x8e, 0x0, 0x7f, 0x2d, 0xf5 };
