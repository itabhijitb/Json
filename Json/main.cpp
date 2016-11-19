#include "json.h"
#include <iostream>
int main()
{
	{
		std::stringstream json1("{\n\"abc\": 12,\n \t\"sub1\":{\n    \t\t\"a\": 20, \n   \t\t \"b\" : 25\n}, \n\"xyz\" : 25, \n\"ccc\" : [\"hello\", \"hello2\", \"hello3\"]\n}");
		std::stringstream json2("{\n\"abc\":12,\n \t\"sub1\":{\n    \t\t\"b\": 20, \n   \t\t \"a\" : 20\n}, \n\"xyz\" : 25, \n\"ccc\" : [\"hello\", \"hello2\", \"hello3\"]\n}");
		try
		{
			JSON jsonify1 = JSON(json1);
			JSON jsonify2 = JSON(json2);
			std::cout << (jsonify1 == jsonify2) << std::endl;

		}
		catch (JSONException& je)
		{
			std::cout << std::string(je) << std::endl;
		}
	}
	{
		JSON js = JSON({ { "abc", JSON(12.0) },
						 { "xyz", JSON(25.0) },
						 { "ccc", JSON({JSON("hello"),
									    JSON("hello2"), 
				 						JSON("hello3") }) },
						 { "sub1", JSON({ { "a", JSON(20) },
										  { "b", JSON(25) } }) }
		});
		std::cout << js << std::endl;
		js["ccc"][2] = JSON(32.0);
		js["ccc"].remove(4);
		std::cout << js << std::endl;
	}
	{
		JSON js = JSON({ { "abc", JSON(12.0) },
		                  { "xyz", JSON(25.0) },
						  { "ccc", JSON() },
						  { "sub1", JSON() } });
		js["ccc"] = JSON(JSON::EMPTY::ARRAY);
		js["ccc"].insert({ JSON("hello2"), JSON("hello3") });
		js["ccc"].insert({ JSON("hello") });
			
		js["sub1"] = JSON(JSON::EMPTY::OBJECT);
		js["sub1"].insert({ { "a", JSON(20) } });
		js["sub1"].insert({ { "b", JSON(25) } });
		
		std::cout << js << std::endl;
																								
	}
	{
		JSON objin = JSON( { { "a", JSON(20) } ,  { "b", JSON(25) } } );
		JSON arrin = JSON({ JSON("hello"), JSON("hello1"), JSON("hello2") });
		JSON obj = JSON(JSON::EMPTY::OBJECT);
		obj.insert({ { "abc", JSON(12.0) }, { "xyz", JSON(25.0) } });
		obj.insert({ { "ccc", std::move(objin) } });
		obj.insert({ { "sub1", std::move(arrin) } });
		std::cout << obj << std::endl;
	}
}