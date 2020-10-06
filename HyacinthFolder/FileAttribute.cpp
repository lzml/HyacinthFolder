#include "FileAttribute.h"
#include "framework.h"


FileAttribute::FileAttribute()
{
	jsData* data = this;
	memset(data, 0, sizeof(jsData));
	strcpy(data->typeName, "Object");
	data->propertyGet = js_getObjectProp;
	data->propertySet = js_setObjectProp;
	data->finalize = js_releaseObject;
}

//js读取区
bool FileAttribute::js_setObjectProp(jsExecState es, jsValue object,
	const char* propertyName, jsValue value)
{
	return false;
}

void FileAttribute::js_releaseObject(jsData* data)
{
	//FileAttribute* pthis = (FileAttribute*)data;
	//delete pthis;
}

jsValue FileAttribute::js_getObjectProp(jsExecState es,
	jsValue object, const char* propertyName)
{
	FileAttribute* pthis = (FileAttribute*)jsGetData(es, object);
	if (strcmp(propertyName, "bReadOnly") == 0)
	{
		return jsBoolean(pthis->dwFileAttributes & FILE_ATTRIBUTE_READONLY);
	}
	else if (strcmp(propertyName, "bFolder") == 0)
	{
		return jsBoolean(pthis->dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY);
	}
	else if (strcmp(propertyName, "toString") == 0)
	{
		return jsStringW(es, L"你成为亿万富翁了！");
	}
	else if (strcmp(propertyName,"valueOf") == 0)
	{
		return jsStringW(es, L"隐式调用了valueOf！");
	}
	else if (strcmp(propertyName, "fileName") == 0)
	{
		return jsStringW(es, pthis->cFileName.c_str());
	}
	
	return jsUndefined();
}