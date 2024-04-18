#pragma once
#include <chrono>

namespace Cobra
{
	namespace Utils
	{
		using namespace std::chrono;

		class Timer
		{
			using hsClock = high_resolution_clock;
			using fs      = duration<float, std::milli>;

		public:
			Timer();

			/** 타이머 초기화 */
			void Reset();
			/** 초기화 된 시점부터 현재까지의 초 반환*/
			float ElapsedTime() const;
			/** 초기화 된 시점부터 현재까지의 milliseconds 반환*/
			float ElapsedMillisecond() const;

		private:
			/** 타이머 초기 시작 시간 */
			time_point<hsClock> mStartTime;
		};
	}
}
