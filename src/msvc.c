#include "dllman.h"

#include <Windows.h>

void dm_load(DmLibrary* library, const char* name)
{
	library->lib_ = (void*)LoadLibrary(name);
}

void dm_unload(DmLibrary* library)
{
	if(library->lib_)
	{
		FreeLibrary((HINSTANCE)library->lib_);
	}
}

void* dm_get(DmLibrary* library, const char* name)
{
	if(library->lib_)
	{
		return GetProcAddress(library->lib_, name);
	}
	else
	{
		return NULL;
	}
}

DmLibrary* dm_new()
{
	return (DmLibrary*)malloc(sizeof(DmLibrary));
}

void dm_free(DmLibrary* library)
{
	if(library->lib_)
	{
		dm_unload(library);
	}

	free(library);
}