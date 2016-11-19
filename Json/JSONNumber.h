#ifndef __JSON__NUMBER__H
#define __JSON__NUMBER__H
/*******************************************************************************
*                                JSON Libraries                                *
*******************************************************************************/
#include "JSONValue.h"

class JSONNumber : public JSONValue
{
	typedef double VALUE_TYPE;
public:
	friend class JSON;
	JSONNumber() {}
	JSONNumber(double n);
	JSONNumber(std::stringstream& strm);
	bool operator == (const JSONValue& json);
	std::stringstream& print(std::stringstream& ss, size_t depth);
private:
	JSONNumber& operator=(const JSONNumber&) = delete;
private:
	std::unique_ptr<VALUE_TYPE> m_value;
};
#endif