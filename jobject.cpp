#include "jobject.h"

template<typename T>
BaseType CheckType() { return -1; }

template<>
BaseType CheckType<int>() { return BaseType::INT; }

template<>
BaseType CheckType<float>() { return BaseType::FLOAT; }

template<>
BaseType CheckType<double>() { return BaseType::DOUBLE; }

template<>
BaseType CheckType<std::string>() { return BaseType::STRING; }

template<>
BaseType CheckType<bool>() { return BaseType::BOOL; }



JType JObject::GetType()
{
	return type;
}


JObject::~JObject()
{

}

JObject& JObject::operator[](int index)
{
	if (type != JType::ARRAY)
	{
		throw std::exception("这不是个数组");
	}

	return *((JArray*)this)->GetValue()[index];
}

JObject& JObject::operator[](std::string name)
{
	if (type != JType::MAP)
	{
		throw std::exception("这不是个数组");
	}

	return *((JMap*)this)->GetValue()[name];
}

std::vector<JObject*>& JObject::GetArray()
{
	if (type != JType::ARRAY)
	{
		throw std::exception("这不是个数组");
	}

	return ((JArray*)this)->GetValue();
}

std::unordered_map<std::string, JObject*>& JObject::GetMap()
{
	if (type != JType::MAP)
	{
		throw std::exception("这不是个数组");
	}

	return ((JMap*)this)->GetValue();
}



JNumber::JNumber()
{
	type = JType::NUMBER;
}

JNumber::JNumber(int num)
{
	type = JType::NUMBER;
	numberType = JNumberType::INT;
	GetValueI() = num;
}

JNumber::JNumber(double num)
{
	type = JType::NUMBER;
	numberType = JNumberType::DOUBLE;
	GetValueD() = num;
}

JNumber::JNumber(float num)
{
	type = JType::NUMBER;
	numberType = JNumberType::FLOAT;
	GetValueF() = num;
}

JNumber::~JNumber(){}

JNumberType JNumber::GetValueType()
{
	return numberType;
}

int& JNumber::GetValueI()
{
	return value.inum;
}

float& JNumber::GetValueF()
{
	return value.fnum;
}

double& JNumber::GetValueD()
{
	return value.dnum;
}



JString::JString(std::string str) :str(str)
{
	type = JType::STRING;
}

JString::~JString() {}

std::string& JString::GetValue()
{
	return str;
}



std::vector<JObject*>& JArray::GetValue()
{
	return array;
}

JArray::JArray()
{
	type = JType::ARRAY;
}

JArray::~JArray()
{
	for (auto it : array)
	{
		delete it;
	}
}



JMap::JMap()
{
	type = JType::MAP;
}

JMap::~JMap()
{
	for (auto it : map)
	{
		delete it.second;
	}
}

std::unordered_map<std::string, JObject*>& JMap::GetValue()
{
	return map;
}

JBool::JBool(bool b) :b(b)
{
	type = JType::BOOL;
}

JBool::~JBool()
{
}

bool& JBool::GetValue()
{
	return b;
}
