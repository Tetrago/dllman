#include "dllman/dllman.h"

#include "dllman/native.h"

DmLibrary* dm_new(DmMode mode)
{
	switch(mode)
	{
#if defined(DLLMAN_INCLUDE_NATIVE)
	case Native:
		return dm_native_new();
#endif
	}

	return NULL;
}