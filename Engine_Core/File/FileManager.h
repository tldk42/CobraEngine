#pragma once
#include "../Common/CommonInclude.h"l

namespace Cobra
{
	class FileManager
	{
	public:
		FileManager() = delete;

		//=== Getter ===
		static bool FileExists(const std::wstring& Path);
		static long GetFileSize(const std::wstring& Path);
		//=== Getter ===


		//=== Read ===
		static bool           ReadFile(const std::wstring& Path, void* Buffer, long Length = -1);
		static unsigned char* ReadFile(const std::wstring& Path);
		static std::wstring   ReadTextFile(const std::wstring& Path);
		//=== Read ===


		//=== Write ===
		static bool WriteFile(const std::wstring& Path, void* Buffer, bool bOverwrite = true);
		static bool WriteTextFile(const std::wstring& Path, const std::wstring& Text, bool bOverwrite = true);
		//=== Write ===
	};
}
