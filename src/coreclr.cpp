#include "dllman/coreclr.h"

#include <vector>
#include <fstream>
#include <iostream>
#include <regex>

#include "coreclrhost.h"

#if defined(DLLMAN_WINDOWS)

#define SEPARATOR ";"
#define CORECLR "coreclr.dll"

#else

#define SEPARATOR ":"

#if defined(DLLMAN_UNIX)
#define CORECLR "libcoreclr.so"
#else
#define CORECLR "libcoreclr.dylib"
#endif

#endif

namespace
{
	const std::string RUNTIME_LIST_FILE = "runtime_list";
}

namespace dllman
{
	std::filesystem::path locate_runtime_library_path(const std::string& preferredVersion)
	{
		// Copy command output into string.
		std::system(("dotnet --list-runtimes > " + RUNTIME_LIST_FILE).c_str());
		std::ifstream dump{ RUNTIME_LIST_FILE };

		std::string runtimesRaw{ (std::istreambuf_iterator<char>(dump)), std::istreambuf_iterator<char>() };

		dump.close();
		std::filesystem::remove(RUNTIME_LIST_FILE);

		// Regex match command output

		static std::regex regex{ R"(^Microsoft.NETCore.App ([\d\.]+) \[([\w:\\/\. ]+)\])" };

		// Command lists versions in ascending order therefore we only need to store the last data.

		std::filesystem::path path_{};

		std::smatch matches;
		while(std::regex_search(runtimesRaw, matches, regex))
		{
			path_ = matches.str(2);
			path_ /= matches.str(1);

			runtimesRaw = runtimesRaw.substr(matches.position() + matches.length());

			if(matches.str(1) == preferredVersion)
			{
				return path_;
			}
		}

		return path_;
	}

	CoreClrLibrary::~CoreClrLibrary()
	{
		unload();
	}

	bool CoreClrLibrary::load(const LoadDesc& desc)
	{
		auto libPath = makeAbsolute(desc.path_);
		if(!std::filesystem::exists(libPath)) return false;
		unload();

		// Determining whether runtimePath_ was specified and finding coreclr
		std::filesystem::path coreClrPath(desc.runtimeLibs_);
		if(coreClrPath.empty())
		{
			coreClrPath = desc.path_.parent_path();
		}

		coreClrPath = makeAbsolute(coreClrPath);
		coreClrPath.append(CORECLR);

		// Loading library
		lib_.load({ coreClrPath });

		initialize_ = reinterpret_cast<coreclr_initialize_ptr>(lib_.get({ "coreclr_initialize" }));
		createDelegate_ = reinterpret_cast<coreclr_create_delegate_ptr>(lib_.get({ "coreclr_create_delegate" }));
		shutdown_ = reinterpret_cast<coreclr_shutdown_ptr>(lib_.get({ "coreclr_shutdown" }));

		std::string tpaList;
		buildTpaList(coreClrPath.parent_path(), tpaList);

		if(!desc.runtimeLibs_.empty() && libPath.parent_path() != coreClrPath.parent_path())
		{
			tpaList.append(libPath.string()).append(SEPARATOR);
		}

		const char* propertyKeys[]{ "TRUSTED_PLATFORM_ASSEMBLIES" };
		const char* propertyValues[]{ tpaList.c_str() };
		assemblyName_ = desc.path_.stem().string();

		return reinterpret_cast<coreclr_initialize_ptr>(initialize_)(
			std::filesystem::current_path().u8string().c_str(),
			assemblyName_.c_str(),
			sizeof(propertyKeys) / sizeof(char*),
			propertyKeys,
			propertyValues,
			&handle_,
			&domain_) >= 0;
	}

	void CoreClrLibrary::unload()
	{
		if(!handle_) return;
		reinterpret_cast<coreclr_shutdown_ptr>(shutdown_)(handle_, domain_);
		handle_ = nullptr;
	}

	void* CoreClrLibrary::get(const GetDesc& desc)
	{
		if(!handle_) return nullptr;

		void* delegate;

		reinterpret_cast<coreclr_create_delegate_ptr>(createDelegate_)(
			handle_,
			domain_,
			assemblyName_.c_str(),
			desc.typeName_.c_str(),
			desc.name_.c_str(),
			&delegate);

		return delegate;
	}

	void CoreClrLibrary::buildTpaList(const std::filesystem::path& searchDir, std::string& list)
	{
		for(auto& f : std::filesystem::recursive_directory_iterator(searchDir))
		{
			if(f.path().extension() == ".dll")
			{
				list.append(f.path().string()).append(SEPARATOR);
			}
		}
	}

	std::filesystem::path CoreClrLibrary::makeAbsolute(const std::filesystem::path& path)
	{
		auto cp = std::filesystem::current_path();
		if(path.is_relative())
		{
			return cp / path;
		}

		return path;
	}
}