#pragma once

#include <iostream>

#include "dllman.h"

namespace dllman
{
	class Ptr
	{
	public:
		explicit Ptr(void* ptr) : ptr_(ptr) {}

		template<typename T, typename = std::enable_if_t<std::is_function_v<T>>>
		operator T*() const
		{
			return static_cast<T*>(ptr_);
		}
	private:
		void* ptr_;
	};

	template<typename T, typename = std::enable_if<std::is_base_of<Library, T>::value>>
	class Container
	{
	public:
		Container(const LoadDesc& desc)
		{
			lib_.load(desc);
		}

		~Container()
		{
			lib_.unload();
		}

		Ptr operator[](const GetDesc& desc)
		{
			return Ptr(lib_.get(desc));
		}
	private:
		T lib_;
	};
}