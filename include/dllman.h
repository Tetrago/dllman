#pragma once

typedef struct DmLibrary
{
	void* lib_;
} DmLibrary;

/**
 * @brief   Creates a new DmLibrary.
 *
 * @returns Returns new DmLibrary.
 */
DmLibrary* dm_new();

/**
 * @brief   Frees DmLibrary and a loaded library (if it exists).
 *
 * @param   library Library to free.
 */
void dm_free(DmLibrary* library);

/**
 * @brief   Loads library with name.
 *
 * @param   library Library to load into.
 * @param   name    Name of library to load.
 */
void dm_load(DmLibrary* library, const char* name);

/**
 * @brief   Unloads loaded library if exists.
 *
 * @param   library Library to unload from.
 */
void dm_unload(DmLibrary* library);

/**
 * @brief   Gets from a library.
 *
 * @param   library Library.
 * @param   name    Name.
 *
 * @return  Address.
 */
void* dm_get(DmLibrary* library, const char* name);