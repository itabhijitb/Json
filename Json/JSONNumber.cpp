#include "JSONNumber.h"
JSONNumber::JSONNumber(double n) 
{
	value_type = JSONValue::VALUE_TYPE::NUMBER;
	m_value = std::unique_ptr<VALUE_TYPE>(new VALUE_TYPE(n));
}
JSONNumber::JSONNumber(std::stringstream& strm)
{
	value_type = JSONValue::VALUE_TYPE::NUMBER;
	m_value = std::unique_ptr<VALUE_TYPE>(new VALUE_TYPE(0));
	strm >> std::ws;
	auto pos = strm.tellg();
	strm >> *m_value;
	if (!strm)
	{
		throw JSONInvalid("Parse error at %d. Expecting NUMBER.", pos);
	}
}
bool JSONNumber::operator == (const JSONValue& json)
{
	return m_value == (dynamic_cast<const JSONNumber &>(json)).m_value;
}
std::stringstream&JSONNumber::print(std::stringstream& ss, size_t depth)
{
	ss << '"' << *m_value << '"';
	return ss;
}