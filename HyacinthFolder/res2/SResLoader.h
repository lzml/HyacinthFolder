#pragma once
#include <vector>
#include <string>

class SResStringLoader;

#define  GETRESSTRINGW(x)   SResStringLoader::GetInstance()->GetResStringW(x)
#define  GETRESSTRINGA(x)   SResStringLoader::GetInstance()->GetResStringA(x)


class SResStringLoader
{
public:
	explicit SResStringLoader();
	~SResStringLoader();

	static  SResStringLoader* GetInstance();

	void initInstance();

	std::wstring GetResStringW(int listNum);
	std::string GetResStringA(int listNum);

private:
	std::vector<std::wstring> resString_;
};


