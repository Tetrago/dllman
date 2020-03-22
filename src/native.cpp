#include "dllman/native.h"

#if defined(DLLMAN_WINDOWS)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

namespace dllman
{
	Library<Support::Native>::~Library()
	{
		unload();
	}

	bool Library<Support::Native>::load(const std::string& path)
	{
		unload();
		
#if defined(DLLMAN_WINDOWS)
		library_ = LoadLibrary(path.c_str());
#else
		library_ = dlopen(path.c_str(), RTLD_LAZY);
#endif
		return library_;
	}

	void Library<Support::Native>::unload()
	{
		if(!library_) return;

#if defined(DLLMAN_WINDOWS)
		FreeLibrary(static_cast<HMODULE>(library_));
#else
		dlclose(library_);
#endif
	}

	void* Library<Support::Native>::get(const std::string& name)
	{
		if(!library_) return nullptr;

#if defined(DLLMAN_WINDOWS)
		return GetProcAddress(static_cast<HMODULE>(library_), name.c_str());
#else
		return dlsym(library_, name.c_str());
#endif
	}
}
