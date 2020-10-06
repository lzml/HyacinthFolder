#pragma once
#include "../miniblink/wke.h"
#include "FileAttribute.h"
#include <vector>


class JsFileArrayObject :public jsData
{
public:
	JsFileArrayObject();


	//  js
	static bool js_setObjectProp(jsExecState es, jsValue object,
		const char* propertyName, jsValue value);

	static void js_releaseObject(jsData* data);

	static jsValue js_getObjectProp(jsExecState es,
		jsValue object, const char* propertyName);


	//c++
	std::vector<pFileAttribute>  value_;
};

