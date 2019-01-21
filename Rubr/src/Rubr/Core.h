#pragma once

#ifdef RUBR_PLATFORM_WINDOWS
	#ifdef RUBR_BUILD_DLL
		#define RUBR_API __declspec(dllexport)
	#else 
		#define RUBR_API __declspec(dllimport)
	#endif
#else
	#error Rubr only supports Windows!
#endif

#ifdef RUBR_ENABLE_ASSERTS
	#define RUBR_ASSERT(x, ...) {if(!(x)) { RUBR_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
	#define RUBR_CORE_ASSERT(x, ...) {if(!(x)) { RUBR_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
	#define RUBR_ASSERT(x, ...)
	#define RUBR_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define RUBR_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)