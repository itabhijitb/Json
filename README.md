# Json
A C++ JSON Library

##What is JSON?##
JSON (JavaScript Object Notation) is a lightweight open-standard that uses human readable cleartext to transmit data. It is one of the few format that is both human and machine readable. It is based on a subset of the JavaScript Programming Language, Standard ECMA-262 3rd Edition - December 1999. JSON gained its popularity where other competiting standards lost (less verbose, less overhead in parsing and generation, easy to read).
Today JSON is the primary choice for

1. AJAX, largely replacing XML for asyncronous communiction
2. NOSQL, where the Key-Value attributes pair can easily make the data scalable across both dimension
3. For Data Serialization

## Why another JSON Library?
The current implementation uses templates and recursive pattern and polymorphism to create an hierarchial structure that has the minimal footprint with high performance. Moreover, the entire structure is iterable enabling easy integration with the existing C++ Design patterns. The JSON generator can be created statically or dynamically. JSON Objects and Arrays can be subscripted, the syntax of which is not alien to a C++ Developer. Moreover, the implementation is C++11 compliant making it more secure (no explicite memory management, no buffer overrun, no type mismatch). The Code has been remediated for any code issues by distilling through Static Analyzer guranteeing that the code would not add any warnings in your existing project.

## Design Pattern


Intuitive syntax. JSON and JSON elements gives a feeling of first class data. Using Dynamic Polymorphism and making each element a friend of others, it gives an intuitive recursive pattern.

Trivial integration. The entire codebase is contained in a single module JSON under the namespace JSON. We have refrained from monolithic design as we want the code to be readable and maintainable. 

Contextual Error Handling. In case the Parser fails to parse the JSON Stream, it would spit out the location where an invalid token was found with a best guess on the missing token.

## Examples

### Parsing JSON

JSON accepts the JSON as a stream. It parses and creates a recursive polymorphic structure. 
```CPP
std::wstringstream json1(L"{\n\"abc\": 12,\n \t\"sub1\":{\n    \t\t\"a\": 20, \n   \t\t \"b\" : 25\n}, \n\"xyz\" : 25, \n\"ccc\" : [\"hello\", \"hello2\", \"hello3\"]\n}");
		std::wstringstream json2(L"{\n\"abc\":12,\n \t\"sub1\":{\n    \t\t\"b\": 20, \n   \t\t \"a\" : 20\n}, \n\"xyz\" : 25, \n\"ccc\" : [\"hello\", \"hello2\", \"hello3\"]\n}");
		try
		{
			JSON::JSON jsonify1 = JSON::JSON(json1);
			std::wcout << jsonify1 << std::endl;
			JSON::JSON jsonify2 = JSON::JSON(json2);
			std::wcout << jsonify1 << std::endl;
			std::cout << (jsonify1 == jsonify2) << std::endl;

		}
		catch (JSON::Exception& je)
		{
			std::wcout << std::wstring(je) << std::endl;
		}
```
