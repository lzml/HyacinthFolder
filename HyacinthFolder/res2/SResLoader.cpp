#include "SResLoader.h"
#include "../framework.h"
#include <base/memory/singleton.h>

#include "../../thirdpart/tinyxml2/tinyxml2.h"


SResStringLoader::SResStringLoader()
{
}

SResStringLoader::~SResStringLoader()
{
}

SResStringLoader* SResStringLoader::GetInstance()
{
	return base::Singleton<SResStringLoader,			
		base::StaticMemorySingletonTraits<SResStringLoader>>::get();
}

void SResStringLoader::initInstance()
{
	tinyxml2::XMLDocument xmlDoc;
	
	base::FilePath  path_current_dir;
	if (!base::PathProvider(base::BasePathKey::DIR_EXE, &path_current_dir))
	{
		return;
	}

	path_current_dir = path_current_dir.AppendASCII("resfile\\string.xml");

	tinyxml2::XMLError xmlError= xmlDoc.LoadFile(path_current_dir.MaybeAsASCII().c_str());
	if (xmlError != tinyxml2::XMLError::XML_SUCCESS)
	{
		return;
	} 

	tinyxml2::XMLElement* stringElements = xmlDoc.FirstChildElement("string");
	tinyxml2::XMLElement* node = nullptr;// 
	std::wstring tmp;
	for (node = stringElements->FirstChildElement();  node; node = node->NextSiblingElement())
	{
		tmp.clear();
		tmp = base::ASCIIToUTF16(node->GetText());
		resString_.push_back(tmp);
	}

}


std::wstring SResStringLoader::GetResStringW(int listNum)
{
	assert(listNum < resString_.size());

	return resString_.at(listNum);

}

std::string SResStringLoader::GetResStringA(int listNum)
{
	return base::UTF16ToASCII(GetResStringW(listNum));
}