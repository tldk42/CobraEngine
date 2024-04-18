#pragma once
#include <spdlog/spdlog.h>

namespace Cobra
{
	class Logger
	{
	public:
		static void Initialize();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger()
		{
			return s_CoreLogger;
		}

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
	};

#define CB_CORE_TRACE(...)	  Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define CB_CORE_INFO(...)     Logger::GetCoreLogger()->info(__VA_ARGS__)
#define CB_CORE_WARN(...)     Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define CB_CORE_ERROR(...)    Logger::GetCoreLogger()->error(__VA_ARGS__)
#define CB_CORE_FATAL(...)    Logger::GetCoreLogger()->critical(__VA_ARGS__)
}
