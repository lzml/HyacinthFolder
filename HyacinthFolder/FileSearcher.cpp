#include "FileSearcher.h"

int FileSearcher::findPath(_In_ const wchar_t* lpPath, _Out_ std::vector<pFileAttribute>& outFiles)
{
	HANDLE hFile;
	WIN32_FIND_DATAW wfd;
	int counter = 0;

	wchar_t szPath[MAX_PATH] = { 0 };

	wcscpy_s(szPath, lpPath);
	wcscat_s(szPath, L"\\*.*");

	hFile = FindFirstFile(szPath, &wfd);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		do {
			pFileAttribute fileItem = new FileAttribute;
			fileItem->cFileName = wfd.cFileName;
			fileItem->cAlternateFileName = wfd.cAlternateFileName;
			fileItem->dwFileAttributes = wfd.dwFileAttributes;
			fileItem->ftCreationTime = to_int64(wfd.ftCreationTime);
			fileItem->ftLastAccessTime = to_int64(wfd.ftLastAccessTime);
			fileItem->ftLastWriteTime = to_int64(wfd.ftLastWriteTime);
			fileItem->nFileSizeHigh = wfd.nFileSizeHigh;
			fileItem->nFileSizeLow = wfd.nFileSizeLow;

			outFiles.push_back(fileItem);
			++counter;
		} while (FindNextFile(hFile, &wfd));
	}
	return counter;
}



__int64 FileSearcher::to_int64(FILETIME ft)
{
	return static_cast<__int64>(ft.dwHighDateTime) << 32 | ft.dwLowDateTime;
}
