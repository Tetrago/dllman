#include "dllman.h"

#include <stdlib.h>
#include <dlfcn.h>

void dm_load(DmLibrary* library, const char* name)
{
	library->lib_ = dlopen(name, RTLD_LAZY);
}

void dm_unload(DmLibrary* library)
{
	if(library->lib_)
	{
		dlclose(library->lib_);
	}
}

void* dm_get(DmLibrary* library, const char* name)
{
	if(library->lib_)
	{
		return dlsym(library->lib_, name);
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
