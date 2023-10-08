#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"

namespace Batumo {
	class BATUMO_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

#define BT_CORE_TRACE(...)	::Batumo::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define BT_CORE_INFO(...)	::Batumo::Log::GetCoreLogger()->info(__VA_ARGS__)
#define BT_CORE_WARN(...)	::Batumo::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define BT_CORE_ERROR(...)	::Batumo::Log::GetCoreLogger()->error(__VA_ARGS__)
#define BT_CORE_FATAL(...)	::Batumo::Log::GetCoreLogger()->critical(__VA_ARGS__)


#define BT_INFO(...)		::Batumo::Log::GetClientLogger()->info(__VA_ARGS__)
#define BT_WARN(...)		::Batumo::Log::GetClientLogger()->warn(__VA_ARGS__)
#define BT_ERROR(...)		::Batumo::Log::GetClientLogger()->error(__VA_ARGS__)
#define BT_FATAL(...)		::Batumo::Log::GetClientLogger()->critical(__VA_ARGS__)
