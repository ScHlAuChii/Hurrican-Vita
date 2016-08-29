#pragma once

#include "windows.h"

struct IID
{
};

typedef const IID &REFIID;

class IUnknown
{
public:
	
	virtual HRESULT Release() = 0;
};

typedef IUnknown *LPUNKNOWN;
