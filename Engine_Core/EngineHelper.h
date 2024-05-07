#pragma once
#include "Common/CommonInclude.h"

namespace Cobra
{
	class EngineHelper
	{
	public:
		EngineHelper()  = delete;
		~EngineHelper() = delete;

	public:
		static void ShowMessageBox(HWND WindowHandle, LPCWSTR Text, LPCWSTR Title);
		static void ShowErrorMessageBox(HWND WindowHandle, bool bQuit);
	};
}
