#pragma once

#include "windows.h"

struct IID
{
};

typedef const IID &REFIID;

class IUnknown
{
public:
	
	virtual ~IUnknown();
	HRESULT Release();
	
private:
	
	int64_t reference_count = 1;
};

typedef IUnknown *LPUNKNOWN;
