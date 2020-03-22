#pragma once

#include <memory>

#if defined(_MSC_VER)
#define DLLMAN_WINDOWS
#endif

namespace dllman
{
	enum class Support
	{
		Native
	};

	template<Support T>
	class Library {};
}