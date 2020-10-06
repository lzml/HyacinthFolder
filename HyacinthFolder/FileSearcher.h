#pragma once

#include "framework.h"
#include "FileAttribute.h"

#define MAX_PATH  1000

class FileSearcher
{
public:
	virtual	~FileSearcher() {}
	/// <summary>
	/// ����·��
	/// </summary>
	int findPath(_In_ const wchar_t* lpPath, _Out_ std::vector<pFileAttribute>& outFiles);



private:
	wchar_t result[MAX_PATH];

	/// <summary>
	/// ʱ��ת��
	/// </summary>
	__int64 to_int64(FILETIME ft);
};

