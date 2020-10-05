#pragma once
#include <cstdio>

#define MAX_PATH  1000

class FileSearcher
{
public:
	/// <summary>
	/// 查找路径
	/// </summary>
	int findPath(const char* lpPath);

	int findPathSaveFile(const char* lp_path, const char* out_file_name);

private:
	char save_path[MAX_PATH] = { 0 };//结果输出路径;    
	char thePath[MAX_PATH] = { 0 };
	char result[MAX_PATH] = { 0 };
	FILE* pf_path_file;

	/// <summary>
	/// 字符串分割，这里主要用于文件名分割扩展
	/// </summary>
	void strTok(char* str);

	/// <summary>
	/// 分割扩展名
	/// </summary>
	void strExtension(char* str);
};

