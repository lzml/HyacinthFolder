#pragma once
#include <cstdio>

#define MAX_PATH  1000

class FileSearcher
{
public:
	/// <summary>
	/// ����·��
	/// </summary>
	int findPath(const char* lpPath);

	int findPathSaveFile(const char* lp_path, const char* out_file_name);

private:
	char save_path[MAX_PATH] = { 0 };//������·��;    
	char thePath[MAX_PATH] = { 0 };
	char result[MAX_PATH] = { 0 };
	FILE* pf_path_file;

	/// <summary>
	/// �ַ����ָ������Ҫ�����ļ����ָ���չ
	/// </summary>
	void strTok(char* str);

	/// <summary>
	/// �ָ���չ��
	/// </summary>
	void strExtension(char* str);
};

