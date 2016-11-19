#ifndef __JSON__OBJECT__H
#define __JSON__OBJECT__H
/*******************************************************************************
*                                JSON Libraries                                *
*******************************************************************************/
#include "json.h"
#include "JSONValue.h"

class JSONObject : public JSONValue
{
	
	static const char starttoken = '{';
	static const char endtoken = '}';
	static const char septoken = ',';
	typedef  std::map < std::string, std::shared_ptr<JSONValue> > VALUE_TYPE;
	typedef VALUE_TYPE::iterator iterator;
	typedef VALUE_TYPE::const_iterator const_iterator;
	
public:
	friend class JSON;
	friend class JSONKey;
private:
	JSONObject();
	JSONObject(const std::initializer_list<std::pair<const std::string, std::shared_ptr<JSONValue>> >& il);
public:
	JSONObject::JSONObject(std::stringstream& strm);
	void insert(const std::initializer_list<std::pair<const std::string, std::shared_ptr<JSONValue>> >& il);
	void remove(const std::initializer_list<const std::string >& il);
	bool JSONObject::operator == (const JSONValue& json);
	JSONValue& operator[](const std::string key);
	std::stringstream& JSONObject::print(std::stringstream& ss, size_t depth);
private:
	
	JSONObject& operator=(const JSONObject&) = delete;
private:

	std::shared_ptr<VALUE_TYPE> m_value;
};
#endif