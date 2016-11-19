#include "JSONNumber.h"
JSON::Number::Number(double n) 
{
	value_type = Value::VALUE_TYPE::NUMBER;
	m_value = std::unique_ptr<VALUE_TYPE>(new VALUE_TYPE(n));
}
JSON::Number::Number(std::wstringstream& strm)
{
	value_type = Value::VALUE_TYPE::NUMBER;
	m_value = std::unique_ptr<VALUE_TYPE>(new VALUE_TYPE(0));
	strm >> std::ws;
	auto pos = strm.tellg();
	strm >> *m_value;
	if (!strm)
	{
		throw Invalid(L"Parse error at %d. Expecting NUMBER.", pos);
	}
}
bool JSON::Number::operator == (const Value& json)
{
	return m_value == (dynamic_cast<const Number &>(json)).m_value;
}
std::wstringstream& JSON::Number::print(std::wstringstream& ss, size_t )
{
	ss << '"' << *m_value << '"';
	return ss;
}