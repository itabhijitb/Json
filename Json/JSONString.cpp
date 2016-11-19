#include "json.h"
JSONString::JSONString()
{
	value_type = JSONValue::VALUE_TYPE::STRING;
	m_value = std::make_unique<VALUE_TYPE>();
}
JSONString::JSONString(std::stringstream& strm)
{
	value_type = JSONValue::VALUE_TYPE::STRING;
	m_value = std::make_unique<VALUE_TYPE>();
	strm >> std::ws;
	char ch;
	strm >> ch;
	if (ch != starttoken)
	{
		throw JSONPgmErr("JSON Stream at %d is %c, %c expected.", strm.tellg(), ch, endtoken);
	}
	std::getline(strm, *m_value, '"');
}
JSONString::JSONString(JSONString&& js)
{
	m_value = std::move(js.m_value);
}
bool JSONString::operator == (const JSONValue& json)
{
	return m_value == (dynamic_cast<const JSONString &>(json)).m_value;
}
std::stringstream& JSONString::print(std::stringstream& ss, size_t depth)
{
	ss << '"' << *m_value << '"';
	return ss;
}
JSONString::operator std::string()
{
	return *m_value;
}