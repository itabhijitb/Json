#ifndef __JSON__STRING__H
#define __JSON__STRING__H
/*******************************************************************************
*                                JSON Libraries                                *
*******************************************************************************/
#include "JSONValue.h"

class JSONString : public JSONValue
{
	static const char starttoken = '"';
	static const char endtoken = '"';
	typedef std::string VALUE_TYPE;
public:
	friend class JSON;
	JSONString();
	JSONString(std::string js) : m_value(std::make_unique<std::string>(js)) {};
	JSONString(const std::unique_ptr<JSONValue>& jv);
	JSONString(JSONString&& js);
	JSONString(std::stringstream& strm);
	virtual bool operator == (const JSONValue& json);
	std::stringstream& print(std::stringstream& ss, size_t depth);
	operator std::string();
private:
	JSONString& operator=(const JSONString&) = delete;
	JSONString(JSONString& jn) = delete;
private:
	std::unique_ptr<VALUE_TYPE> m_value;
};

#endif