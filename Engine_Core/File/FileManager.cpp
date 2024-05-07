#include "FileManager.h"


namespace Cobra
{
	bool FileManager::FileExists(const std::wstring& Path)
	{
		return GetFileSize(Path) > 0;
	}

	long FileManager::GetFileSize(const std::wstring& Path)
	{
		std::ifstream file(Path, std::ifstream::ate | std::ifstream::binary);

		const long size = file.tellg();

		file.close();

		return size;
	}

	bool FileManager::ReadFile(const std::wstring& Path, void* Buffer, long Length)
	{
		std::ifstream file(Path, std::ifstream::in | std::ifstream::binary);

		if (!file)
			return false;

		file.seekg(0, file.end);

		if (Length < 0)
		{
			Length = file.tellg();
		}

		file.seekg(0, file.beg);

		file.read(static_cast<char*>(Buffer), Length);

		file.close();

		return true;
	}

	unsigned char* FileManager::ReadFile(const std::wstring& Path)
	{
		const long fileSize = GetFileSize(Path);

		if (fileSize < 1)
		{
			CB_CORE_ERROR("Invalid file path or no file \nfunction :{} line: {}", __FUNCTION__, __LINE__);
			exit(0);
		}

		char* buffer = new char[fileSize];

		if (ReadFile(Path, buffer, fileSize))
		{
			return (unsigned char*)buffer;
		}

		delete[] buffer;

		return nullptr;
	}

	std::wstring FileManager::ReadTextFile(const std::wstring& Path)
	{
		std::wstring filepath;

		// if (!)

		return {};
	}

	bool FileManager::WriteFile(const std::wstring& Path, void* Buffer, bool bOverwrite)
	{
		if (!bOverwrite && FileExists(Path))
		{
			return false;
		}

		std::wofstream file(Path.c_str(), std::wifstream::binary);

		file << Buffer;
		// file.write(static_cast<wchar_t*>(Buffer), wcslen(static_cast<wchar_t*>(Buffer)));

		file.close();

		return true;
	}

	bool FileManager::WriteTextFile(const std::wstring& Path, const std::wstring& Text, bool bOverwrite)
	{
		return WriteFile(Path, (wchar_t*)&Text[0], bOverwrite);
	}
}
