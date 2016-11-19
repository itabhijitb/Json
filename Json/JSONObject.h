#ifndef __JSON__OBJECT__H
#define __JSON__OBJECT__H
/*******************************************************************************
*                                JSON Libraries                                *
*******************************************************************************/
#include "json.h"
#include "JSONValue.h"
namespace JSON {
	class Object : public Value
	{

		static const char starttoken = '{';
		static const char endtoken = '}';
		static const char septoken = ',';
		typedef  std::map < std::wstring, std::shared_ptr<Value> > VALUE_TYPE;
		typedef VALUE_TYPE::iterator iterator;
		typedef VALUE_TYPE::const_iterator const_iterator;

	public:
		friend class JSON;
		friend class Key;
	private:
		Object();
		Object(const std::initializer_list<std::pair<const std::wstring, std::shared_ptr<Value>> >& il);
	public:
		Object::Object(std::wstringstream& strm);
		void insert(const std::initializer_list<std::pair<const std::wstring, std::shared_ptr<Value>> >& il);
		void remove(const std::initializer_list<const std::wstring >& il);
		bool Object::operator == (const Value& json);
		Value& operator[](const std::wstring key);
		std::wstringstream& Object::print(std::wstringstream& ss, size_t depth);
	private:

		Object& operator=(const Object&) = delete;
	private:

		std::shared_ptr<VALUE_TYPE> m_value;
	};
}
#endif