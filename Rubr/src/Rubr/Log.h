#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Rubr {

	class RUBR_API Log {
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger;  }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define RUBR_CORE_TRACE(...)	::Rubr::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define RUBR_CORE_ERROR(...)	::Rubr::Log::GetCoreLogger()->error(__VA_ARGS__)
#define RUBR_CORE_INFO(...)		::Rubr::Log::GetCoreLogger()->info(__VA_ARGS__)
#define RUBR_CORE_WARN(...)		::Rubr::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define RUBR_CORE_FATAL(...)	::Rubr::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define RUBR_TRACE(...)			::Rubr::Log::GetClientLogger()->trace(__VA_ARGS__)
#define RUBR_ERROR(...)			::Rubr::Log::GetClientLogger()->error(__VA_ARGS__)
#define RUBR_INFO(...)			::Rubr::Log::GetClientLogger()->info(__VA_ARGS__)
#define RUBR_WARN(...)			::Rubr::Log::GetClientLogger()->warn(__VA_ARGS__)
#define RUBR_FATAL(...)			::Rubr::Log::GetClientLogger()->fatal(__VA_ARGS__)