#include "JSONArray.h"
JSON::Array::Array()
{
	value_type = Value::VALUE_TYPE::ARRAY;
	m_value = std::unique_ptr<VALUE_TYPE>(new VALUE_TYPE());
}
JSON::Array::Array(std::wstringstream& strm)
{
	value_type = Value::VALUE_TYPE::ARRAY;
	m_value = std::unique_ptr<VALUE_TYPE>(new VALUE_TYPE());
	strm >> std::ws;
	decltype(strm.peek()) ch{};
	strm >> ch;
	if (ch != starttoken)
	{
		throw PgmErr(L"JSON Stream at %d is %c, %c expected.", strm.tellg(), ch, endtoken);
	}

	while ((ch = strm.peek()) != endtoken)
	{
		strm >> std::ws;
		m_value->push_back(JSON::Parse(strm));
		strm >> std::ws;
		strm >> ch;
		if (ch != septoken && ch != endtoken)
		{
			throw Invalid(L"Parse error at %d. Expecting %c but found  %c", strm.tellg(), endtoken, ch);
		}
		strm >> std::ws;
		if (ch == endtoken) break;

	}
}
JSON::Array::Array(const std::initializer_list< std::shared_ptr<Value>>& il)
{
	value_type = Value::VALUE_TYPE::ARRAY;
	m_value = std::shared_ptr<VALUE_TYPE>(new VALUE_TYPE());
	for (auto& elem : il)
	{
		m_value->push_back(elem);
	}

}
//Value& Array::get() const
//{
//	return *m_value;
//}
//Value& Array::set(const Value& jv)
//{
//	m_value = jv.m_value;
//	return *m_value;
//}
void JSON::Array::insert(const std::initializer_list<std::shared_ptr<Value>>& il)
{

	for (auto& elem : il)
	{
		m_value->push_back(elem);
	}
}
void JSON::Array::remove(const std::initializer_list<size_t >& il)
{
	for (auto& elem : il)
	{
		auto vi = m_value->begin();
		std::advance(vi, elem);
		m_value->erase(vi);
	}
}
void JSON::Array::update(const std::initializer_list< std::pair < size_t, std::shared_ptr<Value>> >& il)
{
	for (auto& elem : il)
	{
		(*m_value)[elem.first] = elem.second;
	}
}
const JSON::Value& JSON::Array::operator[](size_t index) const
{
	return *m_value->at(index);
}
bool JSON::Array::operator == (const Value& json)
{
	return std::equal(
		m_value->begin(), m_value->end(),
		dynamic_cast<const Array &>(json).m_value->begin(),
		[](const VALUE_TYPE::value_type& lhs, const VALUE_TYPE::value_type& rhs) -> bool
	{
		return *lhs == *rhs;
	});
}
std::wstringstream& JSON::Array::print(std::wstringstream& ss, size_t depth)
{
	ss << std::endl << std::wstring(depth, ' ');
	ss << "[" << std::endl << std::wstring(depth, ' ');


	for (auto it = m_value->begin(); it != m_value->end(); it++)
	{

		(*it)->print(ss, depth + 4);
		ss << "," << std::endl << std::wstring(depth, ' ');

	}
	ss << "]";
	return ss;
}