#include "Timer.h"

namespace Cobra
{
	Utils::Timer::Timer()
	{
		Reset();
	}

	void Utils::Timer::Reset()
	{
		// high resolution clock�� �⺻ ������ nano seconds
		mStartTime = hsClock::now();
	}

	float Utils::Timer::ElapsedTime() const
	{
		// 1 milli seconds = 0.001 seconds
		return ElapsedMillisecond() / 1000.f;
	}

	float Utils::Timer::ElapsedMillisecond() const
	{
		// ���� �� ������ ��ȯ�ϴ°� �ƴϸ� duration_cast�� std::milli�� ĳ��Ʈ �ʿ�
		return duration_cast<fs>(hsClock::now() - mStartTime).count();
	}
}
