# JSON-CPP
## C++的json库

```cpp
#include<iostream>
#include"json.h"
using namespace std;

int main()
{
	Json j = Json::Parse("[{\"name\":\"10a\",\"age\":10},{\"name\":\"10b\",\"age\":10.1}]");

	cout << j[0]["name"].Value<string>() << endl;			//10a
	cout << j[0]["age"].Value<int>() << endl;				//10			

	cout << j[1]["name"].Value<string>() << endl;			//10b
	cout << j[1]["age"].Value<double>() << endl;			//10.1

	j.GetArray();
	j.GetArray().push_back(new JMap());
	j[2].GetMap()["name"] = new JString("10c");
	j[2].GetMap()["age"] = new JNumber(12.2f);

	cout << j.ToString() << endl;							//[{"name":"10a","age":10},{"name":"10b","age":10.1},{"name":"10c","age":12.2f}]

	j[2]["age"].Value<float>() = 123.2;
	cout << j[2]["age"].Value<float>() << endl;				//float
}

```
