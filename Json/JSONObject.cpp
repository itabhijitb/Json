#include "JSONObject.h"

JSON::Object::Object()
{
	value_type = Value::VALUE_TYPE::OBJECT;
	m_value = std::unique_ptr<VALUE_TYPE>(new VALUE_TYPE());
}
JSON::Object::Object(std::wstringstream& strm)
{
	value_type = Value::VALUE_TYPE::OBJECT;
	m_value = std::unique_ptr<VALUE_TYPE>(new VALUE_TYPE());
	strm >> std::ws;
	decltype(strm.peek()) ch;
	strm >> ch;
	if (ch != starttoken)
	{
		throw PgmErr(L"JSON Stream at %d is %c, %c expected.", strm.tellg(), ch, endtoken);
	}
	while ((ch = strm.peek()) != endtoken)
	{
		std::wstring key;
		strm >> std::ws;
		std::getline(strm, key, L':');

		(*m_value)[Util::trim(key)] = JSON::Parse(strm);
		strm >> std::ws;
		strm >> ch;
		if (ch != septoken && ch != endtoken)
		{
			throw Invalid(L"Parse error at %d. Expecting %c or %c but found  %c", int(strm.tellg()), septoken, endtoken, ch);
		}
		strm >> std::ws;
		if (ch == endtoken) break;
	}
}
JSON::Object::Object(const std::initializer_list<std::pair<const std::wstring, std::shared_ptr<Value>> >& il)
{
	value_type = Value::VALUE_TYPE::OBJECT;
	m_value = std::unique_ptr<VALUE_TYPE>(new VALUE_TYPE());
	for (auto& elem : il)
	{
		(*m_value)[elem.first] = elem.second;
	}
}
//Value& Object::get() const
//{
//	return *m_value;
//}
//Value& Object::set(const Value& jv)
//{
//	m_value = jv.m_value;
//	return *m_value;
//}
void JSON::Object::insert(const std::initializer_list<std::pair<const std::wstring, std::shared_ptr<Value> > > & il)
{
	for (auto& elem : il)
	{
		(*m_value)[elem.first] = elem.second;
	}
}
void JSON::Object::remove(const std::initializer_list<const std::wstring >& il)
{
	for (auto& elem : il)
	{
		m_value->erase(elem);
	}
}
JSON::Value& JSON::Object::operator[](const std::wstring key)
{
	return *m_value->at(key);
}
bool JSON::Object::operator == (const Value& json)
{
	return std::equal(
		m_value->begin(), m_value->end(),
		dynamic_cast<const Object & >(json).m_value->begin(),
		[](const VALUE_TYPE::value_type& lhs, const VALUE_TYPE::value_type& rhs) -> bool
	{
		bool rc = lhs.first == rhs.first && *lhs.second == *rhs.second;
		return rc;
	});
}
std::wstringstream& JSON::Object::print(std::wstringstream& ss, size_t depth)
{
	ss << std::endl << std::wstring(depth, ' ');
	ss << "{" << std::endl << std::wstring(depth, ' ');
	for (auto it = m_value->begin(); it != m_value->end(); it++)
	{
		ss << it->first << ":";
		it->second->print(ss, depth + 4);
		ss << "," << std::endl << std::wstring(depth, ' ');

	}
	ss << "}" << std::endl << std::wstring(depth, ' ');
	return ss;
}