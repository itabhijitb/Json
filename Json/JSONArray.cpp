#include "JSONArray.h"
JSONArray::JSONArray()
{
	value_type = JSONValue::VALUE_TYPE::ARRAY;
	m_value = std::unique_ptr<VALUE_TYPE>(new VALUE_TYPE());
}
JSONArray::JSONArray(std::stringstream& strm)
{
	value_type = JSONValue::VALUE_TYPE::ARRAY;
	m_value = std::unique_ptr<VALUE_TYPE>(new VALUE_TYPE());
	strm >> std::ws;
	char ch;
	strm >> ch;
	if (ch != starttoken)
	{
		throw JSONPgmErr("JSON Stream at %d is %c, %c expected.", strm.tellg(), ch, endtoken);
	}

	while ((ch = strm.peek()) != endtoken)
	{
		strm >> std::ws;
		m_value->push_back(JSON::Parse(strm));
		strm >> std::ws;
		strm >> ch;
		if (ch != septoken && ch != endtoken)
		{
			throw JSONInvalid("Parse error at %d. Expecting %c but found  %c", strm.tellg(), endtoken, ch);
		}
		strm >> std::ws;
		if (ch == endtoken) break;

	}
}
JSONArray::JSONArray(const std::initializer_list< std::shared_ptr<JSONValue>>& il)
{
	value_type = JSONValue::VALUE_TYPE::ARRAY;
	m_value = std::shared_ptr<VALUE_TYPE>(new VALUE_TYPE());
	for (auto& elem : il)
	{
		m_value->push_back(elem);
	}

}
//JSONValue& JSONArray::get() const
//{
//	return *m_value;
//}
//JSONValue& JSONArray::set(const JSONValue& jv)
//{
//	m_value = jv.m_value;
//	return *m_value;
//}
void JSONArray::insert(const std::initializer_list<std::shared_ptr<JSONValue>>& il)
{

	for (auto& elem : il)
	{
		m_value->push_back(elem);
	}
}
void JSONArray::remove(const std::initializer_list<size_t >& il)
{
	for (auto& elem : il)
	{
		auto vi = m_value->begin();
		std::advance(m_value->begin(), elem);
		m_value->erase(vi);
	}
}
void JSONArray::update(const std::initializer_list< std::pair < size_t, std::shared_ptr<JSONValue>> >& il)
{
	for (auto& elem : il)
	{
		(*m_value)[elem.first] = elem.second;
	}
}
const JSONValue& JSONArray::operator[](size_t index) const
{
	return *m_value->at(index);
}
bool JSONArray::operator == (const JSONValue& json)
{
	return std::equal(
		m_value->begin(), m_value->end(),
		dynamic_cast<const JSONArray &>(json).m_value->begin(),
		[](const VALUE_TYPE::value_type& lhs, const VALUE_TYPE::value_type& rhs) -> bool
	{
		return *lhs == *rhs;
	});
}
std::stringstream& JSONArray::print(std::stringstream& ss, size_t depth)
{
	ss << std::endl << std::string(depth, ' ');
	ss << "[" << std::endl << std::string(depth, ' ');


	for (auto it = m_value->begin(); it != m_value->end(); it++)
	{

		(*it)->print(ss, depth + 4);
		ss << "," << std::endl << std::string(depth, ' ');

	}
	ss << "]";
	return ss;
}