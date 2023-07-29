#ifndef JSON_H
#define JSON_H

#include"parse.h"

class Json
{
public:
	Json(JObject* obj);
	Json(const Json& j);
	Json(Json&& j);
	Json(Json& j);
	~Json();

	JObject*& GetValue();

	JObject& operator[](int index);
	JObject& operator[](std::string name);

	std::vector<JObject*>& GetArray();
	std::unordered_map<std::string, JObject*>& GetMap();

	static JObject* Parse(std::string data);
	std::string ToString();
private:
	void JObjectToString(JObject* obj, std::string& str);
	void JNumberToString(JObject* obj, std::string& str);
	void JBoolToString(JObject* obj, std::string& str);
	void JStringToString(JObject* obj, std::string& str);
	void JMapToString(JObject* obj, std::string& str);
	void JArrayToString(JObject* obj, std::string& str);

	JObject* obj;
};

#endif // !JSON_H
