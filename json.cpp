#include "json.h"

Json::Json(JObject* obj) :obj(obj) { ; }

Json::Json(const Json& j)
{
	throw std::exception("不允许复制");
}

Json::Json(Json&& j)
{
	throw std::exception("不允许复制");
}

Json::Json(Json& j)
{
	throw std::exception("不允许复制");
}

Json::~Json()
{
	delete obj;
}

JObject*& Json::GetValue()
{
	return obj;
}

JObject& Json::operator[](int index)
{
	return (*obj)[index];
}

JObject& Json::operator[](std::string name)
{
	return (*obj)[name];
}

std::vector<JObject*>& Json::GetArray()
{
	return obj->GetArray();
}

std::unordered_map<std::string, JObject*>& Json::GetMap()
{
	return obj->GetMap();
}

JObject* Json::Parse(std::string data)
{
	Lexer lexer(data);
	Parser parser(lexer);

	JObject* ret = parser.GetAST();

	return ret;
}

std::string Json::ToString()
{
	std::string str;

	JObjectToString(obj, str);

	return str;
}

void Json::JObjectToString(JObject* obj, std::string& str)
{
	switch (obj->GetType())
	{
	case JType::NUMBER:
		JNumberToString(obj, str);
		break;
	case JType::STRING:
		JStringToString(obj, str);
		break;
	case JType::ARRAY:
		JArrayToString(obj, str);
		break;
	case JType::MAP:
		JMapToString(obj, str);
		break;
	case JType::BOOL:
		JBoolToString(obj, str);
	default:
		break;
	}
}

void Json::JBoolToString(JObject* obj, std::string& str)
{
	if (((JBool*)obj)->GetValue())
	{
		str += "true";
	}
	else
	{
		str += "false";
	}
}

void Json::JNumberToString(JObject* obj, std::string& str)
{
	JNumber* num = (JNumber*)obj;
	switch (num->GetValueType())
	{
	case JNumberType::DOUBLE:
		str += std::to_string(num->GetValueD());
		break;
	case JNumberType::FLOAT:
		str += std::to_string(num->GetValueF());
		str += 'f';
		break;
	case JNumberType::INT:
		str += std::to_string(num->GetValueI());
		break;
	}
}

void Json::JStringToString(JObject* obj, std::string& str)
{
	str.push_back('"');

	str += ((JString*)obj)->GetValue();

	str.push_back('"');
}

void Json::JMapToString(JObject* obj, std::string& str)
{
	std::unordered_map<std::string, JObject*>& map = ((JMap*)obj)->GetValue();

	str.push_back('{');

	for (auto& it : map)
	{
		str.push_back('"');
		str += it.first;
		str.push_back('"');
		str += ':';
		JObjectToString(it.second, str);
		str += ',';
	}
	str.pop_back();

	str.push_back('}');
}

void Json::JArrayToString(JObject* obj, std::string& str)
{
	std::vector<JObject*>& vec = ((JArray*)obj)->GetValue();
	str.push_back('[');
	for (auto& it : vec)
	{
		JObjectToString(it, str);
		str += ',';
	}
	str.pop_back();
	str.push_back(']');
}
