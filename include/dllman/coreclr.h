#pragma once

#include <string>

#include "native.h"

namespace dllman
{
	class CoreClrLibrary : public Library
	{
	public:
		~CoreClrLibrary() override;

		bool load(const LoadDesc& desc) override;
		void unload() override;
		void* get(const GetDesc& desc) override;
	private:
		/**
		 * @brief	Builds TRUSTED_PLATFORM_ASSEMBLIES list.
		 *
		 * @param	searchDir	Directory to search for dlls.
		 * @param	list		Reference to list.
		 */
		void buildTpaList(const std::filesystem::path& searchDir, std::string& list);

		/**
		 * @brief	Makes a path absolute if it is relative.
		 *
		 * @param	path	Path to check.
		 *
		 * @return	Absolute path, no change if already absolute.
		 */
		std::filesystem::path makeAbsolute(const std::filesystem::path& path);

		NativeLibrary lib_;
		void* handle_ = nullptr;
		unsigned domain_ = 0;
		std::string assemblyName_;

		void* initialize_ = nullptr;
		void* createDelegate_ = nullptr;
		void* shutdown_ = nullptr;
	};
}