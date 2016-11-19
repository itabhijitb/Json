#include "JSONObject.h"
JSONObject::JSONObject()
{
	value_type = JSONValue::VALUE_TYPE::OBJECT;
	m_value = std::unique_ptr<VALUE_TYPE>(new VALUE_TYPE());
}
JSONObject::JSONObject(std::stringstream& strm)
{
	value_type = JSONValue::VALUE_TYPE::OBJECT;
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
		std::string key;
		strm >> std::ws;
		std::getline(strm, key, ':');

		(*m_value)[Util::trim(key)] = JSON::Parse(strm);
		strm >> std::ws;
		strm >> ch;
		if (ch != septoken && ch != endtoken)
		{
			throw JSONInvalid("Parse error at %d. Expecting %c or %c but found  %c", int(strm.tellg()), septoken, endtoken, ch);
		}
		strm >> std::ws;
		if (ch == endtoken) break;
	}
}
JSONObject::JSONObject(const std::initializer_list<std::pair<const std::string, std::shared_ptr<JSONValue>> >& il)
{
	value_type = JSONValue::VALUE_TYPE::OBJECT;
	m_value = std::unique_ptr<VALUE_TYPE>(new VALUE_TYPE());
	for (auto& elem : il)
	{
		(*m_value)[elem.first] = elem.second;
	}
}
//JSONValue& JSONObject::get() const
//{
//	return *m_value;
//}
//JSONValue& JSONObject::set(const JSONValue& jv)
//{
//	m_value = jv.m_value;
//	return *m_value;
//}
void JSONObject::insert(const std::initializer_list<std::pair<const std::string, std::shared_ptr<JSONValue> > > & il)
{
	for (auto& elem : il)
	{
		(*m_value)[elem.first] = elem.second;
	}
}
void JSONObject::remove(const std::initializer_list<const std::string >& il)
{
	for (auto& elem : il)
	{
		m_value->erase(elem);
	}
}
JSONValue& JSONObject::operator[](const std::string key) 
{
	return *m_value->at(key);
}
bool JSONObject::operator == (const JSONValue& json)
{
	return std::equal(
		m_value->begin(), m_value->end(),
		dynamic_cast<const JSONObject & >(json).m_value->begin(),
		[](const VALUE_TYPE::value_type& lhs, const VALUE_TYPE::value_type& rhs) -> bool
	{
		bool rc = lhs.first == rhs.first && *lhs.second == *rhs.second;
		return rc;
	});
}
std::stringstream& JSONObject::print(std::stringstream& ss, size_t depth)
{
	ss << std::endl << std::string(depth, ' ');
	ss << "{" << std::endl << std::string(depth, ' ');
	for (auto it = m_value->begin(); it != m_value->end(); it++)
	{
		ss << it->first << ":";
		it->second->print(ss, depth + 4);
		ss << "," << std::endl << std::string(depth, ' ');

	}
	ss << "}" << std::endl << std::string(depth, ' ');
	return ss;
}