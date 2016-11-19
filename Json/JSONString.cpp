#include "json.h"

JSON::String::String()
{
	value_type = Value::VALUE_TYPE::STRING;
	m_value = std::make_unique<VALUE_TYPE>();
}
JSON::String::String(std::wstringstream& strm)
{
	value_type = Value::VALUE_TYPE::STRING;
	m_value = std::make_unique<VALUE_TYPE>();
	strm >> std::ws;
	wchar_t ch;
	strm >> ch;
	if (ch != starttoken)
	{
		throw PgmErr(L"JSON Stream at %d is %c, %c expected.", strm.tellg(), ch, endtoken);
	}
	std::getline(strm, *m_value, L'"');
}
JSON::String::String(String&& js)
{
	m_value = std::move(js.m_value);
}
bool JSON::String::operator == (const Value& json)
{
	return m_value == (dynamic_cast<const String &>(json)).m_value;
}
std::wstringstream& JSON::String::print(std::wstringstream& ss, size_t )
{
	ss << '"' << *m_value << '"';
	return ss;
}
JSON::String::operator std::wstring()
{
	return *m_value;
}