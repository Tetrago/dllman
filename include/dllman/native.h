#pragma once

#include <string>

#include "dllman.h"

namespace dllman
{
	template<>
	class Library<Support::Native>
	{
	public:
		~Library();

		/**
		 * @brief	Load library by name. WILL unload existing library.
		 *
		 * @param	path	Path to library.
		 *
		 * @return	Success of load.
		 */
		bool load(const std::string& path);

		/**
		 * @brief	Unload library. Destructor WILL unload automatically.
		 */
		void unload();

		/**
		 * @brief	Get a pointer from library.
		 *
		 * @param	name	Name to get.
		 *
		 * @return	Pointer or nullptr if not found.
		 */
		void* get(const std::string& name);
	private:
		void* library_ = nullptr;
	};
}