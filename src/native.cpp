#include "dllman/native.h"

#if defined(DLLMAN_WINDOWS)
#include <Windows.h>
#else
#include <dlfcn.h>
#endif

namespace dllman
{
	NativeLibrary::~NativeLibrary()
	{
		unload();
	}

	bool NativeLibrary::load(const LoadDesc& desc)
	{
		unload();

#if defined(DLLMAN_WINDOWS)
		lib_ = LoadLibrary(desc.path_.u8string().c_str());
#else
		lib_ = dlopen(desc.path_.u8string().c_str(), RTLD_LAZY);
#endif

		return lib_;
	}

	void NativeLibrary::unload()
	{
		if(!lib_) return;

#if defined(DLLMAN_WINDOWS)
		FreeLibrary(static_cast<HMODULE>(lib_));
#else
		dlclose(lib_);
#endif
	}

	void* NativeLibrary::get(const GetDesc& desc)
	{
		if(!lib_) return nullptr;

#if defined(DLLMAN_WINDOWS)
		return GetProcAddress(static_cast<HMODULE>(lib_), desc.name_.c_str());
#else
		return dlsym(lib_, desc.methodName_.c_str());
#endif
	}
}