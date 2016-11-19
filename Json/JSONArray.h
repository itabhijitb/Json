#ifndef __JSON__ARRAY__H
#define __JSON__ARRAY__H
/*******************************************************************************
*                               Standard Headers                               *
*******************************************************************************/
/*******************************************************************************
*                         Standard Template Libraries                          *
*******************************************************************************/
#include <vector>
/*******************************************************************************
*                                JSON Libraries                                *
*******************************************************************************/
#include "json.h"
#include "JSONValue.h"
class JSONArray : public JSONValue
{
	static const char starttoken = '[';
	static const char endtoken = ']';
	static const char septoken = ',';
	typedef  std::vector<std::shared_ptr<JSONValue> > VALUE_TYPE;
	typedef VALUE_TYPE::iterator iterator;
	typedef VALUE_TYPE::const_iterator const_iterator;
public:
	friend class JSON;
	friend class JSONKey;
	friend class JSONIter;
private:
	JSONArray();
	JSONArray(const std::initializer_list< std::shared_ptr<JSONValue>>& il);
public:
	void insert(const std::initializer_list<std::shared_ptr<JSONValue>>& il);
	void remove(const std::initializer_list<size_t >& il);
	void update(const std::initializer_list< std::pair < size_t, std::shared_ptr<JSONValue>> >& il);
	const JSONValue& operator[](size_t index) const;
	JSONArray(std::stringstream& strm);
	operator JSONValue& ()
	{
		return *this;
	}
	virtual bool operator == (const JSONValue& json);
	std::stringstream& print(std::stringstream& ss, size_t depth);
	//VALUE_TYPE::iterator begin() { return m_value->begin(); }
	//VALUE_TYPE::iterator end() { return m_value->end(); }
	//VALUE_TYPE::const_iterator begin() const { return m_value->begin(); }
	//VALUE_TYPE::const_iterator end() const { return m_value->end(); }
	//VALUE_TYPE::const_iterator cbegin() const { return m_value->begin(); }
	//VALUE_TYPE::const_iterator cend() const { return m_value->end(); }
private:
	
	
	JSONArray& operator=(const JSONArray&) = delete;
	//JSONArray(const JSONArray&) = delete;

private:
	std::shared_ptr<VALUE_TYPE> m_value;
};
#endif