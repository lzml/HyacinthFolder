/*
文件相关属性

 直接保留系统定义WIN32_FIND_DATAA的全数据，不够再补充


*/
#pragma once
#include "base/strings/string16.h"



//WIN32_FIND_DATAA wfd; //数据结构;


class FileAttribute
{
public:

	//js读取区


	// C++存储区
	unsigned long  dwFileAttributes;
	__int64 ftCreationTime;
	__int64 ftLastAccessTime;
	__int64 ftLastWriteTime;
	unsigned long  nFileSizeHigh;
	unsigned long  nFileSizeLow;
	//DWORD dwReserved0;
	//DWORD dwReserved1;
	std::wstring  cFileName;
	std::wstring  cAlternateFileName;
};

