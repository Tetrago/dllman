#pragma once

#include <filesystem>
#include <string>
#include <memory>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#define DLLMAN_WINDOWS
#elif __APPLE__
#define DLLMAN_APPLE
#else
#define DLLMAN_UNIX
#endif

namespace dllman
{
	struct GetDesc
	{
		std::string name_;		// Method name.
		std::string typeName_;	// Type name (CoreClr only) which includes the namespace.
	};

	struct LoadDesc
	{
		std::filesystem::path path_;			// Library path.
		std::filesystem::path runtimeLibs_;		// Path to runtime libraries, if empty path_ will be used (CoreClrLibrary ONLY).
	};

	class Library
	{
	public:
		virtual ~Library() {}

		/**
		 * @brief	Load library by name. WILL unload existing library.
		 *
		 * @param	desc	Load description.
		 *
		 * @return	Success of load.
		 */
		virtual bool load(const LoadDesc& desc) = 0;

		/**
		 * @brief	Unload library.
		 */
		virtual void unload() = 0;

		/**
		 * @brief	Get a pointer.
		 *
		 * @param	desc	Description.
		 *
		 * @return	Pointer or nullptr if not found.
		 */
		virtual void* get(const GetDesc& desc) = 0;
	};
}