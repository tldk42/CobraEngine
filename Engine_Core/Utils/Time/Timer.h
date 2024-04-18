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

			/** Ÿ�̸� �ʱ�ȭ */
			void Reset();
			/** �ʱ�ȭ �� �������� ��������� �� ��ȯ*/
			float ElapsedTime() const;
			/** �ʱ�ȭ �� �������� ��������� milliseconds ��ȯ*/
			float ElapsedMillisecond() const;

		private:
			/** Ÿ�̸� �ʱ� ���� �ð� */
			time_point<hsClock> mStartTime;
		};
	}
}
