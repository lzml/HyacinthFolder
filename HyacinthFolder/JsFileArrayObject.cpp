#include "JsFileArrayObject.h"



JsFileArrayObject::JsFileArrayObject()
{
	jsData* data = this;
	memset(data, 0, sizeof(jsData));
	strcpy(data->typeName, "Object");
	data->propertyGet = js_getObjectProp;
	data->propertySet = js_setObjectProp;
	data->finalize = js_releaseObject;
}

 bool JsFileArrayObject::js_setObjectProp(jsExecState es, jsValue object, const char* propertyName, jsValue value)
{
	JsFileArrayObject* pthis = (JsFileArrayObject*)jsGetData(es, object);
	if (strcmp(propertyName, "value") == 0)
	{
		//pthis->m_value = jsToInt(es, value);
		
		return  true;
	}	
	else
		return false;
}

 void JsFileArrayObject::js_releaseObject(jsData* data)
{
	JsFileArrayObject* pthis = (JsFileArrayObject*)data;
	delete pthis;
}

 jsValue JsFileArrayObject::js_getObjectProp(jsExecState es, jsValue object, const char* propertyName)
{
	JsFileArrayObject* pthis = (JsFileArrayObject*)jsGetData(es, object);
	if (strcmp(propertyName, "value") == 0)
	{
		jsValue jsArray = jsEmptyArray(es);
		int i = 0;
		for (i; i<pthis->value_.size(); i++)
		{

			pFileAttribute attri = pthis->value_.at(i);

			jsSetAt(es, jsArray, i, jsObject(es, attri));
		}

		return  jsArray;
	}

	//else if (strcmp(propertyName, "msgbox") == 0) {
	//	return jsFunction(es, new BindTestMsgbox(pthis));
	//}
	else
		return jsUndefined();
}