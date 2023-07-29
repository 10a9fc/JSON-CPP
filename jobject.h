#ifndef JOBJECT_H
#define JOBJECT_H

#include<iostream>
#include<vector>
#include<exception>
#include<unordered_map>

enum class BaseType
{
	INT, FLOAT, DOUBLE, STRING, BOOL
};

template<typename T>
BaseType CheckType();

template<>
BaseType CheckType<int>();

template<>
BaseType CheckType<float>();

template<>
BaseType CheckType<double>();

template<>
BaseType CheckType<std::string>();

template<>
BaseType CheckType<bool>();

enum class JType
{
	NUMBER,
	STRING,
	ARRAY,
	MAP,
	BOOL,
};

enum class JNumberType
{
	DOUBLE, FLOAT, INT
};

class JObject
{
public:
	JType GetType();
	template<class T> T& Value();

	JObject& operator[](int index);
	JObject& operator[](std::string name);

	std::vector<JObject*>& GetArray();
	std::unordered_map<std::string, JObject*>& GetMap();

	virtual ~JObject();
protected:
	JType type;
};

class JNumber :public JObject
{
public:
	JNumber();
	JNumber(int num);
	JNumber(double num);
	JNumber(float num);
	~JNumber();

	JNumberType GetValueType();
	int& GetValueI();
	float& GetValueF();
	double& GetValueD();
private:
	union
	{
		int inum;
		float fnum;
		double dnum;
	}value;
	JNumberType numberType;
};

class JBool :public JObject
{
public:
	JBool(bool b);
	~JBool();

	bool& GetValue();
private:
	bool b;
};

class JString :public JObject
{
public:
	JString(std::string str);
	~JString();

	std::string& GetValue();
private:
	std::string str;
};

class JMap :public JObject
{
public:
	JMap();
	~JMap();

	std::unordered_map<std::string, JObject*>& GetValue();

private:
	std::unordered_map<std::string, JObject*> map;
};

class JArray :public JObject
{
public:
	JArray();
	~JArray();

	std::vector<JObject*>& GetValue();

private:
	std::vector<JObject*> array;
};

template<class T>
T& JObject::Value()
{
	switch (CheckType<T>())
	{
	case BaseType::INT:
		if (this->GetType() != JType::NUMBER)
		{
			throw std::exception("这不是个数字");
		}
		return (T&)((JNumber*)this)->GetValueI();
	case BaseType::FLOAT:
		if (this->GetType() != JType::NUMBER)
		{
			throw std::exception("这不是个数字");
		}
		return (T&)((JNumber*)this)->GetValueF();
	case BaseType::DOUBLE:
		if (this->GetType() != JType::NUMBER)
		{
			throw std::exception("这不是个数字");
		}
		return (T&)((JNumber*)this)->GetValueD();
	case BaseType::STRING:
		if (this->GetType() != JType::STRING)
		{
			throw std::exception("这不是个字符");
		}
		return (T&)((JString*)this)->GetValue();
	case BaseType::BOOL:
		if (((JBool*)this)->GetType() != JType::BOOL)
		{
			throw std::exception("这不是个布尔值");
		}
		return (T&)((JBool*)this)->GetValue();
	default:
		throw std::exception("不存在类型");
	}
}

#endif // !JOBJECT_H
