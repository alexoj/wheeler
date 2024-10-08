
#pragma once
#define IMGUI_DEFINE_MATH_OPERATORS

#pragma warning(push)
#include <RE/Skyrim.h>
#include <REL/Relocation.h>
#include <SKSE/SKSE.h>

#pragma warning(disable: 4702)
#include <SimpleIni.h>

#ifdef NDEBUG
#	include <spdlog/sinks/basic_file_sink.h>
#else
#	include <spdlog/sinks/msvc_sink.h>
#endif
#pragma warning(pop)

using namespace std::literals;

namespace logger = SKSE::log;

namespace util
{
	using SKSE::stl::report_and_fail;
}

namespace std
{
	template <class T>
	struct hash<RE::BSPointerHandle<T>>
	{
		uint32_t operator()(const RE::BSPointerHandle<T>& a_handle) const
		{
			uint32_t nativeHandle = const_cast<RE::BSPointerHandle<T>*>(&a_handle)->native_handle();  // ugh
			return nativeHandle;
		}
	};
}

#define DLLEXPORT __declspec(dllexport)

#define RELOCATION_OFFSET(SE, AE) REL::VariantOffset(SE, AE, 0).offset()

#include "Plugin.h"
#include <d3d11.h>
#include <dxgi.h>
#include "imgui.h"
#define IM_PI 3.14159265358979323846f

struct DrawArgs
{
	double alphaMult = 1.0f;
	float scaleMult = 1.0f;
	float rotationOffset = 0.0f;
	ImVec2 translationOffset = ImVec2(0.0f, 0.0f);
	bool centerObject = true;
};

#define INFO(...) logger::info(__VA_ARGS__)
#define ERROR(...) logger::critical(__VA_ARGS__)
#define DEBUG(...) logger::debug(__VA_ARGS__)
#define ASSERT(CONDITION)                                     \
	if (CONDITION) {                                          \
	} else {                                                  \
		logger::critical("assertion {} failed.", #CONDITION); \
	}

// Remove clashing Windows #defines
#undef GetObject
#undef PlaySound
