// resFileFactory.cpp : 定义应用程序的入口点。
//

#include "pch.h"
#include "framework.h"
#include "resFileFactory.h"
//#include "../../../thirdpart/tinyxml2/tinyxml2.h"




#define  MARKS_char_end     '\0'
#define  MARKS_char_quot    '\"'
#define  MARKS_char_space    ' '


void parseCmdLine(LPWSTR lpCmdLine, std::vector<std::wstring>* cmdlineArray)
{
	wprintf_s(lpCmdLine);
	wprintf_s(L"\r\n");

	std::wstring tmp;
	LPWSTR lpBegin = lpCmdLine;
	BOOL bInQuot = FALSE;
	while (*lpBegin != '\0')
	{
		//如果是引号，必须查找到下一个引号结束，中间部分全部添加到 第一个参数
		if (*lpBegin == MARKS_char_quot)
		{
			if (bInQuot)
			{
				bInQuot = FALSE;
				if (tmp.length() != 0)
				{
					cmdlineArray->push_back(tmp);
					wprintf_s(tmp.c_str());
					wprintf_s(L"\r\n");
					tmp.clear();
				}
			}
			else
			{
				bInQuot = TRUE;
			}
		}
		else
		{
			if (bInQuot)
			{
				tmp.push_back(*lpBegin);
			}
			else
			{
				//如果没有引号，那么到空格结束
				if (*lpBegin == MARKS_char_space)
				{
					if (tmp.length() != 0)
					{
						cmdlineArray->push_back(tmp);
						wprintf_s(tmp.c_str());
						wprintf_s(L"\r\n");
						tmp.clear();
					}
				}
				else
				{
					tmp.push_back(*lpBegin);
				}
			}


		}

		lpBegin++;
	}

	if (tmp.length() != 0)
	{
		cmdlineArray->push_back(tmp);
		wprintf_s(tmp.c_str());
		wprintf_s(L"\r\n");
		tmp.clear();
	}

}


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // 命令行参数
    //参数1：   需要解析文件的路径
    //参数2：   输出资源文件的目录



    std::vector<std::wstring> cmdlineArray;

    if (_tcslen(lpCmdLine) == 0)
    {
        wprintf_s(L"参数不能为空\r\n");
        return 0;
    }

	parseCmdLine(lpCmdLine, &cmdlineArray);

	if (cmdlineArray.size()<2)
	{
		wprintf_s(L"参数少于2个\r\n");
		return 0;
	}

	if ( !PathFileExists(cmdlineArray.at(0).c_str()))
	{
		wprintf_s(L"xml文件不存在\r\n");
		return 0;
	}

	tinyxml2::XMLDocument xmlDoc;
	tinyxml2::XMLError xmlerror = xmlDoc.LoadFile(ATL::CW2A(cmdlineArray.at(0).c_str(), CP_ACP));
	if (xmlerror != tinyxml2::XMLError::XML_SUCCESS)
	{
		wprintf_s(L"打开xml文件失败\r\n");
		return 0;
	}
	tinyxml2::XMLElement* stringElements =  xmlDoc.FirstChildElement("string");
	tinyxml2::XMLElement* node = nullptr;// 
	std::string tmpEleOut;
	for (node = stringElements->FirstChildElement();  node; node = node->NextSiblingElement())
	{
		tmpEleOut += node->Attribute("name");
		tmpEleOut += ",\r\n";
		printf(node->Attribute("name"));
		printf("\r\n");
	}

	std::string fileOutName = (LPCSTR)ATL::CW2A(cmdlineArray.at(1).c_str(), CP_ACP);
	fileOutName += "\\resString.h";
	std::ofstream ofs;
	ofs.open(  fileOutName, std::ios::out);
	ofs << "/**************************************************************/\r"
		<< "//本文件由resFileFactory.exe自动生成，请不要手动修改\r\n"
		<< "enum ResString{\r"
		<< tmpEleOut
		<< "};";
	ofs.close();

	
	wprintf_s(L"resString.h create OK!!!\r\n");
	wprintf_s(L"********************************\r\n");
    return 0;
}

