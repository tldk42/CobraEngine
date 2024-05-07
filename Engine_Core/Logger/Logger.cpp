#include "Logger.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace Cobra
{
	std::shared_ptr<spdlog::logger> Logger::s_CoreLogger;

	void Logger::Initialize()
	{
		spdlog::set_pattern("%^[%T] %n: %v%$");

		s_CoreLogger = spdlog::stdout_color_mt("Cobra Core");
		s_CoreLogger->set_level(spdlog::level::trace);
	}
}
