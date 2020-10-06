/*
文件相关属性

 直接保留系统定义WIN32_FIND_DATAA的全数据，不够再补充


*/
#pragma once
#include "base/strings/string16.h"
#include "../miniblink/wke.h"
#include <memory>


class FileAttribute : public jsData
{
public:
	FileAttribute();

	//js读取区
	static bool js_setObjectProp(jsExecState es, jsValue object,
		const char* propertyName, jsValue value);

	static void js_releaseObject(jsData* data);

	static jsValue js_getObjectProp(jsExecState es,
		jsValue object, const char* propertyName);

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

//using pUniqueFileAttribute = std::unique_ptr<FileAttribute>;
using pFileAttribute = FileAttribute* ;

