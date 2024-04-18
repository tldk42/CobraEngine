#include "Timer.h"

namespace Cobra
{
	Utils::Timer::Timer()
	{
		Reset();
	}

	void Utils::Timer::Reset()
	{
		// high resolution clock의 기본 단위는 nano seconds
		mStartTime = hsClock::now();
	}

	float Utils::Timer::ElapsedTime() const
	{
		// 1 milli seconds = 0.001 seconds
		return ElapsedMillisecond() / 1000.f;
	}

	float Utils::Timer::ElapsedMillisecond() const
	{
		// 나노 초 단위를 반환하는게 아니면 duration_cast로 std::milli로 캐스트 필요
		return duration_cast<fs>(hsClock::now() - mStartTime).count();
	}
}
