/*
�ļ��������

 ֱ�ӱ���ϵͳ����WIN32_FIND_DATAA��ȫ���ݣ������ٲ���


*/
#pragma once
#include "base/strings/string16.h"
#include "../miniblink/wke.h"
#include <memory>


class FileAttribute : public jsData
{
public:
	FileAttribute();

	//js��ȡ��
	static bool js_setObjectProp(jsExecState es, jsValue object,
		const char* propertyName, jsValue value);

	static void js_releaseObject(jsData* data);

	static jsValue js_getObjectProp(jsExecState es,
		jsValue object, const char* propertyName);

	// C++�洢��
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

