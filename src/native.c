#include "dllman/native.h"

#if defined(DLLMAN_WINDOWS)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

DmLibrary* dm_native_new()
{
	DmLibrary* lib = (DmLibrary*)malloc(sizeof(DmLibrary));
	lib->load = dm_native_load;
	lib->unload = dm_native_unload;
	lib->get = dm_native_get;
	lib->free = dm_native_free;
}

void dm_native_free(DmLibrary* self)
{
	self->unload(self);
	free(self);
}

int dm_native_load(DmLibrary* self, const char* path)
{
	self->unload(self);

#if defined(DLLMAN_WINDOWS)
	self->data_ = LoadLibrary(path);
#else
	self->data_ = dlopen(path, RTLD_LAZY);
#endif

	return self->data_ != NULL;
}

void dm_native_unload(DmLibrary* self)
{
	if(!self->data_) return;

#if defined(DLLMAN_WINDOWS)
	FreeLibrary((HMODULE)self->data_);
#else
	dlclose(self->data_);
#endif
}

void* dm_native_get(DmLibrary* self, const char* name)
{
	if(!self->data_) return NULL;

#if defined(DLLMAN_WINDOWS)
	return GetProcAddress((HMODULE)self->data_, name);
#else
	return dlsym(self->data_, name;
#endif
}