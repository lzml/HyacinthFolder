/*
�ļ��������

 ֱ�ӱ���ϵͳ����WIN32_FIND_DATAA��ȫ���ݣ������ٲ���


*/
#pragma once
#include "base/strings/string16.h"



//WIN32_FIND_DATAA wfd; //���ݽṹ;


class FileAttribute
{
public:

	//js��ȡ��


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

