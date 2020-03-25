#pragma once

#include "dllman.h"

namespace dllman
{
	class NativeLibrary : public Library
	{
	public:
		~NativeLibrary() override;

		bool load(const LoadDesc& desc) override;
		void unload() override;
		void* get(const GetDesc& desc) override;
	private:
		void* lib_ = nullptr;
	};
}