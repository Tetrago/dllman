#pragma once

#include <stdlib.h>

#if defined(_MSC_VER)
#define DLLMAN_WINDOWS
#endif

typedef enum DmMode
{
	Native
} DmMode;

typedef struct DmLibrary
{
	/**
	 * @brief	Load library by name. WILL unload existing library.
	 *
	 * @param	path	Path to library.
	 *
	 * @return	Success of load.
	 */
	int(*load)(struct DmLibrary*, const char*);

	/**
	 * @brief	Unload library.
	 */
	void(*unload)(struct DmLibrary*);

	/**
	 * @brief	Get a pointer from library.
	 *
	 * @param	name	Name to get.
	 *
	 * @return	Pointer or nullptr if not found.
	 */
	void*(*get)(struct DmLibrary*, const char*);

	/**
	 * @brief WILL unload loaded library.
	 */
	void(*free)(struct DmLibrary*);

	void* data_;
} DmLibrary;

DmLibrary* dm_new(DmMode mode);