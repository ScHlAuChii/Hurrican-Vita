#include "com.h"

#include <assert.h>

IUnknown::~IUnknown()
{
}

HRESULT IUnknown::Release()
{
	assert(reference_count > 0);
	
	--reference_count;
	if (reference_count == 0)
	{
		delete this;
	}
	
	return 0;
}
