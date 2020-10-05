#include "FileSearcher.h"
#include "framework.h"
#include <base/at_exit.h>
#include <base/threading/thread.h>
#include "res2/resString.h"

int FileSearcher::findPath(const char* lpPath)
{
	static int cnt = 0;
	HANDLE hFile;
	WIN32_FIND_DATAA wfd;

	char szPath[MAX_PATH] = { 0 };
	char buf[MAX_PATH * 2] = { 0 };
	char fileName[MAX_PATH] = { 0 };
	char temp[MAX_PATH] = { 0 };//临时数组;
	char parseFileName[MAX_PATH] = { 0 };

	strcpy_s(szPath, lpPath);
	strcat_s(szPath, "\\*.*");

	hFile = FindFirstFileA(szPath, &wfd);
	if (hFile != INVALID_HANDLE_VALUE)
	{
		do {
			if (wfd.cFileName[0] == '.')
				continue;
			else if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				strcpy_s(szPath, lpPath);
				strcat_s(szPath, "\\");
				strcat_s(szPath, wfd.cFileName);

				findPath(szPath);
			}
			else
			{
				strcpy_s(parseFileName, wfd.cFileName);
				strExtension(parseFileName);

				strcpy_s(fileName, lpPath);//合成文件名全路径
				strcat_s(fileName, "\\");
				strcat_s(fileName, wfd.cFileName);/* 例："c:\dir\test\1.pgm" */

				strcpy_s(temp, lpPath);
				strTok(temp); //获取目录

				/*sprintf_s(buf, "%s;%s", fileName, result);
				fprintf_s(pf_path_file, "%s\n", buf);*/
				++cnt;
			}
		} while (FindNextFileA(hFile, &wfd));
	}
	return cnt;
}

int FileSearcher::findPathSaveFile(const char* lp_path, const char* out_file_name)
{
	fopen_s(&pf_path_file, out_file_name, "w");
	int cnt = findPath(lp_path);
	fclose(pf_path_file);
	return cnt;
}

void FileSearcher::strTok(char* str)
{
	char* p = NULL;
	char* ptr = NULL;
	char delims[] = "\\";
	p = strtok_s(str, delims, &ptr);
	while (p != NULL)
	{
		strcpy_s(result, p);
		p = strtok_s(NULL, delims, &ptr);
	};
}

void FileSearcher::strExtension(char* str)
{
	char* p = NULL;
	char* ptr = NULL;
	char delims[] = ".";
	p = strtok_s(str, delims, &ptr);
	while (p != NULL)
	{
		strcpy_s(result, p);
		p = strtok_s(NULL, delims, &ptr);
	}
}
