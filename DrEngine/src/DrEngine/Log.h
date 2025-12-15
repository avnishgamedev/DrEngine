#pragma once

#include <memory>

#include "Core.h"

#define FMT_UNICODE 0
#include "spdlog/spdlog.h"

namespace DrEngine {

	class DRENGINE_API Log
	{
	public:

		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger;  };
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger;  };

	private:

		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;

	};

// Core Log Macros
#define DE_CORE_ERROR(...)	::DrEngine::Log::GetCoreLogger()->error(__VA_ARGS__)
#define DE_CORE_WARN(...)	::DrEngine::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define DE_CORE_INFO(...)	::DrEngine::Log::GetCoreLogger()->info(__VA_ARGS__)
#define DE_CORE_TRACE(...)	::DrEngine::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define DE_CORE_FATAL(...)	::DrEngine::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client Log Macros
#define DE_ERROR(...)		::DrEngine::Log::GetClientLogger()->error(__VA_ARGS__)
#define DE_WARN(...)		::DrEngine::Log::GetClientLogger()->warn(__VA_ARGS__)
#define DE_INFO(...)		::DrEngine::Log::GetClientLogger()->info(__VA_ARGS__)
#define DE_TRACE(...)		::DrEngine::Log::GetClientLogger()->trace(__VA_ARGS__)
#define DE_FATAL(...)		::DrEngine::Log::GetClientLogger()->fatal(__VA_ARGS__)

}

