#include "json.h"
#include <iostream>
int main()
{
	{
		std::wstringstream json1(L"{\n\"abc\": 12,\n \t\"sub1\":{\n    \t\t\"a\": 20, \n   \t\t \"b\" : 25\n}, \n\"xyz\" : 25, \n\"ccc\" : [\"hello\", \"hello2\", \"hello3\"]\n}");
		std::wstringstream json2(L"{\n\"abc\":12,\n \t\"sub1\":{\n    \t\t\"b\": 20, \n   \t\t \"a\" : 20\n}, \n\"xyz\" : 25, \n\"ccc\" : [\"hello\", \"hello2\", \"hello3\"]\n}");
		try
		{
			JSON::JSON jsonify1 = JSON::JSON(json1);
			JSON::JSON jsonify2 = JSON::JSON(json2);
			std::cout << (jsonify1 == jsonify2) << std::endl;

		}
		catch (JSON::Exception& je)
		{
			std::wcout << std::wstring(je) << std::endl;
		}
	}
	{
		JSON::JSON js = JSON::JSON({ { L"abc", JSON::JSON(12.0) },
						 { L"xyz", JSON::JSON(25.0) },
						 { L"ccc", JSON::JSON({ JSON::JSON(L"hello"),
							 JSON::JSON(L"hello2"),
							 JSON::JSON(L"hello3") }) },
						 { L"sub1", JSON::JSON({ { L"a", JSON::JSON(20) },
										  { L"b", JSON::JSON(25) } }) }
		});
		std::wcout << js << std::endl;
		js[L"ccc"][2] = JSON::JSON(32.0);
		js[L"ccc"].remove(4);
		std::wcout << js << std::endl;
	}
	{
		JSON::JSON js = JSON::JSON({ { L"abc", JSON::JSON(12.0) },
						  { L"xyz", JSON::JSON(25.0) },
						  { L"ccc", JSON::JSON() },
						  { L"sub1", JSON::JSON() } });
		js[L"ccc"] = JSON::JSON(JSON::JSON::EMPTY::ARRAY);
		js[L"ccc"].insert({ JSON::JSON(L"hello2"), JSON::JSON(L"hello3") });
		js[L"ccc"].insert({ JSON::JSON(L"hello") });

		js[L"sub1"] = JSON::JSON(JSON::JSON::EMPTY::OBJECT);
		js[L"sub1"].insert({ { L"a", JSON::JSON(20) } });
		js[L"sub1"].insert({ { L"b", JSON::JSON(25) } });

		std::wcout << js << std::endl;

	}
	{
		JSON::JSON objin = JSON::JSON({ { L"a", JSON::JSON(20) } ,  { L"b", JSON::JSON(25) } });
		JSON::JSON arrin = JSON::JSON({ JSON::JSON(L"hello"), JSON::JSON(L"hello1"), JSON::JSON(L"hello2") });
		JSON::JSON obj = JSON::JSON(JSON::JSON::EMPTY::OBJECT);
		obj.insert({ { L"abc", JSON::JSON(12.0) }, { L"xyz", JSON::JSON(25.0) } });
		obj.insert({ { L"ccc", std::move(objin) } });
		obj.insert({ { L"sub1", std::move(arrin) } });
		std::wcout << obj << std::endl;
	}
}