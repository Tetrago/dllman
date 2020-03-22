#pragma once

#include "dllman.h"

DmLibrary* dm_native_new();
void dm_native_free(DmLibrary* self);
int dm_native_load(DmLibrary* self, const char* path);
void dm_native_unload(DmLibrary* self);
void* dm_native_get(DmLibrary* self, const char* name);