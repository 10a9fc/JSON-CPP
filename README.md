# JSON-CPP
## C++的json库

```cpp
#include<iostream>

int main()
{
  Json j = Json::Parse("[{"name":"10a",age=10},{"name"="10b",age=11.1f}]");
  std::cout<<j[0]["name"].Value<std::string>()<<std::endl; //输出:10a
  std::cout<<j[0]["age"].Value<int>()<<std::endl;          //输出:10
  std::cout<<j[1]["name"].Value<std::string>()<<std::endl; //输出:10b
  std::cout<<j[1]["age"].Value<int>()<<std::endl;          //输出:(float)11.1

  j[0]["age"].Value<int>()=12;                        //可更改
  j.GetArray();                                       //返回vector<JObject*>&
  j.GetArray().push_back(new JMap());
  j[2]["name"]=new JString("10c");
  j[2]["age"]=new JNumber(33.3);

  std::cout<<j.ToString()<<std::endl;                 //输出:[{"name":"10a",age=10},{"name"="10b",age=11.1f},{"name"="10c",age=33.3}]
}
```
